document.addEventListener("DOMContentLoaded", function () {
    var img = document.getElementById("targetImage");
    var canvas = document.getElementById("drawingCanvas");

    // IE11 Safe Check: Execute immediately if cached, otherwise hook the load event
    if (img.complete) {
        initializeAndDraw();
    } else {
        img.addEventListener("load", initializeAndDraw);
    }

    function initializeAndDraw() {
        // Step 1: Extract real layout boundaries of the reference image
        var layoutWidth = img.clientWidth;
        var layoutHeight = img.clientHeight;

        // Step 2: Fix the off-screen bug by forcing the canvas internal grid 
        // to exactly equal its CSS layout display boundaries.
        canvas.width = layoutWidth;
        canvas.height = layoutHeight;

        var ctx = canvas.getContext("2d");
        if (!ctx) return;

        // Step 3: Clear any existing vector arrays before running a new sequence
        ctx.clearRect(0, 0, canvas.width, canvas.height);

        // Step 4: Calculate coordinates relative only to the top-left (0,0) of the canvas
        var centerX = canvas.width / 2;
        var centerY = canvas.height / 2;
        var radius = Math.min(canvas.width, canvas.height) * 0.15; // Radius scaled to 15% of smallest dimension

        // Step 5: Draw the vector sequence
        ctx.beginPath();
        
        // Context.arc configuration
        ctx.arc(
            centerX,          // horizontal center coordinate
            centerY,          // vertical center coordinate
            radius,           // distance from center point to edge
            0,                // start angle (3 o'clock position)
            2 * Math.PI,      // end angle (360 degrees in radians)
            false             // sequence routing direction (clockwise)
        );

        // Step 6: Render paths onto screen
        ctx.lineWidth = 5;
        ctx.strokeStyle = "#ff3b30"; // Bright distinct red outline
        ctx.stroke();

        // Optional fill layer inside vector circumference boundary
        ctx.fillStyle = "rgba(255, 59, 48, 0.2)";
        ctx.fill();
    }
});

window.onload = function () {
    var canvas = document.getElementById("drawingCanvas");
    if (!canvas) return;

    var ctx = canvas.getContext("2d");
    if (!ctx) return;

    // Clear any residual browser buffers
    ctx.clearRect(0, 0, 128, 128);

    // Precise absolute midpoint calculations of 128px grid
    var centerX = 64; 
    var centerY = 64;
    var radius = 45; // Generous circle scale fitting neatly inside 128x128 bounding box

    // Execute drawing pipeline natively 
    ctx.beginPath();
    ctx.arc(centerX, centerY, radius, 0, 2 * Math.PI, false);

    // Apply bright rendering colors
    ctx.lineWidth = 4;
    ctx.strokeStyle = "#ff3b30"; // Pure Red
    ctx.stroke();

    ctx.fillStyle = "rgba(255, 59, 48, 0.25)"; // Translucent red tint overlay
    ctx.fill();
};

