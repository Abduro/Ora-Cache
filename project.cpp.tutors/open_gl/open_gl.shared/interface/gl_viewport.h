#ifndef _GL_VIEWPORT_H_INCLUDED
#define _GL_VIEWPORT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Oct-2025 at 19:30:37.003, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL viewport wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "vertex\gl_vertex_data.h"
#include "vertex\gl_vertex_arr.dat.h"
#include "color._defs.h"

typedef
struct {
	uint32_t cx = 0;
	uint32_t cy = 0;
} t_size_u;

#pragma region __refs_f
// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport ; :: gettig the info of viewport;
// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthrange ; :: z-buffer coord value mapping to window client area;
// https://stackoverflow.com/questions/59262874/how-can-i-use-screen-space-coordinates-directly-with-opengl :: good discussion of coord's precision;
#pragma endregion
namespace ex_ui { namespace draw { namespace open_gl {
namespace view {

	class CColor {
	public:
		CColor (void); CColor (const CColor&) = delete; CColor (CColor&&) = delete; ~CColor (void);

		float Get_a (void) const;
		float Get_b (void) const;
		float Get_g (void) const;
		float Get_r (void) const;

		// sets color as float value; if the value is out of range [0.0...1.0], the value is set to min or max value of the range;
		void Set (const float _r, const float _g, const float _b, const float _a = 1.0f);
		void Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a = 0xff);
		void Set (const rgb_color);  // sets color in RGBA format; the input value is converted to float value color;	

	private:
		CColor& operator = (const CColor&) = delete; CColor& operator = (CColor&&) = delete;
		float m_rgba[4];
	};

	using CVertArr = CVertArray;
	class CGrid : private no_copy {
	public:
		class CCell : private no_copy {
		public:
			CCell (void); ~CCell (void);

			uint32_t Height (void) const;
			bool     Height (const uint32_t); // returns 'true' in case if height of the cell is changed;
			uint32_t Width  (void) const;
			bool     Width  (const uint32_t); // returns 'true' in case if width  of the cell is changed;

			bool   Is_valid (void) const;     // returns 'true' if the height and the width of the cell does not equal to zero (0);

			bool   Set (const uint32_t _u_width, const uint32_t _u_height); // returns 'true' if either cell width ot cell height is changed;

		private:
			t_size_u m_size;
		};
	public:
		CGrid (void); ~CGrid (void);

		const
		CCell& Cell (void) const;
		CCell& Cell (void) ;

		const
		CColor& Clr (void) const;
		CColor& Clr (void) ;
#if (0)
		void Default (void); // sets default values for grid size, draw step and grid color;
#endif
		err_code Draw (void);
		TError& Error (void) const;

		err_code   Update (const t_size_u& _u_size); // recalculates all vertices for input size of the draw area;
		const
		CVertArr&  Vertices (void) const;

	private:
		CCell  m_cell ;  // cell dimensions: height|width;
		CError m_error;
		CColor m_color;
		CVertArr m_vertices;
	};
}
	// https://en.wikipedia.org/wiki/Viewport ;
	// it is supposed the viewport dimensions are the same as target window client area is;
	class CViewPort : private no_copy {
	using CCoord = vertex::CCoord;
	using CGrid = view::CGrid;
	public:
		CViewPort (const uint32_t _u_width = 0, const uint32_t _u_height = 0); ~CViewPort (void);

		TError&   Error (void) const;
		t_size_u& Get (void)/* const*/; // returns the reference to 'unsigned' size structure, 'const' cannot be applied due to the compiler's error;
		t_size    Get (void) const;     // returns the current size of the viewport area; the standard/winapi size structure has fields of signed data type and that looks like not so good;
		err_code  Set (const uint32_t _u_width, const uint32_t _u_height); // sets the size of the viewport, left|top1 is assumed to be at '0|0';
		err_code  Set (const t_rect&);  // it is expected the input rectangle is in the target window client area coordinate system;

		bool Is_valid (void) const;     // it is assumed the width and height both do not equal to 0, otherwise 'false';
		const
		CGrid& Grid (void) const;
		CGrid& Grid (void) ;

		CCoord ToPos (const long _x, const long _y) ;

		CViewPort& operator << (const t_rect&);

	private:
		mutable
		CError   m_error;
		t_size_u m_size ;
		CGrid    m_grid ;
	};

}}}

#endif/*_GL_VIEWPORT_H_INCLUDED*/