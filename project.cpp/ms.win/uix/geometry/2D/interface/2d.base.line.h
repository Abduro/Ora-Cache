#ifndef _2D_BASE_LINE_H_INCLUDED
#define _2D_BASE_LINE_H_INCLUDED
/*
	Created by Tech_Dog (ebontrop@gmail.com) om 16-May-2025 at 03:59:55.777, UTC+4, Batumi, Friday;
	This is Ebo Pack 2D space geometry base primitive line interface declaration file.
*/
#include "2d.base.h"

namespace geometry { namespace _2D { namespace base {

	class CLine {
	public:
		enum e_points {      // it is assumed that a line can have only two points: at begin and at end;
		     e_begin = 0x0,  // it is a point of the beginning of the line, no check is applied for estimating of the point values;
		     e_end   = 0x1,  // it is a point of the line ending; of course, 'ending' and 'beginning' notions are used virtually;
		};
	public:
		static const uint32_t n_points = 2; // this is the count of the points of the side class: begin and end, nothing more or different;

	public:
		 CLine (const uint8_t _n_thickness = 0); CLine (const CLine&) = delete; CLine (CLine&&) = delete;
		~CLine (void) = default;

	public:
		const
		CPoint&  Begin(void) const;
		CPoint&  Begin(void) ;
		const
		TRgbQuad& Color (void) const;
		TRgbQuad& Color (void) ;
		const
		CPoint&  End (void) const;
		CPoint&  End (void) ;

		bool   Is_horz  (void) const;
		bool   Is_valid (void) const;
		bool   Is_vert  (void) const;
			
		// https://www.cuemath.com/euclidean-distance-formula/ ;
		// https://en.wikipedia.org/wiki/Euclidean_distance ;
		// https://stackoverflow.com/questions/27045327/calculating-the-distance-between-2-points-in-2d-space ;
		uint32_t Length (void) const;
		CPoint   Middle (void) const;  // returns a point that resides on middle of the side;

		const
		CPoint&  Point (const e_points) const;  // returns a reference to the point object (read-only);
		CPoint&  Point (const e_points) ;       // returns a reference to the point object (read-write);

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		uint8_t  Thickness (void) const;
		bool     Thickness (const uint8_t);

	public:
		CLine&  operator <<(const CPoint& _begin); // sets a beginning point of the side;
		CLine&  operator >>(const CPoint& _end);   // sets an ending point of the side;
		CLine&  operator <<(const TRgbQuad&) ;
		CLine&  operator <<(const uint8_t&)  ;

	public:
		CLine&  operator = (const CLine&) ;
		CLine&  operator = (CLine&&) = delete;

	protected:
		CPoint   m_points[n_points]; // this is a points of intersecting this side with other ones, or just for positioning in 2D space;

	private:
		TRgbQuad m_color;
		uint8_t  m_thick;
	};

}}}

#endif/*_2D_BASE_LINE_H_INCLUDED*/