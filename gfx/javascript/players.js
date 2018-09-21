const compass = ['n', 'e', 's', 'w', 'n'];

class playerAvatar {
	constructor(opts) {
		this.bubble		= new speechBubble(this)

		this.id			= opts.id;
		this.x 			= opts.x;
		this.y 			= opts.y;
		this.inv		= opts.inv;
		this.level		= opts.level;
		this.team		= opts.team;
		this.facing		= opts.facing || 's';
	}

	broadcast() {
		this.bubble.cmdPopup('broadcast');
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

	put(tile, type, isSuccess) {
		if (isSuccess === 1) {
			this.inventory();
			game.tiles[tile.x][tile.y].addContent(type, 1);
		}
		else {
			this.fail();
		}
	}

	layEgg() {
		this.bubble.cmdPopup('fork');
	}

	doneLayingEgg(tile) {
		console.log(tile);
		console.log(this);
		game.tiles[tile.x][tile.y].addContent('eggs', 1);
	}

	eggHatch(tile) {
		game.tiles[tile.x][tile.y].removeContent('eggs', 1);
	}

	take(tile, type, isSuccess) {
		if (isSuccess === 1) {
			this.inventory();
			game.tiles[tile.x][tile.y].removeContent(type, 1);
		}
		else {
			this.fail();
		}
	}

	see() {
		this.bubble.cmdPopup('see');
	}

	inventory() {
		this.bubble.cmdPopup('inventory');
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

	fail() {
		this.bubble.cmdPopup('fail');
	}
	
	death() {
		this.bubble.cmdPopup('death');
		this.sprite.dispose();
	}

}
