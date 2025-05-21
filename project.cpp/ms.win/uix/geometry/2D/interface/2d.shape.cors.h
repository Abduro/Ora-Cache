#ifndef _2D_SHAPE_CORS_H_INCLUDED
#define _2D_SHAPE_CORS_H_INCLUDED
/*
	Creted by Tech_Dog (ebontrop@gmail.com) on 18-May-2025 at 21:51:24.626,(UTC+4), Batumi, Sunday;
	This is Ebo Pack 2D space geometry curve corners interface declaration file;
*/
#include "2d.base.h"

namespace geometry { namespace base { namespace _2D {

	using namespace shared::types;

	using CMarker = geometry::base::CMarker;

	// the radius value defines how smoothly the angle is rounded; it can have negative value, this, the angle can be convex and concave;
	class CCorner {
	public:
		 CCorner (const CMarker& = CMarker(0, _T("#corn::ctor"), false), const int8_t _radius = 0);
		 CCorner (const CCorner&);
		 CCorner (CCorner&&) = delete;
		~CCorner (void);

	public:
		const
		uint32_t  Id (void) const;     // using typedef 'dword' or uint32_t is not important for the time being;
		uint32_t& Id (void) ;

		bool Is_concave (void) const;
		bool Is_convex (void) const;
		bool Is_valid (void) const;    // returns 'true' in case when identifier value does not equel to zero;

		int8_t   Radius (void) const;
		int8_t&  Radius (void)      ;

	public:
		CCorner& operator = (const CCorner&);
		CCorner& operator = (CCorner&&) = delete;
		CCorner& operator <<(const int8_t _radius);
		CCorner& operator <<(const uint32_t _marker);

	protected:
		CMarker  m_marker;
		int8_t   m_radius;
	};
	// https://www.allacronyms.com/corners/abbreviated >> cors;
	typedef ::std::map<uint32_t, CCorner> TRawCorners; // a key - is a angle marker of placement; a value is angle object itself;
	typedef TRawCorners TRawCors; // just playing with shorter names;

	class CCorners {
	public:
		 CCorners (void);
		 CCorners (const CCorners&); CCorners (CCorners&&) = delete;
		~CCorners (void);

	public:
		err_code   Add (const uint32_t _marker, const CCorner&);
		const
		CCorner&   Get (const uint32_t _marker) const; // returns an angle, if it found, otherwize, fake angle is returned; read-only access, but is not drawn;
		CCorner&   Get (const uint32_t _marker)      ; // returns an angle, if it found, otherwize, fake angle is returned; read-write access, but is not drawn;
		const bool Has (const uint32_t _marker) const; // checks for existing a angle by value provided;
		const bool Is  (void) const;       // returns true if at least one angle is set;
		const
		TRawCorners&  Raw (void) const;       // a reference to angle(s) which are included to angle map; read-only;
		TRawCorners&  Raw (void)      ;       // a reference to angle(s) which are included to angle map; read-write;
		err_code   Rem (const uint32_t _marker);
		err_code   Set (const uint32_t _marker, const int8_t _radius); // a angle will be added, if exists, will be updated;

	public:
		CCorners&  operator  =(const CCorners&);
		CCorners&  operator  =(CCorners&&) = delete;
		CCorners&  operator +=(const CCorner&);
		CCorners&  operator -=(const CCorner&);

	private:
		TRawCorners m_corners;
	};
	// https://www.allacronyms.com/triangle/abbreviated ;
	class CTri_Cors : public CCorners {
	};
}}}

#endif/*_2D_SHAPE_CORS_H_INCLUDED*/