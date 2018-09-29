
function createCustomCamera(canvas, scene) {
	// This creates and positions a free camera (non-mesh)

	// try of isometric camera - GERARDO MODS
	var camera = new BABYLON.FreeCamera("camera1", new BABYLON.Vector3(200, 200, 200), scene);

	// This attaches the camera to the canvas
	camera.attachControl(canvas, true);

	// Remove default keyboard:
	camera.inputs.removeByType("FreeCameraKeyboardMoveInput");

	// Create our own manager:
	var customCameraInput = function () {
		this._keys			= [];
		this.keysLeft		= [65];
		this.keysRight		= [68];
		this.keysUp			= [87];
		this.keysDown		= [83];
		this.keysPlus		= [81];
		this.keysMinus		= [69];
		this.sensibility	= 3;
	};

	// Hooking keyboard events
	customCameraInput.prototype.attachControl = function (element, noPreventDefault) {
		var _this = this;
		if (!this._onKeyDown) {
			element.tabIndex = 1;
			this._onKeyDown = function (evt) {
				if (_this.keysUp.indexOf(evt.keyCode) !== -1 ||
					_this.keysDown.indexOf(evt.keyCode) !== -1 ||
					_this.keysLeft.indexOf(evt.keyCode) !== -1 ||
                    _this.keysRight.indexOf(evt.keyCode) !== -1	||
                    _this.keysPlus.indexOf(evt.keyCode) !== -1	||
                    _this.keysMinus.indexOf(evt.keyCode) !== -1	) {
					var index = _this._keys.indexOf(evt.keyCode);
					if (index === -1) {
						_this._keys.push(evt.keyCode);
					}
					if (!noPreventDefault) {
						evt.preventDefault();
					}
				}
			};
			this._onKeyUp = function (evt) {
				if (_this.keysUp.indexOf(evt.keyCode) !== -1	||
					_this.keysDown.indexOf(evt.keyCode) !== -1	||
                    _this.keysLeft.indexOf(evt.keyCode) !== -1	||
                    _this.keysRight.indexOf(evt.keyCode) !== -1	||
                    _this.keysPlus.indexOf(evt.keyCode) !== -1	||
                    _this.keysMinus.indexOf(evt.keyCode) !== -1	) {
					var index = _this._keys.indexOf(evt.keyCode);
					if (index >= 0) {
						_this._keys.splice(index, 1);
					}
					if (!noPreventDefault) {
						evt.preventDefault();
					}
				}
			};

			element.addEventListener("keydown", this._onKeyDown, false);
			element.addEventListener("keyup", this._onKeyUp, false);
			BABYLON.Tools.RegisterTopRootEvents([
				{ name: "blur", handler: this._onLostFocus }
			]);
		}
	};

	// This function is called by the system on every frame
	customCameraInput.prototype.checkInputs = function () {
		if (this._onKeyDown) {
			var camera = this.camera;
			// Keyboard
			for (var index = 0; index < this._keys.length; index++) {
				var keyCode = this._keys[index];
				var cam_x = camera.getTarget().subtract(camera.position).x;
				var cam_y = camera.getTarget().subtract(camera.position).y;
				var cam_z = camera.getTarget().subtract(camera.position).z;
				if (cam_x > 0)
					cam_x = cam_x * cam_x / (1 - cam_y * cam_y);
				else
					cam_x = -1 * cam_x * cam_x / (1 - cam_y * cam_y);
				if (cam_z > 0)
					cam_z = cam_z * cam_z / (1 - cam_y * cam_y);
				else
					cam_z = -1 * cam_z * cam_z / (1 - cam_y * cam_y);
				if (this.keysUp.indexOf(keyCode) !== -1) {
					camera.position.x += this.sensibility * cam_x;
					camera.position.z += this.sensibility * cam_z;
				}
				if (this.keysDown.indexOf(keyCode) !== -1) {
					camera.position.x -= this.sensibility * cam_x;
					camera.position.z -= this.sensibility * cam_z;
				}
				if (this.keysLeft.indexOf(keyCode) !== -1) {
					camera.position.x -= this.sensibility * cam_z;
					camera.position.z += this.sensibility * cam_x;
				}
				if (this.keysRight.indexOf(keyCode) !== -1) {
					camera.position.x += this.sensibility * cam_z;
					camera.position.z -= this.sensibility * cam_x;
				}
				if (this.keysMinus.indexOf(keyCode) !== -1) {
					if (camera.mode !== BABYLON.Camera.ORTHOGRAPHIC_CAMERA) {
						camera.position.y += this.sensibility;
					}
				}
				if (this.keysPlus.indexOf(keyCode) !== -1) {
					if (camera.mode !== BABYLON.Camera.ORTHOGRAPHIC_CAMERA) {
						camera.position.y -= this.sensibility;
					}
				}
			}
		}
	};
	customCameraInput.prototype.getTypeName = function () {
		return "customCameraInput";
	};
	customCameraInput.prototype._onLostFocus = function (e) {
		this._keys = [];
	};
	customCameraInput.prototype.getSimpleName = function () {
		return "customInput";
	};

	// Connect to camera:
	camera.inputs.add(new customCameraInput());
}
