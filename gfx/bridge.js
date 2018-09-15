#!/usr/bin/env node
var net = require("net");
var path = require('path');
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

var key = "banana";
var client;
var HOST;
var PORT;

app.get('/', (req, res) => {
	res.sendFile( __dirname +  '/example.html');
})

io.on('connection', (socket) => {
	console.log('A user connected');

	// if (connected)
	setTimeout( () => {
		socket.emit('testerEvent', { description: 'Sent a message 4 seccond after connection' });
	}, 4000)

	socket.on('disconnect', () => {
		console.log('A user disconnected');
	})
})

const usage = () => {
	let mess = "Usage: \n";
	mess += "Server Host Port";
	console.log(mess);
	process.exit();
}

const parse_args = () => {
	if (process.argv.length != 4) {
		usage();
	} else {
		HOST = process.argv[2];
		PORT = process.argv[3];
	}
}

const init_server = () => {
	http.listen(3000, () => {
		console.log('listening on *:3000');
	});
}

const init_client = () => {
	
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

parse_args();
init_server();
init_client();
