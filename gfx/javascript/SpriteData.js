const SpriteData = {};

function facingCamera(facing) {
	return facing === 's' || facing === 'e';
}

function shouldInvert(facing) {
	return facing === 'n' || facing === 'e';
}

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

const genericFftaSpriteData = {
	getMaxSprites: () => 1000,
	dimensions: {
		width: 64,
		height: 64,
	},
	size: 25,
	animations: {
		walk: function (legInterval) {
			let startFrame = 1;
			if (facingCamera(this.player.facing))
				startFrame += 4;
			if (this.player.team % 2 !== 0)
				startFrame += 8;
			this.invertU = shouldInvert(this.player.facing);
			this.playAnimation(
				startFrame,
				startFrame + 2,
				true,
				legInterval
			);
		},
		idle: function () {
			this.cellIndex = 1;
			if (facingCamera(this.player.facing))
				this.cellIndex += 4;
			if (this.player.team % 2 !== 0)
				this.cellIndex += 8;
			this.invertU = shouldInvert(this.player.facing);
		}
	}
};

SpriteData.blackMage = {
	assetPath: 'player-sprites/human-blackmage/human-blackmage-sheet.png',
};
Object.assign(SpriteData.blackMage, genericFftaSpriteData);

SpriteData.mogKnight = {
	assetPath: 'player-sprites/moogle-mogknight/moogle-mogknight-sheet.png',
};
Object.assign(SpriteData.mogKnight, genericFftaSpriteData);

SpriteData.bangaa = {
	assetPath: 'player-sprites/bangaa-warrior/bangaa-warrior-sheet.png',
};
Object.assign(SpriteData.bangaa, genericFftaSpriteData);

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
