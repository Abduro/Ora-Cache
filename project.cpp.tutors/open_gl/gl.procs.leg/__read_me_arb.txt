the query to Google AI: ARB in opengl

AI Overview

In OpenGL, ARB stands for the Architecture Review Board, the industry consortium that formerly governed the OpenGL specification.
https://en.wikipedia.org/wiki/OpenGL_Architecture_Review_Board ;

The term typically refers to two distinct but related things in graphics programming:

1. ARB Extensions and Suffixes

In OpenGL code, you will often see functions or constants ending in ARB (e.g., glGenBuffersARB or GL_ARB_vertex_buffer_object).
(1) Purpose: These are "official" extensions approved by the entire Architecture Review Board.
(2) Evolution: Most OpenGL features start as vendor-specific (like NV for NVIDIA or AMD),
    then become multi-vendor EXT extensions, and finally become ARB extensions once they are widely accepted.
(3) Core Integration: Eventually, these features are often folded into the "Core" OpenGL specification.
    When this happens, the ARB suffix is dropped (e.g., glGenBuffersARB became glGenBuffers in OpenGL 1.5/2.0).

2. ARB Assembly Language
   https://en.wikipedia.org/wiki/ARB_assembly_language ;

Before high-level shading languages like GLSL became standard, the ARB defined a low-level, assembly-like language for programming the GPU.

(1) Functionality: It provides direct, low-level access to vertex and fragment processing.
(2) Syntax: It uses instructions like DP3 (dot product), MUL (multiply), and RSQ (reciprocal square root) to manipulate 4-component vectors.
(3) Status: Today, it is largely considered legacy and has been replaced by the more human-readable GLSL (OpenGL Shading Language).
    https://www.nvidia.com/docs/IO/8227/GDC2003_OGL_ARBVertexProgram.pdf ;
    https://registry.khronos.org/OpenGL/extensions/ARB/ARB_vertex_program.txt ;
    https://mid.net.ua/posts/glarbasm.html ;

Should you use it today?

(1) Modern Projects: No. You should use Core OpenGL functions and GLSL for better performance, portability, and readability.
(2) Legacy/Compatibility: You might only use ARB functions if you are targeting extremely old hardware (pre-2004) or drivers that do not support the Core OpenGL versions you need.
    