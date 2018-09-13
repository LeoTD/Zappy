function displayAxes(scene, size) {
	// show axis
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

function createBoardTiledGround(scene) {
	var tiledGround = new BABYLON.MeshBuilder.CreateTiledGround("Tiled Ground", {xmin: 0, zmin: 0, xmax: 3, zmax: 3,
																		subdivisions:{w:MapInfo.cols, h:MapInfo.rows}}, scene);
	
	var materialPlane = new BABYLON.StandardMaterial("texturePlane", scene);
	materialPlane.diffuseTexture = new BABYLON.Texture("assets/tile.png", scene);
	tiledGround.material = materialPlane;
}

function createBoardSingleMesh(scene) {

	var box = BABYLON.MeshBuilder.CreateBox("box", {height:0.5, width:TileSize * MapInfo.rows, depth:TileSize * MapInfo.cols}, scene);
	box.position = {x:((MapInfo.rows / 2) - 0.5) * TileSize, y:-0.7, z:((MapInfo.cols / 2) - 0.5) * TileSize};

	var materialPlane = new BABYLON.StandardMaterial("texturePlane", scene);
	materialPlane.diffuseTexture = new BABYLON.Texture("assets/tile.png", scene);
	materialPlane.diffuseTexture.uScale = MapInfo.cols;//Repeat {cols} times on the Vertical Axes
	materialPlane.diffuseTexture.vScale = MapInfo.rows;//Repeat {rows} times on the Horizontal Axes
	box.material = materialPlane;

}

function createBoardMultiMesh(scene) {
	var tiles = [];

	for (var i = 0; i < MapInfo.rows; i++) {
		var new_row = [];
		for (var k = 0; k < MapInfo.cols; k++) {
			new_row[k] = BABYLON.MeshBuilder.CreateBox("box", {height:0.5, width:TileSize, depth:TileSize}, scene);
			new_row[k].position = {x:(i * TileSize), y:-0.7, z:(k * TileSize)};
		
			var materialPlane = new BABYLON.StandardMaterial("texturePlane", scene);
			materialPlane.diffuseTexture = new BABYLON.Texture("assets/tile.png", scene);
			materialPlane.diffuseTexture.uScale = 1;
			materialPlane.diffuseTexture.vScale = 1;
			new_row[k].material = materialPlane;
		}
		tiles.push(new_row);
	}
}
