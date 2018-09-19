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
		this.idle		= this.idle.bind(this);
	}

	right() {
		let prev = this.facing;
		this.compass.push(this.compass.shift());
		console.log(`right(): ${prev} -> ${this.facing}`);
		this.idle();
	}

	left() {
		let prev = this.facing;
		this.compass.unshift(this.compass.pop());
		console.log(`left(): ${prev} -> ${this.facing}`);
		this.idle();
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

		this.sprite.size = 10;
		const zone_width = (TILE_SIZE) - (this.sprite.size);
		const zone_height= (TILE_SIZE / 2);
		const w_offset   = (TILE_SIZE / 2) - (this.sprite.size / 2);
		const h_offset   = (TILE_SIZE / 3);
		this.spriteOffsets = {
			x:(Math.random() * zone_width) - w_offset,
			y:(Math.random() * zone_height) - h_offset
		}
		this.sprite.position.y = 5;
		this.sprite.position.z = (this.x * TILE_SIZE) + this.spriteOffsets.x;
		this.sprite.position.x = (this.y * TILE_SIZE) + this.spriteOffsets.y;
		this.sprite.isPickable = true;
	}

	moveDirection(dir) {
		if (false === ['n', 'e', 's', 'w'].includes(dir))
			console.warn(`${this.id}: invalid direction '${dir}'`);
		this.x = (this.x + { n: 0, e: 1, w: -1, s: 0 }[dir] + game.x) % game.x;
		this.y = (this.y + { n: -1, e: 0, w: 0, s: 1 }[dir] + game.y) % game.y;
	}

	moveSprite(val, dir) {
		var animation = new BABYLON.Animation("tutoAnimation",
			{n:"position.x", s:"position.x", e:"position.z", w:"position.z"}[dir],
			15 * game.tickrate,
			BABYLON.Animation.ANIMATIONTYPE_FLOAT,
			BABYLON.Animation.ANIMATIONLOOPMODE_CYCLE
		);
		var keys = [];
		keys.push({
			frame: 0,
			value: val 
		});
		keys.push({
			frame: 100,
			value: val + (dir === 'n' || dir === 'w' ? -TILE_SIZE : TILE_SIZE)
		});
		animation.setKeys(keys);
		this.sprite.animations.push(animation);
		game.scene.beginAnimation(this.sprite, 0, 100, false, 1, () => {
			this.sprite.stopAnimation();
			this.sprite.position.x = this.y * TILE_SIZE + this.spriteOffsets.y;
			this.sprite.position.z = this.x * TILE_SIZE + this.spriteOffsets.x;
			this.idle();
		});
		this.sprite.playAnimation(
			{n:7,  e:13, s:1, w:19}[dir],
			{n:10, e:16, s:4, w:22}[dir],
			true,
			100
		);
	}

	advance() {
		this.moveDirection(this.facing);
		this.moveSprite({n:this.sprite.position.x, s:this.sprite.position.x,
						 e:this.sprite.position.z, w:this.sprite.position.z}[this.facing], this.facing)
		//this.idle();
	}

	connect_client() {
		this.sprite.playAnimation(0, 3, true, 100);
	}

	idle() {
		const startFrame = { n: 38, e: 44, s: 32, w: 50 }[this.facing];
		this.sprite.playAnimation(startFrame, startFrame + 3, true, 200);
	}
}
