/*
	Created by Tech_dog (ebontrop@gmail.com) om 11-Nov-2026 at 07:41:49.630, UTC+4, Batumi, Wednesday;
	This is virtual camera drawing wedge diagram JavaScript file;
*/
const canvas_high  = 512;
const canvas_width = canvas_high;
const image_hight  = 256;
const image_width  = image_hight;
const padding_horz = 128;
const padding_vert = padding_horz;

const draw_tria = false;
var   b_app_started = false;

function drawCross(ctx) {

	var grid = document.getElementById("can-grid");
	var overlay = document.getElementById("myCanvas");
	if (!grid || !overlay || !ctx)
		return;

	const x_center = overlay.left + (overlay.width / 2);
	const y_center = overlay.top  + (overlay.height / 2);

//	var ctx = grid.getContext("2d");

	ctx.lineWidth = 1;
	ctx.strokeStyle = "rgba(150, 150, 150, 0.4)";
	ctx.beginPath();

	ctx.moveTo(x_center, 0);
	ctx.lineTo(x_center, grid.height);
	ctx.closePath();
	ctx.stroke();
}

function drawGrid() {

	var canvas = document.getElementById("can-grid");
	var image  = document.getElementById("myImage");
	var gridSize = 50; // the distance between grid lines in pixels;

	if (!canvas || !canvas.getContext("2d") || !image)
		return;
	var ctx = canvas.getContext("2d");
	ctx.lineWidth = 1;
	ctx.strokeStyle = "rgba(200, 200, 200, 0.25)"; // sets very soft gray lines' color;
	ctx.clearRect(0, 0, canvas.width, canvas.height);

	// draws vertical grid lines;
	ctx.beginPath();
	for (var x = 0; x < canvas.width; x += gridSize) {
		ctx.moveTo(x, 0);
		ctx.lineTo(x, canvas.height);
	}

	// draws horizontal grid lines;
	for (var y = 0; y < canvas.height; y += gridSize) {
		ctx.moveTo(0, y);
		ctx.lineTo(canvas.width, y);
	}
	ctx.closePath();
	ctx.stroke();
}

function initApp() {
	var container = document.getElementById("dragContainer");
	var canvas = document.getElementById("myCanvas");
	var image  = document.getElementById("myImage");

	if (!container || !canvas || !image)
		return;

	if (b_app_started === false) {
		b_app_started = true;
		drawGrid();
	}

	var image_size  = image_hight;
	var canvas_size = canvas_high;

	// Forces internal drawing coordinates to match the {imgSize} box;
	canvas.width  = canvas_size;
	canvas.height = canvas_size;

	// step #1: centers the container on the screen;
	var initialLeft = (window.innerWidth - canvas_size) / 2;
	var initialTop = (window.innerHeight - canvas_size) / 2;

	container.style.left = initialLeft + "px";
	container.style.top  = initialTop + "px";

	// step #2: draws the equilateral triangle using {imgSize} grid math;
	var ctx = canvas.getContext("2d");
	ctx.clearRect(0, 0, canvas.width, canvas.height);
if (draw_tria === true) {
	// chooses a side width that fits safely inside a {imgSize} boundary;
	// the absolute mathematical maximum side width for a {imgSize} frame is ~110px.
	var sideWidth = 90; 

	var cx = canvas_size / 2;
	var cy = canvas_size / 2;

	// Precise Equilateral Height formula (side * 0.866):
	var triangleHeight = sideWidth * (Math.sqrt(3) / 2);

	// True bounding box vertical alignment limits:
	var yTop = cy - (triangleHeight / 2);
	var yBottom = cy + (triangleHeight / 2);

	var topLeft  = { x: cx - (sideWidth / 2), y: yTop };
	var topRight = { x: cx + (sideWidth / 2), y: yTop };
	var bottom   = { x: cx, y: yBottom };

	// executes the path;
	ctx.beginPath();
	ctx.moveTo(topLeft.x, topLeft.y);
	ctx.lineTo(topRight.x, topRight.y);
	ctx.lineTo(bottom.x, bottom.y);
	ctx.closePath();
} else {
/* how to calculate an arc() start and end angles:
	var radians = degrees * (Math.PI / 180); // angles must be in radians;
	Unlike standard Cartesian math where angles move counter-clockwise, the HTML5 Canvas default orientation moves clockwise:
	•   0° (0 Radians)     : 3 o'clock (East);
	•  90° (pi / 2 Radians): 6 o'clock (South);
	• 180° (pi Radians)    : 9 o'clock (West);
	• 270° (3 * pi / 2) Radians): 12 o'clock (North);
*/
	var shift_horz = 80; // it requires to put exactly the center at specified horizontal position;
	var shift_vert = 32; // it requires to put exactly the center at specified vertical position;

	var img_rect = image.getBoundingClientRect();
	var cx = img_rect.left + img_rect.width / 2 - shift_horz;
	var cy = canvas.height / 2 - shift_vert;

	var radius = 170;

	var start_angle = 320 * Math.PI / 180;
	var end_angle = 40 * Math.PI / 180;

	ctx.beginPath();
	ctx.moveTo(cx, cy); // connects arc back to center point;
	ctx.arc(cx, cy, radius, start_angle, end_angle, false);
	ctx.closePath();    // automatically draws line from end angle back to center;
}
	ctx.strokeStyle = "#ff0000";
	ctx.lineWidth = 1;
	ctx.fillStyle = "rgba(255, 0, 0, 0.1)";
	ctx.fill();

	ctx.stroke();

	// 3. Dragging Mechanics
	var isDragging = false;
	var offsetX = 0, offsetY = 0;

	container.onmousedown = function(e) {

		e = e || window.event;
		isDragging = true;

		offsetX = e.clientX - container.offsetLeft;
		offsetY = e.clientY - container.offsetTop;

		if (e.preventDefault) e.preventDefault();
			return false;
		};

	document.onmousemove = function(e) {

		if (!isDragging)
			return;
		e = e || window.event;

		var targetLeft = e.clientX - offsetX;
		var targetTop  = e.clientY - offsetY;

		var minLeft = -padding_horz;
		var minTop  = -padding_vert;

		var maxLeft = window.innerWidth  - canvas_width + padding_horz;
		var maxTop  = window.innerHeight - canvas_high + padding_vert;

		if (targetLeft < minLeft) targetLeft = minLeft;
		if (targetTop  < minTop) targetTop = minTop;

		if (targetLeft > maxLeft) targetLeft = maxLeft;
		if (targetTop  > maxTop ) targetTop = maxTop;

		container.style.left = targetLeft + "px";
		container.style.top = targetTop + "px";
	};

	document.onmouseup = function() {
		isDragging = false;
	};
}

function resizeGrid() {

	var canvas = document.getElementById("can-grid");
	if (!canvas)
		return;
	// Lookup the physical display size the browser gave the canvas via CSS
	var displayWidth  = canvas.clientWidth;
	var displayHeight = canvas.clientHeight;

	// Check if the internal resolution matches the actual display size
	if (canvas.width !== displayWidth || canvas.height !== displayHeight) {
		// Set internal resolution to match physical display size 1:1
		canvas.width  = displayWidth;
		canvas.height = displayHeight;

		// Changing canvas dimensions clears it automatically, so redraw the grid
		drawGrid();
	}
}

//if (window.attachEvent) { window.attachEvent('onload', initApp); } else { window.addEventListener('load', initApp, false); }
//if (window.attachEvent) { window.attachEvent('resize', resizeGrid); } else { window.addEventListener('load', resizeGrid, false); }
window.onload = initApp;
window.onresize = resizeGrid;