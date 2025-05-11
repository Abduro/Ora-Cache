#ifndef _2D_BASE_H_INCLUDED
#define _2D_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2024 at 21:55:27.203, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry fundamental objects' interface declaration file.
*/
#include <map>
#include "shared.preproc.h"
#include "shared.string.h"

#include "shared.types.h"
#include "sys.err.codes.h"

// the 'base' namespace does not mean a base of shape, but basic notations or fundamental objects in geometry;
namespace geometry { namespace base { namespace _2D {

	using namespace shared::types;

	// https://www.allacronyms.com/primitive/abbreviated ;

	class CMarker {
	public:
		 CMarker (void); 
		 CMarker (const uint32_t _u_id, _pc_sz _p_tag, const bool _b_valid); // a tag or maybe better to call it as just a name;
		 CMarker (const CMarker&);
		 CMarker (CMarker&&) = delete; // is not required yet;
		~CMarker (void);

	public:
		uint32_t Id (void) const;
		bool     Id (const uint32_t);  // returns true in case if this marker identifier is changed;

		bool  Is_valid (void) const;   // returns true if marker identifier is equal to 0; a tag name is optional
		bool  Is_valid (const bool);   // sets a validity attribute to the input value;

		bool  Set (const uint32_t _u_id, _pc_sz _p_tag, bool _b_valid = false); // returns true in case of the marker identifier or tag value is changed;

		_pc_sz   Tag (void) const;
		bool     Tag (_pc_sz) ;        // returns true if tag text is changed, case sensitive; nullptr is acceptable;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif

	public:
		CMarker& operator = (const CMarker&);
		CMarker& operator = (CMarker&&) = delete;   // is not required yet;

		CMarker& operator <<(const uint32_t _u_id); // error C2666: 'geometry::shape::_2D::CMarker::operator <<': 2 overloads have similar conversions ...;
		CMarker& operator <<(_pc_sz _p_tag);
		CMarker& operator <<(const bool _b_valid);

		operator _pc_sz   (void) const; // returns a pointer to tag string;
		operator uint32_t (void) const; // returns an identifier of this marker;

		bool operator == (const CMarker&) const;
		bool operator != (const CMarker&) const;

	private:
		CString  m_tag;
		uint32_t m_id ;
		bool     m_valid;
	};
	
	// https://en.wikipedia.org/wiki/Geometry ;  << all shapes are mentioned in this article;
	// https://en.wikipedia.org/wiki/Point_(geometry) ;

	class CPoint {
	public:
		 CPoint (int32_t _x = 0, int32_t _y = 0);
		 CPoint (const CPoint&);
		 CPoint (CPoint&&)/*=delete*/; // otherwise C2280;
		~CPoint (void);

	public:
		void Clear   (void);        // just calling this->Set(0,0);
		bool Is_zero (void) const;  // returns true in case when all point structure attributes have zero value;

		const
		t_point& Raw (void) const;
		t_point& Raw (void) ;

		bool Set (const int32_t _x, const int32_t _y); // returns true if one of the point structure members changes its value;

		int32_t  X (void) const;
		bool     X (const int32_t); // returns true in case of change X point structure attribute value;
		int32_t  Y (void) const;
		bool     Y (const int32_t); // returns true in case of change Y point structure attribute value;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	public:
		CPoint&  operator = (const CPoint&);
		CPoint&  operator = (CPoint&&)/*=delete*/; // otherwise C2280;

		CPoint&  operator <<(const int32_t _x);
		CPoint&  operator >>(const int32_t _y);    // another operator symbol, for instance, like this '^', is not easy noticeable;
		CPoint&  operator <<(const t_point&  );    // sets attributes value from raw/plain point data structure; 

		operator const t_point& (void) const;
		operator       t_point& (void) ;

		bool operator == (const CPoint&) const;
		bool operator != (const CPoint&) const;

		CPoint&  operator += (const CPoint&);
		CPoint&  operator -= (const CPoint&);

	protected:
		t_point  m_point;
	};

