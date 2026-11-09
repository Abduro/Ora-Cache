/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Oct-2026 at 15:28:42.155, UTC+4, Batumi, Sunday;
	This is virtual camera field of view test javascript file.
*/
/* https://stackoverflow.com/questions/33811677/html-canvas-draw-a-circle-on-mouse-click-and-drag-it-untill-the-required-radius << doesn't works;*/
var caption   = document.getElementById("caption");
var monitor   = document.getElementById('img_monitor');
var viewer    = document.getElementById('img_viewer');
var statusbar = document.getElementById('status_bar');
var viewport  = document.getElementById("viewport");
/* In IE11 emulation mode via the IWebBrowser2 control, the returned object contains the following six core properties:
   top   : Y-coordinate of the top edge of the rectangle relative to the viewport.
   bottom: Y-coordinate of the bottom edge of the rectangle relative to the viewport.
   left  : X-coordinate of the left edge of the rectangle relative to the viewport.
   right : X-coordinate of the right edge of the rectangle relative to the viewport.
   width : The width of the bounding box (right minus left).
   height: The height of the bounding box (bottom minus top).
*/
var rc_caption  = caption.getBoundingClientRect();   // the bottom boundary is important only, because the monitor image should not overlap the caption;
var rc_status   = statusbar.getBoundingClientRect(); // the top of the statusbar rectangle is important only;
var rc_viewport = viewport.getBoundingClientRect();  // the top boundary is important only, because a title is placed on the top html page;

var offsetX  = 0;
var offsetY  = 0;
var act_element  = null;

monitor.addEventListener ? monitor.addEventListener('mousedown', On_mouse_down, false) : monitor.attachEvent('onmousedown', On_mouse_down);
viewer.addEventListener ? viewer.addEventListener('mousedown', On_mouse_down, false) : viewer.attachEvent('onmousedown', On_mouse_down);

