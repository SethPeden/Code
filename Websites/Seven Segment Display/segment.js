class Segment {
  constructor(x, y, width, height, vertical) {
    this.orientation = vertical
    this.tipPercent = height / (2 * width)
    this.x = x
    this.y = y
    this.width = width
    this.height = height
  }
  draw(on) {
    push()
    translate(this.x, this.y)
    if (this.orientation) rotate(PI / 2)
    fill(on ? 255 : 100, 0, 0)
    // stroke(on ? 255 : 100, 0, 0)
    noStroke()
    triangle(0, this.height / 2, this.tipPercent * this.width, this.height, this.tipPercent * this.width, 0)
    rectMode(CORNER)
    rect(this.tipPercent * this.width, 0, (1 - 2 * this.tipPercent) * this.width, this.height)
    triangle(this.width, this.height / 2, (1 - this.tipPercent) * this.width, 0, (1 - this.tipPercent) * this.width, this.height)
    pop()
  }
}