	class CPoint_2 : public CPoint { typedef CPoint TBase;
	public:
		 CPoint_2 (int32_t _x = 0, int32_t _y = 0);
		 CPoint_2 (const CPoint_2&);
		 CPoint_2 (CPoint_2&&);
		~CPoint_2 (void);

	public:
		const
		CMarker&  Marker (void) const;
		CMarker&  Marker (void) ;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif

	public:
		CPoint_2&  operator = (const CPoint_2&);
		CPoint_2&  operator = (CPoint_2&&);
		CPoint_2&  operator <<(const CMarker&);

	private:
		CMarker  m_marker;
	};
}}}

typedef geometry::base::_2D::CPoint  TPoint;
typedef ::std::vector<TPoint>    TRawPoints; typedef TRawPoints t_raw_pts;

TPoint  operator + (const TPoint& _lsv, const TPoint& _rsv);
/*
	the operator declaration below leads to this error of compilation:
	error C2280:'geometry::shape::_2D::CPoint &geometry::shape::_2D::CPoint::operator =(geometry::shape::_2D::CPoint &&)': attempting to reference a deleted function ;
	what is the reason for that?
	why operator '+' that is declared above does not produce such a kind of error?
*/
TPoint  operator - (const TPoint& _lsv, const TPoint& _rsv);

namespace geometry { namespace base { namespace _2D {

	class CPoints {
	public:
		 CPoints (void);
		 CPoints (const CPoints&);
		 CPoints (CPoints&&);
		~CPoints (void);

	public:
		const
		t_raw_pts& Raw (void) const;
		t_raw_pts& Raw (void) ;

#if defined (_DEBUG)
		CString Print (void) const;
#endif
	
	public:
		CPoints&  operator = (const CPoints&);
		CPoints&  operator = (CPoints&&);

		bool operator == (const CPoints&) const;
		bool operator != (const CPoints&) const;

	private:
		t_raw_pts m_points;
	};

}}}

typedef geometry::base::_2D::CPoints TPoints;

namespace geometry { namespace base { namespace _2D {

	// https://simple.wikipedia.org/wiki/Side ;

	/*
		Regardless of accepting negative values either for height and width attributes of the size structure,
		there is no sense in such a case as 'a figure has a height less than zero';
		it is obvious the size class should do not accept negative values but 0 or greater, i.e. unsigned values;
		otherwise, when a figure or shape is positioned in the negative part of the area on the X or Y axis or on both axes,
		the values of the points of the figure should be set accordingly, and the height and width of the figure will be kept equal to 0 or more;
	*/
	// this class still accepts a nagative value either for width or height attribute;
	class CSize {
	public:
		 CSize (int32_t _width = 0, int32_t _height = 0);
		 CSize (const CSize&);
		 CSize (CSize&&);
		~CSize (void);

	public:
		int32_t H (void) const;      // returns t_size.cy value or height in other words;
		bool    H (const int32_t);   // returns true in case when height (t_size.cy) of the size structure is changed;

		int32_t Height (void) const; // just playing with name readability;
		bool    Height (const int32_t);

		bool Is_point (void) const;  // the same as Is_zero but using another word;
		bool Is_zero  (void) const;  // returns true in case when height and width equal to 0; this means an object has no size and may be considered as 0x0 point;

#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		const
		t_size& Raw (void) const;    // returns a reference to raw data of this class, i.e. to t_size data structure; read-only;
		t_size& Raw (void) ;         // returns a reference to raw data of this class, i.t. to t_size data structure; read-write access;

		bool    Set (const int32_t _width, const int32_t _height);

		int32_t W (void) const;      // returns t_size.cx value or width in other words;
		bool    W (const int32_t);   // returns true in case when width (t_size.cx) of the size structure is changed;

		int32_t Width (void) const;  // just playing with name readability;
		bool    Width (const int32_t);

	public:
		CSize&  operator = (const CSize&);
		CSize&  operator = (CSize&&);

