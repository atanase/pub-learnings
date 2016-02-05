var http = require('http');
var server = http.createServer();
var settings = require('./settings');

console.log(settings);

server.on('request', function(req, res) {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.write('hello, world!!!');
  res.end();
});
server.listen(settings.port, settings.host);
console.log("server listening ...");
