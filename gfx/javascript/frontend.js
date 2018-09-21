document.addEventListener('DOMContentLoaded', function() {
	var socket = io();
	socket.on('tick', (data) => {
		const tick = JSON.parse(data);
		console.log(tick.tickNum);
		for (const ev of tick.events) {
			console.log(ev);
			switch(ev.type) {
			case 'INIT':
				fastForwardToGameState(ev);
				break;
			case 'BROADCAST':
				game.get_player(ev.playerId).broadcast();
				break;
			case 'ADVANCE':
				game.get_player(ev.playerId).advance();
				break;
			case 'RIGHT':
				game.get_player(ev.playerId).right();
				break;
			case 'LEFT':
				game.get_player(ev.playerId).left();
				break;
			case 'KICK':
				if (ev.kickees.length === 0)
					game.get_player(ev.playerId).fail();
				else
					kickPlayers(ev.kickees, ev.direction);
				break;
			case 'TAKE':
				game.get_player(ev.playerId).take({x:ev.x, y:ev.y}, ev.objType, ev.isSuccess);
				break;
			case 'PUT':
				game.get_player(ev.playerId).put({x:ev.x, y:ev.y}, ev.objType, ev.isSuccess);
				break;
			case 'LAY_EGG':
				game.get_player(ev.playerId).layEgg();
				break;
			case 'DONE_LAYING_EGG':
				game.get_player(ev.playerId).doneLayingEgg({x:ev.x, y:ev.y});
				break;
			case 'EGG_HATCH':
				const o = {};
				o.id = ev.playerId;
				o.team = ev.teamId;
				o.level = ev.level;
				o.x = ev.x;
				o.y = ev.y;
				o.energy = ev.energy;
				o.facing = ev.facing;
				o.food = ev.food;
				o.inv = ev.inventory;
				game.addPlayer(o);
				game.get_player(o.id).eggHatch({x:o.x, y:o.y});
				console.log(o.team);
				break;
			case 'SEE':
				game.get_player(ev.playerId).see();
				break;
			case 'INVENTORY':
				game.get_player(ev.playerId).inventory();	
				break;
			case 'SPAWN_RESOURCE':
				game.tiles[ev.x][ev.y].addContent(ev.objType);
				break;
			case 'BAD_COMMAND':
				game.get_player(ev.playerId).fail();	
				break;
			case 'BROADCAST':
				game.get_player(ev.playerId).broadcast();
				break;
			case 'DEATH':
				game.get_player(ev.playerId).death();
				break;
			default:
				console.log('event type not yet handled: ' + ev.type);
			}
		}
	});
});

var game;

function fastForwardToGameState(ev) {
	game = new Game({
		x: ev.width,
		y: ev.height,
		tickrate: ev.tickrate,
		num_elapsed_ticks: ev.startTick,
		teams: ev.teamNames
	});
	game.startup();
	for (let tileStat of ev.tiles) {
		const t = game.addTile({ x: tileStat.x, y: tileStat.y });
		t.addContent("food", tileStat.food);
		t.addContent("eggs", tileStat.eggs);
		tileStat.stones.forEach((amt, idx) => {
			t.addContent(`stone${idx}`, amt);
		});
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
		});
		game.get_player(p.playerId).idle();
	}
}

function kickPlayers(kicked_pids, direction) {
	for (let pid of kicked_pids) {
		game.get_player(pid).getKicked(direction);
	}
}