		CSize&  operator <<(const int32_t _width);
		CSize&  operator >>(const int32_t _height);

		CSize&  operator <<(const t_size&);  // sets this class object attribute valuse by applying plane size structure;

		operator const t_size& (void) const;
		operator       t_size& (void);

		bool operator == (const CSize&) const;
		bool operator != (const CSize&) const;

	protected:
		t_size m_size;
	};

	struct SIZE_U {
		uint32_t cx;
		uint32_t cy;
	};
	using size_u = SIZE_U;
	// maybe it would be better to create a template for applying different data types to 'size' class declaration, but trying to keep things simple;
	class CSize_U {
	public:
		 CSize_U (void);
		 CSize_U (const CSize_U&);
		 CSize_U (const uint32_t _width, const uint32_t _height);
		 CSize_U (CSize_U&&);
		~CSize_U (void);

	public:
		uint32_t H (void) const;
		bool     H (const uint32_t);

		uint32_t Height (void) const;
		bool     Height (const uint32_t);

		bool  Is_zero (void) const;
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		const
		size_u&   Raw (void) const;
		size_u&   Raw (void) ;

		bool  Set (const uint32_t _width, const uint32_t _height);

		uint32_t  W (void) const;
		bool      W (const uint32_t);

		uint32_t  Width (void) const;
		bool      Width (const uint32_t);

	public:
		CSize_U&  operator = (const CSize_U&);
		CSize_U&  operator = (CSize_U&&);

		CSize_U&  operator <<(const uint32_t _width);
		CSize_U&  operator >>(const uint32_t _height);

		operator const size_u& (void) const;
		operator       size_u& (void) ;

		bool operator == (const CSize_U&) const;
		bool operator != (const CSize_U&) const;

		CSize_U& operator += (const CSize_U&); // maybe it woild be better to return boolean value that indicates of this size changing;
		CSize_U& operator -= (const CSize_U&);

	private:
		size_u m_size;
	};
}}}

typedef geometry::base::_2D::CSize     TSize ;
typedef geometry::base::_2D::CSize_U   TSizeU;

TSize   operator + (const TSize& , const TSize& );
TSize   operator - (const TSize& , const TSize& );

TSizeU  operator + (const TSizeU&, const TSizeU&);
TSizeU  operator - (const TSizeU&, const TSizeU&);

namespace geometry { namespace base { namespace _2D {

	class CAnchor : public CPoint_2 { typedef CPoint_2 TBase;
	public:
		 CAnchor (const int32_t _x = 0, const int32_t _y = 0);
		 CAnchor (const CAnchor&);
		 CAnchor (CAnchor&&);
		~CAnchor (void) ;

	public:
		CAnchor& operator = (const CAnchor&);
		CAnchor& operator = (CAnchor&&);
		CAnchor& operator <<(const t_point&);
		CAnchor& operator <<(const t_rect&);    // sets: _x = _rect.left; _y = _rect.top;
	};

	class CPosition {
	public:
		 CPosition (void);
		 CPosition (const CPosition&); CPosition (CPosition&&) = delete;
		~CPosition (void) = default;

	public:
		const
		CAnchor&   Anchor (void) const;
		CAnchor&   Anchor (void) ;	
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		const
		CSize_U&   Size (void) const;
		CSize_U&   Size (void) ;

	public:
		CPosition& operator = (const CPosition&);
		CPosition& operator = (CPosition&&) = delete;

		CPosition& operator <<(const CAnchor&);
		CPosition& operator <<(const CSize_U&);
		CPosition& operator <<(const t_point&); // sets the anchor point;
		CPosition& operator <<(const t_rect& ); // transfers rectangle to position as follows: anchor={x<<left|y<<top};size={right-left|bottom-top};

		operator const t_rect (void) const;     // transfers position to rectangle as follows: anchor>>left|top;right=left+size.width;bottom=top+size.height;
		

	private:
		CAnchor   m_anchor;
		CSize_U   m_size;
	};
}}}

#endif/*_2D_BASE_H_INCLUDED*/