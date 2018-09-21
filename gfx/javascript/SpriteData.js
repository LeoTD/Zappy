const SpriteData = {};

function facingCamera(facing) {
	return facing === 's' || facing === 'e';
}

function shouldInvert(facing) {
	return facing === 'n' || facing === 'e';
}

const fftaPlayerSprite = (path) => ({
	assetPath: path,
	getMaxSprites: () => 2000,
	dimensions: {
		width: 32,
		height: 32,
	},
	size: 8,
	animations: {
		walk: function (legInterval) {
			let startFrame = 2;
			if (facingCamera(this.player.facing))
				startFrame += 4;
			if (this.player.team % 2 !== 0)
				startFrame += 8;
			this.invertU = shouldInvert(this.player.facing);
			this.playAnimation(
				startFrame,
				startFrame + 1,
				true,
				legInterval * 2,
				this.idle
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
});

SpriteData.blackMage = fftaPlayerSprite(
	'player-sprites/human-blackmage/human-blackmage-sheet.png'
);

SpriteData.mogKnight = fftaPlayerSprite(
	'player-sprites/moogle-mogknight/moogle-mogknight-sheet.png'
);

SpriteData.bangaa = fftaPlayerSprite(
	'player-sprites/bangaa-warrior/bangaa-warrior-sheet.png'
);

SpriteData.eggs = {
	assetPath: 'egg0.png',
	getMaxSprites: (game) => 2000,
	dimensions: {
		height: 200,
		width: 240,
	}
};

SpriteData.food = {
	assetPath: 'meat-small.png',
	getMaxSprites: (game) => 2000,
	dimensions: {
		height: 32,
		width: 32,
	},
	yOffsetOverride: 2.7,
	size: 5,
};

const fftaStone = (path) => ({
	assetPath: `stones/${path}`,
	getMaxSprites: (game) => 2000,
	dimensions: {
		height: 14,
		width: 12,
	},
	yOffsetOverride: 1.5,
	size: 3,
});

SpriteData.stone0 = fftaStone('ffta-stone-blue.png');
SpriteData.stone1 = fftaStone('ffta-stone-bluegreen.png');
SpriteData.stone2 = fftaStone('ffta-stone-green.png');
SpriteData.stone3 = fftaStone('ffta-stone-sunset.png');
SpriteData.stone4 = fftaStone('ffta-stone-fairypink.png');
SpriteData.stone5 = fftaStone('ffta-stone-fireplum.png');

SpriteData.put = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.putFail = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.take = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.takeFail = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.inventory = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.broadcast = {
	assetPath: 'broadcast.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 50,
		width: 50
	}
};

SpriteData.see = {
	assetPath: 'see.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 120,
		width: 120
	}
};

SpriteData.kick = {
	assetPath: 'kick.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 225,
		width: 225,
	}
};

SpriteData.kickFail = {
	assetPath: 'kick.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 225,
		width: 225,
	}
};

SpriteData.incant = {
	assetPath: 'death.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 120,
		width: 120,
	}
};

SpriteData.incantFail = {
	assetPath: 'death.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 120,
		width: 120,
	}
};

SpriteData.death = {
	assetPath: 'death.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 120,
		width: 120,
	}
};

SpriteData.fork = {
	assetPath: 'egg0.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 200,
		width: 240
	}
};

SpriteData.fail = {
	assetPath: 'fail.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 334,
		width: 334
	}
};
