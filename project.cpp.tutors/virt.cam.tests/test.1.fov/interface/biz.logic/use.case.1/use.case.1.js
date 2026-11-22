/*
	Created by Tech_dog (ebontrop@gmail.com) om 08-Nov-2026 at 17:17:53.278, UTC+4, Batumi, Sunday;
	This is virtual camera drawing draggable shapes JavaScript file;
*/
var circle   = document.getElementById("circle");    // a circle basic shape canvas;
var image    = document.getElementById("myImage");   // this an image object;   
var square   = document.getElementById("square");    // a square basic shape canvas;
var triangle = document.getElementById("triangle");  // a triangle basic shape canvas;

var crs_layer = document.getElementById("cross-layer"); // cross layer canvas for an element being moded;
var rul_layer = document.getElementById("ruler-layer"); // ruler layer canvas for drawing X & Y axes;

var act_element = null;
var offsetX = 0;
var offsetY = 0;

var z_index = 4; // should take into account what the last z-index value is set in CSS file;

var margins = {  // these margins are used by drawCross() and drawRulers() functions;
	horz: 0, vert: 0
};

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

	if (!crs_layer) {
		alert('drawCross(): crs_layer canvas does not exist!'); return;
	}
	const ctx = crs_layer.getContext('2d');
	ctx.fillStyle = "rgba(239, 68, 68, 0.3)";

	x_center = Math.round(x_center);
	y_center = Math.round(y_center);

	ctx.clearRect(0, 0, crs_layer.width, crs_layer.height);

	// this works regardless of the possible scaling of the line width by the canvas on which it is drawn;
	ctx.fillRect(x_center, 0, 1, margins.vert);               // draws the vertical line of the cross;
	ctx.fillRect(margins.horz, y_center, crs_layer.width, 1); // draws the horizontal line of the cross;
}

function drawRulers() {

	if (!rul_layer) {
		alert('drawRulers(): rul_layer canvas does not exist!'); return;
	}

	var  capation = document.getElementById("caption");
	var  cap_rect = capation.getBoundingClientRect();

	var  status_bar  = document.getElementById("status_bar");
	var  status_rect = status_bar.getBoundingClientRect();
	
	const h_margin = 7; // horizontal margin: x-axis should not coincident with the left border of html-page;
	const v_margin = 5;

	var width  = rul_layer.width  - h_margin;
	var height = rul_layer.height - v_margin - status_rect.height;

	const t_margin = 0 ;//Math.round(cap_rect.height) + v_margin;  // this is the top margin for x - axis does not overlap the caption;
	const step     = 50;  // 50-pixel delimiter spacing;
	const tick_sz  = 6 ;  // the length of tick marks;

	var origin_x = h_margin; // the left edge of viewport;
	var origin_y = height;   // the bottom edge of viewport (1px high);

	margins.horz = origin_x;
	margins.vert = origin_y;  

	var ctx = rul_layer.getContext('2d');

	ctx.clearRect(0, 0, width, height);
	ctx.fillStyle = '#64748b'; // neutral slate gray;
	ctx.font = "10px verdana";

	// (0) draws main 1px Y-axis (left edge) and X-axis (bottom edge);
	ctx.fillRect(origin_x, t_margin, 1, height - t_margin);  // vertical Y-axis at x = h_margin;
	ctx.fillRect(h_margin, origin_y, width, 1);              // horizontal X-axis at y = height;

	// (1) draws origin '0' label in the bottom-left corner;
	ctx.textAlign = 'left';
	ctx.textBaseline = 'bottom';
	ctx.fillText('0', origin_x + tick_sz + 3, origin_y - tick_sz - 1);

	// (2) draws 50px delimiters along the bottom X-axis (left to right);
	ctx.textAlign = 'center';
	ctx.textBaseline = 'bottom';

	for (var x = step; x < width; x += step) {
		// draws a tick pointing upward into the canvas;
		ctx.fillRect(x, origin_y - tick_sz, 1, tick_sz);
		ctx.fillText(x, x, origin_y - tick_sz - 2);
	}

	// (3) draws 50px delimiters along the left Y-axis (bottom to top);
	ctx.textAlign = 'left';
	ctx.textBaseline = 'middle';

	for (var y = step; y < height; y += step) {
		var canvas_y = origin_y - y;
		// draws a tick pointing rightward into the canvas;
		ctx.fillRect(origin_x, canvas_y, tick_sz, 1);
		ctx.fillText(y, origin_x + tick_sz + 3, canvas_y);
	}
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
	if (false)
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

        	// determine new absolute screen coordinates;
		const newLeft = event.clientX - offsetX;
		const newTop  = event.clientY - offsetY;

		// applies new coordinates directly to the inline styles of the active element;
		act_element.style.left = newLeft + 'px';
		act_element.style.top  = newTop  + 'px';

		const element  = event.target || event.srcElement;
		const x_center = newLeft + element.width / 2;
		const y_center = newTop  + element.height / 2;

		drawCross(x_center, y_center);

		status_msg("mousemove(): the objects '"+ element.id  +"' being moved >>[x = " + newLeft + "; y = " + newTop +"] px;");
	});

	document.addEventListener('mouseup', function(event) {
		if (act_element) {
			act_element.className = act_element.className.replace(" dragging", "");
			act_element = null;

			if (crs_layer) {
				const ctx = crs_layer.getContext('2d');
				ctx.clearRect(0, 0, crs_layer.width, crs_layer.height);
			}
		}
	});
}

window.onload = initApp;
window.onresize = function (event) {

	if (!crs_layer) { alert('on_window_size(): crs-layer canvas does not exist!'); return; }
	if (!rul_layer) { alert('on_window_size(): rul-layer canvas does not exist!'); return; }

/* it very looks like no device pixel ratio is required to be defined, because this time the test program runs on laptop with 15 inches monitor; */
	if (true) {
		crs_layer.width  = window.innerWidth;
		crs_layer.height = window.innerHeight;
		rul_layer.height = crs_layer.height;
		rul_layer.width  = crs_layer.width;
		status_msg("on_window_size(): rul_layer size >> { height = " + rul_layer.height + "; width = " + rul_layer.width + "} px;");
	} else {
		const dpr    = window.devicePixelRatio;
		const width  = document.documentElement.clientWidth;
		const height = document.documentElement.clientHeight;

		crs_layer.width  = Math.round(width  * dpr);
		crs_layer.height = Math.round(height * dpr);
		rul_layer.height = crs_layer.height;
		rul_layer.width  = crs_layer.width;

		const ctx_cross = crs_layer.getContext('2d'); ctx_cross.setTransform(dpr, 0, 0, dpr, 0, 0);
		const ctx_ruler = ctx_ruler.getContext('2d'); ctx_ruler.setTransform(dpr, 0, 0, dpr, 0, 0);
		status_msg("on_window_size(): rul_layer dpr >> " + dpr + " >> size >> { height = " + rul_layer.height + "; width = " + rul_layer.width + "} px;");
	}
	drawRulers();
};

// window.addEventListener('resize', On_window_size, false);

function status_msg (_msg_text) {
	var status_bar = document.getElementById("status_bar");
	if (status_bar){
		status_bar.innerHTML = _msg_text;
	}
}
