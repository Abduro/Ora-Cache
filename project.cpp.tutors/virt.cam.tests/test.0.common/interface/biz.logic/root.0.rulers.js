/*
	Createed by Tech_dog (ebontrop@gmail.com) on 21-Nov-2026 at 10:38:48.115, UTC+4, Batumi, Saturday;
	This is virtual camera test cases' HTML rulers and cross layers' JavaScript file;
	-----------------------------------------------------------------------------
	***Note***: it is assumed the following files are inclided in the HTML page before this one:
	(0) 'root.0.grid.js'   << for rulers' margin definition;
	(1) 'root.0.body.js'   << for getting the caption Y-coordinate value of the bottom border;
	(2) 'root.0.status.js' << for getting the status bar the top border y-coordinate value;
*/
const cross_id = "cross-layer";
const ruler_id = "ruler-layer";

var crs_layer = document.getElementById(cross_id); // cross layer canvas for an element being moded;
var rul_layer = document.getElementById(ruler_id); // ruler layer canvas for drawing X & Y axes;

const err_no_cross = "the canvas with id = ''" + cross_id + "'' does not exist!";
const err_no_ruler = "the canvas with id = ''" + ruler_id + "'' does not exist!";

function clearCross () { // this function should be called from 'onmouseup' event handler;

	if (!crs_layer) {
		alert("clearCross(): " + err_no_cross); return;
	}
	const ctx = crs_layer.getContext('2d');
	ctx.clearRect(0, 0, crs_layer.width, crs_layer.height);
}

function getCrossPoint (active_element) {

	var cross_pt = { x: 0, y: 0 };
	if (active_element) {
		const rc_active = round_rect(active_element.getBoundingClientRect());
		cross_pt.x = rc_active.left + rc_active.width / 2,
		cross_pt.y = rc_active.top  + rc_active.height / 2
	}
	return cross_pt;
}


function drawCross (arg_0, arg_1) { // this function should be called from 'onmousemove' event handler;

	if (!crs_layer) {
		alert("drawCross(): " + err_no_cross); return;
	}
	var obj_center = { x: 0, y: 0 };

	if (false){}
	else if (typeof arg_0 === 'object') {
		const cross_pt = getCrossPoint(arg_0);
		obj_center.x = cross_pt.x;
		obj_center.y = cross_pt.y;
	}
	else if (typeof arg_0 === 'number' && typeof arg_1 === 'number') {
		obj_center.x = Math.round(arg_0);
		obj_center.y = Math.round(arg_1);
	}

	const margins = calcMargins();

	const ctx = crs_layer.getContext('2d');
	ctx.fillStyle = "rgba(239, 68, 68, 0.3)";

	ctx.clearRect(0, 0, crs_layer.width, crs_layer.height);

	const n_thickness = 1;

	// fillRect(x, y, width, height) takes four numeric parameters that define the rectangle's top-left starting corner and its dimensions in pixels;
	// this works regardless of the possible scaling of the line width by the canvas on which it is drawn;
	ctx.fillRect(obj_center.x, 0, n_thickness, crs_layer.height - margins.bottom);          // draws the vertical line of the cross;
	ctx.fillRect(margins.left, obj_center.y, crs_layer.width - margins.left, n_thickness);  // draws the horizontal line of the cross;
}

function drawRulers() { // this function should be called from the following event handlers: 'onload' and 'onresize';

	if (!rul_layer) {
		alert("drawRulers(): " + err_no_ruler); return;
	}

	var  cap_rect = get_caption_rect(); // this function is defined in 'root.0.body.js';
	const margins = calcMargins();

	var width  = rul_layer.width  - margins.left;   // h_margin;
	var height = rul_layer.height - margins.bottom; // v_margin - sta_rect.height;

	const t_margin = 0 ;         // this is the top margin for x - axis does not overlap the caption;
	const step     = cell_size;  // 50-pixel delimiter spacing;
	const tick_sz  = 6 ;         // the length of tick marks;

	var origin_x = margins.left; // the left edge of viewport;
	var origin_y = height;       // the bottom edge of viewport (1px high);

	var ctx = rul_layer.getContext('2d');

	ctx.clearRect(0, 0, width, height);
	ctx.fillStyle = '#999999'; // neutral slate gray;
	ctx.font = "10px verdana";

	const n_thickness = 1;

	// (0) draws main 1px Y-axis (left edge) and X-axis (bottom edge);
	ctx.fillRect(origin_x, t_margin, n_thickness, height - t_margin);  // vertical Y-axis at x = h_margin;
	ctx.fillRect(margins.left, origin_y, width, n_thickness);          // horizontal X-axis at y = height;

	// (1) draws origin '0' label in the bottom-left corner;
	ctx.textAlign = 'left';
	ctx.textBaseline = 'bottom';
	ctx.fillText('0', origin_x + tick_sz + 3, origin_y - tick_sz - n_thickness);

	// (2) draws 50px delimiters along the bottom X-axis (left to right);
	ctx.textAlign = 'center';
	ctx.textBaseline = 'bottom';

	for (var x = step; x < width; x += step) {
		// draws a tick pointing upward into the canvas;
		ctx.fillRect(x, origin_y - tick_sz, n_thickness, tick_sz);
		ctx.fillText(x, x, origin_y - tick_sz - n_thickness * 2);
	}

	// (3) draws 50px delimiters along the left Y-axis (bottom to top);
	ctx.textAlign = 'left';
	ctx.textBaseline = 'middle';

	for (var y = step; y < height; y += step) {
		var canvas_y = origin_y - y;
		// draws a tick pointing rightward into the canvas;
		ctx.fillRect(origin_x, canvas_y, tick_sz, n_thickness);
		ctx.fillText(y, origin_x + tick_sz + n_thickness * 3, canvas_y);
	}
}

function updateRulerArea () {
	if (!crs_layer) { alert("on_window_size(): " + err_no_cross); return; }
	if (!rul_layer) { alert("on_window_size(): " + err_no_ruler); return; }
	/* it very looks like no device pixel ratio is required to be defined, because this time the test program runs on laptop with 15 inches monitor; */
	if (true) {
		crs_layer.width  = window.innerWidth;
		crs_layer.height = window.innerHeight;
		rul_layer.height = crs_layer.height;
		rul_layer.width  = crs_layer.width;
		status_msg("updateRulerArea(): rul_layer size >> { height = " + rul_layer.height + "; width = " + rul_layer.width + "} px;");
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
		status_msg("updateRulerArea(): rul_layer dpr >> " + dpr + " >> size >> { height = " + rul_layer.height + "; width = " + rul_layer.width + "} px;");
	}
	drawRulers();
}