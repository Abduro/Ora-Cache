#ifndef _2D_SHAPE_H_INCLUDED
#define _2D_SHAPE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Oct-2024 at 17:52:08.453, UTC+4, Batumi, Monday;
	This is Ebo Pack 2D space geometry base shape interface declaration file.
*/
#include "shared.preproc.h"
#include "shared.string.h"

#include "2d.base.h"

namespace geometry { namespace shape { namespace _2D {

	using namespace shared::types;

	using CPoint  = geometry::base::_2D::CPoint;
	using CPoints = geometry::base::_2D::CPoints;
	using CMarker = geometry::base::_2D::CMarker;

	// https://simple.wikipedia.org/wiki/Side ;

	class CSide {
	public:
		enum e_points {      // it is assumed that a side can have only two points: at begin and at end;
		     e_begin = 0x0,  // it is a point of the beginning of the side, no check is applied for estimating of the point values;
		     e_end   = 0x1,  // it is a point of the side ending; of course, 'ending' and 'beginning' notions are used virtually;
		};

	public:
		static const uint32_t n_points = 2; // this is the count of the points of the size class: begin and end, nothing more or different;

	public:
		 CSide (void);
		 CSide (const CPoint& _begin, const CPoint& _end);
		 CSide (const CMarker&);
		 CSide (const CSide&);
		 CSide (CSide&&);
		~CSide (void) = default;

	public:
		const
		CPoint&  Begin(void) const;
		CPoint&  Begin(void) ;

		_pc_sz   Desc (void) const;    // returns a description of this side;
		bool     Desc (_pc_sz) ;       // returns true in case if description value is changed, case sensitive; no trim is made and is assigned as it is;

		const
		CPoint&  End (void) const;
		CPoint&  End (void) ;

		const
		CMarker& Marker (void) const;
		CMarker& Marker (void) ;

		CPoint   Middle (void) const;  // returns a point that resides on middle of the side;

		const
		CPoint&  Point (const e_points) const;  // returns a reference to the point object (read-only);
		CPoint&  Point (const e_points) ;       // returns a reference to the point object (read-write);

#if defined (_DEBUG)
		enum e_print : uint16_t {
		     e_all   = 0,
		     e_no_ns = 1,
		     e_req   = 2,
		};
		CString  Print (const e_print = e_print::e_all) const;
#endif

	public:
		CSide&  operator = (const CSide&);
		CSide&  operator = (CSide&&);
		CSide&  operator <<(const CMarker&);
		CSide&  operator <<(const CPoint& _begin); // sets a beginning point of the side;
		CSide&  operator >>(const CPoint& _end);   // sets an ending point of the side;
		CSide&  operator <<(_pc_sz _p_desc);

		bool operator == (const CSide&) const;
		bool operator != (const CSide&) const;

	private:
		CMarker   m_marker;           // this is a marker of a side that is defined by particular geometrical figure or shape;
		CPoint    m_points[n_points]; // this is a points of intersecting this side with other ones, or just for positioning in 2D space;
		CString   m_desc;             // #not_set by default;
	};

}}}

typedef geometry::shape::_2D::CMarker  TMarker;
typedef geometry::shape::_2D::CSide    TSide  ;

typedef ::std::vector<TSide> TRawSides; typedef TRawSides t_raw_sides;

namespace geometry { namespace shape { namespace _2D {

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
		enum e_print {
		     e_all   = 0,
		     e_no_ns = 1,
		     e_req   = 2,
		};
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
		 CShape (void);
		 CShape (const CShape&);
		 CShape (CShape&&) = delete;
		~CShape (void);

	public:
#if defined (_DEBUG)
		enum e_print {
		     e_all   = 0,
		     e_no_ns = 1,
		     e_req   = 2,
		};
		CString Print (const e_print = e_print::e_all) const;
#endif
	const
	CSides&  Sides (void) const;
	CSides&  Sides (void) ;

	public:
		CShape& operator = (const CShape&);
		CShape& operator = (CShape&&) = delete;

		CShape& operator <<(const CSides&);

