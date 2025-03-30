#ifndef _WND_LAYOUT_H_INCLUDED
#define _WND_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Dec-2021 at 2:01:28.3414539 pm, UTC+7, Novosibirsk, Saturday;
	This is base window layout interface declaration file;
*/
#include "sys.error.h"
#include "2d.base.h"

#include "shared.types.h"

namespace ex_ui { namespace popup {  namespace layout {

	using namespace shared::types;

	using CError = shared::sys_core::CError;
	using TError = const CError;

	// https://wikidiff.com/position/placement ;

	class CPosition {
	public:
		 CPosition (void) ;
		 CPosition (const TPoint&, const TSize &);
		 CPosition (const CPosition&) ;
		 CPosition (CPosition&&);
		~CPosition (void);

	public:
		const
		TPoint&    Anchor (void) const;  // gets a point where an object is anchered to by its left-top corner; (read-obly);
		TPoint&    Anchor (void) ;

		const
		t_point    Center (void) const;  // calculates a center point of the position in absolute coordinates;

#if defined(_DEBUG)
		enum e_print : uint32_t {
			e_all   = 0x0,  // prints out all attributes' values, including this class name, namespace path;
			e_no_ns = 0x1,  // prints out the same as above option, but no namespace path;
			e_req   = 0x2,  // prints out the attributes' values only;
		};
		CString    Print (const e_print = e_print::e_all) const;
#endif
		const
		TSize &    Size (void) const;    // gets a width and a height of an object;
		TSize &    Size (void);

	public:
		CPosition& operator = (const CPosition&);
		CPosition& operator = (CPosition&&);

		CPosition& operator <<(const TPoint&);
		CPosition& operator <<(const TSize &);

		CPosition& operator <<(const t_rect& _pos); // sets the anchor(r.left|r.top) and the size(r.right-r.left|r.bottom-r.top) values;

	protected:
		TPoint  m_anchor;
		TSize   m_size  ;  // a size class of unsigned values cannot be used here due to compiler requirement to cast data types;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-monitorfrompoint ;
	// this class is for determining the position of a window in the center of primary monitor work area;
	class CPrimary : public CPosition {
	                typedef CPosition TBase;
	public:
		 CPrimary (void) ;
		~CPrimary (void) ;

	public:
		t_rect Autosize (void) const;                       // a window size is calculated as: width = resolution / 2; height = (resolution / 4) * 2;
		t_rect Centered (const TSize& _size) const;         // returns a rectangle of the specidied size at the center of monitor area;
		t_size Default  (const float _coeff = 1.56) const ; // this is a default size of a window; the size is dependable from current resolution;
	};

	class CWndLayout : public CPrimary {
	                  typedef CPrimary TBase;
	public:
		 CWndLayout (void);
		~CWndLayout (void);

	public:
		TError& Error (void) const;  // not used yet;

	private:
		CError   m_error;
	};
}}}

typedef ex_ui::popup::layout::CWndLayout TWndLayout;

#endif/*_WND_LAYOUT_H_INCLUDED*/