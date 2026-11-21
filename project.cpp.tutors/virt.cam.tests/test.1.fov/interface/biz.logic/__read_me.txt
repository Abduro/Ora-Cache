/* Event object exact structure and the primary properties available on this object:
	Pointer Coordinates (where the click happened):
		clientX, clientY: The coordinates of the mouse pointer relative to the browser window's client area.
		screenX, screenY: The coordinates relative to the user's physical monitor screen.
		pageX, pageY: The coordinates relative to the entire HTML document (includes page scrolling).
	Mouse Buttons (which button was clicked):
		button: a number indicating which mouse button was pressed:
			0 - left button; 1 - middle button (scroll wheel click); 2 - right button; 
		buttons: a bitmask representing all buttons currently being held down simultaneously:
			1 - left button; 4 - middle button (scroll wheel click); 2 - right button;
	State & Targets (What was clicked):
		target       : The actual deepest element that triggered the event.
		currentTarget: The element that the event listener is currently bound to.
		type         : Returns the string "mousedown".
		bubbles      : A boolean (true) indicating if the event bubbles up through the DOM.
		cancelable   : A boolean (true) indicating if the event's default behavior can be prevented.
*/
/* HTML image object description or an object created by '<img>' tag.
	Positioning & Layout Properties (Crucial for Movement):
		(1) offsetLeft / offsetTop: The pixel distance from the image's top/left outer border to its parent container's (offsetParent) padding edge.
		(2) offsetWidth / offsetHeight: The total visual width and height of the image element (includes the image size, borders, and padding).
		(3) clientWidth / clientHeight: The inner width and height of the image (includes padding, but excludes borders or margins).
 	Core Image Properties:                                                                         	
		(1) src: Gets or sets the full absolute URL of the image.
		    (Note: In IE11, reading img.src always returns the fully qualified absolute URL, even if you set it as a relative path like ../pic.png).
		(2) naturalWidth / naturalHeight: Supported in IE11. 
		    These return the actual, density-independent pixel width and height of the raw image file itself, regardless of any CSS sizing applied to the tag.
		(3) complete: A boolean (true/false) indicating whether the image has completely finished downloading.
		(4) alt: Gets or sets the alternative text string.
	Styles & Filters:
		(1) Exposes the inline CSS styles object.
		    For smooth movement in IE11, you will heavily rely on setting img.style.left, img.style.top, and img.style.transform; 
		    -ms-transform and standard transform for 2D movements like translation and rotation are also supported.
*/