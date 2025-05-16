#ifndef _2D_SHAPE_LINE_H_INCLUDED
#define _2D_SHAPE_LINE_H_INCLUDED
/*
	Created by Tech_Dog (ebontrop@gmail.com) om 16-May-2025 at 03:59:55.777, UTC+4, Batumi, Friday;
	This is Ebo Pack 2D space geometry primitive shape line interface declaration file.
*/
#include "2d.shape.h"

namespace geometry { namespace shape { namespace _2D {

	class CLine : public CSide { typedef CSide TBase;
	public:
		 CLine (const uint8_t _n_thickness = 0); CLine (const CLine&) = delete; CLine (CLine&&) = delete;
		~CLine (void) = default;

	public:
		const
		TRgbQuad& Color (void) const;
		TRgbQuad& Color (void) ;

		bool   Is_valid (void) const;
		// https://www.cuemath.com/euclidean-distance-formula/ ;
		// https://en.wikipedia.org/wiki/Euclidean_distance ;
		// https://stackoverflow.com/questions/27045327/calculating-the-distance-between-2-points-in-2d-space ;
		uint32_t  Length(void) const;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		uint8_t  Thickness (void) const;
		bool     Thickness (const uint8_t);

	public:
		CLine& operator <<(const TRgbQuad&) ;
		CLine& operator <<(const uint8_t&)  ;

	private:
		CLine& operator = (const CLine&) = delete;
		CLine& operator = (CLine&&) = delete;

	private:
		TRgbQuad m_color;
		uint8_t  m_thick;
	};

}}}

#endif/*_2D_SHAPE_LINE_H_INCLUDED*/