/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Oct-2026 at 15:28:42.155, UTC+4, Batumi, Sunday;
	This is virtual camera field of view test javascript file.
*/
/* https://stackoverflow.com/questions/33811677/html-canvas-draw-a-circle-on-mouse-click-and-drag-it-untill-the-required-radius << doesn't works;*/
var isDragging = false;
var offsetX, offsetY;

function On_mouse_down (e) {
	isDragging = true;
	// calculates click offset relative to the image top-left;
	var img = document.getElementById('img_the_monitor');
	if (img){
		offsetX = e.clientX - img.offsetLeft;
		offsetY = e.clientY - img.offsetTop;
		Set_stat_message("On_mouse_down event occurred;");
	}
			e.preventDefault(); // prevents default drag-and-drop ghost image;
}

function On_mouse_move (e) {
	if (!isDragging) return;
	var img = document.getElementById('img_the_monitor');
	if (img){
		img.style.left = (e.clientX - offsetX) + 'px';
		img.style.top  = (e.clientY - offsetY) + 'px';
		Set_stat_message("On_mouse_move event occurred;");
	}
	if (window.external && window.external.RefreshUI) {
		window.external.RefreshUI();
	}
}

function On_mouse_up (e) {
	isDragging = false;
	Set_stat_message("On_mouse_up event occurred;");
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
