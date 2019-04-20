function range(min, max, delta) {
    out = []
    for (let x = min; x <= max; x += delta)
      out.push(x)
    return out
}

var xrange
var yrange

var x = []
var y = []

function setup() {
  createCanvas(window.innerWidth, window.innerHeight)
  xrange = [-10, 10]
  let ratio = height / width
  yrange = [xrange[0] * ratio, xrange[1] * ratio]
  x = range(xrange[0], xrange[1], 1 / 1000.0)
  for (let i = 0; i < x.length; i++)
    y.push(Complex.fromPolar(1, -x[i]).multiply(new Complex(exp(-x[i]), 0)))
}

function draw() {
  background(24)
  stroke(255)
  strokeWeight(0.15)
  for (let xx = 0; xx <= xrange[1]; xx++) {
    var i = map(xx, xrange[0], xrange[1], 0, width)
    line(i, 0, i, height)
    i = map(-xx, xrange[0], xrange[1], 0, width)
    line(i, 0, i, height)
  }
  for (let yy = 0; yy <= yrange[1]; yy++) {
    var j = map(yy, yrange[1], yrange[0], 0, height)
    line(0, j, width, j)
    j = map(-yy, yrange[1], yrange[0], 0, height)
    line(0, j, width, j)
  }

  strokeWeight(4)
  // stroke(255, 0, 0)
  var a = map(x[0], xrange[0], xrange[1], 0, width)
  var b = map(y[0].magnitude(), yrange[1], yrange[0], 0, height)
  for (let i = 1; i < x.length; i++) {
    let color = map(y[i].angle(), -PI, PI, 0, 0xFFFFFF)
    stroke((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF)
    let c = map(x[i], xrange[0], xrange[1], 0, width)
    let d = map(y[i].magnitude(), yrange[1], yrange[0], 0, height)
    line(a, b, c, d)
    a = c
    b = d
  }


  noLoop()
  // let c = Complex.fromPolar(r, a)
  // i = map(c.a, xrange[0], xrange[1], 0, width)
  // j = map(c.b, yrange[1], yrange[0], 0, height)
  // strokeWeight(1)
  // line(width / 2, height / 2, i, height / 2)
  // line(i, height / 2, i, j)
  // strokeWeight(4)
  // point(i, height / 2)
  // point(i, j)
  // a = a + PI / 50.0
}
