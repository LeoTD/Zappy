document.addEventListener('DOMContentLoaded', function() {
	var socket = io();
	socket.on('tick', (data) => {
		//console.log(data)
		const events = JSON.parse(data)
		events.player.filter(e => e.type == "ADVANCE" && parseInt(e.playerId) < 12).forEach(e => {
			const player = game.get_player(e.playerId)
			player.advance({x: -1, y: -1 })
		})
	})
})
