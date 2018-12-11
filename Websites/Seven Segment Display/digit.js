let encodings = [ 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 ]

class Digit {
  constructor(x, y, width) {
    this.buffer = 0.02 * height
    this.x = x
    this.y = y
    this.width = width
    let t = 0.20 * this.width
    let d = this.width - t - 2 * this.buffer
    this.height = 2 * this.buffer + t + 2 * d
    this.segments = []
    this.segments.push(new Segment(this.x + this.buffer + t / 2, this.y + this.buffer, d, t, false))
    this.segments.push(new Segment(this.x + this.width - this.buffer, this.y + this.buffer + t / 2, d, t, true))
    this.segments.push(new Segment(this.x + this.width - this.buffer, this.y + this.buffer + d + t / 2, d, t, true))
    this.segments.push(new Segment(this.x + this.buffer + t / 2, this.y + this.buffer + 2 * d, d, t, false))
    this.segments.push(new Segment(this.x + this.buffer + t, this.y + this.buffer + d + t / 2, d, t, true))
    this.segments.push(new Segment(this.x + this.buffer + t, this.y + this.buffer + t / 2, d, t, true))
    this.segments.push(new Segment(this.x + this.buffer + t / 2, this.y + this.buffer + d, d, t, false))
  }
  show(val) {
    for (let i = 0; i < this.segments.length; ++i)
      this.segments[i].draw((encodings[val] >> i) & 0b1)
  }
}
