var http = require('http');
var server = http.createServer();
var settings = require('./settings');
var msg = '';

console.log(settings);

server.on('request', function(req, res) {
  switch (req.url){
    case '/about':
      msg = "About this page";
      break;
    case '/profile':
      msg = "About me";
      break;
    default:
      msg = "Wrong page";
      break;
  }
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.write(msg);
  res.end();
});
server.listen(settings.port, settings.host);
console.log("server listening ...");
