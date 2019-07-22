package com.sethpeden.storage;

import java.lang.reflect.InvocationTargetException;

public class Main {
  public static void main(String[] args) throws IllegalAccessException, NoSuchMethodException, ClassNotFoundException, InvocationTargetException {
    Dog dog = new Dog("Fido", "Black", 3);
    String d = dog.toString();
    System.out.println(d);
    System.out.println();
    Serializable ser = Serializable.fromString(d);
    ser.clss.getDeclaredMethod("details", null).invoke(ser);
  }
}

class Dog extends Serializable {

  String name;
  String color;
  int age;

  Dog() {

  }

  Dog(String name, String color, int age) {
    this.name = name;
    this.color = color;
    this.age = age;
  }

  @Override
  ByteStream toBytes(ByteStream bs) {
    return bs.writeString(this.name).writeString(this.color).writeInt(this.age);
  }

  @Override
  Serializable fromBytes(ByteStream bs) {
    this.name = bs.readString();
    this.color = bs.readString();
    this.age = bs.readInt();
    return this;
  }

  void details() {
    System.out.println(this.getClass().getSimpleName());
    System.out.println("Name: " + this.name);
    System.out.println("Color: " + this.color);
    System.out.println("Age: " + this.age);
  }
}