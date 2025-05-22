#ifndef _2D_SHAPE_H_INCLUDED
#define _2D_SHAPE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Oct-2024 at 17:52:08.453, UTC+4, Batumi, Monday;
	This is Ebo Pack 2D space geometry base shape interface declaration file.
*/
#include "2d.base.h"
#include "2d.base.line.h"

namespace geometry { namespace _2D { namespace shapes {

	// https://dictionary.cambridge.org/dictionary/english/shape ;
	using namespace shared::types;

	using CPoint  = geometry::_2D::base::CPoint;
	using CPoints = geometry::_2D::base::CPoints;
	using CLine   = geometry::_2D::base::CLine;
	using CMarker = geometry::_2D::CMarker;

	// https://simple.wikipedia.org/wiki/Side ;

	class CSide : public CLine { typedef CLine TBase;
	public:
		 CSide (void);
		 CSide (const CPoint& _begin, const CPoint& _end);
		 CSide (const CMarker&);
		 CSide (const CSide&);
		 CSide (CSide&&);
		~CSide (void) = default;

	public:
		_pc_sz   Desc (void) const;  // returns a description of this side;
		bool     Desc (_pc_sz) ;     // returns true in case if description value is changed, case sensitive; no trim is made and is assigned as it is;
		const
		CMarker& Marker (void) const;
		CMarker& Marker (void) ;

#if defined (_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif

	public:
		CSide&  operator = (const CSide&);
		CSide&  operator = (CSide&&);
		CSide&  operator <<(const CMarker&);
		CSide&  operator <<(_pc_sz _p_desc);

		bool operator == (const CSide&) const;
		bool operator != (const CSide&) const;

	protected:
		CMarker   m_marker; // this is a marker of a side that is defined by particular geometrical figure or shape;
		CString   m_desc;   // #not_set by default; ToDo: not sure that it is required for functionality of a shape;
	};

}}}

typedef geometry::_2D::shapes::CMarker  TMarker;
typedef geometry::_2D::shapes::CSide    TSide  ;

typedef ::std::vector<TSide> TRawSides; typedef TRawSides t_raw_sides;

namespace geometry { namespace _2D { namespace shapes {

	class CSides {
	public:
		 CSides (void) ;
		 CSides (const CSides&);
		 CSides (CSides&&) = delete;
		~CSides (void);

	public:
		bool    Append (const CSide&) ;                  // if an object with the same marker identifier is found, it is replaced;
		const
		CSide&  Find (const uint32_t _marker_id) const;  // if there is no a side with such a marker identifier, fake object is returned;
		const
		t_raw_sides& Get (void) const;
		t_raw_sides& Get (void) ;

		bool    Has (const uint32_t _marker_id) const;   // checks an existance of a side by input marker identifier;

		bool    Remove (const uint32_t _marker_id);      // removes the object by marker identifier provided; returns true in case of success;

#if defined (_DEBUG)
		CString Print (const e_print = e_print::e_all, _pc_sz _pfx = _T(""), _pc_sz _sfx = _T(";")) const;
#endif

	bool Set (const t_raw_sides&);

	public:
		CSides& operator = (const CSides&);
		CSides& operator = (CSides&&) = delete;

		CSides& operator <<(const t_raw_sides&);

		CSides& operator +=(const CSide&);          // input side marker identrifier is checked: if raw sides' vector has already the object it is replaced;
		CSides& operator -=(const CSide&);          // finds a side by marker identifier, if found, the found side is removed;
		CSides& operator -=(const uint32_t _u_id);  // removes a side by its identifier, if found;

	private:
		t_raw_sides m_sides;
	};

	// https://simple.wikipedia.org/wiki/Shape ;
	// https://en.wikipedia.org/wiki/List_of_two-dimensional_geometric_shapes ;

	class CShape {
	public:
		static const uint32_t n_min_point_count = 3; // a triangle is the simplest figure that can be considered as a shape;

	public:
		 CShape (const uint32_t _angles = 0); // there is a several words such as angle, angle, vertex, but they look like just a point;
		 CShape (const CShape&); CShape (CShape&&) = delete;
		~CShape (void);

	public:
		bool   Is_valid (void) const;  // checks a count of points and all points must have different values from each other; a rectangle overrides this property;
		const
		CPoints& Points (void) const;
		CPoints& Points (void) ;

#if defined (_DEBUG)
		enum e_prn_details {
		e_out_sides  = 0,
		e_out_points = 1,
		};
		CString Print (const e_print = e_print::e_all, const e_prn_details = e_prn_details::e_out_points) const;
#endif
#if (0)
	const
	CSides&  Sides (void) const;
	CSides&  Sides (void) ;
#endif
	public:
		CShape& operator = (const CShape&);
		CShape& operator = (CShape&&) = delete;
#if (1)
		CShape& operator <<(const CPoints&);
#else
		CShape& operator <<(const CSides&);
#endif
	protected:
#if (0)
		CSides  m_sides ;
#endif
		CPoints m_points;
	};
}}}

typedef geometry::_2D::shapes::CSides TSides;

#endif/*_2D_SHAPE_H_INCLUDED*/