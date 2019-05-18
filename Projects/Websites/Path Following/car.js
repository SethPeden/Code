class Car {
  constructor(pos, brain) {
    this.width = 15
    this.height = 10
    this.alive = true
    this.pos = pos
    this.lastpos = null
    // this.speed = random(0, 15)
    this.angle = random(0, 2 * PI)
    this.speed = 5
    // this.angle = 0
    this.sensorIDs = [0, 1, 2, 3, 4, 5, 6, 7]
    this.sensorLength = 100
    if (brain) {
      this.brain = []
      for (let y = 0; y < 2; y++) {
        this.brain.push([])
        for (let x = 0; x < 10; x++) {
          this.brain[y].push(brain[y][x] + random(-0.2, 0.2) / ((y + 1) * (y + 1)))
        }
      }
    } else {
      this.brain = []
      for (let y = 0; y < 2; y++) {
        this.brain.push([])
        for (let x = 0; x < 10; x++) {
          this.brain[y].push(random(-1.0, 1.0) / ((y + 1) * (y + 1)))
        }
      }
    }
    this.checks = []
  }
  accelerate(dv) {
    if (abs(this.speed + dv) < 15) {
      this.speed += dv
    }
  }
  turn(da) {
    this.angle += da / 2000
  }
  update() {
    if (this.alive) {
      this.lastpos = this.pos.copy()
      this.pos = this.pos.add(p5.Vector.fromAngle(this.angle).mult(this.speed))
    }
  }
  draw() {
    if (this.alive) {
      rectMode(CENTER)
      fill(255)
      translate(this.pos.x, this.pos.y)
      rotate(this.angle)
      stroke(255)
      strokeWeight(1.0)
      rect(0, 0, this.width, this.height)
      // stroke(255, 0, 0)
      // for (let x in this.sensorIDs) {
      //   let vec = p5.Vector.fromAngle(this.sensorIDs[x] * 2 * PI / this.sensorIDs.length).mult(this.sensorLength)
      //   line(0, 0, vec.x, vec.y)
      // }
      rotate(-this.angle)
      translate(-this.pos.x, -this.pos.y)
    }
  }
  senses(sensor, wall) {
    let vec = p5.Vector.fromAngle(this.sensorIDs[sensor] * 2 * PI / this.sensorIDs.length + this.angle).mult(this.sensorLength)
    let x1 = this.pos.x
    let y1 = this.pos.y
    let x2 = this.pos.x + vec.x
    let y2 = this.pos.y + vec.y
    let x3 = wall.start.x
    let y3 = wall.start.y
    let x4 = wall.end.x
    let y4 = wall.end.y
    let den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    let t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den
    let u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den
    if ((0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0)) {
      return createVector(x1 + t * (x2 - x1), y1 + t * (y2 - y1))
    }
    return null
  }
  think(data) {
    var out = []
    for (let y = 0; y < 2; y++) {
      let layer = this.brain[y]
      var sum = 0
      for (let x = 0; x < 10; x++) {
        sum = sum + layer[x] * data[x]
      }
      out.push(sum)
    }
    return out
  }
  intersects(wall) {
    let x3 = wall.start.x
    let y3 = wall.start.y
    let x4 = wall.end.x
    let y4 = wall.end.y
    this.corners = [ this.pos.copy().add(createVector(-this.width / 2, -this.height / 2)), this.pos.copy().add(createVector(this.width / 2, -this.height / 2)), this.pos.copy().add(createVector(this.width / 2, this.height / 2)), this.pos.copy().add(createVector(-this.width / 2, this.height / 2)) ]
    for (let i = 0; i < this.corners.length; i++) {
      let x1 = this.corners[i].x
      let y1 = this.corners[i].y
      let x2 = this.corners[(i + 1) % 4].x
      let y2 = this.corners[(i + 1) % 4].y
      let den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
      let t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den
      let u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den
      if ((0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0)) {
        return true
      }
    }
    let x1 = this.pos.x
    let y1 = this.pos.y
    let x2 = this.lastpos.x
    let y2 = this.lastpos.y
    let den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    let t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den
    let u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den
    if ((0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0)) {
      return true
    }
    return false
  }
}
