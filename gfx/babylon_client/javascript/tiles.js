class Tile {
	constructor(opts, SM) {
		
		this.x					= opts.x;
		this.y					= opts.y;

		this.tileCenter			= {
			x:(this.x * TILE_SIZE),
			y:(this.y * TILE_SIZE)
		}

		this.eggs				= opts.eggs;
		this.inventory			= opts.inventory;

		// Sprite Managers for tile contents. 0-5 stones{0-5}. 6 food.
		if (!SM){
			throw 'Ya dun goofed';
		}
		this.contentSM			= [
			SM[0],
			SM[1],
			SM[2],
			SM[3],
			SM[4],
			SM[5],
			SM[6],
		];

		this.contentSprites		= [];
	}

	_hard_update() {
		this.contentSprites = [];
		for (var i = 0; i < 7; i++) {
			this.contentSprites[i] = {}
			this.contentSM[i].dispose();

			this.contentSprites.sml = new BABYLON.Sprite("inv" + i + "sml", this.contentSM[i])
			this.contentSprites.sml.size		= 4;
			this.contentSprites.sml.position.y	= 2;
			this.contentSprites.sml.position.x	= this.tileCenter.x + (TILE_SIZE / 3);
			this.contentSprites.sml.position.z	= this.tileCenter.x + (TILE_SIZE / 3);
			this.contentSprites.sml.isVisible	= false;
			if (this.inventory[i] > 0) {
				this.contentSprites.sml.isVisible = true;
			}
			this.contentSprites.med = new BABYLON.Sprite("inv" + i + "med", this.contentSM[i])
			this.contentSprites.med.size		= 4;
			this.contentSprites.med.position.y	= 2;
			this.contentSprites.med.position.x	= this.tileCenter.x + (TILE_SIZE / 3);
			this.contentSprites.med.position.z	= this.tileCenter.x + (TILE_SIZE / 3);
			this.contentSprites.med.isVisible	= false;
			if (this.inventory[i] > 0) {
				this.contentSprites.med.isVisible = true;
			}
			this.contentSprites.lrg = new BABYLON.Sprite("inv" + i + "lrg", this.contentSM[i])
			this.contentSprites.lrg.size		= 4;
			this.contentSprites.lrg.position.y	= 2;
			this.contentSprites.lrg.position.x	= this.tileCenter.x + (TILE_SIZE / 3);
			this.contentSprites.lrg.position.z	= this.tileCenter.x + (TILE_SIZE / 3);
			this.contentSprites.lrg.isVisible	= false;
			if (this.inventory[i] > 0) {
				this.contentSprites.lrg.isVisible = true;
			}
		}
	}	
}
