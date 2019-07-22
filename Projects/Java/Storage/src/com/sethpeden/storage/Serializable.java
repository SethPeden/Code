package com.sethpeden.storage;

public abstract class Serializable {

  public Class clss;

  Serializable() {
  }

  abstract ByteStream toBytes(ByteStream bs);

  abstract Serializable fromBytes(ByteStream bs);

  @Override
  public String toString() {
    return new XMLNode(this).toString();
  }

  public static Serializable fromString(String s) throws ClassNotFoundException {
    XMLNode xml = new XMLNode(s);
    Class clss = Class.forName(xml.getTag());
    try {
      Serializable inst = (Serializable) clss.newInstance();
      inst.fromBytes(xml.getData());
      inst.clss = clss;
      return inst;
    } catch (IllegalAccessException | InstantiationException exception) {
      System.out.println("Need to implement the default constructor for " + clss + ".");
      exception.printStackTrace();
      return null;
    }
  }
}
