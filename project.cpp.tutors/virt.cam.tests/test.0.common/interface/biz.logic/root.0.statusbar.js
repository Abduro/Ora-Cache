/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Nov-2026 at 15:40:47.305, UTC+4, Batumi, Friday;
	This is virtual camera common HTML statusbar related JavaScript file;
*/
var statusbar = document.getElementById('status-text');
var rc_status = statusbar.getBoundingClientRect(); // the top of the statusbar rectangle is important only;
var msg_block = false; // just temporary variable for blocking alert;

function status_msg (_msg_text) {
	if (statusbar) {
		statusbar.innerHTML = _msg_text;
		if (!msg_block && false) { msg_block = true; alert("status_bar rect >> " + rect_2_str(round_rect(rc_status))); }
	}
}