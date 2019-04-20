var http = require('http');

var hostname = 'localhost';
var port = 3000;

var server = http.createServer(function (req, res) {
  if (req['method'] == 'GET') {
    console.log('GET recieved');
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('Hello Seth!');
    res.end('Hello World!');
  } else if (req['method'] == 'POST') {
    console.log('GET recieved');
  }
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
