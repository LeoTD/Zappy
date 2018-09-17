#!/usr/bin/env node
var net = require("net");
var path = require('path');
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var split2 = require('split2');
var TickEventParser = require('./TickEventParser.js');
var TickEventCollection = require('./TickEventCollection.js');

var key = "banana";
var client;
var HOST;
var PORT;

app.get('/', (req, res) => {
	res.sendFile( __dirname +  '/example.html');
})

io.sockets.on('connection', (frontend) => {
	const parser = new TickEventParser({
		onTickParsed: ev => { frontend.emit('tick', JSON.stringify(ev)) },
	})

	const zappy = new net.Socket()
	zappy.pipe(split2())
		.on('data', parser.parse)
	zappy.connect(5555, 'localhost', () => {
		zappy.write('banana\n')
	})
});

const usage = () => {
	let mess = "Usage: \n";
	mess += "Server Host Port";
	console.log(mess);
	process.exit();
}

const parseArgs = () => {
	if (process.argv.length != 4) {
		usage();
	} else {
		HOST = process.argv[2];
		PORT = process.argv[3];
	}
}

const initServer = () => {
	http.listen(3000, () => {
		console.log('listening on *:3000');
	});
}

const initClient = () => {
	
	client = new net.Socket();

	client.on('error', (error) => {
		client.destroy();
		client = null;
		console.log("Error: connection can not be opened %s", error.message);
		process.exit();
		// because of timeout and stuff
	})

	client.on('data', (data) => {
		console.log("[SERVER]: %s", data);
		//piping or sending data to the express server
	})

	client.connect(PORT, HOST, () => {
		console.log(`Conected to ${HOST}:${PORT} nice!`);
		client.write(key);
	})
}

parseArgs();
initServer();
initClient();
