/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Nov-2026 at 15:40:47.305, UTC+4, Batumi, Friday;
	This is virtual camera common HTML statusbar related JavaScript file;
	Note: it is assumed the 'root.0.utils.js' file is included to the HTML page before this one;
*/
const status_id = "status-text";

var statusbar = document.getElementById(status_id);
var rc_status = statusbar.getBoundingClientRect(); // the top of the statusbar rectangle is important only;
var msg_block = false; // just temporary variable for blocking alert;

function get_status_rect () {
	var rect_out = {
		left: 0, top: 0, right: 0, bottom: 0, height: 0, width: 0
	};
	var the_status = document.getElementById(status_id);
	if (the_status) {
		rect_out = round_rect(the_status.getBoundingClientRect()); // round_rect() is defined in the 'root.0.utils.js' file;
	}
	return rect_out;
}

function status_msg (_msg_text) {
	if (statusbar) {
		statusbar.innerHTML = _msg_text;
		if (!msg_block && false) { msg_block = true; alert("status_bar rect >> " + rect_2_str(round_rect(rc_status))); }
	}
}