package com.sethpeden.storage;

import java.util.ArrayList;
import java.util.List;

public class ByteStream {
  private List<Character> data = new ArrayList<>();

  public ByteStream() {

  }

  public ByteStream(String s) {
    this.writeString(s);
  }

  @Override
  public String toString() {
    char data[] = new char[this.size()];
    int i = 0;
    for (char c : this.data)
      data[i++] = c;
    return String.copyValueOf(data);
  }

  public int size() {
    return this.data.size();
  }

  public ByteStream writeByte(byte b) {
    this.data.add((char) b);
    return this;
  }

  public byte readByte() {
    return (byte) this.data.remove(0).charValue();
  }

  public ByteStream writeInt(int i) {
    for (int j = Integer.BYTES - 1; j >= 0; --j)
      this.writeByte((byte) (i >> (j * 8)));
    return this;
  }

  public int readInt() {
    int i = 0;
    for (int j = Integer.BYTES - 1; j >= 0; --j)
      i |= ((this.readByte() & 0xFF) << (j * 8));
    return i;
  }

  public ByteStream writeLong(long l) {
    for (int j = Long.BYTES / Integer.BYTES - 1; j >= 0; --j)
      this.writeInt((int) (l >> (j * 32)));
    return this;
  }

  public long readLong() {
    long l = 0;
    for (int j = Long.BYTES / Integer.BYTES - 1; j >= 0; --j)
      l |= ((((long) this.readInt()) & 0xFFFFFFFFL) << (j * 32));
    return l;
  }

  public ByteStream writeFloat(float f) {
    return this.writeInt(Float.floatToIntBits(f));
  }

  public float readFloat() {
    return Float.intBitsToFloat(this.readInt());
  }

  public ByteStream writeDouble(double d) {
    return this.writeLong(Double.doubleToLongBits(d));
  }

  public double readDouble() {
    return Double.longBitsToDouble(this.readLong());
  }

  public ByteStream writeString(String s) {
    if (s == null)
      s = "";
    this.writeInt(s.length());
    for (char c : s.toCharArray())
      this.writeByte((byte) c);
    return this;
  }

  public String readString() {
    char[] data = new char[this.readInt()];
    for (int i = 0; i < data.length; ++i)
      data[i] = (char) this.readByte();
    return String.copyValueOf(data);
  }

}
