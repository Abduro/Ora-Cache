/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Nov-2026 at 19:01:40.078, UTC+4, Batumi, Saturday;
	This is virtual camera test cases' common body HTML javascript file.
	-----------------------------------------------------------------------------
	***Note***: It is assumend 'root.0.utils.js' file is included to HTML page before this one;
*/
const caption_id = "caption";

function get_caption_rect () {
	var rect_out = {
		left: 0, top: 0, right: 0, bottom: 0, height: 0, width: 0
	};
	var the_caption = document.getElementById(caption_id);
	if (the_caption) {
		rect_out = round_rect(the_caption.getBoundingClientRect()); // round_rect() is defined in the 'root.0.utils.js' file;
	}
	return rect_out;
}