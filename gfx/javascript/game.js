const MAX_SPRITES					= 256;
const SPRITE_DIMENSIONS				= {height:32, width:32};
const FOOD_DIMENSIONS				= {height:384, width: 427};
const AVATAR_SPRITE_ASSET_STRINGS	= [
	'bob.png',
];

const STONE_ASSET_STRINGS			= {
	'stone0.png': { height: 89, width: 67 },
	'stone1.png': { height: 114, width: 123 },
	'stone2.png': { height: 120, width: 120 },
	'stone3.png': { height: 89, width: 107 },
	'stone4.png': { height: 500, width: 500 },
	'stone5.png': { height: 155, width: 155 },
};

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
		this.tiles					= [];
		for (let i = 0; i < this.x; i++)
			this.tiles.push([]);

		// ------- Constructs required by the BABYLON graphics engine ------- //
		// -------	   or created to better manage BABYLON resources: ------- //
		this.canvas					= undefined;
		this.engine					= undefined;
		this.scene					= undefined;

		// Various Sprite Managers
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
		this.canvas 	= document.getElementById('renderCanvas');		// Get the canvas element
		this.engine 	= new BABYLON.Engine(this.canvas, true);		// Generate the BABYLON 3D engine
		this.scene 		= new BABYLON.Scene(this.engine);				// Create the scene object

		this.scene.clearColor = new BABYLON.Color3(0, 0.1, 0.5);

		this.sunlight	= new BABYLON.HemisphericLight('sunlight', new BABYLON.Vector3(1, 1, 0), this.scene);

		this.board		= new Board();
		this.board.createMesh({x:this.x, y:this.y}, this.scene);
		this.board.displayAxes(this.scene, 50);							// #ifdef DEBUG
		this.initSpriteManagers();

		this.camera = createCustomCamera(this.canvas, this.scene);
	
		// Register a render loop to repeatedly render the scene
		this.engine.runRenderLoop(function () {
			game.scene.render();
		});
	
		// Watch for browser/canvas resize events
		window.addEventListener('resize', function () { 
			game.engine.resize();
		});
	}

	game_over() {

	}

	tick() {

	}

	spawn_resources() {

	}

	addPlayer(pinfo) {
		var new_player = new playerAvatar(
			this.spriteManagers.avatars[pinfo.team], pinfo);
		this.players[new_player.id] = new_player;
		this.players[new_player.id].createSprite();
	}

	get_player(pid) {
		if (this.players) {
			return this.players[pid];
		}
		else {
			console.warn('Failed to get_player');
		}
	}

	addTile({ x, y }) {
		return (this.tiles[x][y] = new Tile({ x, y }));
	}

	getContentSpriteManagerFor(type) {
		if ('stone' === type.slice(0, 5))
			return this.spriteManagers.stones[type[5]];
		if ('eggs' === type || 'food' === type)
			return this.spriteManagers[type];
		console.warn('couldn\'t get sprite manager for ' + type);
	}

	initSpriteManagers() {
		this.spriteManagers = {
			stones: Object.keys(STONE_ASSET_STRINGS).map((asset_path, idx) => {
				return new BABYLON.SpriteManager(
					`stone${idx}-manager`,
					asset_path,
					this.x * this.y * 10,
					STONE_ASSET_STRINGS[asset_path],
					this.scene
				);
			}),
			avatars: this.teams.map((teamName, idx) => {
				const whichSprite = idx % AVATAR_SPRITE_ASSET_STRINGS.length;
				return new BABYLON.SpriteManager(
					`avatar-${teamName}-manager`,
					AVATAR_SPRITE_ASSET_STRINGS[whichSprite],
					MAX_SPRITES,
					SPRITE_DIMENSIONS,
					this.scene
				);
			}),
			eggs: new BABYLON.SpriteManager(
				'eggs-manager',
				'egg.png', //XXX changeme
				this.x * this.y * 10,
				SPRITE_DIMENSIONS,
				this.scene
			),
			food: new BABYLON.SpriteManager(
				'food-manager',
				'food.png', //XXX changeme
				this.x * this.y * 10,
				FOOD_DIMENSIONS,	
				this.scene
			),
		};
	}
}
