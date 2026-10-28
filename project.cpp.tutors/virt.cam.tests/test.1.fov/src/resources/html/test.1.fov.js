/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Oct-2026 at 15:28:42.155, UTC+4, Batumi, Sunday;
	This is virtual camera field of view test javascript file.
*/
/* https://stackoverflow.com/questions/33811677/html-canvas-draw-a-circle-on-mouse-click-and-drag-it-untill-the-required-radius << doesn't works;*/
var isDragging = false;
var offsetX  = 0;
var offsetY  = 0;
var activeEl = null;
var allElements = [];

// caches all items;
var items = document.getElementsByClassName('block-img');
for (var i = 0; i < items.length; i++) {
	allElements.push(items[i]);
	initDrag(items[i]);
}

function initDrag (el) {
	if (el.addEventListener) {
		el.addEventListener('mousedown', On_mouse_down, false);
	} else {
		el.attachEvent('onmousedown', On_mouse_down);
	}
}
/*
function On_mouse_down (e) {
	isDragging = true;
	// calculates click offset relative to the image top-left;
	var img = document.getElementById('img_target');
	if (img){
		offsetX = e.clientX - img.offsetLeft;
		offsetY = e.clientY - img.offsetTop;
		Set_stat_message("On_mouse_down event occurred;");
	}
	e.preventDefault(); // prevents default drag-and-drop ghost image;
}
*/
function On_mouse_down (e) {
	var ev = e || window.event;
	if (ev.preventDefault) { ev.preventDefault(); } else { ev.returnValue = false; }
            
	activeEl = ev.target || ev.srcElement;
	activeEl.className += " dragging";

	offsetX = ev.clientX - activeEl.offsetLeft;
	offsetY = ev.clientY - activeEl.offsetTop;

	if (document.addEventListener) {
		document.addEventListener('mousemove', On_mouse_move, true);
		document.addEventListener('mouseup', On_mouse_up, true);
	} else {
		document.attachEvent('onmousemove', On_mouse_move);
		document.attachEvent('onmouseup', On_mouse_up);
	}
}
/*
function On_mouse_move (e) {
	if (!isDragging) return;
	var img = document.getElementById('img_target');
	if (img){
		img.style.left = (e.clientX - offsetX) + 'px';
		img.style.top  = (e.clientY - offsetY) + 'px';
		Set_stat_message("On_mouse_move event occurred;");
	}
	if (window.external && window.external.RefreshUI) {
		window.external.RefreshUI();
	}
}
*/
function On_mouse_move (e) {
	if (!activeEl) return;
	var ev = e || window.event;

	// Intended next position coordinates
	var nextLeft = ev.clientX - offsetX;
	var nextTop = ev.clientY - offsetY;

	// Predict and verify horizontal movement
	if (!willOverlap(activeEl, nextLeft, activeEl.offsetTop)) {
		activeEl.style.left = nextLeft + 'px';
	}

	// Predict and verify vertical movement
	if (!willOverlap(activeEl, activeEl.offsetLeft, nextTop)) {
		activeEl.style.top = nextTop + 'px';
	}
}

/*
function On_mouse_up (e) {
	isDragging = false;
	Set_stat_message("On_mouse_up event occurred;");
}
*/
function On_mouse_up() {
	if (activeEl) {
		activeEl.className = activeEl.className.replace(" dragging", "");
		activeEl = null;
	}
	if (document.removeEventListener) {
		document.removeEventListener('mousemove', On_mouse_move, true);
		document.removeEventListener('mouseup', On_mouse_up, true);
	} else {
		document.detachEvent('onmousemove', On_mouse_move);
		document.detachEvent('onmouseup', On_mouse_up);
	}
}

function willOverlap(movingEl, predictedLeft, predictedTop) {
	var r1 = {
		left  : predictedLeft,
		top   : predictedTop ,
		right : predictedLeft + movingEl.offsetWidth,
		bottom: predictedTop  + movingEl.offsetHeight
	};

	for (var i = 0; i < allElements.length; i++) {
		var target = allElements[i];
		if (target === movingEl) continue;

		var r2 = {
			left  : target.offsetLeft,
			top   : target.offsetTop,
			right : target.offsetLeft + target.offsetWidth,
			bottom: target.offsetTop + target.offsetHeight
		};

		// Returns true if bounding rectangles intersect
		var collision = !(r1.right <= r2.left || 
		                  r1.left >= r2.right || 
		                  r1.bottom <= r2.top || 
		                  r1.top >= r2.bottom);

		if (collision) {
			return true; 
		}
	}
	return false;
}

document.addEventListener('mousedown', On_mouse_down);
document.addEventListener('mousemove', On_mouse_move);
document.addEventListener('mouseup'  , On_mouse_up);

function Set_stat_message (_msg_text) {
	var status_bar = document.getElementById("status_bar");
	if (status_bar){
		status_bar.innerHTML = _msg_text;
	}
}
