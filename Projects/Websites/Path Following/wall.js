class Wall {
  constructor(start, end, width) {
    this.start = start
    this.end = end
    this.width = width
  }
  draw(r, g, b, a) {
    stroke(r, g, b, a)
    strokeWeight(this.width)
    line(this.start.x, this.start.y, this.end.x, this.end.y)
  }
}
