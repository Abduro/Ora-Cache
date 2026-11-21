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
//var monitor   = document.getElementById('img_monitor');
//var viewer    = document.getElementById('img_viewer');

var offsetX  = 0;
var offsetY  = 0;
var act_element  = null;

var is_loaded = false; // it is required for avoiding a calling On_window_load() function twice on 'Refresh' command of the host application;

//monitor.addEventListener ? monitor.addEventListener('mousedown', On_mouse_down, false) : monitor.attachEvent('onmousedown', On_mouse_down);
//viewer.addEventListener ? viewer.addEventListener('mousedown', On_mouse_down, false) : viewer.attachEvent('onmousedown', On_mouse_down);

function Set_handlers () {
/*
document.body.addEventListener('mouseleave',...) works;
document.documentElement.addEventListener('mouseleave',...) does not work;
document.addEventListener('mouseout',...) works perfectly!
*/
	if (document.addEventListener) {
		document.addEventListener('mousemove', On_mouse_move, false);
		document.addEventListener('mouseup'  , On_mouse_up, false);
		document.addEventListener('mouseout' , On_mouse_leave, false);
	} else if (document.attachEvent) {
		document.attachEvent('onmousemove', On_mouse_move);
		document.attachEvent('onmouseup'  , On_mouse_up);
		document.attachEvent('mouseout'   , On_mouse_leave);
	}
}

function Rem_handlers () {
	// cleans up event listeners immediately to save memory and CPU cycles;
	if (document.removeEventListener) {
		document.removeEventListener('mousemove', On_mouse_move, false);
		document.removeEventListener('mouseup'  , On_mouse_up, false);
		document.removeEventListener('mouseout' , On_mouse_leave, false);
	} else if (document.detachEvent) {
		document.detachEvent('onmousemove', On_mouse_move);
		document.detachEvent('onmouseup'  , On_mouse_up);
		document.detachEvent('mouseout'   , On_mouse_leave);
	}
}

function On_mouse_down(_event) {
	var event = _event || window.event;

	if (event.preventDefault) { event.preventDefault(); } else { event.returnValue = false; }

	act_element = event.target || event.srcElement;
	act_element.className += " dragging";

	var rect = act_element.getBoundingClientRect();

	// calculates the distance from the mouse pointer to the top-left of the image;
	// this prevents the image from wildly jumping/snapping to its center when clicked;
	offsetX = Math.round(event.clientX - rect.left);
	offsetY = Math.round(event.clientY - rect.top );
	Set_handlers();
	status_msg ("On_mouse_down: offsetX = " + offsetX + " px; offsetY = " + offsetY + " px;");
}

function On_mouse_leave (_event) {

	var event = _event || window.event;
	if (event) {
		var str_side  = "";
		if (false){}
		else if (event.clientX < rc_viewport.left  ) str_side = "left";
		else if (event.clientX > rc_viewport.right ) str_side = "right";
		else if (event.clientY < rc_viewport.top   ) str_side = "top";
		else if (event.clientY > rc_viewport.bottom) str_side = "bottom";
/*
	The Falsy Check: In JavaScript, "", null, undefined, 0, and false are all "falsy".
*/
		if (str_side !== "")
			status_msg("On_mouse_leave: out of the viewport " + str_side + " side;");
	}
}

var visible_part = 30;

