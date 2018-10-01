const compass = ['n', 'e', 's', 'w', 'n'];

class playerAvatar {
	constructor(opts) {
		this.bubble = new speechBubble(this);
		this.id = opts.id;
		this.x = opts.x;
		this.y = opts.y;
		this.inventory = {};
		for (let i in opts.inv) {
			this.inventory[`stone${i}`] = opts.inv[i];
		}
		this.inventory.food = opts.food;
		this.level = opts.level;
		this.team = opts.team;
		this.facing = opts.facing || 's';
		this.alive = true;
	}

	broadcast() {
		this.bubble.cmdPopup('broadcast');
	}

	eatFood() {
		this.inventory.food -= 1;
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
			this.bubble.cmdPopup('inventory');
			this.inventory[type] -= 1;
			game.tiles[tile.x][tile.y].addContent(type, 1);
		}
		else {
			this.fail();
		}
	}

	leadIncant(isSuccess) {
		this.sprite.playLeadIncantationAnimation();
	}

	finishLeadIncant(newLevel) {
		this.sprite.resetAndIdle();
		this.level = newLevel;
	}

	layEgg() {
		this.bubble.cmdPopup('fork');
	}

	doneLayingEgg(tile) {
		game.tiles[tile.x][tile.y].addContent('eggs', 1);
	}

	eggHatch(tile) {
		game.tiles[tile.x][tile.y].removeContent('eggs', 1);
	}
	
	death() {
		this.bubble.cmdPopup('death');
		this.alive = false;
		this.sprite.dispose();
	}

	take(tile, type, isSuccess) {
		if (isSuccess === 1) {
			this.inventory[type] += 1;
			this.bubble.cmdPopup('inventory');
			game.tiles[tile.x][tile.y].removeContent(type, 1);
		}
		else {
			this.fail();
		}
	}

	checkInventory() {
		this.bubble.cmdPopup('inventory');
	}

	see() {
		this.bubble.cmdPopup('see');
	}

	createSprite() {
		const opts = {};
		Object.assign(opts, SpriteData[game.getTeamSpriteName(this.team)]);
		opts.player = this;
		this.sprite = new PlayerSprite(opts);
		this.idle();
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
	

}
