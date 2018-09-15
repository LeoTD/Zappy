var game;

document.addEventListener("DOMContentLoaded", function(event) {
	console.log("DOM fully loaded and parsed");
	game = new Game({x:16, y:16, teams:["zerg", "terran", "protoss"], tickrate:7, num_elapsed_ticks:0});
	game.startup();
	for (var i = 0; i < 12; i++) {
		game.add_player({x:Math.floor(Math.random() * (game.x - 1)), y:Math.floor(Math.random() * (game.y - 1)),
						inv:[0, 0, 0, 0, 0, 0, 1260], level:1, team:(i % game.teams.length), id:i});
	}

});
