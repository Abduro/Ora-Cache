#ifndef _WND_LAYOUT_H_INCLUDED
#define _WND_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Dec-2021 at 2:01:28.3414539 pm, UTC+7, Novosibirsk, Saturday;
	This is base window layout interface declaration file;
*/
#include "sys.error.h"
#include "2d.base.h"
#include "2d.shape.rect.h"

#include "shared.types.h"

namespace ex_ui { namespace popup {  namespace layout {

	using namespace shared::types;

	using CError = shared::sys_core::CError;
	using TError = const CError;
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
		bool   Includes  (const t_point&) const; // checks this rectangle contains input point;  if placement rectangle is empty the false is returned;
		bool   Intercepts(const t_rect&) const;  // checks an interception with input rectangle; empty rectangles are not taken into account;

		bool   DoNormal  (void)      ; // empty rectangle is not affected, otherwise rectangle sides' values that are not normal are swapped;
		bool   IsNormal  (void) const; // this is required that left < right and top < bottom, otherwise Includes() never returns true;
		const
		t_rect& Rect (void) const;
		t_rect& Rect (void)      ;

	public:
		CPlacement& operator = (const CPlacement&);
		CPlacement& operator <<(const t_rect&);
	protected:
		t_rect   m_rect;
	};

	// https://wikidiff.com/position/placement ;

	class CPosition : public TPosition { typedef TPosition TBase;
	public:
		 CPosition (void);
		~CPosition (void) = default;

	public:
		// it is supposed the left-top corner of the window frame is at the anchor point;
		// calculates a center point of the position in absolute coordinates;
		const
		t_point    Center (void) const;
		t_rect     Place  (void) const;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-monitorfrompoint ;
	// this class is for determining the position of a window in the center of primary monitor work area;
	class CPrimary : public CPosition {
	                typedef CPosition TBase;
	public:
		 CPrimary (void) ;
		~CPrimary (void) ;

	public:
		t_rect Autosize (void) const;                        // a window size is calculated as: width = resolution / 2; height = (resolution / 4) * 2;
		t_rect Centered (const TSizeU& _size) const;         // returns a rectangle of the specidied size at the center of monitor area;
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
		RECT   Accepted (const t_rect& _work_area) const; // gets an accepted ratio for primary monitor work area;
		RECT   Accepted (const CPosition&  _res) const;   // gets an accepted ratio for primary monitor resolution;

		const
		TRatios& Get (void) const ;
		TRatios& Get (void)       ;

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