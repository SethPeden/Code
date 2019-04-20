var digits = [];

function setup() {
  createCanvas(window.innerWidth, window.innerHeight)
  let w = 150
  for (let i = 0; i < 8; ++i)
    digits.push(new Digit((7 - i) * w, 0, w))
  frameRate(60)
}

var i = 0
function draw() {
  background(24)
  for (let j = 0; j < digits.length; ++j)
    digits[j].show(((i >> (4 * j)) % 16))
  i++
}
