
class playerAvatar {
	constructor(s_manager, opts) {

		this.manager 	= s_manager;
		this.id			= opts.id;
		this.x 			= opts.x;
		this.y 			= opts.y;
		this.inv		= opts.inv;
		this.level		= opts.level;
		this.team		= opts.team;
		this.compass	= ['n', 'e', 's', 'w'];
		this.facing		= opts.facing || 's';
		this.idle = this.idle.bind(this)
	}

	right() {
		let prev = this.facing
		this.compass.push(this.compass.shift());
		console.log(`right(): ${prev} -> ${this.facing}`)
		this.idle()
	}

	left() {
		let prev = this.facing
		this.compass.unshift(this.compass.pop());
		console.log(`left(): ${prev} -> ${this.facing}`)
		this.idle()
	}

	set facing(dir) {
		if (!this.compass.includes(dir))
			throw('bad direction: ' + dir);
		while (this.compass[0] != dir)
			this.compass.unshift(this.compass.pop());
	}

	get facing() {
		return this.compass[0];
	}

	createSprite() {
		this.sprite 	= new BABYLON.Sprite("player", this.manager);

		this.sprite.position.y = 5;
		this.sprite.position.x = (this.x * TILE_SIZE) + (Math.random() * (TILE_SIZE / 2)) - (TILE_SIZE / 2);;
		this.sprite.position.z = (this.y * TILE_SIZE) + (Math.random() * (TILE_SIZE / 2)) - (TILE_SIZE / 2);;
		this.sprite.size = 10;
		this.sprite.isPickable = true;
	}

	createAvatar(scene) {
		this.avatar = BABYLON.MeshBuilder.CreateCylinder("cone", 
			{faceColors:colors, diameterTop:0, diameterBottom:0.25, height: .5, tessellation: 3}, scene);

		this.avatar.position.y = 1;
		this.avatar.position.x = this.x;
		this.avatar.position.z = this.y;
	}

	createCreatureAvatar(scene) {
		var that = this;
		BABYLON.SceneLoader.ImportMesh("", "models/", "pikachu.obj", scene, function (newMesh){
			that._mesh 	= newMesh[0];
		});
	}

	moveDirection(dir) {
		if (false === ['n', 'e', 's', 'w'].includes(dir))
			console.warn(`${this.id}: invalid direction '${dir}'`)
		this.x = (this.x + { n: 0, e: -1, w: 1, s: 0 }[dir] + game.x) % game.x
		this.y = (this.y + { n: -1, e: 0, w: 0, s: 1 }[dir] + game.y) % game.y
		this.sprite.position.x = this.x * TILE_SIZE
		this.sprite.position.z = this.y * TILE_SIZE
	}

	advance() {
		this.moveDirection(this.facing)
		this.idle()
	}

	connect_client() {
		this.sprite.playAnimation(0, 3, true, 100);
	}

	idle() {
		const startFrame = { n: 38, e: 44, s: 32, w: 50 }[this.facing];
		this.sprite.playAnimation(startFrame, startFrame + 3, true, 200)
	}
}
