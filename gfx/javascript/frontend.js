document.addEventListener('DOMContentLoaded', function() {
	var socket = io();
	socket.on('tick', (data) => {
		const tick = JSON.parse(data)
		console.log(tick.tickNum)
		for (const ev of tick.events) {
			console.log(ev)
			switch(ev.type) {
				case 'INIT':
					fastForwardToGameState(ev)
					break
				case 'ADVANCE':
					game.get_player(ev.playerId).advance()
					break
				case 'RIGHT':
					game.get_player(ev.playerId).right()
					break
				case 'LEFT':
					game.get_player(ev.playerId).left()
					break
				default:
					console.log('event type not yet handled: ' + ev.type)
			}
		}
	})
})

var game

function fastForwardToGameState(ev) {
	game = new Game({
		x: ev.width,
		y: ev.height,
		tickrate: ev.tickrate,
		num_elapsed_ticks: ev.startTick,
		teams: ev.teamNames
	})
	game.startup()
	for (let p of ev.players) {
		console.log(p)
		game.addPlayer({
			id: p.playerId,
			team: p.teamId,
			level: p.level,
			x: p.x,
			y: p.y,
			energy: p.energy,
			facing: p.facing,
			food: p.food,
			inv: p.inventory,
		})
		//if (p.isConnected)
			//p.connectClient
		game.get_player(p.playerId).idle()
	}
}
