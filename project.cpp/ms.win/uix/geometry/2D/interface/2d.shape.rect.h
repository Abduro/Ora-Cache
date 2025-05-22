#ifndef _2D_SHAPE_RECT_H_INCLUDED
#define _2D_SHAPE_RECT_H_INCLUDED
/*
	Created by Tech_Dog (ebontrop@gmail.com) om 17-May-2025 at 02:11:14.370, UTC+4, Batumi, Saturday;
	This is Ebo Pack 2D space geometry primitive shape rectangle interface declaration file.
*/
#include "2d.shape.h"

namespace geometry { namespace _2D { namespace shapes {

	// https://learn.microsoft.com/en-us/windows/win32/gdi/rectangle-functions >> most rectangle related methods are designed for drawing only;

	using CPoint_2 = geometry::_2D::base::CPoint_2;
	using CSize    = geometry::_2D::base::CSize;
	/*
		Taking into account a rectangle has 4 (four) sides as a shape, it looks like do not use such a kind of rectangle declaration
		due to a simple reason: both OpenGL and DirectX uses a vertices for drawing a rectangle in 2D (3D) spaces;

		https://en.wikipedia.org/wiki/Rectangle ;
		https://en.wiktionary.org/wiki/oblong   ; << very alternative name of the rectangle word;
		https://en.wikipedia.org/wiki/Vertex_(geometry) ;
		https://en.wikipedia.org/wiki/Vertex_(computer_graphics) ;
	*/

	class COblong : public CShape { typedef CShape TBase;
	public:
		enum e_corners : uint32_t {
		     e_A = 0x0, // the left-top corner of the rectangle; (A)— —(D)
		     e_B = 0x1, // the left-bottom corner;                |     |
		     e_C = 0x2, // the right-bottom corner;               |     |
		     e_D = 0x3, // the right-top corner;                 (B)— —(C) 
		};
		/*   but taking into account the all angles are the right angles, i.e. equal to 90 degree, only 2 (two) vertices enough for
		     exact describing or specifying a rectangle size and position, this is diagonal points: left-top and right-bottom; */
		enum e_vertex : uint32_t { // this enumeration has different name from above one for better readability, nothing more;
		     e__undef    = 0x0,
		     e_left_top  = 0x1,    // taking into account that left-top or left-up may be not at the top due to values or rotation, it would better to call it as e_A corner;
		     e_right_low = 0x2,    // the same notice as above, and element name as e_C; so that means corners e_A and e_C are on diagonal, the same can be said for e_B and e_D;
		};
	public:
		using e_index = e_corners;
		static const uint32_t u_corners  = e_index::e_D + 1;
		static const uint32_t u_vertices = 2;

	public:
		 COblong (void) ;
		 COblong (const COblong&) ; COblong (COblong&&);
		~COblong (void);

	public:
		CPoint   Center (void) const;
		CPoint   Corner (const e_corners) const; // returns the point of the corner specified; if input value is out of range, fake/empty point is returned;

		const
		TRgbQuad& Color (void) const;
		TRgbQuad& Color (void) ;
		
		bool   Is_valid (void) const;            // returns true in case if it has 2 (two) diagonal vertices have different coordinates from each other;

#if defined (_DEBUG)
		CString  Print (const e_print = e_print::e_all, _pc_sz _pfx = _T("\t\t"), _pc_sz _sfx = _T("\n")) const;
#endif
		CSize    Size (void) const;              // returns a size object of this rectangle;
		const
		CPoint&  Vertex (const e_vertex) const;
		CPoint&  Vertex (const e_vertex) ;

	public:
		COblong& operator = (const COblong&);
		COblong& operator = (COblong&&);

		COblong& operator <<(const CPoint& _left_up);
		COblong& operator >>(const CPoint& _right_low);

	private:
		TRgbQuad m_color; // the color that fills this rectangle body;
	};
}}}

typedef geometry::_2D::shapes::COblong  TRect;

#endif/*_2D_SHAPE_RECT_H_INCLUDED*/