/*
	Created by Tech_dog (ebontrop@gmail.com) om 11-Nov-2026 at 07:41:49.630, UTC+4, Batumi, Wednesday;
	This is virtual camera drawing wedge diagram JavaScript file;
*/

const draw_canv   = document.getElementById("draw_canv");  // the draw arc canvas has fixed size and is positioned by image position function;
const the_cross   = document.getElementById("the_cross");  // the cross draw canvas is resized by On_window_size handler function;
const the_image   = document.getElementById("the_image");  // the image object is movable by a mouse;
const the_grid    = document.getElementById("the_grid");   // the draw grid canvas is resized by On_window_size handler function;
const the_rulers  = document.getElementById("the_rulers"); // ruler layer canvas for drawing X & Y axes;
const status_bar  = document.getElementById("status_bar"); // this div element always at the viewport area bottom and has fixed height;

const image_size  = { height: 256, width: 256 };
const canvas_size = { height: 512, width: 512 };

const shifts = { // this shift variable is used for a connection the image position and the draw canvas position; the values is dependable on the image;
	horz: canvas_size.width  / 2 + 28,
	vert: canvas_size.height / 2 - 33
};
const cell_size = 50; // the distance between grid lines in pixels;

var margins  = { left: 0, bottom: 0 }; // these margins are used by drawCross() and drawRulers() functions;
var b_app_started = false;

function drawCross() {

	if (!the_cross) { alert("drawCross(): the canvas id = ''the_cross'' does not exist!"); return; }
	if (!the_image) { alert("drawCross(): the canvas id = ''the_image'' does not exist!"); return; }

	const image_rect = the_image.getBoundingClientRect();

	const x_center = image_rect.left + Math.round(image_rect.width  / 2);
	const y_center = image_rect.top  + Math.round(image_rect.height / 2);

	status_msg("drawCross(): center >> { x=" + x_center + "; y=" + y_center + "}");

	const ctx = the_cross.getContext('2d');

	ctx.clearRect(0, 0, the_cross.width, the_cross.height);
	ctx.fillStyle = "rgba(239, 68, 68, 0.3)";

	const line_thick = 1;

	// this works regardless of the possible scaling of the line width by the canvas on which it is drawn;
	ctx.fillRect(x_center, 0, line_thick, the_cross.height - margins.bottom);           // draws the vertical line of the cross;
	ctx.fillRect(margins.left,  y_center, the_cross.width  - margins.left, line_thick); // draws the horizontal line of the cross;
}

function drawGrid() {

	if (!the_grid) { alert("drawGrid(): the canvas id = ''the_grid'' does not exist!"); return; }

	var ctx = the_grid.getContext("2d");
	ctx.clearRect(0, 0, the_grid.width, the_grid.height);

	ctx.lineWidth = 1;
	ctx.strokeStyle = "rgba(200, 200, 200, 0.25)"; // sets very soft gray lines' color;

	// the grid is drawn the first in comparison with rulers' canvas, so margins must be defined here, not in drawRulers() function;
	const h_margin = 7; // horizontal margin: x-axis should not coincident with the left border of html-page;
	const v_margin = 7;
	margins.left   = h_margin;
	margins.bottom = v_margin + (status_bar ? status_bar.getBoundingClientRect().height : 0); //alert (margins.bottom); // sets the bottom margin;

	// draws vertical grid lines;
	ctx.beginPath();
	for (var x = margins.left; x < the_grid.width; x += cell_size) {
		ctx.moveTo(x, 0);
		ctx.lineTo(x, the_grid.height - margins.bottom); // the line should not penetrate the top border of status bar;
	}

	// draws horizontal grid lines;
	for (var y = the_grid.height - margins.bottom; y > 0; y -= cell_size) {
		ctx.moveTo(margins.left, y);
		ctx.lineTo(the_grid.width - margins.left, y);
	}
	ctx.closePath();
	ctx.stroke();
}

