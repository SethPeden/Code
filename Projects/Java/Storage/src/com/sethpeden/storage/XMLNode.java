package com.sethpeden.storage;

public class XMLNode extends Serializable {
  private static final String FILLER_PATTERN = "@@@@";
  private static final String OPEN_TAG_PATTERN = "<" + XMLNode.FILLER_PATTERN + ">";
  private static final String CLOSE_TAG_PATTERN = "</" + XMLNode.FILLER_PATTERN + ">";

  private String tag;
  private ByteStream data;

  public XMLNode(String s) {
    this.fromBytes(new ByteStream(s));
  }

  public XMLNode(String tag, ByteStream data) {
    this.tag = tag;
    this.data = data;
  }

  public XMLNode(Serializable object) {
    this.tag = object.getClass().getName();
    this.data = object.toBytes(new ByteStream());
  }

  @Override
  public String toString() {
    return XMLNode.OPEN_TAG_PATTERN.replace(XMLNode.FILLER_PATTERN, this.tag) +
            this.data +
            XMLNode.CLOSE_TAG_PATTERN.replace(XMLNode.FILLER_PATTERN, this.tag);
  }

  @Override
  ByteStream toBytes(ByteStream bs) {
    return bs.writeString(this.toString());
  }

  @Override
  Serializable fromBytes(ByteStream bs) {
    String[] s = bs.readString().split(">");
    this.tag = s[0].replace("<", "");
    this.data = new ByteStream(s[1].split("<")[0]);
    this.data.readInt();
    return this;
  }

  public String getTag() {
    return tag;
  }

  public ByteStream getData() {
    return data;
  }
}