/* Event object exact structure and the primary properties available on this object:
	Pointer Coordinates (where the click happened):
		clientX, clientY: The coordinates of the mouse pointer relative to the browser window's client area.
		screenX, screenY: The coordinates relative to the user's physical monitor screen.
		pageX, pageY: The coordinates relative to the entire HTML document (includes page scrolling).
	Mouse Buttons (which button was clicked):
		button: a number indicating which mouse button was pressed:
			0 - left button; 1 - middle button (scroll wheel click); 2 - right button; 
		buttons: a bitmask representing all buttons currently being held down simultaneously:
			1 - left button; 4 - middle button (scroll wheel click); 2 - right button;
	State & Targets (What was clicked):
		target       : The actual deepest element that triggered the event.
		currentTarget: The element that the event listener is currently bound to.
		type         : Returns the string "mousedown".
		bubbles      : A boolean (true) indicating if the event bubbles up through the DOM.
		cancelable   : A boolean (true) indicating if the event's default behavior can be prevented.
*/
function Set_handlers () {
/*
document.body.addEventListener('mouseleave',...) works;
document.documentElement.addEventListener('mouseleave',...) does not work;
document.addEventListener('mouseout',...) works perfectly!
*/
	if (document.addEventListener) {
		document.addEventListener('mousemove' , On_mouse_move, false);
		document.addEventListener('mouseup'   , On_mouse_up, false);
		document.addEventListener('mouseout', On_mouse_leave, false);
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
/* HTML image object description or an object created by '<img>' tag.
	Positioning & Layout Properties (Crucial for Movement):
		(1) offsetLeft / offsetTop: The pixel distance from the image's top/left outer border to its parent container's (offsetParent) padding edge.
		(2) offsetWidth / offsetHeight: The total visual width and height of the image element (includes the image size, borders, and padding).
		(3) clientWidth / clientHeight: The inner width and height of the image (includes padding, but excludes borders or margins).
 	Core Image Properties:                                                                         	
		(1) src: Gets or sets the full absolute URL of the image.
		    (Note: In IE11, reading img.src always returns the fully qualified absolute URL, even if you set it as a relative path like ../pic.png).
		(2) naturalWidth / naturalHeight: Supported in IE11. 
		    These return the actual, density-independent pixel width and height of the raw image file itself, regardless of any CSS sizing applied to the tag.
		(3) complete: A boolean (true/false) indicating whether the image has completely finished downloading.
		(4) alt: Gets or sets the alternative text string.
	Styles & Filters:
		(1) Exposes the inline CSS styles object.
		    For smooth movement in IE11, you will heavily rely on setting img.style.left, img.style.top, and img.style.transform; 
		    -ms-transform and standard transform for 2D movements like translation and rotation are also supported.
*/
var visible_part = 30;

function On_mouse_move (_event) {

	if (!act_element) return;

	var event = _event || window.event;

	if (act_element === viewer) {
		// gets monitor image rectangle bottom value;
		var rc_monitor = monitor.getBoundingClientRect();
		var rc_bottom  = Math.round(rc_monitor.bottom);
		var rc_viewer  = viewer.getBoundingClientRect();

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

//		updateWedgeDiagram(tentativeLeft, tentativeTop);
		

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
}

function On_mouse_up (_event) {
	if (act_element) {
		act_element.className = act_element.className.replace(" dragging", "");
		act_element = null;
	}
	Rem_handlers();
}

window.addEventListener ? window.addEventListener('load', On_html_load, false) : window.attachEvent('load', On_html_load);
window.addEventListener ? window.addEventListener('resize', On_window_size, false) : window.attachEvent('resize', On_window_size);

function On_html_load (_event) {
	if (!monitor) monitor = document.getElementById('img_monitor');
	if (!viewer)  viewer  = document.getElementById('img_viewer');

	if (!rc_viewport) {
		rc_viewport.top  = 0;
		rc_viewport.left = 0;
		rc_viewport.right = rc_viewport.width = window.innerWidth || document.documentElement.clientWidth;
		rc_viewport.bottom = rc_viewport.height = window.innerHeight || document.documentElement.clientHeight;
		status_msg("On_html_load: viewport >> {left = 0; top = 0; right =" + rc_viewport.width + "; bottom = " + rc_viewport.height + "}(px);");
	}
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

	monitor.style.left = (x_center - monitor.offsetWidth / 2) + "px";
	monitor.style.top  = (y_center - monitor.offsetHeight) + "px";

	viewer.style.left = (x_center - viewer.offsetWidth / 2) + "px";
	viewer.style.top  = (y_center) + "px";
}

var resizeTimeout = 0;

function On_window_size (_event) {
/*
	Debounce the Resize Event: IE11 will fire the resize event continuously while the user drags the host application window.
	This can freeze the UI thread. Use a debounce function to wait until the resizing stops.
*/
	clearTimeout(resizeTimeout);
        resizeTimeout = setTimeout(function() {
/*
	Force Layout Recalculation (IE11 Bug Mitigation): Sometimes IE11 in emulation mode fails to visually redraw elements after a container resize.
	Reading offsetHeight forces IE11 to recalculate the layout immediately.
*/
		var triggerReflow = document.body.offsetHeight;
		if (null === viewport) {
			rc_viewport.left = 0;
			rc_viewport.top  = 0;
			rc_viewport.right  = rc_viewport.width  = window.innerWidth  || document.documentElement.clientWidth  || document.body.clientWidth;
			rc_viewport.bottom = rc_viewport.height = window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight;
		} else {
			rc_viewport = viewport.getBoundingClientRect();
			status_msg ("On_window_size: height = " + rc_viewport.height + "px; width = " + rc_viewport.width + "px;");
		}
	}, 100);
}

function status_msg (_msg_text) {
	var status_bar = document.getElementById("status_bar");
	if (status_bar){
		status_bar.innerHTML = _msg_text;
	}
}
