#ifndef _WND_LAYOUT_H_INCLUDED
#define _WND_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Dec-2021 at 2:01:28.3414539 pm, UTC+7, Novosibirsk, Saturday;
	This is base window layout interface declaration file;
*/
#include "wnd.defs.h"
#include "2d.base.h"
#include "2d.shape.rect.h"

namespace ex_ui { namespace popup {  namespace layout {

	using namespace ::ex_ui::popup::defs;

	using TPosition = geometry::_2D::base::CPosition;
	using CRect  = geometry::_2D::shapes::COblong;

	// https://wikidiff.com/position/placement ;
	// https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_geticonsize ;
	//
	// this class is used as a base one for providing an ability of saving current rectangle data of GUI component;
	// it is expected the rectangle is calculated by layout class and is saved for using by drawing function(s);
	class CPlacement {
	public:
		 CPlacement (void);
		 CPlacement (const CPlacement&);
		~CPlacement (void);
	// https://learn.microsoft.com/en-us/windows/win32/gdi/rectangle-functions ;
	public:
		bool   Includes  (const point_t&) const; // checks this rectangle contains input point;  if placement rectangle is empty the false is returned;
		bool   Intercepts(const rect_t&) const;  // checks an interception with input rectangle; empty rectangles are not taken into account;

		bool   DoNormal  (void)      ; // empty rectangle is not affected, otherwise rectangle sides' values that are not normal are swapped;
		bool   IsNormal  (void) const; // this is required that left < right and top < bottom, otherwise Includes() never returns true;
		const
		rect_t& Rect (void) const;
		rect_t& Rect (void)      ;

	public:
		CPlacement& operator = (const CPlacement&);
		CPlacement& operator <<(const rect_t&);
	protected:
		rect_t   m_rect;
	};

	class CPosition : public TPosition { typedef TPosition TBase; // this class needs to be reviewed due to it is not compatible with WinAPI: rect_t is not used;
	public:
		CPosition (void); CPosition (const CPosition&) = delete; CPosition (CPosition&&) = delete; ~CPosition (void) = default;

		// it is supposed the left-top corner of the window frame is at the anchor point;
		// calculates a center point of the position in absolute coordinates;
		const
		point_t  Center (void) const;
		rect_t   Place  (void) const;

		TError&  Error (void) const;

		err_code Load (void);         // loads the app/main window position from the regestry;
		err_code Save (const HWND);   // saves the app/main window position in the regestry;

		const
		rect_t&  Get (void) const;    // gets the reference to the rectangle of the main window frame position on the screen; (ro);
		bool     Set (const rect_t&); // sets the window rectangle;

		const
		rect_t&  operator ()(void) const;
		rect_t&  operator ()(void) ;

		CPosition& operator <<(const rect_t&);

	private:
		CPosition& operator = (const CPosition&) = delete; CPosition& operator = (CPosition&&) = delete;
		rect_t  m_rect;
		CError  m_error;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-monitorfrompoint ;
	// this class is for determining the position of a window in the center of primary monitor work area;
	class CPrimary : public CPosition {
	                typedef CPosition TBase;
	public:
		 CPrimary (void) ;
		~CPrimary (void) ;

	public:
		rect_t Autosize (void) const;                        // a window size is calculated as: width = resolution / 2; height = (resolution / 4) * 2;
		rect_t Centered (const TSizeU& _size) const;         // returns a rectangle of the specidied size at the center of monitor area;
		t_size Default  (const float  _coeff = 1.56) const ; // this is a default size of a window; the size is dependable from current resolution;
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
		RECT   Accepted (const rect_t& _work_area) const; // gets an accepted ratio for primary monitor work area;
		RECT   Accepted (const CPosition&  _res) const;   // gets an accepted ratio for primary monitor resolution;

		const
		TRatios& Get (void) const;
		TRatios& Get (void) ;

	public:
		CRatios& operator = (const CRatios&);
		CRatios& operator = (CRatios&&) = delete;

	private:
		TRatios  m_ratios;
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