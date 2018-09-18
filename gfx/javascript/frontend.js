document.addEventListener('DOMContentLoaded', function() {
	var socket = io();
	socket.on('tick', (data) => {
		const tick = JSON.parse(data)
		console.log(tick.tickNum)
		for (const ev of tick.events) {
			console.log(ev)
			if (ev.type == 'ADVANCE') {
				game.get_player(ev.playerId).advance()
			} else if (ev.type == 'RIGHT') {
				game.get_player(ev.playerId).right()
			} else if (ev.type == 'LEFT') {
				game.get_player(ev.playerId).left()
			}
		}
	})
})
