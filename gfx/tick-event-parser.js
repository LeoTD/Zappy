const TickEventCollection = require('./tick-event-collection.js')
const assert = require('assert')

class TickEventParser {
	constructor(options) {
		this.events = null
		this.multi = { pool: null, info: null }
		this.callback = options.onTickParsed
		console.log(this.onConnect)
		this.parse = this.parse.bind(this)
	}

	add_event_to_pool(event_object, event_pool) {
		event_pool.push(event_object)
	}

	finish_multi_message_event() {
		this.add_event_to_pool(this.multi.info, this.multi.pool)
		this.multi.info = null
		this.multi.pool = null
	}

	construct_multi_message_event(event_info, event_pool) {
		assert(this.multi.info == null)
		this.multi.pool = event_pool
		this.multi.info = event_info
	}

	parse(line) {
		let new_tick = null
		const msg = line.toString().split(' ')
		switch(msg[0]) {
			case 'SEE':
			case 'ADVANCE':
			case 'RIGHT':
			case 'LEFT':
			case 'DEATH':
			case 'INVENTORY':
			case 'LAY_EGG':
				this.add_event_to_pool(
					{
						type: msg[0],
						player_id: msg[1]
					},
					this.events.player
				)
				break

			case 'TAKE':
			case 'PUT':
				this.add_event_to_pool(
					{
						type: msg[0],
						player_id: msg[1],
						obj_type: msg[2],
						x: msg[3],
						y: msg[4],
						is_success: msg[5]
					},
					this.events.player
				)
				break

			case 'BAD_COMMAND':
			case 'BROADCAST':
				this.add_event_to_pool(
					{
						type: msg[0],
						player_id: msg[1],
						message: msg.slice(2).join(' ')
					},
					this.events.player
				)
				break

			case 'CONNECT':
				this.add_event_to_pool(
					{
						type: 'CONNECT',
						player_id: msg[1]
					},
					this.events.global.accept_client
				)
				break

			case 'DONE_LAYING_EGG':
				this.add_event_to_pool(
					{
						type: 'DONE_LAYING_EGG',
						player_id: msg[1],
						team_id: msg[2],
						x: msg[3],
						y: msg[4]
					},
					this.events.player
				)
				break

			case 'EGG_HATCH':
				this.add_event_to_pool(
					{
						type: 'EGG_HATCH',
						player_id: msg[1],
						team_id: msg[2],
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
				this.add_event_to_pool(
					{
						type: 'SPAWN_RESOURCE',
						x: msg[1],
						y: msg[2],
						obj_type: msg[3]
					},
					this.events.global.spawn_resource
				)
				break

			case 'LEAD_RITUAL':
				this.construct_multi_message_event(
					{
						type: 'INCANT_START',
						priest_id: msg[1],
						will_succeed: msg[2],
						participants: [msg[1]],
						new_level: msg[3]
					},
					this.events.player
				)
				break
			case 'JOIN_RITUAL':
				this.multi.info.participants.push(msg[1])
				break

			case 'INCANT_FINISH':
				this.construct_multi_message_event(
					{
						type: 'INCANT_FINISH',
						priest_id: msg[1],
						new_level: msg[2],
						levelup_pids: []
					},
					this.events.global.incant_done
				)
				break
			case 'LEVEL_UP':
				this.multi.info.levelup_pids.push(msg[1])
				break

			case 'KICK':
				this.construct_multi_message_event(
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
				this.construct_multi_message_event(
					{
						type: 'GAME_END',
						winning_team_ids: []
					},
					this.events.global.game_end
				)
				break
			case 'WINNING_TEAM':
				this.multi.info.winning_team_ids.push(msg[1])
				break

			case 'WORLD':
				this.construct_multi_message_event(
					{
						type: 'INIT',
						width: msg[1],
						height: msg[2],
						tickrate: msg[3],
						start_tick: msg[4],
						tiles: [],
						command_delays: [],
						team_names: [],
						players: []
					},
					this.events.global.game_start
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
				this.multi.info.team_names.push(msg.slice(1).join(' '))
				break
			case 'PLAYER':
				this.multi.info.players.push(
					{
						player_id: msg[0],
						team_id: msg[1],
						level: msg[2],
						x: msg[3],
						y: msg[4],
						energy: msg[5],
						facing: msg[6],
						food: msg[7],
						is_connected: msg[8],
						inventory: msg.slice(9)
					}
				)
				break
			case 'DELAY_TIME':
				this.multi.info.command_delays.push(
					{
						cmd: msg[1],
						time: msg[2]
					}
				)
				break

			case 'TICK':
				new_tick = new TickEventCollection(msg[1])
				break

			case 'DONE':
				this.finish_multi_message_event()
				break

			default:
				console.log("not handled", msg)
				//assert.fail('unhandled message type')
		}
		if (new_tick) {
			this.callback(this.events)
			this.events = new_tick
		}
	}
}

module.exports = TickEventParser
