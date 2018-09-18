const TickEventCollection = require('./TickEventCollection.js')
const assert = require('assert')
const stream = require('stream')

class TickEventParser extends stream.Transform {
	constructor(opts = { writableObjectMode: true, readableObjectMode: true }) {
		super(opts)
		this.currentTick = null
		this.multi = null
		this.parse = this.parse.bind(this)
		this.completedTicks = []
	}

	addEvent(ev) {
		this.currentTick.events.push(ev)
	}

	finishMultiMessageEvent() {
		this.addEvent(this.multi)
		this.multi = null
	}

	constructMultiMessageEvent(ev) {
		assert(this.multi == null)
		this.multi = ev
	}

	_transform(line, _, callback) {
		this.parse(line)
		if (this.completedTicks.length)
			callback(null, this.completedTicks.shift())
		else {
			callback()
		}
	}

	parse(line) {
		const msg = line.toString().split(' ')
		switch(msg[0]) {
			case 'SEE':
			case 'ADVANCE':
			case 'RIGHT':
			case 'LEFT':
			case 'DEATH':
			case 'INVENTORY':
			case 'LAY_EGG':
			case 'CONNECT':
				this.addEvent({
					type: msg[0],
					playerId: msg[1]
				})
				break;

			case 'TAKE':
			case 'PUT':
				this.addEvent({
					type: msg[0],
					playerId: msg[1],
					objType: msg[2],
					x: msg[3],
					y: msg[4],
					isSuccess: msg[5]
				})
				break

			case 'BAD_COMMAND':
			case 'BROADCAST':
				this.addEvent({
					type: msg[0],
					playerId: msg[1],
					message: msg.slice(2).join(' ')
				})
				break

			case 'DONE_LAYING_EGG':
				this.addEvent({
						type: 'DONE_LAYING_EGG',
						playerId: msg[1],
						teamId: msg[2],
						x: msg[3],
						y: msg[4]
					})
				break

			case 'EGG_HATCH':
				this.addEvent({
					type: 'EGG_HATCH',
					playerId: msg[1],
					teamId: msg[2],
					level: msg[3],
					x: msg[4],
					y: msg[5],
					energy: msg[6],
					facing: msg[7],
					inventory: msg.slice(8)
				})
				break

			case 'SPAWN_RESOURCE':
				this.addEvent({
					type: 'SPAWN_RESOURCE',
					x: msg[1],
					y: msg[2],
					objType: msg[3]
				})
				break

			case 'LEAD_RITUAL':
				this.constructMultiMessageEvent({
					type: 'INCANT_START',
					priestId: msg[1],
					willSucceed: msg[2],
					participants: [msg[1]],
					newLevel: msg[3]
				})
				break
			case 'JOIN_RITUAL':
				this.multi.participants.push(msg[1])
				break

			case 'INCANT_FINISH':
				this.constructMultiMessageEvent({
					type: 'INCANT_FINISH',
					priestId: msg[1],
					newLevel: msg[2],
					levelupPids: []
				})
				break
			case 'LEVEL_UP':
				this.multi.levelupPids.push(msg[1])
				break

			case 'KICK':
				this.constructMultiMessageEvent({
					type: 'KICK',
					kicker: msg[1],
					direction: msg[2],
					kickees: []
				})
				break
			case 'GET_KICKED':
				this.multi.kickees.push(msg[1])
				break

			case 'GAME_END':
				this.constructMultiMessageEvent({
					type: 'GAME_END',
					winningTeamIds: []
				})
				break
			case 'WINNING_TEAM':
				this.multi.winningTeamIds.push(msg[1])
				break

			case 'WORLD':
				this.constructMultiMessageEvent({
					type: 'INIT',
					width: msg[1],
					height: msg[2],
					tickrate: msg[3],
					startTick: msg[4],
					tiles: [],
					commandDelays: [],
					teamNames: [],
					players: []
				})
				break
			case 'TILE':
				this.multi.tiles.push({
					x: msg[1],
					y: msg[2],
					eggs: msg[3],
					food: msg[4],
					stones: msg.slice(5)
				})
				break
			case 'TEAMNAME':
				this.multi.teamNames.push(msg.slice(1).join(' '))
				break
			case 'PLAYER':
				this.multi.players.push({
					playerId: msg[0],
					teamId: msg[1],
					level: msg[2],
					x: msg[3],
					y: msg[4],
					energy: msg[5],
					facing: msg[6],
					food: msg[7],
					isConnected: msg[8],
					inventory: msg.slice(9)
				})
				break
			case 'DELAY_TIME':
				this.multi.commandDelays.push({
					cmd: msg[1],
					time: msg[2]
				})
				break

			case 'TICK':
				if (this.currentTick) {
					this.completedTicks.push(this.currentTick)
				}
				this.currentTick = {
					tickNum: msg[1],
					events: []
				}
				break

			case 'DONE':
				this.finishMultiMessageEvent()
				break

			default:
				console.log("not handled", msg)
				//assert.fail('unhandled message type')
		}
	}
}

module.exports = TickEventParser
