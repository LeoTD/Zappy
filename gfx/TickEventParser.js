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
		console.log(msg)
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
					playerId: Number(msg[1])
				})
				break;

			case 'TAKE':
			case 'PUT':
				this.addEvent({
					type: msg[0],
					playerId: Number(msg[1]),
					objType: objNameFor(msg[2]),
					x: Number(msg[3]),
					y: Number(msg[4]),
					isSuccess: Number(msg[5])
				})
				break

			case 'BAD_COMMAND':
			case 'BROADCAST':
				this.addEvent({
					type: msg[0],
					playerId: Number(msg[1]),
					message: msg.slice(2).join(' ')
				})
				break

			case 'DONE_LAYING_EGG':
				this.addEvent({
						type: 'DONE_LAYING_EGG',
						playerId: Number(msg[1]),
						teamId: Number(msg[2]),
						x: Number(msg[3]),
						y: Number(msg[4])
					})
				break

			case 'EGG_HATCH':
				this.addEvent({
					type: 'EGG_HATCH',
					playerId: Number(msg[1]),
					teamId: Number(msg[2]),
					level: Number(msg[3]),
					x: Number(msg[4]),
					y: Number(msg[5]),
					energy: Number(msg[6]),
					facing: Number(msg[7]),
					inventory: msg.slice(8).map(Number)
				})
				break

			case 'SPAWN_RESOURCE':
				this.addEvent({
					type: 'SPAWN_RESOURCE',
					x: Number(msg[1]),
					y: Number(msg[2]),
					objType: objNameFor(msg[3])
				})
				break

			case 'LEAD_RITUAL':
				this.constructMultiMessageEvent({
					type: 'INCANT_START',
					priestId: Number(msg[1]),
					willSucceed: Number(msg[2]),
					participants: [Number(msg[1])],
					newLevel: Number(msg[3])
				})
				break
			case 'JOIN_RITUAL':
				this.multi.participants.push(Number(msg[1]))
				break

			case 'INCANT_FINISH':
				this.constructMultiMessageEvent({
					type: 'INCANT_FINISH',
					priestId: Number(msg[1]),
					newLevel: Number(msg[2]),
					levelupPids: []
				})
				break
			case 'LEVEL_UP':
				this.multi.levelupPids.push(Number(msg[1]))
				break

			case 'KICK':
				this.constructMultiMessageEvent({
					type: 'KICK',
					kicker: Number(msg[1]),
					direction: ['n', 'w', 's', 'e'][Math.floor(Number(msg[2]) / 2)],
					kickees: []
				})
				break
			case 'GET_KICKED':
				this.multi.kickees.push(Number(msg[1]))
				break

			case 'GAME_END':
				this.constructMultiMessageEvent({
					type: 'GAME_END',
					winningTeamIds: []
				})
				break
			case 'WINNING_TEAM':
				this.multi.winningTeamIds.push(Number(msg[1]))
				break

			case 'WORLD':
				this.constructMultiMessageEvent({
					type: 'INIT',
					width: Number(msg[1]),
					height: Number(msg[2]),
					tickrate: Number(msg[3]),
					startTick: Number(msg[4]),
					tiles: [],
					commandDelays: [],
					teamNames: [],
					players: []
				})
				break
			case 'TILE':
				this.multi.tiles.push({
					x: Number(msg[1]),
					y: Number(msg[2]),
					eggs: Number(msg[3]),
					food: Number(msg[4]),
					stones: msg.slice(5).map(Number)
				})
				break
			case 'TEAMNAME':
				this.multi.teamNames.push(msg.slice(1).join(' '))
				break
			case 'PLAYER':
				this.multi.players.push({
					playerId: Number(msg[1]),
					teamId: Number(msg[2]),
					level: Number(msg[3]),
					x: Number(msg[4]),
					y: Number(msg[5]),
					energy: Number(msg[6]),
					facing: ['n', 'w', 's', 'e'][Math.floor(Number(msg[7]) / 2)],
					food: Number(msg[8]),
					isConnected: Number(msg[9]),
					inventory: msg.slice(10).map(Number)
				})
				break
			case 'DELAY_TIME':
				this.multi.commandDelays.push({
					cmd: msg[1],
					time: Number(msg[2])
				})
				break

			case 'TICK':
				if (this.currentTick) {
					this.completedTicks.push(this.currentTick)
				}
				this.currentTick = {
					tickNum: Number(msg[1]),
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

function objNameFor(typeEnum) {
	return Number(typeEnum) === 6 ? "food" : "stone" + typeEnum
}

module.exports = TickEventParser