	protected:
		CSides  m_sides;
	};

	// https://learn.microsoft.com/en-us/windows/win32/gdi/rectangle-functions >> most rectangle related methods are designed for drawing only;
	/*
		Taking into account a rectangle has 4 (four) sides as a shape, it looks like do not use such a kind of rectangle declaration
		due to a simple reason: both OpenGL and DirectX uses a vertices for drawing a rectangle in 2D (3D) spaces;

		https://en.wikipedia.org/wiki/Rectangle ;
		https://en.wikipedia.org/wiki/Vertex_(geometry) ;
		https://en.wikipedia.org/wiki/Vertex_(computer_graphics) ;
	*/

	using CPoint_2 = geometry::base::_2D::CPoint_2;
	using CSize = geometry::base::_2D::CSize;

	class CRectangle { // ToDo: it is not optimized for drawing performance yet; perhaps, it would be better to use a vector as points' container;
	public:
		enum e_corners : uint32_t {
		     e_A = 0x0, // the left-top corner of the rectangle; (A)— —(D)
		     e_B = 0x1, // the left-bottom corner;                |     |
		     e_C = 0x2, // the right-bottom corner;               |     |
		     e_D = 0x3, // the right-top corner;                 (B)— —(C) 
		};
	public:
		class CCorners {
		static const uint32_t n_count = e_corners::e_D + 1;
		public:
			 CCorners (void);
			 CCorners (const CCorners&);
			 CCorners (CCorners&&) = delete;
			~CCorners (void) = default;

		public:
			const CPoint_2& A(void) const; CPoint_2& A(void);
			const CPoint_2& B(void) const; CPoint_2& B(void);
			const CPoint_2& C(void) const; CPoint_2& C(void);
			const CPoint_2& D(void) const; CPoint_2& D(void);

			const CPoint_2& Corner(const e_corners) const; CPoint_2& Corner(const e_corners);

		public:
			CCorners& operator = (const CCorners&);
			CCorners& operator = (CCorners&&) = delete;

			const
			CPoint_2& operator [](const e_corners) const; // in case when an index >= CRectangle::u_corners a reference to fake point is returned;
			CPoint_2& operator [](const e_corners) ;      // in case when an index >= CRectangle::u_corners a reference to fake point is returned;

		private:
			CPoint_2  m_points[n_count];  // it is incorrect to call this a set of vertices here, since this is not the context of the drawing function;
			friend class CRectangle;
		};
	public:
		using e_index = e_corners;

		static
		const uint32_t u_corners = e_index::e_D + 1;

	public:
		 CRectangle (void) ;
		 CRectangle (const CRectangle&) ;
		 CRectangle (CRectangle&&) = delete;
		~CRectangle (void);

	public:
		CPoint     Center  (void) const;
		const
		CCorners&  Corners (void) const;
		CCorners&  Corners (void) ;

		const bool Is_valid (void) const; // returns true in case if all corners have valid markers;

#if defined (_DEBUG)
		enum e_print : uint32_t {
		     e_all   = 0,  // prints out complete information of this class object: namespace path, class name, data values and marker info;
		     e_no_ns = 1,  // prints out the same info as above option, but without namespace path;
		     e_req   = 2,  // prints out rectangle corners' data and marker info;
		};
		CString  Print (const e_print = e_print::e_all, _pc_sz _pfx = _T("\t\t"), _pc_sz _sfx = _T("\n")) const;
#endif
		CSize Size (void) const; // returns a size object of this rectangle;

	public:
		CRectangle& operator = (const CRectangle&);
		CRectangle& operator = (CRectangle&&) = delete;

		CRectangle& operator <<(const CCorners&);

		const
		CPoint_2&   operator [](const e_index) const; // in case when an index >= CRectangle::u_corners a reference to fake point is returned;
		CPoint_2&   operator [](const e_index) ;      // in case when an index >= CRectangle::u_corners a reference to fake point is returned;

	private:
		CCorners m_corners;
	};
}}}

typedef geometry::shape::_2D::CSides TSides;

#endif/*_2D_SHAPE_H_INCLUDED*/