/*
	Created by Tech_dog (ebontrop@gmail.com) om 08-Nov-2026 at 17:17:53.278, UTC+4, Batumi, Sunday;
	This is virtual camera drawing draggable shapes JavaScript file;
*/
var circle   = document.getElementById("circle");    // a circle basic shape canvas;
var image    = document.getElementById("myImage");   // this an image object;   
var square   = document.getElementById("square");    // a square basic shape canvas;
var triangle = document.getElementById("triangle");  // a triangle basic shape canvas;
var bg_layer = document.getElementById("bkg-layer"); // background canvas which has viewport size;

var act_element = null;
var offsetX = 0;
var offsetY = 0;

var z_index = 4; // should take into account what the last z-index value is set in CSS file;

function drawCircle() {

	if (!circle) {
		alert('drawCircle(): circle canvas does not exist!'); return;
	}

	const ctx = circle.getContext('2d');

	const border_thick = 1;

	const x_center = circle.width  / 2 + border_thick;
	const y_center = circle.height / 2 + border_thick;
	const n_radius = x_center - border_thick * 3;
/* how to calculate an arc() start and end angles:
	var radians = degrees * (Math.PI / 180); // angles must be in radians;
	Unlike standard Cartesian math where angles move counter-clockwise, the HTML5 Canvas default orientation moves clockwise:
	•   0° (0 Radians)     : 3 o'clock (East);
	•  90° (pi / 2 Radians): 6 o'clock (South);
	• 180° (pi Radians)    : 9 o'clock (West);
	• 270° (3 * pi / 2) Radians): 12 o'clock (North);
*/
	ctx.beginPath();
	ctx.arc(x_center, y_center, n_radius, 0, Math.PI * 2, false);

	ctx.fillStyle = "rgba(255, 0, 0, 0.3)";
	ctx.fill();
	ctx.lineWidth = border_thick;
	ctx.strokeStyle = "#f00";
	ctx.stroke();
	// starts to draw a wedge (pie slice);
	const angle_0 = -60 * Math.PI / 180;
	const angle_1 =  30 * Math.PI / 180;	

	ctx.beginPath();
	ctx.moveTo(x_center, y_center);
	ctx.arc(x_center, y_center, n_radius, angle_0, angle_1, false);
	ctx.closePath();

	ctx.fillStyle = "rgba(255, 0, 255, 0.3)";
	ctx.fill();
	ctx.lineWidth = border_thick;
	ctx.strokeStyle = "#f00";
	ctx.stroke();
}

function drawCross (x_center, y_center) {

	if (!bg_layer) {
		alert('drawCross(): bg_layer canvas does not exist!'); return;
	}
	const ctx = bg_layer.getContext('2d');
	ctx.fillStyle = "rgba(239, 68, 68, 0.3)";

	x_center = Math.round(x_center);
	y_center = Math.round(y_center);

	ctx.clearRect(0, 0, bg_layer.width, bg_layer.height);

	ctx.fillRect(x_center, 0, 1, bg_layer.height);
	ctx.fillRect(0, y_center, bg_layer.width, 1);
/*
	ctx.strokeStyle = "rgba(239, 68, 68, 0.3)";
	ctx.lineWidth   = 1;

	ctx.beginPath();
	ctx.moveTo (x_center, 0);
  	ctx.lineTo (x_center, bg_layer.height);
  	ctx.moveTo (0, y_center);
	ctx.lineTo (bg_layer.width, y_center);
	ctx.stroke (); */
}

function drawSquare() {

	if (!square) {
		alert('drawSquare(): square canvas does not exist!'); return;
	}
	var ctx = square.getContext('2d');

	ctx.clearRect(0, 0, square.width, square.height);

	ctx.fillStyle = "rgba(0, 0, 255, 0.3)";
	ctx.fillRect(0, 0, square.width, square.height);

}

