const MAX_SPRITES			= 256;
const SPRITE_DIMENSIONS		= {height:24, width:24};
const SPRITE_ASSET_STRINGS	= [
	"assets/dino_blue.png",
	"assets/dino_red.png",
	"assets/dino_yellow.png",
	"assets/dino_green.png"
]

class Game {
	constructor(opts) {
		
		// General information:
		this.x				= opts.x;
		this.y				= opts.y;
		this.teams			= opts.teams;
		this.tickrate		= opts.tickrate;
		this.current_tick	= opts.num_elapsed_ticks;

		// Player and tile arrays for detailed game state
		//     management and for deploying animations.
		this.players		= [];
		this.tiles			= undefined;

// ------- Constructs required by the BABYLON graphics engine ------- //
// -------	   or created to better manage BABYLON resources: ------- //
		this.canvas			= undefined;
		this.engine			= undefined;
		this.scene			= undefined;

		// Array of sprite managers. One per team.
		this.spriteManagers	= [];

		// Graphical entities with global scope:
		this.camera			= undefined;
		this.skybox			= undefined;
		this.board			= undefined;
		this.sunlight		= undefined;
	}

	tick() {

	}

	spawn_resources() {

	}

	startup() {
		this.canvas 	= document.getElementById("renderCanvas");		// Get the canvas element 
		this.engine 	= new BABYLON.Engine(this.canvas, true);		// Generate the BABYLON 3D engine
		this.scene 		= new BABYLON.Scene(this.engine);				// Create the scene object

		this.sunlight	= new BABYLON.HemisphericLight("sunlight", new BABYLON.Vector3(1, 1, 0), this.scene);

		this.board		= new Board();
		this.board.createMesh({x:this.x, y:this.y}, this.scene);
		this.board.displayAxes(this.scene, 50) // #ifdef DEBUG

		// Create a spriteManager for each team. (Different color dinos! :D)
		for (var i = 0; i < this.teams.length; i++) {
			this.spriteManagers.push(
				new BABYLON.SpriteManager(this.teams[i], SPRITE_ASSET_STRINGS[i % SPRITE_ASSET_STRINGS.length],
											MAX_SPRITES, SPRITE_DIMENSIONS, this.scene)
			)
		}

		//this.camera = createArcCamera(this.canvas, this.scene); 		// #ifdef DEBUG
		this.camera = createCustomCamera(this.canvas, this.scene);	// Custom camera setup for final version.
	
		// Register a render loop to repeatedly render the scene
		this.engine.runRenderLoop(function () {
				game.scene.render();
		});
	
		// Watch for browser/canvas resize events
		window.addEventListener("resize", function () { 
				this.engine.resize();
		});
	}

	game_over() {

	}

	add_player(pinfo) {
		var new_player = new playerAvatar(this.spriteManagers[pinfo.team], pinfo);
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


}
