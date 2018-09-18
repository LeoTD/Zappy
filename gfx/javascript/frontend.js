document.addEventListener('DOMContentLoaded', function() {
	var socket = io();
	socket.on('tick', (data) => {
		const tick = JSON.parse(data)
		console.log(tick.tickNum)
		tick.events.forEach(console.log)
		tick.events.filter(e => e.type == "ADVANCE" && parseInt(e.playerId) < 12).forEach(e => {
			const player = game.get_player(e.playerId)
			player.advance({x: -1, y: -1 })
		})
	})
})
