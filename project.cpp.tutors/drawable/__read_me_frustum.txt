the query to Google AI: frustum that is used in opengl is used in DirectX also?

AI Overview

Yes, the concept of a view frustum is used in both OpenGL and DirectX.
In both APIs, it represents the truncated pyramid (the volume of space) that the virtual camera can see.

However, while the concept is identical, the mathematical matrices used to define the frustum differ between the two APIs:

(1) Z-axis Clip Space Range:
    In OpenGL, the normalized device coordinate (NDC) depth range is [-1...+1];
    In DirectX, the depth range is [0...+1];
(2) Coordinate Handedness:
    OpenGL traditionally defaults to a right-handed coordinate system (where +Z points out of the screen towards the viewer).
    DirectX defaults to a left-handed system (where +Z points into the screen, away from the viewer).
(3) Triangle Winding Order:
    OpenGL treats counter-clockwise (CCW) vertices as the front face.
    DirectX treats clockwise (CW) vertices as the front face by default.

Because of these differences, projection matrices generated for OpenGL cannot be used directly in DirectX without adjusting the math.

If you are currently writing a renderer or porting code, let me know:
Are you building the projection matrix manually?
Which math library are you using (e.g., DirectXMath, GLM, XNA)?