function On_mouse_move (_event) {

	if (!act_element) return;

	var event = _event || window.event;

	if (act_element === viewer) {
		// gets monitor image rectangle bottom value;
		var rc_monitor = monitor.getBoundingClientRect();
		var rc_bottom  = Math.round(rc_monitor.bottom);
		var rc_viewer  = round_rect(get_viewport_rect());

		var tentativeTop = event.clientY - offsetY;

		if (tentativeTop < rc_bottom) { // strict constraint: viewer top can never go higher than monitor bottom;
			tentativeTop = rc_bottom;
		}
		var v_limit = Math.round(rc_status.top) - visible_part;
		if (v_limit < tentativeTop) { // strict constraint: viewer top cannot be lower statusbar top;
			tentativeTop = v_limit;
			status_msg("On_mouse_move: viewport bottom limit = " + v_limit + " px;");
		}

		var h_limit_r = Math.round(rc_viewport.right) - visible_part; // the right border limit;
		var h_limit_l = -rc_viewer.width + visible_part;              // the left border limit;

		var tentativeLeft = event.clientX - offsetX;
		if (false) {}
		else if (tentativeLeft < h_limit_l) { tentativeLeft = h_limit_l; }
		else if (tentativeLeft > h_limit_r) { tentativeLeft = h_limit_r; }
		else {} 

		viewer.style.top  = tentativeTop  + 'px';
		viewer.style.left = tentativeLeft + 'px';
		status_msg(
			"On_mouse_move: tentative point >> [x:" + tentativeLeft + ";y:" + tentativeTop + "] px;"/* limits >> [left:"+ h_limit_l + "; right:" + h_limit_r +"] px;"*/
		);

	} else if (act_element === monitor) {
		// gets viewer image rectangle top value;
		var viewerRect = viewer.getBoundingClientRect();
		var viewerTop  = Math.round(viewerRect.top);
		var rc_monitor = monitor.getBoundingClientRect();

		var monitorHeight = monitor.offsetHeight; 
		var tentativeTop  = event.clientY - offsetY;

		// strict Constraint: monitor bottom can never push past viewer top;
		if ((tentativeTop + monitorHeight) > viewerTop) {
			tentativeTop = viewerTop - monitorHeight;
		}
		var v_limit_t = Math.round(rc_caption.bottom);
		if (tentativeTop < v_limit_t) {
			tentativeTop = v_limit_t;
		}

		var h_limit_r = Math.round(rc_viewport.right) - visible_part; // the right border limit;
		var h_limit_l = -rc_monitor.width + visible_part;             // the left border limit;

		var tentativeLeft = event.clientX - offsetX;
		if (false) {}
		else if (tentativeLeft < h_limit_l) { tentativeLeft = h_limit_l; }
		else if (tentativeLeft > h_limit_r) { tentativeLeft = h_limit_r; }
		else {}

		monitor.style.top  = tentativeTop  + 'px';
		monitor.style.left = tentativeLeft + 'px';
		status_msg(
			"On_mouse_move: tentative point >> [x:" + tentativeLeft + ";y:" + tentativeTop + "] px; "/*limits >> [left:"+ h_limit_l + "; right:" + h_limit_r +"] px;"*/
		);
	}
	var cross_center = {
		x : act_element.left + act_element.width / 2,
		y : act_element.top  + act_element.height / 2
	};

	drawCross(cross_center.x, cross_center.y); // this function is defined in 'root.0.rulers.js' file;
}

function On_mouse_up (_event) {
	if (act_element) {
		act_element.className = act_element.className.replace(" dragging", "");
		act_element = null;
		clearCross(); // this function is defined in 'root.0.rulers.js' file;
	}
	Rem_handlers();
}

window.addEventListener('load', On_html_load, false);
window.addEventListener('resize', On_window_size, false);

function On_html_load (_event) {

	if (is_loaded) return; else is_loaded = true;

/*
	if (!monitor) monitor = document.getElementById('img_monitor');
	if (!viewer)  viewer  = document.getElementById('img_viewer');

	rc_viewport = get_viewport_rect();
	var v_top = 0;
	var v_bottom = rc_viewport.height;

	if (rc_caption) v_top += rc_caption.height;
	if (rc_status)  v_bottom -= rc_status.height;

	var x_center = rc_viewport.width / 2;
	var y_center = v_top + (v_bottom - v_top) / 2;

	/* to-do: placing images relative to the vertical center is not enough due to the fact that the images have different heights,
	   and visually the images do not look vertically centered;
	   it is necessary take into account a total height both images and correct the vertical center;
	*/
/*
	monitor.style.left = (x_center - monitor.offsetWidth / 2) + "px";
	monitor.style.top  = (y_center - monitor.offsetHeight) + "px";

	viewer.style.left = (x_center - viewer.offsetWidth / 2) + "px";
	viewer.style.top  = (y_center) + "px";
*/
	updateRulerArea();
	drawRulers(); // this function is defined in 'root.0.rulers.js' file;
}

var resizeTimeout = 0;

function On_window_size (_event) {
	updateRulerArea(); // this function is defined in 'root.0.rulers.js' file;
}
