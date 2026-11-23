/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Nov-2026 at 18:55:09.422, UTC+7) Batumi, Sunday;
	This is virtual camera test cases' common HTML grid element related JavaScript file;
	-----------------------------------------------------------------------------
	***important***:
	The following file must be inclode to HTML page before this one:
	(1) root.0.utils.js;
	(2) root.0.status.js;
*/
const grid_id = "the_grid";
var the_grid  = document.getElementById(grid_id);   // the draw grid canvas is resized by On_window_size handler function;

const cell_size = 50;
var ruler_margins = {  // these margins are used by drawCross() and drawRulers() functions;
	left: 0, right: 0, top: 0, bottom: 0
};

function calcMargins () {
	// the grid is drawn the first in comparison with rulers' canvas, so margins must be defined here, not in drawRulers() function;
	const h_margin = 7; // horizontal margin: x-axis should not coincident with the left border of html-page;
	const v_margin = 7; // the same as above: horizontal x-axis shouldn't coincident with the top border of the statusbar control;

	const sta_rect = get_status_rect(); // functions are defined in 'root.0.status.js';
	ruler_margins.left   = h_margin;
	ruler_margins.bottom = v_margin + sta_rect.height; // takes into account the statusbar height value;

	return ruler_margins;
}

function drawGrid() {

	if (!the_grid) { alert("drawGrid(): the canvas id = '" + grid_id + "' does not exist!"); return; }

	var ctx = the_grid.getContext("2d");
	ctx.clearRect(0, 0, the_grid.width, the_grid.height);

	ctx.lineWidth = 1;
	ctx.strokeStyle = "rgba(200, 200, 200, 0.25)"; // sets very soft gray lines' color;

	// the grid is drawn the first in comparison with rulers' canvas, so margins must be defined here, not in drawRulers() function;
	const h_margin = 7; // horizontal margin: x-axis should not coincident with the left border of html-page;
	const v_margin = 7;
	ruler_margins.horz = h_margin;
	ruler_margins.vert = v_margin + get_status_rect().height; // sets the bottom margin; the function is defined in 'root.0.status.js';

	// draws vertical grid lines;
	ctx.beginPath();
	for (var x = ruler_margins.horz; x < the_grid.width; x += cell_size) {
		ctx.moveTo(x, 0);
		ctx.lineTo(x, the_grid.height - ruler_margins.vert); // the line should not penetrate the top border of status bar;
	}

	// draws horizontal grid lines;
	for (var y = the_grid.height - ruler_margins.vert; y > 0; y -= cell_size) {
		ctx.moveTo(ruler_margins.horz, y);
		ctx.lineTo(the_grid.width - ruler_margins.horz, y);
	}
	ctx.closePath();
	ctx.stroke();
}