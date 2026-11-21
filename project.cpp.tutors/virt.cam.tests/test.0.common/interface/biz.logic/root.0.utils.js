/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Nov-2026 at 16:55:35.456, UTC+4, Batumi, Friday;
	This is virtual camera common utilities' JavaScript file;
*/
function get_viewport_rect () {
	var rect_out = {
		top   : 0,
		left  : 0,
		right : window.innerWidth ,
		bottom: window.innerHeight,
		width : window.innerWidth ,
		height: window.innerHeight
	};
	return rect_out;
}

function rect_2_str (rect) {
	if (!rect)
		return "rect_2_str(): input rectangle object is invalid;";
	else	return "{ left = " + rect.left + "; top = " + rect.top + "; width = " + rect.width + "; height = " + rect.height + " } px;";
}

function round_rect (rect_in) {
	var rect_out = {
		top   : Math.round(rect_in.top)   ,
		left  : Math.round(rect_in.left)  ,
		right : Math.round(rect_in.right) ,
		bottom: Math.round(rect_in.bottom),
		width : Math.round(rect_in.width) ,
		height: Math.round(rect_in.height)
	};
	return rect_out;
}