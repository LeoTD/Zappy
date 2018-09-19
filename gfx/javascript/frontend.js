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
				case 'KICK':
					kickPlayers(ev.kickees, ev.direction)
					break
				case 'SPAWN_RESOURCE':
					game.tiles[ev.x][ev.y].addContent(ev.objType)
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
	for (let tileStat of ev.tiles) {
		const t = game.addTile({ x: tileStat.x, y: tileStat.y })
		t.addContent("food", tileStat.food)
		t.addContent("eggs", tileStat.eggs)
		tileStat.stones.forEach((amt, idx) => {
			t.addContent(`stone${idx}`, amt)
		})
	}
	for (let p of ev.players) {
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
		game.get_player(p.playerId).idle()
	}
}

function kickPlayers(kicked_pids, direction) {
	for (let pid of kicked_pids) {
		game.get_player(pid).moveDirection(direction)
	}
}
