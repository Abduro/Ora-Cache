/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Nov-2026 at 18:21:52.475, UTC+4, Batumi, Monday;
	This is virtual camera field of view test javascript file for drawing'pie' diagram.
	*Note*: this script file must be included before 'test.1.fov.js'script file in HTML page;
*/
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

var viewerImg  = document.getElementById('img_viewer');
var monitorImg = document.getElementById('img_monitor');
var canvas     = document.getElementById('fov-canvas');
var ctx = canvas.getContext('2d');

function updateWedgeDiagram (viewerLeft, viewerTop) {

	if (!viewerImg || !monitorImg || !canvas) {
		return;
	}

canvas.style.top    = viewerImg.offsetY + "px";
canvas.style.left   = viewerImg.offsetX + "px";
canvas.style.width  = viewerImg.clientWidth + "px";
canvas.style.height = viewerImg.clientHeight + "px";

	ctx.clearRect(0, 0, canvas.width, canvas.height);

	var vCenterX = viewerLeft + (viewerImg.offsetWidth / 2);
   	var vCenterY = viewerTop  + (viewerImg.offsetHeight / 2);

	var mCenterX = monitorImg.offsetLeft + (monitorImg.offsetWidth / 2);
	var mCenterY = monitorImg.offsetTop + (monitorImg.offsetHeight / 2);
	
	var targetAngle = Math.atan2(mCenterY - vCenterY, mCenterX - vCenterX);

	var radius = vCenterY - mCenterY;
	var fovRadians = 60 * (Math.PI / 180);

	var startAngle = targetAngle - (fovRadians / 2);
	var endAngle   = targetAngle + (fovRadians / 2);

	ctx.beginPath();
	ctx.moveTo(vCenterX, vCenterY);
	status_msg("updateWedgeDiagram(): radius = " + radius + " px; center >> [x = " + vCenterX  + "; y = " + vCenterY +"] px");
/* arc() method params description:
	• x (#): The horizontal (X) coordinate of the center point of the arc, measured in pixels from the top-left corner of the canvas.
	• y (#): The vertical (Y) coordinate of the center point of the arc.
	• radius (#)    : The distance from the center point to the edge of the circle. Must be a positive value.
	• startAngle (#): The starting point of the arc, measured in radians along the perimeter from the positive x-axis (the 3 o'clock position).
	• endAngle (#)  : The ending point of the arc, also measured in radians from the positive x-axis
	• counterclockwise (Boolean, Optional):
		• false (Default): The arc is drawn clockwise from startAngle to endAngle.
		• true: The arc is drawn counter-clockwise.
*/
	ctx.arc(vCenterX, vCenterY, radius, 0 /*startAngle*/, 2 * Math.PI /*endAngle*/, false);
	ctx.lineTo(vCenterX, vCenterY); // Close back to center

	ctx.fillStyle = "rgba(0, 150, 255, 0.2)"; // Soft transparent blue fill
	ctx.fill();

	ctx.strokeStyle = "rgba(0, 100, 255, 0.6)"; // Sharper blue border lines
	ctx.lineWidth = 1;
	ctx.stroke();
}