"use strict";
const http = require('http'),
    fs = require('fs'),
    ejs = require('ejs');
const server = http.createServer();
const settings = require('./settings');
const template = fs.readFileSync(__dirname + '/public/hello.ejs', 'utf-8');
var n = 0;
server.on('request', function(req, res) {
  var data = ejs.render(template, {
    title: "hello",
    content: "<strong>world</strong>",
    n: n++
  });
  res.writeHead(200, {'Content-Type': 'text/html'});
  res.write(data);
  res.end();
});
server.listen(settings.port, settings.host);
console.log("server listening ...");
