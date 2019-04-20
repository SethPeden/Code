class Block {
  constructor(pos, vel, side, mass) {
    this.pos = pos
    this.vel = vel
    this.mass = mass
    this.side = side
  }
  draw(xConstrain) {
    fill(255)
    let x = constrain(this.pos.x, xConstrain, 100 * width)
    rect(x - this.side / 2, this.pos.y - this.side / 2, this.side, this.side)
  }
  update() {
    this.pos.add(this.vel)
  }
  collide(other) {
    return !(this.pos.x + this.side / 2 < other.pos.x - other.side / 2 || this.pos.x - this.side / 2 > other.pos.x + other.side / 2)
  }
  hit(other) {
    let u1 = this.vel.copy()
    let u2 = other.vel.copy()
    let mSum = this.mass + other.mass
    return u1.mult(this.mass - other.mass).add(u2.mult(2 * other.mass)).mult(1 / mSum)
  }
}
