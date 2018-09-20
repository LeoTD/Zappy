const SpriteData = {};

SpriteData.bob = {
	assetPath: 'bob.png',
	getMaxSprites: () => 256,
	dimensions: {
		height: 32,
		width: 32,
	},
	size: 10,
	animations: {
		walk: function (legInterval) {
			this.playAnimation(
				{n:7,  e:13, s:1, w:19}[this.player.facing],
				{n:10, e:16, s:4, w:22}[this.player.facing],
				true,
				legInterval
			);
		},
		idle: function () {
			const startFrame = { n: 38, e: 44, s: 32, w: 50 }[this.player.facing];
			this.playAnimation(startFrame, startFrame + 3, true, 200);
		}
	}
};

SpriteData.eggs = {
	assetPath: 'egg.png',
	getMaxSprites: (game) => game.x * game.y * 10,
	dimensions: {
		height: 32,
		width: 32,
	}
};

SpriteData.food = {
	assetPath: 'food.png',
	getMaxSprites: (game) => game.x * game.y * 10,
	dimensions: {
		height: 384,
		width: 427,
	}
};

SpriteData.stone0 = {
	assetPath: 'stone0.png',
	getMaxSprites: (game) => game.x * game.y * 10,
	dimensions: {
		height: 89,
		width: 67
	}
};

SpriteData.stone1 = {
	assetPath: 'stone1.png',
	getMaxSprites: (game) => game.x * game.y * 10,
	dimensions: {
		height: 114,
		width: 123
	}
};

SpriteData.stone2 = {
	assetPath: 'stone2.png',
	getMaxSprites: (game) => game.x * game.y * 10,
	dimensions: {
		height: 120,
		width: 120
	}
};

SpriteData.stone3 = {
	assetPath: 'stone3.png',
	getMaxSprites: (game) => game.x * game.y * 10,
	dimensions: {
		height: 89,
		width: 107
	}
};

SpriteData.stone4 = {
	assetPath: 'stone4.png',
	getMaxSprites: (game) => game.x * game.y * 10,
	dimensions: {
		height: 500,
		width: 500
	}
};

SpriteData.stone5 = {
	assetPath: 'stone5.png',
	getMaxSprites: (game) => game.x * game.y * 10,
	dimensions: {
		height: 155,
		width: 155
	}
};
