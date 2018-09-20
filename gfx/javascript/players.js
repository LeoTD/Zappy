const compass = ['n', 'e', 's', 'w', 'n'];

class playerAvatar {
	constructor(opts) {
		this.id			= opts.id;
		this.x 			= opts.x;
		this.y 			= opts.y;
		this.inv		= opts.inv;
		this.level		= opts.level;
		this.team		= opts.team;
		this.facing		= opts.facing || 's';
	}

	right() {
		this.facing = compass[compass.indexOf(this.facing) + 1];
		this.sprite.idleAnimation();
	}

	left() {
		this.facing = compass[compass.lastIndexOf(this.facing) - 1];
		this.sprite.idleAnimation();
	}

	idle() {
		this.sprite.idleAnimation();
	}

	createSprite() {
		const opts = {};
		Object.assign(opts, SpriteData[game.getTeamSpriteName(this.team)]);
		opts.player = this;
		this.sprite = new PlayerSprite(opts);
	}

	moveDirection(dir) {
		if (false === ['n', 'e', 's', 'w'].includes(dir))
			console.warn(`${this.id}: invalid direction '${dir}'`);
		this.x = (this.x + { n: 0, e: 1, w: -1, s: 0 }[dir] + game.x) % game.x;
		this.y = (this.y + { n: -1, e: 0, w: 0, s: 1 }[dir] + game.y) % game.y;
	}

	advance() {
		this.sprite.advanceAnimation();
		this.moveDirection(this.facing);
	}

	getKicked(dir) {
		this.sprite.getKickedAnimation(dir);
		this.moveDirection(dir);
	}
}
