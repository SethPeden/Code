let cars = []
var walls = []
var checkpoints = []
var best = null
let N = 100
var c

function setup() {
  createCanvas(window.innerWidth, window.innerHeight)
  start()
  walls.push(new Wall(createVector(0, 0), createVector(0, height), 4))
  walls.push(new Wall(createVector(0, height), createVector(width, height), 4))
  walls.push(new Wall(createVector(width, height), createVector(width, 0), 4))
  walls.push(new Wall(createVector(width, 0), createVector(0, 0), 4))

  walls.push(new Wall(createVector(width / 8, height / 4), createVector(width / 8, 3 * height / 4), 4))
  walls.push(new Wall(createVector(width / 8, 3 * height / 4), createVector(7 * width / 8, 3 * height / 4), 4))
  // walls.push(new Wall(createVector(2 * width / 3, 2 * height / 3), createVector(2 * width / 3, 7 * height / 8), 4))
  // walls.push(new Wall(createVector(2 * width / 3, 7 * height / 8), createVector(5 * width / 6, 2 * height / 3), 4))


  walls.push(new Wall(createVector(7 * width / 8, 3 * height / 4), createVector(7 * width / 8, height / 4), 4))
  walls.push(new Wall(createVector(7 * width / 8, height / 4), createVector(width / 8, height / 4), 4))

  let center = createVector(width / 2, height / 2)
  for (let x = 0; x < N; x++) {
    let angle = 2 * PI * x / N
    let outer = center.copy().add(p5.Vector.fromAngle(angle).mult(max(width, height)))
    checkpoints.push(new Wall(center, outer, 4))
  }
}

function start() {
  c = 1
  cars = []
  for (let i = 0; i < 100; i++) {
    cars.push(new Car(createVector(width / 8, height / 8), best))
  }
}

function draw() {
  c++
  // if (c % (60 * 7) == 0 || keyIsDown(ENTER)) {
  if (c % (60 * 7) == 0) {
    highest = 0
    for (let i = 0; i < cars.length; i++) {
      let score = 2 * (cars[i].alive ? 1 : 0) + 4 * cars[i].checks.length
      if (score > highest || highest == 0) {
        highest = score
        best = cars[i].brain
      }
    }
    start()
  }

  background(24)

  if (keyIsDown(ENTER)) {
    for (let x in walls) {
      walls[x].draw(255, 255, 255, 255)
    }
    for (let x in checkpoints) {
      checkpoints[x].draw(255, 0, 0, 32)
    }
  }

  for (let x = cars.length - 1; x >= 0; x--) {
    car = cars[x]

    if (keyIsDown(ENTER)) {
      car.draw()
    }

    car.update()

    if (car.alive) {
      inters = [ null, null, null, null, null, null, null, null ]
      for (let x in walls) {
        let wall = walls[x]
        if (car.intersects(wall)) {
          car.alive = false
        }
        for (let y in car.sensorIDs) {
          let id = car.sensorIDs[y]
          p = car.senses(id, wall)
          if (p != null) {
            inters[id] = p
            // stroke(0, 0, 255)
            // strokeWeight(10.0)
            // point(p.x, p.y)
          }
        }
      }

      for (let x in checkpoints) {
        let check = checkpoints[x]
        fresh = true
        for (y in car.checks) {
          has = car.checks[y]
          if (has === check) {
            fresh = false
          }
        }
        if (fresh && car.intersects(check)) {
          car.checks.push(check)
        }
        if (car.checks.length % N == 0) {
          for (y in car.checks) {
            car.checks[y] = null
          }
        }
      }

      data = []
      data.push(car.speed)
      data.push(car.angle)
      for (let x in inters) {
        let p = inters[x]
        if (p != null) {
          data.push(p.x)
          data.push(p.y)
        } else {
          data.push(-1.0)
          data.push(-1.0)
        }
      }

      let changes = car.think(data)
      car.accelerate(changes[0])
      car.turn(changes[1])

    }
  }
}
