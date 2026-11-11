/*
	Created by Tech_dog (ebontrop@gmail.com) om 08-Nov-2026 at 17:17:53.278, UTC+4, Batumi, Sunday;
	This is virtual camera drawing draggable shapes JavaScript file;
*/
const canvas_high  = 128;
const canvas_width = canvas_high;
const image_hight  = 128;
const image_width  = image_hight;
const padding_horz = 0;
const padding_vert = padding_horz;

var square = document.getElementById("square");
var image  = document.getElementById("myImage");

var act_element = null;
var offsetX = 0;
var offsetY = 0;

var z_index = 0;

function initApp() {

	if (!square || !image)
		return;

//	drawSquare(); not required: it is made through style;

	var draggables = document.querySelectorAll('.draggable');

	for (var i = 0; i < draggables.length; i++) {
		setupDrag(draggables[i]);
	}

	function setupDrag(element) {
		element.addEventListener('mousedown', function(event) {

		// prevents default drag-and-drop behavior inherent to <img> elements;
		if (event.preventDefault) { event.preventDefault(); } else { event.returnValue = false; }

		act_element = event.target || event.srcElement;
		act_element.className += " dragging"; // gives the top z-index;

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

		// Apply new coordinates directly to the inline styles
		act_element.style.left = newLeft + 'px';
		act_element.style.top  = newTop + 'px';
	});

	document.addEventListener('mouseup', function(event) {
		if (act_element) {
			act_element.className = act_element.className.replace(" dragging", "");
			act_element.style.zIndex = z_index++;
			act_element = null;
		}
	});
}

window.onload = initApp;

function drawSquare() {

	if (!square) return;

	var ctx = square.getContext('2d');

	ctx.clearRect(0, 0, square.width, square.height);

	ctx.fillStyle = "rgba(0, 0, 255, 0.3)";
	ctx.fillRect(0, 0, square.width, square.height);

}
