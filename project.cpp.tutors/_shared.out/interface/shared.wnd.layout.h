#ifndef _SHARED_WND_LAYOUT_H_INCLUDED
#define _SHARED_WND_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Aug-2025 at 04:57:55.510, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorial main window layout interface declaration file;
*/
#include "shared.defs.h"

namespace ex_ui { namespace popup { namespace layout {

	using namespace shared::defs;

	// https://wikidiff.com/position/placement ;
	// https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_geticonsize ;
	//
	// this class is used as a base one for providing an ability of saving current rectangle data of GUI component;
	// it is expected the rectangle is calculated by layout class and is saved for using by drawing function(s);
	class CPlacement {
	public:
		 CPlacement (void);
		 CPlacement (const CPlacement&); CPlacement (CPlacement&&) = delete; // not required yet;
		~CPlacement (void);
	// https://learn.microsoft.com/en-us/windows/win32/gdi/rectangle-functions ;
	public:
		bool   Includes  (const t_point&) const; // checks this rectangle contains input point;  if placement rectangle is empty the false is returned;
		bool   Intercepts(const t_rect&) const;  // checks an interception with input rectangle; empty rectangles are not taken into account;

		bool   DoNormal  (void)      ; // empty rectangle is not affected, otherwise rectangle sides' values that are not normal are swapped;
		bool   IsNormal  (void) const; // this is required that left < right and top < bottom, otherwise Includes() never returns true;
		const
		t_rect& Rect (void) const;
		t_rect& Rect (void)      ;

	public:
		CPlacement& operator = (const CPlacement&); CPlacement& operator = (CPlacement&&) = delete;
		CPlacement& operator <<(const t_rect&);

		operator const t_rect& (void) const;
		operator       t_rect& (void) ;

		const
		t_rect& operator ()(void) const;
		t_rect& operator ()(void) ;

	protected:
		t_rect   m_rect;
	};

	class CPosition : public CPlacement { typedef CPlacement TBase;
	public:
		 CPosition (void); CPosition (const CPosition&); CPosition (CPosition&&) = delete; // not required yet;
		~CPosition (void) = default;

	public:
		// it is supposed the left-top corner of the window frame is at the anchor point;
		// calculates a center point of the position in absolute coordinates;
		const
		t_point    Center (void) const;

		CPosition& operator = (const CPosition&) ; CPosition& operator = (CPosition&&) = delete;
		const
		CPlacement&  operator ()(void) const;
		CPlacement&  operator ()(void) ;
	};

	// https://math.stackexchange.com/questions/2556531/negative-length-is-there-a-specific-reason-that-a-length-cannot-be-negative ;

	struct t_size_u {
		uint32_t cx = 0;
		uint32_t cy = 0;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-monitorfrompoint ;
	// this class is for determining the position of a window in the center of primary monitor work area;
	class CPrimary : public CPosition {
	                typedef CPosition TBase;
	public:
		 CPrimary (void) ; CPrimary (const CPrimary&) = delete; CPrimary (CPrimary&&) = delete;
		~CPrimary (void) ;

	public:
		t_rect Autosize (void) const;                        // a window size is calculated as: width = resolution / 2; height = (resolution / 4) * 2;
		t_rect Centered (const t_size_u& _size) const;       // returns a rectangle of the specidied size at the center of monitor area;
		t_size Default  (const float  _coeff = 1.56) const ; // this is a default size of a window; the size is dependable on current resolution;

		_pc_sz Name (void) const;  // returns the primary monitor name that is set by operating system; this name is used in work with drivers usually;

		CPrimary& operator = (const CPrimary&) = delete; CPrimary& operator = (CPrimary&&) = delete;
	private:
		CString m_name;
	};

	// https://learn.microsoft.com/en-us/troubleshoot/windows-client/shell-experience/video-stabilization-resolution-limits-h-264 ;
	// https://en.wikipedia.org/wiki/Advanced_Video_Coding ;
	typedef ::std::vector<t_size> TRatios;

	class CRatios {
	public:
		 CRatios (void);
		 CRatios (const CRatios&); CRatios (CRatios&&) = delete;
		~CRatios (void);

	public:
		t_rect Accepted (const t_rect& _work_area) const; // gets an accepted ratio for primary monitor work area;

		const
		TRatios& Get (void) const ;
		TRatios& Get (void)       ;

	public:
		CRatios& operator = (const CRatios&);
		CRatios& operator = (CRatios&&) = delete;

	private:
		TRatios  m_ratios;
	};

}}}

#endif/*_SHARED_WND_LAYOUT_H_INCLUDED*/