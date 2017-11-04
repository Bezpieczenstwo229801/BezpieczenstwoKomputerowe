var https = require('https');
var fs = require('fs');

console.log("jajco")

var options = {
  key: fs.readFileSync('privkeyA.pem'),
  cert: fs.readFileSync('certA.crt')
};

console.log("dzikus")

var a = https.createServer(options, function (req, res) {
	console.log("piszczel")
  res.write('Hello World!'); //write a response to the client
  console.log("tromba")
  res.end(); //end the response
  console.log("gawron")

}).listen(8800);