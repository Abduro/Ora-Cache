/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Oct-2026 at 15:28:42.155, UTC+4, Batumi, Sunday;
	This is virtual camera field of view test javascript file.
*/
/* https://stackoverflow.com/questions/33811677/html-canvas-draw-a-circle-on-mouse-click-and-drag-it-untill-the-required-radius << doesn't works;*/
var canvas  = document.getElementById("canvas");
var caption = document.getElementById("caption");
var monitor = document.getElementById('img_monitor');
var viewer  = document.getElementById('img_viewer');
var rc_canvas = canvas.getBoundingClientRect();       // the top boundary is important only, because a title is placed on the top html page;
var rc_caption = caption.getBoundingClientRect();     // the bottom boundary is important only, because the monitor image should not overlap the caption;

var offsetX  = 0;
var offsetY  = 0;
var act_element  = null;

monitor.addEventListener ? monitor.addEventListener('mousedown', On_mouse_down, false) : monitor.attachEvent('onmousedown', On_mouse_down);
viewer.addEventListener ? viewer.addEventListener('mousedown', On_mouse_down, false) : viewer.attachEvent('onmousedown', On_mouse_down);

function On_mouse_down(_event) {
	var event = _event || window.event;

	if (event.preventDefault) { event.preventDefault(); } else { event.returnValue = false; }

	act_element = event.target || event.srcElement;
	act_element.className += " dragging";

	var rect = act_element.getBoundingClientRect();

	// calculates the distance from the mouse pointer to the top-left of the image;
	// this prevents the image from wildly jumping/snapping to its center when clicked;
	offsetX = event.clientX - rect.left;
	offsetY = event.clientY - rect.top;

	if (document.addEventListener) {
		document.addEventListener('mousemove', On_mouse_move, false);
		document.addEventListener('mouseup', On_mouse_up, false);
	} else if (document.attachEvent) {
		document.attachEvent('onmousemove', On_mouse_move);
		document.attachEvent('onmouseup', On_mouse_up);
	}
}

function On_mouse_move(_event) {

	if (!act_element) return;

	var event = _event || window.event;

	if (act_element === viewer) {
		// gets monitor image rectangle bottom value;
		var monitorRect = monitor.getBoundingClientRect();
		var monitorBottom = Math.round(monitorRect.bottom) - rc_canvas.top;

		var tentativeViewerTop = event.clientY - offsetY;

		// strict Constraint: viewer top can never go higher than monitor bottom;
		if (tentativeViewerTop < monitorBottom) {
			tentativeViewerTop = monitorBottom;
		}

		viewer.style.top  = tentativeViewerTop + 'px';
		viewer.style.left = (event.clientX - offsetX) + 'px';

	} else if (act_element === monitor) {
		// gets viewer image rectangle top value;
		var viewerRect = viewer.getBoundingClientRect();
		var viewerTop = Math.round(viewerRect.top) - rc_canvas.top;

		var monitorHeight = monitor.offsetHeight; 
		var tentativeMonitorTop = event.clientY - offsetY;

		// strict Constraint: monitor bottom can never push past viewer top
		if ((tentativeMonitorTop + monitorHeight) > viewerTop) {
			tentativeMonitorTop = viewerTop - monitorHeight;
		}
		if (tentativeMonitorTop < rc_caption.bottom) {
			tentativeMonitorTop = rc_caption.bottom;
		}

		monitor.style.top = tentativeMonitorTop + 'px';
		monitor.style.left = (event.clientX - offsetX) + 'px';
	}
}

function On_mouse_up (_event) {

	if (act_element) {
		act_element.className = act_element.className.replace(" dragging", "");
		act_element = null;
	}

	// cleans up event listeners immediately to save memory and CPU cycles;
	if (document.removeEventListener) {
		document.removeEventListener('mousemove', On_mouse_move, false);
		document.removeEventListener('mouseup', On_mouse_up, false);
	} else if (document.detachEvent) {
		document.detachEvent('onmousemove', On_mouse_move);
		document.detachEvent('onmouseup', On_mouse_up);
	}
}


function Set_stat_message (_msg_text) {
	var status_bar = document.getElementById("status_bar");
	if (status_bar){
		status_bar.innerHTML = _msg_text;
	}
}
