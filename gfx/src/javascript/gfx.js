var TileSize = 2;
var MapInfo = {rows:16, cols:16};

document.addEventListener("DOMContentLoaded", function(event) {
	console.log("DOM fully loaded and parsed");
	initGfx();
});

function initGfx() {
	var canvas = document.getElementById("renderCanvas"); // Get the canvas element 
	var engine = new BABYLON.Engine(canvas, true); // Generate the BABYLON 3D engine

	var scene = createScene(engine, canvas); //Get the scene variable. Day 1. Let there be light.
	createBoard(scene);
	createSprites(scene);

	// Register a render loop to repeatedly render the scene
	engine.runRenderLoop(function () { 
			scene.render();
	});

	// Watch for browser/canvas resize events
	window.addEventListener("resize", function () { 
			engine.resize();
	});
}

function createScene() {

	// Create the scene space
	var scene = new BABYLON.Scene(arguments[0]);

	// Add a camera to the scene and attach it to the canvas
	var camera = new BABYLON.ArcRotateCamera("Camera", Math.PI / 2, Math.PI / 2, 50, new BABYLON.Vector3(0,0,0), scene);
	camera.attachControl(arguments[1], true);

	// Add lights to the scene
	var light1 = new BABYLON.HemisphericLight("light1", new BABYLON.Vector3(1, 1, 0), scene);
	var light2 = new BABYLON.PointLight("light2", new BABYLON.Vector3(0, 1, -1), scene);

	return scene;
};

function createBoard(scene) {

	var box = BABYLON.MeshBuilder.CreateBox("box", {height:0.5, width:TileSize * MapInfo.rows, depth:TileSize * MapInfo.cols}, scene);
	box.position = {x:((MapInfo.rows / 2) - 0.5) * TileSize, y:-0.7, z:((MapInfo.cols / 2) - 0.5) * TileSize};

	var materialPlane = new BABYLON.StandardMaterial("texturePlane", scene);
	materialPlane.diffuseTexture = new BABYLON.Texture("assets/tile.png", scene);
	materialPlane.diffuseTexture.uScale = MapInfo.rows;//Repeat 1 times on the Vertical Axes
	materialPlane.diffuseTexture.vScale = MapInfo.cols;//Repeat 1 times on the Horizontal Axes
	box.material = materialPlane;

}

function createSprites(scene) {
	var MAX_SPRITES = 350000;
	var img_dimensions = {height:24, width:24};

	var dinoSpriteManager = new BABYLON.SpriteManager("dinoManager", "assets/dino_blue.png", MAX_SPRITES, img_dimensions, scene);

    // First animated player
    var player = new BABYLON.Sprite("player", dinoSpriteManager);
    player.playAnimation(0, 3, true, 100);
    player.position.y = 0;
    player.size = 1;
    player.isPickable = true;
}
