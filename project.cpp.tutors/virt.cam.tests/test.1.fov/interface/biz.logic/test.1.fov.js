/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Oct-2026 at 15:28:42.155, UTC+4, Batumi, Sunday;
	This is virtual camera field of view test javascript file.
	-----------------------------------------------------------------------------
	The following files are expected to be included before this one:
	1) root.0.utils.jas;  << for rounding a rectangle;
	2) root.0.status.js;  << for output of a text to status bar control;
	3) root.0.body.js;    << for getting a HTMLM page caption rectangle;
	4) root.0.rulers.js;  << for getting rulers HTML canvas that shows rulers and active object movement cross;
*/
/* https://stackoverflow.com/questions/33811677/html-canvas-draw-a-circle-on-mouse-click-and-drag-it-untill-the-required-radius << doesn't works;*/
const monitor_id = "img_monitor";
const viewer_id  = "img_viewer";

var the_monitor  = document.getElementById(monitor_id);
var the_viewer   = document.getElementById(viewer_id);

var offset = {
	x : 0, y : 0
};

var act_element  = null;
var last_mouse = { // for tracking through what border the mouse goes out of the browser window;
	x : 0, y : 0
};

var is_loaded = false; // it is required for avoiding a calling On_window_load() function twice on 'Refresh' command of the host application;

if (the_monitor) the_monitor.addEventListener('mousedown', On_mouse_down, false);
if (the_viewer ) the_viewer.addEventListener ('mousedown', On_mouse_down, false);

function get_available_area () { // returns a rectangle that is available for moving the images inside of it;

	var rect_out = get_viewport_rect();
	rect_out.left   += ruler_margins.horz; rect_out.width  -= ruler_margins.horz;
	rect_out.bottom -= ruler_margins.vert; rect_out.height -= ruler_margins.vert;
	return rect_out;

}

function stop_dragging () { // returns 'false' in case there is nothing to stop, otherwise returns 'true' - dragging operation is completed;
	if (!act_element)
		return false;

	if (document.releaseCapture) {
		document.releaseCapture();
	}

	act_element.className = act_element.className.replace(" dragging", "");
	act_element = null;
	clearCross(); // this function is defined in 'root.0.rulers.js' file;

	status_msg ("stop_dragging: the drag operation is completed;");
	return true;
}

function On_mouse_down (_event) {
	var event = _event || window.event;

	if (event.preventDefault) { event.preventDefault(); } else { event.returnValue = false; }
	if (event.button !== 0) // left button only (in IE11 standard mode, 0 = left);
		return;

	act_element = event.target || event.srcElement;
	act_element.className += " dragging";

	// calculates the distance from the mouse pointer to the top-left of the image;
	// this prevents the image from wildly jumping/snapping to its center when clicked;
	offset.x = event.clientX - act_element.offsetLeft;
	offset.y = event.clientY - act_element.offsetTop ;

	drawCross (act_element); // this function is defined in 'root.0.rulers.js' file;

	// captures mouse on document.body so events still reach document outside the window;
	if (document.body.setCapture) {
		document.documentElement.setCapture();
	}

	var rc_active = round_rect(act_element.getBoundingClientRect());
	status_msg ("On_mouse_down: offset >> [x: " + offset.x + "; y: " + offset.y + "] px; rect >> " + rect_2_str(rc_active));
}

var visible_part = 30;

function On_mouse_move (_event) {

	var event = _event || window.event;

	// caches the last mouse position;
	last_mouse.x = event.clientX;
	last_mouse.y = event.clientY;

	if (!act_element) return; // there is no drag operation;

	// safety fallback: if left button was released outside and capture was lost;
	if (event.buttons !== undefined && (event.buttons & 1) === 0) {
		stop_dragging(); return;
	}

	var rc_monitor  = round_rect(the_monitor.getBoundingClientRect()); // gets monitor image rectangle;
	var rc_viewer   = round_rect(the_viewer.getBoundingClientRect());  // gets viewr image rectangle;
//	var rc_viewport = round_rect(get_viewport_rect());                 // these functions are defined in 'root.0.utils.js' file;
	var rc_viewport = get_available_area();

	var tentative_pt = {
		x : event.clientX - offset.x,
		y : event.clientY - offset.y
	};
	
	if (act_element === the_monitor) {

		// strict Constraint: monitor bottom can never push past viewer top;
		if ((tentative_pt.y + rc_monitor.height) > rc_viewer.top) {
			tentative_pt.y = rc_viewer.top - rc_monitor.height;
		}
		var v_limit_t = get_caption_rect().bottom; // this function is defined in 'root.0.body.js';
		if (tentative_pt.y < v_limit_t) {
			tentative_pt.y = v_limit_t;
		}

		var h_limit_r = rc_viewport.right - visible_part; // the right border limit;
		var h_limit_l = -rc_monitor.width + visible_part; // the left border limit;

		if (false) {}
		else if (tentative_pt.x < h_limit_l) { tentative_pt.x = h_limit_l; }
		else if (tentative_pt.x > h_limit_r) { tentative_pt.x = h_limit_r; }
		else {}

		act_element.style.top  = tentative_pt.y  + 'px';
		act_element.style.left = tentative_pt.x + 'px';
	}
	if (act_element === the_viewer) {

		const rc_status = get_status_rect();

		if (tentative_pt.y < rc_monitor.bottom) { // strict constraint: viewer top can never go higher than monitor bottom;
			tentative_pt.y = rc_monitor.bottom;
		}
		var v_limit = rc_status.top - visible_part;
		if (v_limit < tentative_pt.y) { // strict constraint: viewer top cannot be lower statusbar top;
			tentative_pt.y = v_limit;
			status_msg("On_mouse_move: viewport bottom limit = " + v_limit + " px;");
		}

		var h_limit_r = rc_viewport.right - visible_part;  // the right border limit;
		var h_limit_l = -rc_viewer.width + visible_part;   // the left border limit;

		if (false) {}
		else if (tentative_pt.x < h_limit_l) { tentative_pt.x = h_limit_l; }
		else if (tentative_pt.x > h_limit_r) { tentative_pt.x = h_limit_r; }
		else {} 

		act_element.style.top  = tentative_pt.y + 'px';
		act_element.style.left = tentative_pt.x + 'px';
	}
	drawCross (act_element); // this function is defined in 'root.0.rulers.js' file;

	status_msg ("On_mouse_move: tentative point of '" + act_element.id  + "'>> [x:" + tentative_pt.x + ";y:" + tentative_pt.y + "] px; ");
}

