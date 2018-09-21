class Tile {
	constructor(opts) {
		this.x					= opts.x;
		this.y					= opts.y;
		this.inventory = {
			eggs: 0,
			food: 0,
			stone0: 0,
			stone1: 0,
			stone2: 0,
			stone3: 0,
			stone4: 0,
			stone5: 0
		};
		this.contentSprites		= {
			eggs: [],
			food: [],
			stone0: [],
			stone1: [],
			stone2: [],
			stone3: [],
			stone4: [],
			stone5: [],
		};
	}

	get center() {
		return { x: this.x * game.tileSize, y: this.y * game.tileSize };
	}

	removeContent(type, amt) {
		this.inventory[type] -= amt;
		for (var i = 0; i < amt; i++) {
			this.removeContentSprite(type);
		}
	}

	removeContentSprite(type) {
		const sp = this.contentSprites[type].shift();
		if (sp) {
			sp.dispose();
		}
	}

	addContent(type, amt) {
		this.inventory[type] += amt;
		for (var i = 0; i < amt; i++) {
			this.addContentSprite(type);
		}
	}

	addContentSprite(type) {
		const sp = new BABYLON.Sprite(type, game.getContentSpriteManagerFor(type));
		sp.position.x = this.y * (game.tileSize + Math.random() * 2 - 1);
		sp.position.y = 5;
		sp.position.z = this.x * (game.tileSize + Math.random() * 2 - 1);
		sp.size = 3;
		this.contentSprites[type].push(sp);
	}
}
