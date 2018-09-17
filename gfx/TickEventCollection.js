class TickEventCollection {
	constructor(tickNum) {
		this.tickNum = tickNum
		this.global = {
			gameStart: [],
			hatch: [],
			spawnResource: [],
			incantDone: [],
			connectClient: [],
			gameEnd: [],
		}
		this.player = []
	}
}

module.exports = TickEventCollection
