const TickEventCollection = require('./TickEventCollection.js')
const assert = require('assert')

class TickEventParser {
	constructor(options) {
		this.events = null
		this.multi = { pool: null, info: null }
		this.callback = options.onTickParsed
		console.log(this.onConnect)
		this.parse = this.parse.bind(this)
	}

	addEventToPool(eventObject, eventPool) {
		eventPool.push(eventObject)
	}

	finishMultiMessageEvent() {
		this.addEventToPool(this.multi.info, this.multi.pool)
		this.multi.info = null
		this.multi.pool = null
	}

	constructMultiMessageEvent(eventInfo, eventPool) {
		assert(this.multi.info == null)
		this.multi.pool = eventPool
		this.multi.info = eventInfo
	}

	parse(line) {
		let newTick = null
		const msg = line.toString().split(' ')
		switch(msg[0]) {
			case 'SEE':
			case 'ADVANCE':
			case 'RIGHT':
			case 'LEFT':
			case 'DEATH':
			case 'INVENTORY':
			case 'LAY_EGG':
				this.addEventToPool(
					{
						type: msg[0],
						playerId: msg[1]
					},
					this.events.player
				)
				break

			case 'TAKE':
			case 'PUT':
				this.addEventToPool(
					{
						type: msg[0],
						playerId: msg[1],
						objType: msg[2],
						x: msg[3],
						y: msg[4],
						isSuccess: msg[5]
					},
					this.events.player
				)
				break

			case 'BAD_COMMAND':
			case 'BROADCAST':
				this.addEventToPool(
					{
						type: msg[0],
						playerId: msg[1],
						message: msg.slice(2).join(' ')
					},
					this.events.player
				)
				break

			case 'CONNECT':
				this.addEventToPool(
					{
						type: 'CONNECT',
						playerId: msg[1]
					},
					this.events.global.acceptClient
				)
				break

			case 'DONE_LAYING_EGG':
				this.addEventToPool(
					{
						type: 'DONE_LAYING_EGG',
						playerId: msg[1],
						teamId: msg[2],
						x: msg[3],
						y: msg[4]
					},
					this.events.player
				)
				break

			case 'EGG_HATCH':
				this.addEventToPool(
					{
						type: 'EGG_HATCH',
						playerId: msg[1],
						teamId: msg[2],
						level: msg[3],
						x: msg[4],
						y: msg[5],
						energy: msg[6],
						facing: msg[7],
						inventory: msg.slice(8)
					},
					this.events.global.hatch
				)
				break

			case 'SPAWN_RESOURCE':
				this.addEventToPool(
					{
						type: 'SPAWN_RESOURCE',
						x: msg[1],
						y: msg[2],
						objType: msg[3]
					},
					this.events.global.spawnResource
				)
				break

			case 'LEAD_RITUAL':
				this.constructMultiMessageEvent(
					{
						type: 'INCANT_START',
						priestId: msg[1],
						willSucceed: msg[2],
						participants: [msg[1]],
						newLevel: msg[3]
					},
					this.events.player
				)
				break
			case 'JOIN_RITUAL':
				this.multi.info.participants.push(msg[1])
				break

			case 'INCANT_FINISH':
				this.constructMultiMessageEvent(
					{
						type: 'INCANT_FINISH',
						priestId: msg[1],
						newLevel: msg[2],
						levelupPids: []
					},
					this.events.global.incantDone
				)
				break
			case 'LEVEL_UP':
				this.multi.info.levelupPids.push(msg[1])
				break

			case 'KICK':
				this.constructMultiMessageEvent(
					{
						type: 'KICK',
						kicker: msg[1],
						direction: msg[2],
						kickees: []
					},
					this.events.player
				)
				break
			case 'GET_KICKED':
				this.multi.info.kickees.push(msg[1])
				break

			case 'GAME_END':
				this.constructMultiMessageEvent(
					{
						type: 'GAME_END',
						winningTeamIds: []
					},
					this.events.global.gameEnd
				)
				break
			case 'WINNING_TEAM':
				this.multi.info.winningTeamIds.push(msg[1])
				break

			case 'WORLD':
				this.constructMultiMessageEvent(
					{
						type: 'INIT',
						width: msg[1],
						height: msg[2],
						tickrate: msg[3],
						startTick: msg[4],
						tiles: [],
						commandDelays: [],
						teamNames: [],
						players: []
					},
					this.events.global.gameStart
				)
				break
			case 'TILE':
				this.multi.info.tiles.push(
					{
						x: msg[1],
						y: msg[2],
						eggs: msg[3],
						food: msg[4],
						stones: msg.slice(5)
					}
				)
				break
			case 'TEAMNAME':
				this.multi.info.teamNames.push(msg.slice(1).join(' '))
				break
			case 'PLAYER':
				this.multi.info.players.push(
					{
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
					}
				)
				break
			case 'DELAY_TIME':
				this.multi.info.commandDelays.push(
					{
						cmd: msg[1],
						time: msg[2]
					}
				)
				break

			case 'TICK':
				newTick = new TickEventCollection(msg[1])
				break

			case 'DONE':
				this.finishMultiMessageEvent()
				break

			default:
				console.log("not handled", msg)
				//assert.fail('unhandled message type')
		}
		if (newTick) {
			this.callback(this.events)
			this.events = newTick
		}
	}
}

module.exports = TickEventParser