function drawTriangle() {

	if (!triangle)  {
		alert('drawTriangle(): triangle canvas does not exist!'); return;
	}

	const ctx = triangle.getContext('2d');
	const border_thick = 1;

	const vertex_a = { x: border_thick, y: border_thick };                 // left-top vertex;
	const vertex_b = { x: triangle.width - border_thick, y: border_thick}; // right-top vertex;
	const vertex_c = { x: triangle.width / 2, y: triangle.height - border_thick - vertex_b.y};

	ctx.clearRect(0, 0, triangle.width, triangle.height);

	// executes the path;
	ctx.beginPath();

	ctx.moveTo(vertex_a.x, vertex_a.y);
	ctx.lineTo(vertex_b.x, vertex_b.y);
	ctx.lineTo(vertex_c.x, vertex_c.y);

	ctx.closePath();

	ctx.lineWidth = border_thick;
	ctx.fillStyle = "rgba(0, 255, 0, 0.3)";
	ctx.fill();

	ctx.strokeStyle = "#00ff00";
	ctx.stroke();
}

function initApp() {

	// Google AI: runs this immediately on load to verify IE11 mode is actually active, the currently set mode must be 11;
	alert('Document Mode: ' + document.documentMode + '\nCanvas supported: ' + !!window.HTMLCanvasElement);

	drawCircle();
	drawSquare();
	drawTriangle();

	var draggables = document.querySelectorAll('.draggable');

	for (var i = 0; i < draggables.length; i++) {
		attachDrag(draggables[i]);
	}

	function attachDrag(element) {
		element.addEventListener('mousedown', function(event) {

		// prevents default drag-and-drop behavior inherent to <img> elements;
		if (event.preventDefault) { event.preventDefault(); } else { event.returnValue = false; }

		act_element = event.target || event.srcElement;
		act_element.className += " dragging"; // gives the top z-index;
		act_element.style.zIndex = z_index++;

		var rect = act_element.getBoundingClientRect();
		// calculates the distance from the mouse pointer to the top-left of the image;
		// this prevents the image from wildly jumping/snapping to its center when clicked;
		offsetX = Math.round(event.clientX - rect.left);
		offsetY = Math.round(event.clientY - rect.top );
		});
	}

	document.addEventListener('mousemove', function(event) {
        	if (!act_element) return;

        	// Determine new absolute screen coordinates
		var newLeft = event.clientX - offsetX;
		var newTop  = event.clientY - offsetY;

		// applies new coordinates directly to the inline styles
		act_element.style.left = newLeft + 'px';
		act_element.style.top  = newTop  + 'px';

		drawCross(newLeft, newTop);

		status_msg("mousemove(): the objects '"+ act_element.id  +"' being moved >>[x = " + newLeft + "; y = " + newTop +"] px;");
	});

	document.addEventListener('mouseup', function(event) {
		if (act_element) {
			act_element.className = act_element.className.replace(" dragging", "");
			act_element = null;

			if (bg_layer) {
				const ctx = bg_layer.getContext('2d');
				ctx.clearRect(0, 0, bg_layer.width, bg_layer.height);
			}
		}
	});
}

window.onload = initApp;
window.onresize = function (event) {
	if (!bg_layer) {
		alert('on_window_size(): bkg-layer canvas does not exist!'); return;
	}

	const dpr    = window.devicePixelRatio;
	const width  = document.documentElement.clientWidth;
	const height = document.documentElement.clientHeight;

//	bg_layer.width  = window.innerWidth;
//	bg_layer.height = window.innerHeight;
	bg_layer.width  = Math.round(width  * dpr);
	bg_layer.height = Math.round(height * dpr);

	const ctx = bg_layer.getContext('2d');

	ctx.setTransform(dpr, 0, 0, dpr, 0, 0);

	status_msg("on_window_size(): bkg-layer dpr >> " + dpr + " >> size >> { height = " + bg_layer.height + "; width = " + bg_layer.width + "} px;");
};

// window.addEventListener('resize', On_window_size, false);

function status_msg (_msg_text) {
	var status_bar = document.getElementById("status_bar");
	if (status_bar){      2
		status_bar.innerHTML = _msg_text;
	}
}
