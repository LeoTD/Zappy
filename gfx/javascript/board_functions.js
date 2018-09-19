const TILE_SIZE 	= 25;
const TILE_ASSET	= "tile.png";

class Board {
	constructor(opts) {
		this._mesh		= undefined;
	}
	
	displayAxes(scene, size) {
		var makeTextPlane = function (text, color, size) {
			var dynamicTexture = new BABYLON.DynamicTexture("DynamicTexture", 50, scene, true);
			dynamicTexture.hasAlpha = true;
			dynamicTexture.drawText(text, 5, 40, "bold 36px Arial", color, "transparent", true);
			var plane = new BABYLON.Mesh.CreatePlane("TextPlane", size, scene, true);
			plane.material = new BABYLON.StandardMaterial("TextPlaneMaterial", scene);
			plane.material.backFaceCulling = false;
			plane.material.specularColor = new BABYLON.Color3(0, 0, 0);
			plane.material.diffuseTexture = dynamicTexture;
			return plane;
		};

		var axisX = BABYLON.Mesh.CreateLines("axisX", [
			new BABYLON.Vector3.Zero(), new BABYLON.Vector3(size, 0, 0), new BABYLON.Vector3(size * 0.95, 0.05 * size, 0),
			new BABYLON.Vector3(size, 0, 0), new BABYLON.Vector3(size * 0.95, -0.05 * size, 0)
		], scene);
		axisX.color = new BABYLON.Color3(1, 0, 0);
		var xChar = makeTextPlane("X", "red", size / 10);
		xChar.position = new BABYLON.Vector3(0.9 * size, 0.05 * size, 0);
		var axisY = BABYLON.Mesh.CreateLines("axisY", [
			new BABYLON.Vector3.Zero(), new BABYLON.Vector3(0, size, 0), new BABYLON.Vector3(-0.05 * size, size * 0.95, 0),
			new BABYLON.Vector3(0, size, 0), new BABYLON.Vector3(0.05 * size, size * 0.95, 0)
		], scene);
		axisY.color = new BABYLON.Color3(0, 1, 0);
		var yChar = makeTextPlane("Y", "green", size / 10);
		yChar.position = new BABYLON.Vector3(0, 0.9 * size, -0.05 * size);
		var axisZ = BABYLON.Mesh.CreateLines("axisZ", [
			new BABYLON.Vector3.Zero(), new BABYLON.Vector3(0, 0, size), new BABYLON.Vector3(0, -0.05 * size, size * 0.95),
			new BABYLON.Vector3(0, 0, size), new BABYLON.Vector3(0, 0.05 * size, size * 0.95)
		], scene);
		axisZ.color = new BABYLON.Color3(0, 0, 1);
		var zChar = makeTextPlane("Z", "blue", size / 10);
		zChar.position = new BABYLON.Vector3(0, 0.05 * size, 0.9 * size);
	}

	createMesh(dim, scene) {

		this._mesh = BABYLON.MeshBuilder.CreateBox("board", {height:0.5, width:TILE_SIZE * dim.y, depth:TILE_SIZE * dim.x}, scene);
		this._mesh.position = {x:((dim.y / 2) - 0.5) * TILE_SIZE, y:-0.7, z:((dim.x / 2) - 0.5) * TILE_SIZE};

		var tileTexture = new BABYLON.StandardMaterial("tileTexture", scene);
		tileTexture.diffuseTexture = new BABYLON.Texture(TILE_ASSET, scene);
		tileTexture.diffuseTexture.uScale = dim.x; //Repeat {x} times on the Vertical Axes
		tileTexture.diffuseTexture.vScale = dim.y; //Repeat {y} times on the Horizontal Axes
		this._mesh.material = tileTexture;
	}
}
