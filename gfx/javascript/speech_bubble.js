class speechBubble {
	constructor(managers, player) {

		this.p				= player;
		this.m				= {
			put:		managers.put,
			putFail:	managers.putFail,
			take:		managers.take,
			takeFail:	managers.takeFail,
			inventory:	managers.inventory,
			broadcast:	managers.broadcast,
			see:		managers.see,
			kick:		managers.kick,
			kickFail:	managers.kickFail,
			incant:		managers.incant,
			incantFail:	managers.incantFail,
			fork:		managers.fork,
		};

		this.s				= {
			put:		undefined,
			putFail:	undefined,
			take:		undefined,
			takeFail:	undefined,
			inventory:	undefined,
			broadcast:	undefined,
			see:		undefined,
			kick:		undefined,
			kickFail:	undefined,
			incant:		undefined,
			incantFail:	undefined,
			fork:		undefined,
		}
	}

	cmdPopup(key) {
		this.updatePosition(key);
		this.s[key].isVisible = true;

		const cascade = new BABYLON.Animation("cascadePopup",
			'position.y',
			15 * game.tickrate,
			BABYLON.Animation.ANIMATIONTYPE_FLOAT,
			BABYLON.Animation.ANIMATIONLOOPMODE_CONSTANT
		);
		const start = this.s[key].position.y;
		const end = 0;
		fade.setKeys([
			{ frame: 0, value: start },
			{ frame: 50, value: start},
			{ frame: 100, value: end }
		]);

		const fade = new BABYLON.Animation("fadePopup",
			'color.a',
			15 * game.tickrate,
			BABYLON.Animation.ANIMATIONTYPE_FLOAT,
			BABYLON.Animation.ANIMATIONLOOPMODE_CONSTANT
		);
		const start = this.s[key].color.a;
		const end = 0;
		fade.setKeys([
			{ frame: 0, value: start },
			{ frame: 50, value: start},
			{ frame: 100, value: end }
		]);

		game.scene.beginDirectAnimation(
			this.s[key],
			[fade, cascade],
			0,
			100,
			false,
			1,
			() => {
				this.s[key].isVisible = false;
				this.updatePosition(key);
			}
		);
	}

	init() {
		for (let key in this.m) {
			this.s[key] = new BABYLON.Sprite(key, this.m[key]);
			this.s[key].isVisible = false;
			this.updatePosition(key);
		}
	}

	updatePosition(key) {
		this.s[key].position = this.p.sprite.position;
		this.s[key].position.y += this.p.sprite.size;
	}

}
