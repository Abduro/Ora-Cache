/*
	Created by Tech_dog (ebontrop@gmail.com) om 17-Nov-2026 at 15:33:47.719, UTC+4, Batumi, Tuesday;
	This is virtual camera test case sidebar control JavaScript file;
	-----------------------------------------------------------------------------
	The base code is created by Google AI Search;
	Note: it is assumed the 'root.0.status.js' is included to HTML page before this file;
*/
const btn_down_id = "btn-scroll-down";
const btn_up_id   = "btn-scroll-up";
const viewport_id = "nav-viewport";

var btnDown  = document.getElementById(btn_down_id);
var btnUp    = document.getElementById(btn_up_id);
var viewport = document.getElementById(viewport_id);

var ITEM_STEP_HEIGHT = 46;
var activeDesc = "";

const err_no_scroll_down = ": the canvas id = ''" + btn_down_id + "'' does not exist!";
const err_no_scroll_up   = ": the canvas id = ''" + btn_up_id + "'' does not exist!";
const err_no_status_txt  = ": the <div> id = ''" + status_id + "'' does not ewxist";   // status_id must be declared in 'root.0.status.js' file;
const err_no_viewport    = ": the canvas id = ''" + viewport_id + "'' does not exist!";

function handleSidebarWheel(_event) {
	var event = _event || window.event;
	var delta =  event.deltaY || -event.wheelDelta || event.detail;
	stepSidebar(delta > 0 ? 1 : -1);
}


/* automatically highlights the link matching the current page filename */
/* it is not necessary to use this function because 'Home' page is not a test case;*/
function highlightCurrentUrl() {
	var links = document.getElementsByClassName("nav-link");
	var currentPath = window.location.pathname.toLowerCase();
	var matched = false;

	for (var i = 0; i < links.length; i++) {
		var href = links[i].getAttribute("href").toLowerCase();
		if (currentPath.indexOf(href) !== -1) {
			links[i].className += " active";
			activeDesc = links[i].getAttribute("data-desc") || "";
			matched = true;
			break;
		}
	}

	/* Fallback to first item when testing standalone */
	if (!matched && links.length > 0) {
		links[0].className += " active";
		activeDesc = links[0].getAttribute("data-desc") || "";
	}
	status_msg (activeDesc);
}

function initPage () {
	highlightCurrentUrl();
	updateScrollButtons();
}

function resetStatus() {
	if (activeDesc === "")
		activeDesc = "Select a test case to run;";
	status_msg (activeDesc);
}

function setStatus(link) {
	var desc = link.getAttribute("data-desc");
	if (desc) {
		status_msg (desc);
	}
}

function stepSidebar(direction) {
	if (!viewport) { alert("stepSidebar():" + err_no_viewport); return; }

	viewport.scrollTop += direction * ITEM_STEP_HEIGHT;
	updateScrollButtons();
}

function updateScrollButtons() {
	var btnDown  = document.getElementById(btn_down_id);  if (!btnDown)  { alert("updateScrollButtons():" + err_no_scroll_down); return; }
	var btnUp    = document.getElementById(btn_up_id);    if (!btnUp)    { alert("updateScrollButtons():" + err_no_scroll_up); return; }
	var viewport = document.getElementById(viewport_id);  if (!viewport) { alert("updateScrollButtons():" + err_no_viewport); return; }

	var hasOverflow = viewport.scrollHeight > viewport.clientHeight + 1;
	if (!hasOverflow) {
		viewport.scrollTop = 0;
		btnUp.disabled = true;
		btnDown.disabled = true;
	} else {
		btnUp.disabled = (viewport.scrollTop <= 0);
		btnDown.disabled = (viewport.scrollTop + viewport.clientHeight >= viewport.scrollHeight - 1);
	}
}