function drawRulers() {

	if (!the_rulers) { alert("drawRulers(): the canvas id = ''the_rulers'' does not exist!"); return; }

	var width  = the_rulers.width  - margins.left;
	var height = the_rulers.height - margins.bottom;

	const t_margin = 0 ;  //Math.round(cap_rect.height) + v_margin;  // this is the top margin for x - axis does not overlap the caption;
	const tick_sz  = 6 ;  // the length of tick marks;

	var origin_x = margins.left; // the left edge of viewport;
	var origin_y = height;       // the bottom edge of viewport (1px high);

	var ctx = the_rulers.getContext('2d');

	ctx.clearRect(0, 0, width, height);
	ctx.fillStyle = '#bababa'; // neutral slate gray;
	ctx.font = "10px verdana";

	// (0) draws main 1px Y-axis (left edge) and X-axis (bottom edge);
	ctx.fillRect(origin_x, t_margin, 1, height - t_margin);  // vertical Y-axis at x = h_margin;
	ctx.fillRect(margins.left, origin_y, width, 1);              // horizontal X-axis at y = height;

	// (1) draws origin '0' label in the bottom-left corner;
	ctx.textAlign = 'left';
	ctx.textBaseline = 'bottom';
	ctx.fillText('0', origin_x + tick_sz + 3, origin_y - tick_sz - 1);

	// (2) draws 50px delimiters along the bottom X-axis (left to right);
	ctx.textAlign = 'center';
	ctx.textBaseline = 'bottom';

	var canvas_x = cell_size;
	for (var x = cell_size; canvas_x < width; x += cell_size) {
		// draws a tick pointing upward into the canvas;
		canvas_x = x + margins.left;
		ctx.fillRect(canvas_x, origin_y - tick_sz, 1, tick_sz);
		ctx.fillText(x, canvas_x, origin_y - tick_sz - 2);
	}

	// (3) draws 50px delimiters along the left Y-axis (bottom to top);
	ctx.textAlign = 'left';
	ctx.textBaseline = 'middle';

	for (var y = cell_size; y < height; y += cell_size) {
		var canvas_y = origin_y - y;
		// draws a tick pointing rightward into the canvas;
		ctx.fillRect(origin_x, canvas_y, tick_sz, 1);
		ctx.fillText(y, origin_x + tick_sz + 3, canvas_y);
	}
}

