class Complex {
  constructor(a, b) {
    this.a = a
    this.b = b
  }
  magnitude() {
    return sqrt(this.a * this.a + this.b * this.b)
  }
  angle() {
    return atan2(this.b, this.a)
  }
  conjugate() {
    return new Complex(this.a, -this.b)
  }
  add(c) {
    return new Complex(this.a + c.a, this.b + c.b)
  }
  multiply(c) {
    return new Complex(this.a * c.a - this.b * c.b, this.a * c.b + c.a * this.b)
  }
  subtract(c) {
    return this.add(c.multiply(new Complex(-1, 0)))
  }
  divide(c) {
    return this.multiply(c.conjugate()).multiply(1.0 / (c.multiple(c.conjugate())).a)
  }
  static fromPolar(r, a) {
    return new Complex(r * cos(a), r * sin(a));
  }
}
