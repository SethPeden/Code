var slider

function setup() {
  createCanvas(window.innerWidth, window.innerHeight - 25)
  slider = createSlider(0, 10, 0)
}

var h = []
var angle = 0
var da = 0.05

var L = 3

function draw() {
  background(25)

  var x = window.innerWidth / 4;
  var y = window.innerHeight / 2;

  for (var i = 0; i < exp(slider.value() * log(2)); ++i) {
    var n = 2 * i + 1;
    var radius = 4 / (n * PI) * 150
    var theta = (n * PI) * angle / L

    translate(x, y)
    stroke(255)
    noFill()
    strokeWeight(1)
    ellipse(0, 0, 2 * radius)
    line(0, 0, radius * cos(theta), radius * -sin(theta))
    translate(-x, -y)

    x += radius * cos(theta)
    y += radius * -sin(theta)
  }

  translate(x, y)
  stroke(255)
  noFill()
  strokeWeight(10)
  point(0, 0)
  translate(-x, -y)

  h.unshift(y)

  stroke(255)
  noFill()
  strokeWeight(2)
  beginShape()
  vertex(x, y)
  var sx = 65 * window.innerWidth / 100
  vertex(sx, h[0])
  endShape(CLOSE)

  translate(sx, 0)
  var dx = 0
  var px = 0
  var py = h[0]
  for (var i = 0; i < h.length; ++i) {
    stroke(255)
    noFill()
    strokeWeight(2)
    beginShape()
    vertex(px, py)
    vertex(dx, h[i])
    endShape(CLOSE)
    px = dx
    py = h[i]
    dx += da * 100
  }

  if (h.length > 700) {
    h.pop()
  }

  angle += da
}