function On_mouse_up (_event) {

	const object_id = act_element ? act_element.id : "unknown";

	if (stop_dragging())
		status_msg ("On_mouse_up: the drag operation of '" + object_id + "' is completed;");
}

function On_mouse_leave (_event) {

	var event = _event || window.event;
	var target = event.relatedTarget || event.toElement;

	if (target) // this means the mouse hovers other html document element;
		return;

	var last_x = (event.clientX >= 0) ? event.clientX : last_mouse.x;
	var last_y = (event.clientY >= 0) ? event.clientY : last_mouse.y;
		
	const rc_viewport = {
		left: 0, top: 0, right: window.innerWidth, bottom: window.innerHeight
	};

	var borders = {
		top   : last_y,
		bottom: rc_viewport.bottom - last_y,
		left  : last_x,
		right : rc_viewport.right - last_x
	};
	var closest_border = Math.min(borders.top, borders.bottom, borders.left, borders.right);

//	const str_borders = "{t:" + borders.top + ";b:" + borders.bottom + ";l:" + borders.left + ";r:" + borders.right + "};";
//	const str_point   = "the last>>[x:" + last_x + ";y:" + last_y + "]";

//	status_msg ("On_mouse_leave: borders>>" + str_borders + str_point);

	var str_side  = "";
	if (false){}
	else if (closest_border === borders.left  ) str_side = "left";
	else if (closest_border === borders.right ) str_side = "right";
	else if (closest_border === borders.top   ) str_side = "top";
	else if (closest_border === borders.bottom) str_side = "bottom";

	status_msg("On_mouse_leave: out of the viewport " + str_side + " side;");
}

window.addEventListener('load', On_html_load, false);
window.addEventListener('resize', On_window_size, false);
window.onblur = function() {
	const object_id = act_element ? act_element.id : "unknown";

	if (stop_dragging())
		status_msg ("On_blur: the drag operation of '" + object_id + "' is completed;");
};

function On_html_load (_event) {

	if (is_loaded) return; else is_loaded = true;

	if (!the_monitor) the_monitor = document.getElementById(monitor_id);
	if (!the_viewer)  the_viewer  = document.getElementById(viewer_id);

	const rc_monitor  = round_rect(the_monitor.getBoundingClientRect());
	const rc_viewer   = round_rect(the_viewer.getBoundingClientRect());
	const rc_viewport = round_rect(get_viewport_rect());   // these functions are defined in 'root.0.utils.js';

	var v_top = 0;
	var v_bottom = rc_viewport.height;

	v_top += get_caption_rect().height;                    // this function is defined in 'root.0.body.js';
	v_bottom -= get_status_rect().height;                  // this function is defined in 'root.0.status.js';

	var x_center = rc_viewport.width / 2;
	var y_center = v_top + (v_bottom - v_top) / 2;

	/* to-do: placing images relative to the vertical center is not enough due to the fact that the images have different heights,
	   and visually the images do not look vertically centered;
	   it is necessary take into account a total height both images and correct the vertical center;
	*/

	the_monitor.style.left = (x_center - the_monitor.offsetWidth / 2) + "px";
	the_monitor.style.top  = (y_center - the_monitor.offsetHeight) + "px";

	the_viewer.style.left = (x_center - the_viewer.offsetWidth / 2) + "px";
	the_viewer.style.top  = (y_center) + "px";

	updateRulerArea(); // this function is defined in 'root.0.grid.js' file;
	updateGridArea();  // this function is defined in 'root.0.rulers.js' file;

	document.addEventListener('mousemove', On_mouse_move, false);
	document.addEventListener('mouseup'  , On_mouse_up, false);
	document.addEventListener('mouseout' , On_mouse_leave, false);
	document.body.onlosecapture = function() {
		stop_dragging();
		status_msg ("onlosecapture event: dragging operation is ended;");
	}
	status_msg ("On_html_load: Init() is completed;");
}

function On_window_size (_event) {
	updateGridArea();  // this function is defined in 'root.0.grid.js' file;
	updateRulerArea(); // this function is defined in 'root.0.rulers.js' file;
}
