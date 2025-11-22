#ifndef _GL_SURFACE_H_INCLUDED
#define _GL_SURFACE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Nov-2025 at 01:26:55.387, (UTC+4) Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' draw surface class interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace procs {

	// the 'surface' class name is just the alias for different types of buffers;
	class CEraser : public CBase {
	typedef void (__stdcall *pfnAll) (const uint32_t _u_mask); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glClear.xml ;
	typedef void (__stdcall *pfnClr) (const float _r, const float _g, const float _b, const float _a); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glClearColor.xml ;
	typedef void (__stdcall *pfnDepth) (const float _f_z); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glClearDepthf.xml ;
	typedef void (__stdcall *pfnStencil) (const uint32_t _u_ndx); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glClearStencil.xml ;
	public:
		enum e_clear_ops : uint32_t {
		e__undef  = 0x0,
		e_color   = GL_COLOR_BUFFER_BIT,   // indicates the buffers currently enabled for color writing;
		e_depth   = GL_DEPTH_BUFFER_BIT,   // indicates the depth buffer;
		e_stencil = GL_STENCIL_BUFFER_BIT, // indicates the stencil buffer;
		};
	public:
		CEraser (void); ~CEraser (void) = default;

		err_code All (const uint32_t _u_mask); // clears buffers to preset values;
		err_code Clr (const float _r, const float _g, const float _b, const float _a); // specifies clear values for the color buffers;
		err_code Depth (const float _f_z);  // specifies the clear value for the depth buffer;
		err_code Stencil (const uint32_t _u_bits); // specifies the clear value for the stencil buffer; input argument a number of bits: 2^_u_bits - 1 is the mask;

		err_code Get_all (void) ;

	private:
		CEraser& operator = (const CEraser&) = delete; CEraser& operator = (CEraser&&) = delete;
	};
	// https://registry.khronos.org/OpenGL/specs/gl/glspec44.core.pdf#page=328;
	// https://wikis.khronos.org/opengl/primitive ;
	// it is supposed the primitive types have different values and it's separated to different enums by primitives' category;
	class CPrimitives : private no_copy {
	public:
		enum class e_line : uint32_t {
		/* alias    | value    | OpenGL symbolic def      | brief description ;
		------------+----------+--------------------------+--------------------------*/
		e_adjacency = 0x000A, // GL_LINES_ADJACENCY       | primitive type that draws connected line segments, using a group of four vertices [v0...v3], v0 and v3 are considered as "adjacency" vertices, but are acceptable in geometry shader only;
		e_lines     = 0x0001, // GL_LINES                 | vertices 0 and 1 are considered a line, vertices 2 and 3 are considered a line and so on; if a non-even number of vertices is specified, then the extra vertex is ignored;
		e_loop      = 0x0002, // GL_LINE_LOOP             | as line strips, except that the first and last vertices are also used as a line; thus, n-vertices will get n lines;
		e_strip     = 0x0003, // GL_LINE_STRIP            | the adjacent vertices are considered lines; thus, n-vertices will get n-1 lines; if 1 vertex is specified, the drawing command is ignored;
		e_strip_adj = 0x000B, // GL_LINE_STRIP_ADJACENCY  | is  similar to line strips, except that each line segment has a pair of adjacent vertices that can be accessed by a geometry shader;
		};

		enum class e_others : uint32_t {
		/* alias    | value    | OpenGL symbolic def      | brief description ;
		------------+----------+--------------------------+--------------------------*/
		e_patches   = 0x000E, // GL_PATCHES               | this is a primitive with a user-defined number of vertices; these primitives can be used in tessellation shader only;
		e_points    = 0x0000, // GL_POINTS                | each individual vertex in the stream is interpreted as a point; points that have a texture mapped onto them are often called 'point sprites';
		};

		enum class e_triangle : uint32_t {
		/* alias    | value    | OpenGL symbolic def      | brief description ;
		------------+----------+--------------------------+--------------------------*/
		e_adjacency = 0x000C, // GL_TRIANGLES_ADJACENCY   | uses 6 vertices per triangle to define not only the triangle but also its neighboring faces, which is useful for tasks like tessellation and advanced geometry processing;
		e_fan       = 0x0006, // GL_TRIANGLE_FAN          | a set of primitives that draws a connected series of triangles using a single central vertex;  modern approaches often favor using indexed GL_TRIANGLES; // https://en.wikipedia.org/wiki/Triangle_fan ;
		e_strip     = 0x0005, // GL_TRIANGLE_STRIP        | primary reason to use triangle strips is to reduce the amount of data needed to create a series of triangles; https://en.wikipedia.org/wiki/Triangle_strip ;
		e_strip_adj = 0x000D, // GL_TRIANGLE_STRIP_ADJACENCY | is used for drawing a series of connected triangles with adjacency information, primarily in conjunction with a geometry shader;
		e_triangles = 0x0004, // GL_TRIANGLES             | a primitive formed by 3 vertices;
		};

		static CString To_str (const uint32_t _prom_id);
	};

	class CRenderer : public CBase {
		typedef void (__stdcall *pfnDrawArrays) (const uint32_t _u_mode, const uint32_t _u_start_ndx, const uint32_t _u_count); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml ;
	public:
		CRenderer (void); ~CRenderer (void) = default;

		err_code  DrawArrays (const uint32_t _prog_id, const uint32_t _u_mode, const uint32_t _u_start_ndx, const uint32_t _u_count); // draws a figure in specified mode; 'prog_id' is checked by getting active shaders enum;

		err_code Get_all (void) ;

	private:
		CRenderer& operator = (const CRenderer&) = delete; CRenderer& operator = (CRenderer&&) = delete;
	};
}}}}

typedef ex_ui::draw::open_gl::procs::CEraser   TEraserProcs; TEraserProcs& __get_eraser_procs (void);
typedef ex_ui::draw::open_gl::procs::CRenderer TRenderProcs; TRenderProcs& __get_render_procs (void);

#endif/*_GL_SURFACE_H_INCLUDED*/