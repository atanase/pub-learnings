"use strict";
const http = require('http'),
  fs = require('fs');
const server = http.createServer();
const settings = require('./settings');

server.on('request', function(req, res) {
  fs.readFile(__dirname + '/public/hello.html', 'utf-8', (err, data) => {
    if(err){
      res.writeHead(404, {'Content-Type': 'text/plain'});
      res.write('not found!');
      return res.end();
    }
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data);
    return res.end();
  });
});
server.listen(settings.port, settings.host);
console.log("server listening ...");
