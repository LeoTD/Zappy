const stream = require('stream')
const fs = require('fs')
const net = require('net')
const split2 = require('split2')
const util = require('util')
const TickEventParser = require('./tick-event-parser.js')
const TickEventCollection = require('./tick-event-collection.js')

const gameServer = process.stdin
const logFile = process.stdout
const tickEventParser = new TickEventParser()
gameServer.pipe(split2()).pipe(tickEventParser).pipe(logFile)
