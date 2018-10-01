class speechBubble {
	constructor(player) {

		this.p = player;

		this.s = {
			put: undefined,
			take: undefined,
			inventory:	undefined,
			broadcast:	undefined,
			see: undefined,
			kick: undefined,
			incant: undefined,
			incantFail:	undefined,
			fork: undefined,
			layEgg: undefined,
			doneLayingEgg: undefined,
			eggHatch:	undefined,
			death: undefined,
			fail: undefined,
		};
	}

	cmdPopup(key) {
		SpriteData[key].manager.renderingGroupId = 1;
		this.s[key] = new BABYLON.Sprite(key, SpriteData[key].manager);
		this.s[key].color.a = 1;
		this.s[key].size = 5;
		this.updatePosition(key);
		this.s[key].isVisible = true;

		const cascade = new BABYLON.Animation("cascadePopup",
			'position.y',
			15 * game.tickrate,
			BABYLON.Animation.ANIMATIONTYPE_FLOAT,
			BABYLON.Animation.ANIMATIONLOOPMODE_CONSTANT
		);
		var start = this.s[key].position.y;
		var end = start / 2;
		cascade.setKeys([
			{ frame: 0, value: start },
			{ frame: 40, value: start },
			{ frame: 75, value: ((end - start) / 2) + start},
			{ frame: 100, value: end }
		]);

		const fade = new BABYLON.Animation("fadePopup",
			'color.a',
			15 * game.tickrate,
			BABYLON.Animation.ANIMATIONTYPE_FLOAT,
			BABYLON.Animation.ANIMATIONLOOPMODE_CONSTANT
		);
		start = 1;
		end = 0;
		fade.setKeys([
			{ frame: 0, value: start },
			{ frame: 50, value: start},
			{ frame: 100, value: end }
		]);

		game.scene.beginDirectAnimation(
			this.s[key],
			[cascade, fade],
			0,
			100,
			false,
			1,
			() => {
				this.s[key].dispose();
			}
		);
	}

	updatePosition(key) {
		this.s[key].position.x = this.p.sprite.position.x;
		this.s[key].position.y = this.p.sprite.position.y;
		this.s[key].position.z = this.p.sprite.position.z;

		this.s[key].position.y += this.p.sprite.size;
	}

}
