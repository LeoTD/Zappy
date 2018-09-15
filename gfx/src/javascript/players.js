
class playerAvatar {
	constructor(s_manager, opts) {

		this.manager 	= s_manager;
		this.id			= opts.id;
		this.x 			= opts.x;
		this.y 			= opts.y;
		this.inv		= opts.inv;
		this.level		= opts.level;
		this.facing		= opts.facing;
		this.team		= opts.team;
	}

	createSprite() {
		this.sprite 	= new BABYLON.Sprite("player", this.manager);

		this.sprite.position.y = 5;
		this.sprite.position.x = (this.x * TILE_SIZE) + (Math.random() * TILE_SIZE) - (TILE_SIZE / 2);;
		this.sprite.position.z = (this.y * TILE_SIZE) + (Math.random() * TILE_SIZE) - (TILE_SIZE / 2);;
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
		BABYLON.SceneLoader.ImportMesh("", "assets/models/", "pikachu.obj", scene, function (newMesh){
			that._mesh 	= newMesh[0];
		});
	}

	advance(vec) {
		if (this.sprite) {
			this.sprite.position.x = vec.x * TILE_SIZE;
			this.sprite.position.z = vec.y * TILE_SIZE;
		}
	}

	connect_client() {
		this.sprite.playAnimation(0, 3, true, 100);
	}
}
