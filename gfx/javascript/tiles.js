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
		const sdataEntry = SpriteData[type];
		const offset = Tile.generateContentSpriteOffset();
		sp.position.x = this.y * game.tileSize + offset.y;
		if (sdataEntry.yOffsetOverride)
			sp.position.y = sdataEntry.yOffsetOverride;
		else
			sp.position.y = sdataEntry.dimensions.height / 2;
		sp.position.z = this.x * game.tileSize + offset.x;
		sp.size = sdataEntry.size;
		this.contentSprites[type].push(sp);
	}

	static generatePlayerSpriteOffset() {
		let y = randomInNonnegativeRange(0.05, 0.3) * game.tileSize * -1;
		let x = randomInNonnegativeRange(0, 0.3) * game.tileSize;
		if (Math.random() < 0.5)
			x *= -1;
		return { x, y };
	}

	static generateContentSpriteOffset() {
		let y = randomInNonnegativeRange(0.05, 0.3) * game.tileSize;
		let x = randomInNonnegativeRange(0, 0.3) * game.tileSize;
		if (Math.random() < 0.5)
			x *= -1;
		return { x, y };
	}
}

function randomInNonnegativeRange(min, max) {
	return Math.random() * (max - min) + min;
}