function initApp() {
	if (false)
	alert('Document Mode: ' + document.documentMode + '\nCanvas supported: ' + !!window.HTMLCanvasElement);

	if (!the_image) { alert("initApp(): the canvas id = ''the_image'' does not exist!"); return; }
	if (!draw_canv) { alert("initApp(): the canvas id = ''draw_canv'' does not exist!"); return; }

	// forces internal drawing coordinates to match the {FoV arc draw canvas} box:
	draw_canv.width  = canvas_size.width;
	draw_canv.height = canvas_size.height;

	// step #1: centers the image on the screen and sets the FoV arc draw canvas:
	var img_left = (window.innerWidth  - the_image.width - margins.left) / 2;
	var img_top  = (window.innerHeight - the_image.height - margins.bottom) / 2;

	the_image.style.left = img_left + "px";
	the_image.style.top  = img_top  + "px";

	const img_rect = the_image.getBoundingClientRect();
	const img_center = {
		_x: img_left + img_rect.width  / 2,
		_y: img_top  + img_rect.height / 2
	};

	if (b_app_started === false) {
		b_app_started = true;
		drawGrid();
		drawCross(); // image position is set above;
	}
/*
	draw_canv.style.left = img_center._x + shifts.horz + "px";
	draw_canv.style.top  = img_center._y - shifts.vert + "px";
*/
	draw_canv.style.left = img_center._x - canvas_size.width  / 2 + "px";  // centers the draw canvas horizontally with respect to the image;
	draw_canv.style.top  = img_center._y - canvas_size.height / 2 + "px";  // centers the draw canvas vertically with respect to the image;

	// step #2: draws a FoV arc in the draw canvas:
	var ctx = draw_canv.getContext("2d");
	ctx.clearRect(0, 0, draw_canv.width, draw_canv.height);

/* how to calculate an arc() start and end angles:
	var radians = degrees * (Math.PI / 180); // angles must be in radians;
	Unlike standard Cartesian math where angles move counter-clockwise, the HTML5 Canvas default orientation moves clockwise:
	•   0° (0 Radians)     : 3 o'clock (East);
	•  90° (pi / 2 Radians): 6 o'clock (South);
	• 180° (pi Radians)    : 9 o'clock (West);
	• 270° (3 * pi / 2) Radians): 12 o'clock (North);
*/
	var cx = shifts.horz;
	var cy = shifts.vert;

	var radius = 170;

	var start_angle = 320 * Math.PI / 180;
	var end_angle = 40 * Math.PI / 180;

	ctx.beginPath();
	ctx.moveTo(cx, cy); // connects arc center to the shift point;
	ctx.arc(cx, cy, radius, start_angle, end_angle, false);
	ctx.closePath();    // automatically draws line from end angle back to center;

	ctx.strokeStyle = "#ff0000";
	ctx.lineWidth = 1;
	ctx.fillStyle = "rgba(255, 0, 0, 0.1)";
	ctx.fill();

	ctx.stroke();

	// dragging mechanics:
	var is_dragging = false;
	var offset_x = 0, offset_y = 0;

	the_image.onmousedown = function(event) {

		event = event || window.event;
		is_dragging = true;

		offset_x = event.clientX - the_image.offsetLeft;
		offset_y = event.clientY - the_image.offsetTop;

		if (event.preventDefault) { event.preventDefault(); } else { event.returnValue = false; }
	};

	document.onmousemove = function(event) {

		if (!is_dragging || !the_image || !draw_canv) // it is supposed the image is the only draggable object; draw_canv is dependable object;
			return;
		event = event || window.event;

		var target = {
			left: event.clientX - offset_x, // this is the image left value, not the left of arc draw canvas;
			top : event.clientY - offset_y  // this is the image top value, not the top of arc draw canvas;
		};
		const limits = {
			min_: {
				left: -30, // the draggable object cannot intersect the left border of the window;
				top :   0, // the draggable object cannot intersect the top border of the window;
			},
			max_: {
				left: window.innerWidth  - the_image.width + 25, // the draggable object right side cannot intersect right border of the window;,
				top : window.innerHeight - the_image.height      // the draggable object bottom side cannot intersect bottom border of the window;
			}
		};

		if (target.left < limits.min_.left) target.left = limits.min_.left;
		if (target.top  < limits.min_.top ) target.top  = limits.min_.top;

		if (target.left > limits.max_.left) target.left = limits.max_.left;
		if (target.top  > limits.max_.top ) target.top  = limits.max_.top;
		// moves the image in specified position:
		the_image.style.left = target.left + "px";
		the_image.style.top  = target.top  + "px";

		const img_rect = the_image.getBoundingClientRect();
		const img_center = {
			_x: img_rect.left + img_rect.width  / 2,
			_y: img_rect.top  + img_rect.height / 2
		};

		const canv_pos = {
			left: img_center._x - canvas_size.width  / 2,
			top : img_center._y - canvas_size.height / 2
		};

		// moves the draw canvas in specified position:
		draw_canv.style.left = canv_pos.left + "px";
		draw_canv.style.top  = canv_pos.top  + "px";

		drawCross();

		const str_pos = "{left = " + target.left + "; top = " + target.top + "}; ";
		const str_y   = "{top:min = " +  limits.min_.top + ";max = " + limits.max_.top + "}; "
		const str_x   = "{left:min = " +  limits.min_.left + ";max = " + limits.max_.left + "};"


	//	status_msg ("On_mouse_move(): image pos >> " + str_pos + '\n' +"limits >> " +  str_x + str_y + " px;");
	};

	document.onmouseup = function(event) {
		is_dragging = false;
	};
}

function resizeGrid() {

	if (!the_grid || !the_cross || !the_rulers) // only these elements are dependable on window client/inner area;
		return;
	var cli_width  = window.innerWidth;
	var cli_height = window.innerHeight;

	if (the_grid.width !== cli_width || the_grid.height !== cli_height) {
		the_grid.width  = cli_width;
		the_grid.height = cli_height;

		drawGrid();
	}
	if (the_cross.width !== cli_width || the_cross.height !== cli_height) {
		the_cross.width  = cli_width;
		the_cross.height = cli_height;

		drawCross();
	}
	if (the_rulers.width !== cli_width || the_rulers.height !== cli_height) {
		the_rulers.width  = cli_width;
		the_rulers.height = cli_height;

		drawRulers();
	}

	status_msg("on_window_size(): grid size >> { height = " + the_grid.height + "; width = " + the_grid.width + "} px;");
}

//if (window.attachEvent) { window.attachEvent('onload', initApp); } else { window.addEventListener('load', initApp, false); }
//if (window.attachEvent) { window.attachEvent('resize', resizeGrid); } else { window.addEventListener('load', resizeGrid, false); }
window.onload = initApp;
window.onresize = resizeGrid;

function status_msg (_msg_text) {
	if (status_bar){
	//	status_bar.innerHTML = _msg_text;//.replace(/\r?\n/g, '<br>');
		status_bar.textContent = _msg_text;
	}
}