!important!
the matrix calculation especially for frustrum and projection can be made in different ways:
(1) manually by using regular rules and functions of the trigonometry;
(2) by using GLM that is recommended;
(3) and finally by using OpenGL version 1.1 API; this way is the mostly important for testing under MS Windows Remote Desktop;
    but for this process some steps are required:
    the query to Google AI:
    glMatrixMode returns error GL_INVALID_OPERATION but there neither glBegin nor glEnd is called under MS Window OpenGL ver 1.1
    AI Overview
    The GL_INVALID_OPERATION error you are receiving from glMatrixMode typically indicates one of three common issues:
    (a) No Active OpenGL Rendering Context
        This is the most common cause of 'mysterious' OpenGL errors.
        If glMatrixMode is called *before* a valid device context has been *made current* to your thread via wglMakeCurrent, OpenGL will reject the call.
        Fix:
        Ensure you have successfully set up your window pixel format, created the rendering context with wglCreateContext, and activated it via wglMakeCurrent prior to making any GL calls.
        https://stackoverflow.com/questions/10088222/glcolor-glmatrixmode-mysteriously-giving-invalid-operation-errors ;
        https://wikis.khronos.org/opengl/OpenGL_and_multithreading << sharing context between threads; it is very good explanation with code example;

    (b) The Error State is 'sticky'
        OpenGL does not reset its error flag after every frame. If GL_INVALID_OPERATION was triggered by an entirely different function earlier in your code,
        that error remains in the queue. When glMatrixMode executes, it simply reads the current error state.
        Fix:
        Empty the error queue by placing a while loop over glGetError() right before the line causing the issue. For example:
        while (glGetError() != GL_NO_ERROR); // Clear previous errors;
        glMatrixMode(GL_PROJECTION);         // Now check if this specifically throws;

    (c) Context Profile Restrictions (Modern Windows Drivers)
        While you mentioned OpenGL 1.1, running modern graphics hardware on MS Windows often bridges compatibility through drivers that simulate older environments.
        If you unintentionally requested a Core Profile (OpenGL 3.1 or higher) instead of a Compatibility Profile,
        the legacy matrix stack is *removed*, and calling glMatrixMode will *immediately* return GL_INVALID_OPERATION.
        Fix:
        If using modern context creation (wglCreateContextAttribsARB), explicitly request the WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB to retain legacy matrix functions,
        or migrate away from glMatrixMode toward shader-based transformations.