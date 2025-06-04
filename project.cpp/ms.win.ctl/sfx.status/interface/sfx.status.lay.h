#ifndef _SFXSTATUSLAY_H_4B393BB4_36DD_4D7C_B258_EA4DD332BA87_INCLUDED
#define _SFXSTATUSLAY_H_4B393BB4_36DD_4D7C_B258_EA4DD332BA87_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Aug-2020 at 11:36:16p, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack shared status bar control layout interface declaration file.
*/
#if (0)
#include "shared.gen.sys.err.h"
#include "shared.uix.ctrl.base.lay.h"

namespace ST_Ctrls { class CStatusBar; namespace layout {

	using shared::sys_core::CError ;

	using ex_ui::controls::CSides  ;
	using ex_ui::controls::TSide   ;
	using ex_ui::controls::CMargins;
	using ex_ui::controls::layout::CImage;
	using ex_ui::controls::layout::CText_Ext;

	// TODO: it very looks like a glyph has an image, maybe it is useful to have image cache inside the glyph;
	class CGlyph : public CImage { typedef CImage TBase;
	protected:
		DWORD    m_img_ndx;  // an index of image frame in status bar image list;

	public:
		 CGlyph (void);
		 CGlyph (const CGlyph&);
		~CGlyph (void);

	public:
		DWORD    Image_Ndx(void) const;
		DWORD&   Image_Ndx(void)      ;
		bool     Is       (void) const; // returns true if image resource identifier is set; if rectangle is empty, glyph is invisible;

	public:
		CGlyph&  operator = (const CGlyph& );
		CGlyph&  operator <<(const DWORD _img_ndx);
	};

	class CLayout_Style {
	public:
		enum e_stick {
			e_left = 0,  // this is default side of stick of a panel
			e_right      // this is a case when a panel is sticked to the right side of window and changes its position when window is resized;
		};
		enum e_width {
			e_fixed = 0, // this is default type of a panel width, it is defined by given value of the width and is not changed by layout;
			e_auto  = 1, // when this type of panel width is set, the panel will automatically fill all available space of the control;
		};
	private:
		e_stick  m_e_stick; // stick style;
		e_width  m_e_width; // width style;

	public:
		 CLayout_Style (void);
		 CLayout_Style (const CLayout_Style&);
		~CLayout_Style (void);

	public:
		const
		e_stick   Stick (void) const;
		e_stick&  Stick (void)      ;
		const
		e_width   Width (void) const;
		e_width&  Width (void)      ;

	public:
		CLayout_Style& operator = (const CLayout_Style&);
		CLayout_Style& operator <<(const e_stick);
		CLayout_Style& operator <<(const e_width);
	};

	class CPanel_Layout {
	private:
		CLayout_Style  m_style;
		RECT           m_rect ; // this is entire area of a panel;
		TAlign         m_align; // align inside a panel, by default is horz:left|vert:middle;
		CImage         m_image; // an image layout if any image is assigned to this panel;
		TTextLayEx     m_text ; // a text layout;
		DWORD          m_fixed; // a fixed width;
		
	public:
		 CPanel_Layout (void);
		 CPanel_Layout (const CPanel_Layout&);
		~CPanel_Layout (void);

	public:
		const
		TAlign& Align  (void) const;
		TAlign& Align  (void)      ;
		DWORD   Fixed  (void) const;  // gets a fixed size of the width;
		DWORD&  Fixed  (void)      ;  // sets/gets fixed size of the width;
		const
		CImage& Image(void) const;
		CImage& Image(void)      ;
		const
		RECT&   Rect (void) const;
		RECT&   Rect (void)      ;
		const
		CLayout_Style&  Style (void) const;
		CLayout_Style&  Style (void)      ;
		const
		TTextLayEx& Text  (void) const;
		TTextLayEx& Text  (void)      ;
		HRESULT     Update(void)      ;

	public:
		CPanel_Layout& operator = (const CPanel_Layout&);
		CPanel_Layout& operator <<(const CImage&);
		CPanel_Layout& operator <<(const CLayout_Style&);
		CPanel_Layout& operator <<(const TTextLayEx& );
		CPanel_Layout& operator <<(const RECT & );
		CPanel_Layout& operator <<(const TAlign&);
	};
	//
	// if several panels have an auto-width style/type available space is divided to equal values for all such panels;
	//
	class CStatus_Layout {
	protected:
		CStatusBar&  m_control;
		mutable
		CError       m_error  ;
		CMargins     m_margins;
		DWORD        m_height ;
		CGlyph       m_glyph  ;

	public:
		 CStatus_Layout (CStatusBar&);
		~CStatus_Layout (void);

	public:
		TErrorRef    Error  (void) const;
		DWORD        Height (void) const;
		DWORD&       Height (void)      ;
		const
		CGlyph&      Glyph  (void) const;
		CGlyph&      Glyph  (void)      ;
		const bool   Is     (void) const;                        // returns true if height > 0;
		const
		CMargins&    Margins(void) const;
		CMargins&    Margins(void)      ;
		HRESULT      Update (void)      ;
		HRESULT      Update (const RECT& _rc_area);              // updates status bar control window position into an area provided;
	public:
		CStatus_Layout& operator<<(const RECT& _rc_area);        // updates status bar control window position in accordance with area  ;
		const RECT      operator =(const RECT& _rc_area) const;  // returns calculated rectangle of status bar control for area provided;
	};

}}
typedef ST_Ctrls::layout::CPanel_Layout   TPanelLay  ;
typedef ST_Ctrls::layout::CStatus_Layout  TStatusLay ;
typedef ST_Ctrls::layout::CLayout_Style   TLayStyle  ;
#endif
#endif/*_SFXSTATUSLAY_H_4B393BB4_36DD_4D7C_B258_EA4DD332BA87_INCLUDED*/