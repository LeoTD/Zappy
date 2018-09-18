const MAX_SPRITES					= 256;
const SPRITE_DIMENSIONS				= {height:32, width:32};
const AVATAR_SPRITE_ASSET_STRINGS	= [
	"bob.png",
];
const STONE_ASSET_STRINGS			= [
	"temp_stone.png",	// Stone0, ...
	"temp_stone.png",
	"temp_stone.png",
	"temp_stone.png",
	"temp_stone.png",
	"temp_stone.png",
	"temp_stone.png"		// Food
];

class Game {
	constructor(opts) {
		
		// General information:
		this.x						= opts.x;
		this.y						= opts.y;
		this.teams					= opts.teams;
		this.tickrate				= opts.tickrate;
		this.current_tick			= opts.num_elapsed_ticks;

		// Player and tile arrays for detailed game state
		//     management and for deploying animations.
		this.players				= [];
		this.tiles					= undefined;

// ------- Constructs required by the BABYLON graphics engine ------- //
// -------	   or created to better manage BABYLON resources: ------- //
		this.canvas					= undefined;
		this.engine					= undefined;
		this.scene					= undefined;

		// Various Sprite Managers
		this.tileContentsSM			= []; // One per stone sprite + one for food.
		this.avatarSM				= []; // One per team. Handles the main avatar sprite.
		
		// Space saved for action/reaction sprite assets
		//
		//
		//

		// Graphical entities with global scope:
		this.camera					= undefined;
		this.skybox					= undefined;
		this.board					= undefined;
		this.sunlight				= undefined;
	}

	startup() {
		this.canvas 	= document.getElementById("renderCanvas");		// Get the canvas element 
		this.engine 	= new BABYLON.Engine(this.canvas, true);		// Generate the BABYLON 3D engine
		this.scene 		= new BABYLON.Scene(this.engine);				// Create the scene object

		this.sunlight	= new BABYLON.HemisphericLight("sunlight", new BABYLON.Vector3(1, 1, 0), this.scene);

		this.board		= new Board();
		this.board.createMesh({x:this.x, y:this.y}, this.scene);
		this.board.displayAxes(this.scene, 50) // #ifdef DEBUG

// ------- Load sprite managers with their respective sprites ------- //
		// Create an avatar manager for each team. (Different color dinos! :D)
		for (var i = 0; i < this.teams.length; i++) {
			this.avatarSM.push(
				new BABYLON.SpriteManager(this.teams[i], AVATAR_SPRITE_ASSET_STRINGS[i % AVATAR_SPRITE_ASSET_STRINGS.length],
											MAX_SPRITES, SPRITE_DIMENSIONS, this.scene)
			)
		}

		// Create a manager for each stone type of stone and food.
		this.tileContentsSM[0] = new BABYLON.SpriteManager("stone0", STONE_ASSET_STRINGS[0], (this.x * this.y) * 10, SPRITE_DIMENSIONS, this.scene);
		this.tileContentsSM[1] = new BABYLON.SpriteManager("stone1", STONE_ASSET_STRINGS[0], (this.x * this.y) * 10, SPRITE_DIMENSIONS, this.scene);
		this.tileContentsSM[2] = new BABYLON.SpriteManager("stone2", STONE_ASSET_STRINGS[0], (this.x * this.y) * 10, SPRITE_DIMENSIONS, this.scene);
		this.tileContentsSM[3] = new BABYLON.SpriteManager("stone3", STONE_ASSET_STRINGS[0], (this.x * this.y) * 10, SPRITE_DIMENSIONS, this.scene);
		this.tileContentsSM[4] = new BABYLON.SpriteManager("stone4", STONE_ASSET_STRINGS[0], (this.x * this.y) * 10, SPRITE_DIMENSIONS, this.scene);
		this.tileContentsSM[5] = new BABYLON.SpriteManager("stone5", STONE_ASSET_STRINGS[0], (this.x * this.y) * 10, SPRITE_DIMENSIONS, this.scene);
		this.tileContentsSM[6] = new BABYLON.SpriteManager("food", STONE_ASSET_STRINGS[0], (this.x * this.y) * 10, SPRITE_DIMENSIONS, this.scene);

// ------ END SPRITE LOADING ------- //

		//this.camera = createArcCamera(this.canvas, this.scene);	// #ifdef DEBUG
		this.camera = createCustomCamera(this.canvas, this.scene);	// Custom camera setup for final version.
	
		// Register a render loop to repeatedly render the scene
		this.engine.runRenderLoop(function () {
				game.scene.render();
		});
	
		// Watch for browser/canvas resize events
		window.addEventListener("resize", function () { 
				game.engine.resize();
		});
	}

	game_over() {

	}

	tick() {

	}

	spawn_resources() {

	}

	add_player(pinfo) {
		var new_player = new playerAvatar(this.avatarSM[pinfo.team], pinfo);
		this.players[new_player.id] = new_player;
		this.players[new_player.id].createSprite();
	}

	get_player(pid) {
		if (this.players) {
			return this.players[pid];
		}
		else {
			console.log("Failed to get_player");
		}
	}

	create_tile(tinfo) {
		var new_tile;
		for (var i = 0; i < tinfo.length; i++) {
			new_tile = tinfo[i];
			this.tiles[new_tile.x][new_tile.y] = new Tile(new_tile);

		}
	}

}
