var http = require('http');
var url = require('url');
var fs = require('fs');
var formidable = require('formidable');

http.createServer(function (req, res) {
	var q = url.parse(req.url, true);
	main_name = q.pathname
	
	if (main_name == '/fileupload') {
		fields = q.query
		var output = fields.from_input + "\n" + fields.to_input + "\n" + fields.how_much_input + "\n" + fields.name_input + "\n" + fields.date_input + "\n\n"
		fs.appendFile('database.txt', output, function (err) {
			if (err) throw err;
		});
		main_name = "/sent.html"
	}
	if (main_name != "/fileupload") {
		var filename = "." + main_name;
		fs.readFile(filename, function(err, data) {
			if (err) {
				res.writeHead(404, {'Content-Type': 'text/html'});
				return res.end("404 Not Found");
			}  
			var extension = main_name.substr(main_name.lastIndexOf('.'))
			if (extension == '.css')
				res.writeHead(200, {'Content-Type': 'text/css'});
			else if (extension == 'jpg')
				res.writeHead(200, {'Content-Type': 'image/jpeg'});
			else if (extension == 'js')
				res.writeHead(200, {'Content-Type': 'text/javascript'});
			else 
				res.writeHead(200, {'Content-Type': 'text/html'});
			res.write(data);
			return res.end();
		});
	}
}).listen(8080);