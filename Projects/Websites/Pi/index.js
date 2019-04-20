let b1
let b2
let wall
let clack
let digits = 7
let count = 0
let timestep

function setup() {
  createCanvas(window.innerWidth, window.innerHeight)
  b1 = new Block(createVector(width / 4, height / 2), createVector(0, 0), 50, 1)
  let m = pow(100, digits - 1)
  timestep = pow(10, round(log(digits) / log(1.5) + 1))
  b2 = new Block(createVector(width / 2, height / 2), createVector(-5 / timestep, 0), 100, m)
  wall = new Block(createVector(-height / 2, height / 2), createVector(0, 0), height, 1E10)
  clack = new Audio('clack.wav')
  textSize(32)
}

function draw() {
  background(25)
  b1.draw(0)
  b2.draw(b1.side + b2.side / 2)
  for (let i = 0; i < timestep; i++) {
    b1.update()
    b2.update()
    if (b1.collide(b2)) {
      let v1 = b1.hit(b2)
      let v2 = b2.hit(b1)
      b1.vel = v1
      b2.vel = v2
      clack.play()
      count++
    }
    if (b1.collide(wall)) {
      b1.vel.mult(-1)
      clack.play()
      count++
    }
    if (b2.collide(wall)) {
      b2.vel.mult(-1)
      clack.play()
      count++
    }
  if (i % (timestep / 10) == 0)
    text(nf(count, digits), 10, 40)
  }
}
