#ifndef _2D_SHAPE_H_INCLUDED
#define _2D_SHAPE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Oct-2024 at 17:52:08.453, UTC+4, Batumi, Monday;
	This is Ebo Pack 2D space geometry base shape interface declaration file.
*/
#include "2d.base.h"

namespace geometry { namespace shape { namespace _2D {

	// https://dictionary.cambridge.org/dictionary/english/shape ;
	using namespace shared::types;

	using CPoint  = geometry::base::_2D::CPoint;
	using CPoints = geometry::base::_2D::CPoints;
	using CMarker = geometry::base::_2D::CMarker;

	// the radius value defines how smoothly the corner is rounded; it can have negative value, this, the corner can be convex and concave;
	class CCorner {
	public:
		 CCorner (const uint32_t _marker = 0, const int8_t _radius = 0);
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
		uint32_t  m_marker;   // it seems to be better to call it as ID;
		int8_t    m_radius;
	};

	// https://www.allacronyms.com/corners/abbreviated >> cors;
	typedef ::std::map<uint32_t, CCorner> TRawCorners; // a key - is a corner marker of placement; a value is corner object itself;
	typedef TRawCorners TRawCors; // just playing with shorter names;

	class CCorners {
	public:
		 CCorners (void);
		 CCorners (const CCorners&); CCorners (CCorners&&) = delete;
		~CCorners (void);

	public:
		err_code   Add (const uint32_t _marker, const CCorner&);
		const
		CCorner&   Get (const uint32_t _marker) const; // returns a corner, if it found, otherwize, fake corner is returned; read-only access, but is not drawn;
		CCorner&   Get (const uint32_t _marker)      ; // returns a corner, if it found, otherwize, fake corner is returned; read-write access, but is not drawn;
		const bool Has (const uint32_t _marker) const; // checks for existing a corner by value provided;
		const bool Is  (void) const;       // returns true if at least one corner is set;
		const
		TRawCorners&  Raw (void) const;       // a reference to corner(s) which are included to corner map; read-only;
		TRawCorners&  Raw (void)      ;       // a reference to corner(s) which are included to corner map; read-write;
		err_code   Rem (const uint32_t _marker);
		err_code   Set (const uint32_t _marker, const int8_t _radius); // a corner will be added, if exists, will be updated;

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

	// https://simple.wikipedia.org/wiki/Side ;

	class CSide {
	public:
		enum e_points {      // it is assumed that a side can have only two points: at begin and at end;
		     e_begin = 0x0,  // it is a point of the beginning of the side, no check is applied for estimating of the point values;
		     e_end   = 0x1,  // it is a point of the side ending; of course, 'ending' and 'beginning' notions are used virtually;
		};

	public:
		static const uint32_t n_points = 2; // this is the count of the points of the side class: begin and end, nothing more or different;

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

	protected:
		CMarker   m_marker;           // this is a marker of a side that is defined by particular geometrical figure or shape;
		CPoint    m_points[n_points]; // this is a points of intersecting this side with other ones, or just for positioning in 2D space;
		CString   m_desc;             // #not_set by default; ToDo: not sure that it is required for functionality of a shape;
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
		class CCorners { // ToDo: this class must be renamed, or inherited from corners class that is defined outside above;
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