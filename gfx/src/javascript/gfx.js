var TileSize = 25;
var MapInfo = {rows:16, cols:16};

document.addEventListener("DOMContentLoaded", function(event) {
	console.log("DOM fully loaded and parsed");
	initGfx();
});

function initGfx() {
	var canvas = document.getElementById("renderCanvas"); // Get the canvas element 
	var engine = new BABYLON.Engine(canvas, true); // Generate the BABYLON 3D engine

	var scene = createScene(engine);
	
	// Types of Cameras:
	createArcCamera(canvas, scene); // Mouse control around a point. Arrows to pan.
//	createCustomCamera(canvas, scene); // fixed angle and height. No mouse. Panning with arrow keys.

	// Display x, y, z axis arrows at origin.
	displayAxes(scene, 50);

	// Different types of boards:
	createBoardSingleMesh(scene);
//	createBoardTiledGround(scene);

	// Create sprite manager. This loads the texture and sets sprites to clickable.
	var sprite_manager = prepareSpriteManager(scene);

	var test_player = new playerAvatar(sprite_manager, {x:0, y:0, inv:[1260, 0, 0, 0, 0, 0, 0], level:1, team:1});

	test_player.createSprite();
//	test_player.createAvatar(scene);
//	test_player.createCreatureAvatar(scene);



	// Register a render loop to repeatedly render the scene
	engine.runRenderLoop(function () {
			if (scene) scene.render();
	});

	// Watch for browser/canvas resize events
	window.addEventListener("resize", function () { 
			engine.resize();
	});
}

function createScene(engine) {

	// Create the scene space
	var scene = new BABYLON.Scene(engine);

	// Add lights to the scene
	var light1 = new BABYLON.HemisphericLight("light1", new BABYLON.Vector3(1, 1, 0), scene);
//	var light2 = new BABYLON.PointLight("light2", new BABYLON.Vector3(0, 1, -1), scene);

	return scene;
};

function prepareSpriteManager(scene) {
	var MAX_SPRITES = 350000;
	var img_dimensions = {height:24, width:24};

	var dinoSpriteManager = new BABYLON.SpriteManager("dinoManager", "assets/dino_blue.png", MAX_SPRITES, img_dimensions, scene);

	dinoSpriteManager.isPickable = true;
	scene.onPointerDown = function (evt) {
		var pickResult = scene.pickSprite(this.pointerX, this.pointerY);
		if (pickResult.hit) {
			pickResult.pickedSprite.position.x += TileSize;
		}
	};

	return dinoSpriteManager;
}
