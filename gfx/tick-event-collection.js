class TickEventCollection {
	constructor(tick_num) {
		this.tick_num = tick_num
		this.global = {
			game_start: [],
			hatch: [],
			spawn_resource: [],
			incant_done: [],
			connect_client: [],
			game_end: [],
		}
		this.player = []
	}
}

module.exports = TickEventCollection
