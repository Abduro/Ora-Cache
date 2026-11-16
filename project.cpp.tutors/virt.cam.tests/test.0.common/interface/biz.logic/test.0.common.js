/*
	Created by Tech_dog (ebontrop@gmail.com) om 15-Nov-2026 at 18:24:14.555, UTC+4, Batumi, Sunday;
	This is virtual camera comon test case JavaScript file; ii is used by HTML page 'test.common.html' which is opened by default;
*/
var the_image = document.getElementById("the_image");  // the main image of the HTML page which must be centered;
var is_loaded = false; // it is required for avoiding a calling On_window_load() function twice on 'Refresh' command of the host application;

const err_img_msg = "the canvas id = ''the_image'' does not exist!";
const u_threshold = 5;

var size_cache = {
	height : 0,
	width  : 0
};

function centerImage () {

	if (!the_image)
		return;	// alert(the_image);
	const position = {
		left : (window.innerWidth  - the_image.width ) / 2,
		top  : (window.innerHeight - the_image.height) / 2
	};
	the_image.style.left = position.left + "px";
	the_image.style.top  = position.top  + "px";
//	alert("pos: left = " + position.left + "; top = " + position.top + "px;");
}

function scaleImage () {

	if (!the_image) { alert("scaleImage(): " + err_img_msg); return; }
	// important note: centerImage() uses window.inner* properties, that means they have higher priority in comparison width documentElement properties;
	const view_size = {
		height : window.innerHeigth || document.documentElement.clientHeight,
		width  : window.innerWidth  || document.documentElement.clientWidth
	};
	const size_ratio = {
		height : view_size.height / the_image.naturalHeight,
		width  : view_size.width  / the_image.naturalWidth
	};
	const scale_factor = Math.min(size_ratio.height, size_ratio.width); // alert(scale_factor);

	the_image.style.height = Math.floor(the_image.naturalHeight * scale_factor) + "px";
	the_image.style.width  = Math.floor(the_image.naturalWidth  * scale_factor) + "px";
}


function On_window_load (event) {
	if (false)
	alert('Document Mode: ' + document.documentMode + '\nCanvas supported: ' + !!window.HTMLCanvasElement);

	if (is_loaded) return; else is_loaded = true;
	if (!the_image) { alert("On_window_load(): " + err_img_msg); return; }

	scaleImage();
        centerImage();
}

function On_window_resize (event) {

	const curr_size = {
		height : window.innerHeight,
		width  : window.innerWidth 
	};
	if (Math.abs(curr_size.height - size_cache.height) < u_threshold && 
	    Math.abs(curr_size.width  - size_cache.width ) < u_threshold) return;

	size_cache.hight = curr_size.height;
	size_cache.width = curr_size.width ;

	scaleImage();
	centerImage();
}                                         

window.onload = On_window_load;
window.onresize = On_window_resize;