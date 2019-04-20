var n = 0;
var c = 4;

function setup() {
  createCanvas(window.innerWidth, window.innerHeight)
  background(25)
  colorMode(HSB)
  frameRate(60)
}

function draw() {
  let a = n * 5.626 / 180 * 2 * PI
  let r = c * sqrt(n)
  let x = r * cos(a)
  let y = r * sin(a)
  translate(window.innerWidth / 2, window.innerHeight / 2)
  strokeWeight(1)
  stroke(r, a, 255)
  noFill()
  ellipse(x, y, sqrt(r) / c, sqrt(r) / c)
  n++;
}
