class BobSprite extends BABYLON.Sprite {
	constructor(player, manager) {
		super("player", manager);
		this.size = 10;
		this.player = player;
		const zone_width = (game.tileSize) - (this.size);
		const zone_height= (game.tileSize / 2);
		const w_offset   = (game.tileSize / 2) - (this.size / 2);
		const h_offset   = (game.tileSize / 3);
		this.player.spriteOffsets = {
			x:(Math.random() * zone_width) - w_offset,
			y:(Math.random() * zone_height) - h_offset
		};
		this.position.y = 5;
		this.position.z = (this.player.x * game.tileSize) + this.player.spriteOffsets.x;
		this.position.x = (this.player.y * game.tileSize) + this.player.spriteOffsets.y;
		this.isPickable = true;
	}

	resetAndIdle() {
		this.stopAnimation();
		this.position.x = this.player.y * game.tileSize + this.player.spriteOffsets.y;
		this.position.z = this.player.x * game.tileSize + this.player.spriteOffsets.x;
		this.idleAnimation();
	}

	advanceAnimation() {
		this.playWalkAnimation(100);
		this.slideInDirection({
			direction: this.player.facing,
			speed: 1,
			onAnimationEnd: this.resetAndIdle.bind(this)
		});
	}

	getKickedAnimation(direction) {
		this.resetAndIdle();
		this.playWalkAnimation(10); // kick frantically
		this.slideInDirection({
			direction,
			speed: 6,
			onAnimationEnd: this.resetAndIdle.bind(this)
		});
	}

	playWalkAnimation(legInterval) {
		this.playAnimation(
			{n:7,  e:13, s:1, w:19}[this.player.facing],
			{n:10, e:16, s:4, w:22}[this.player.facing],
			true,
			legInterval
		);
	}

	slideInDirection({ direction, speed, onAnimationEnd }) {
		const axis = ['n', 's'].includes(direction) ? "x" : "z";
		const slide = new BABYLON.Animation("slidePlayer",
			`position.${axis}`,
			15 * game.tickrate,
			BABYLON.Animation.ANIMATIONTYPE_FLOAT,
			BABYLON.Animation.ANIMATIONLOOPMODE_CONSTANT
		);
		const start = this.position[axis];
		const end = start + game.tileSize * { n: -1, w: -1, s: 1, e: 1}[direction];
		slide.setKeys([
			{ frame: 0, value: start },
			{ frame: 100, value: end }
		]);
		game.scene.beginDirectAnimation(
			this,
			[slide],
			0,
			100,
			false,
			speed,
			onAnimationEnd
		);
	}

	idleAnimation() {
		const startFrame = { n: 38, e: 44, s: 32, w: 50 }[this.player.facing];
		this.playAnimation(startFrame, startFrame + 3, true, 200);
	}
}
