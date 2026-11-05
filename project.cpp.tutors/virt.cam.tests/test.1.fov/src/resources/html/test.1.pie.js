/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Nov-2026 at 18:21:52.475, UTC+4, Batumi, Monday;
	This is virtual camera field of view test javascript file for drawing'pie' diagram.
	*Note*: this script file must be included before 'test.1.fov.js'script file in HTML page;
*/
var canvas = document.getElementById('pieCanvas');
var ctx = canvas.getContext('2d');

var pie_cfg = {
	center: {
		x_: 0, // center x-coordinate;
		y_: 0  // center y-coordinate;
	},
	radius: 120,   // circle bounding radius;
	angles: {
		end  : 360, // deg: default 360 (3 o'clock orientation);
		start: 270  // deg: default 270 (12 o'clock top orientation);
	}
};

var point = {
	center: {
		x_: 0, // absolute x on the page including vertical scroll shift;
		y_: 0  // absolute y on the page including horizontal scroll shift;
	},
	viewport: {
		x_: 0, // X relative to visible window;
		y_: 0  // Y relative to visible window;
	}
};
/*
// central rendering loop (clears canvas, redraws image, computes Slice);
function drawScene() {

        ctx.clearRect(0, 0, canvas.width, canvas.height); // clears previous layer;
        // step #0: draws base image backdrop;
//	ctx.drawImage(img, 0, 0, canvas.width, canvas.height);
        
	// converts degrees to radians for canvas arc math API (angle * PI / 180);
	var endRad   = (pie_cfg.angles.end * Math.PI) / 180;
	var startRad = (pie_cfg.angles.start * Math.PI) / 180;

	// step #1: builds paths for the pie slice;
	ctx.beginPath();
	ctx.moveTo(pie_cfg.center.x_, pie_cfg.center.y_); // anchor node point at circle center;
	ctx.arc(pie_cfg.center.x_, pie_cfg.center.y_, pie_cfg.radius, startRad, endRad, false);
	ctx.closePath(); // connects arc endpoint back straight to center node;

	// step #2: sets fill semi-transparant color;
	ctx.fillStyle = "rgba(0, 220, 100, 0.35)"; // Vibrant Green at 35% opacity
	ctx.fill();

	// step #3: sets stroke style and crisp outline solid color;
	ctx.strokeStyle = "#00aa44"; // solid darker green line color;
	ctx.lineWidth = 4;
	ctx.lineJoin = "round"; // prevents sharp pixelated edge spikes at the wedge center;
	ctx.stroke();
}

function getCenterPoint(_element) {
	if (!_element)
		return null;
	var rect = _element.getBoundingClientRect();

	var viewportX = rect.left + (rect.width  || (rect.right - rect.left)) / 2;
	var viewportY = rect.top  + (rect.height || (rect.bottom - rect.top)) / 2;

	// gets document scroll offsets (IE11 compatible);
	var scrollX = window.pageXOffset || document.documentElement.scrollLeft || document.body.scrollLeft;
	var scrollY = window.pageYOffset || document.documentElement.scrollTop  || document.body.scrollTop;

	// returns both viewport-relative and document-absolute coordinates;

	point.center.x = viewportX + scrollX;
	point.center.y = viewportY + scrollY;
	point.viewport.x = viewportX;
	point.viewport.y = viewportY;

	return point;
}

function updateWedge(_event) {

	var event  = _event || window.event;

	// IE11 bounding rect calculations;
	var rect   = canvas.getBoundingClientRect();
	var mouseX = event.clientX - rect.left;
	var mouseY = event.clientY - rect.top;

	// trigonometric math: computes absolute rotation angle relative to center point;
	var dx = mouseX - pie_cfg.center.x_;
	var dy = mouseY - pie_cfg.center.y_;
	var radians = Math.atan2(dy, dx);
	var degrees = radians * (180 / Math.PI);

	// normalizes coordinates to clean 0-360 range scale;
	if (degrees < 0) { degrees += 360; }
        
        // Set dynamic drawing variables
        pieConfig.endAngle = Math.round(degrees);
        endInput.value = pieConfig.endAngle; // Mirror result value to input textbox UI
        
        // Fire canvas refresh
        drawScene();
}
*/