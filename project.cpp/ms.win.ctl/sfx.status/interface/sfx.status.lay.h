#ifndef _SFXSTATUSLAY_H_INCLUDED
#define _SFXSTATUSLAY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Aug-2020 at 11:36:16p, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack shared status bar control layout interface declaration file.
*/
#include "sfx.status.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace status { class CControl;

	using namespace ex_ui::controls::sfx;

namespace layout {

	class CStyle {
	public:
		enum e_stick {
			e_left = 0,  // this is default side of stick of a pane;
			e_right      // this is a case when a pane is sticked to the right side of window and changes its position when window is resized;
		};
		enum e_width {
			e_fixed = 0, // this is default type of a panel width, it is defined by given value of the width and is not changed by layout;
			e_auto  = 1, // when this type of panel width is set, the panel will automatically fill all available space of the control;
		};

	public:
		 CStyle (void);
		 CStyle (const CStyle&); CStyle (CStyle&&) = delete;
		~CStyle (void);

	public:
		const
		e_stick   Stick (void) const;
		e_stick&  Stick (void)      ;
		const
		e_width   Width (void) const;
		e_width&  Width (void)      ;

	public:
		CStyle& operator = (const CStyle&);
		CStyle& operator <<(const e_stick);
		CStyle& operator <<(const e_width);

	private:
		e_stick  m_e_stick;
		e_width  m_e_width;
	};
}
	//
	// if several panels have an auto-width style/type available space is divided to equal values for all such panels;
	//
	class CLayout {
	friend class  CControl;
	private:
		 CLayout (CControl&); CLayout (void) = delete; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void);

	public:
		TError&  Error  (void) const;
		uint32_t Height (void) const;
		bool     Height (const uint32_t);           // returns 'true' in case of height value is changed;
		bool     Is     (void) const;               // returns true if height > 0;

		err_code Update (void) ;                    // updates the internal components' layout by using this control window client area;
		err_code Update (const t_rect& _rc_area);   // updates status bar control window position into an area provided;

	public:
		CLayout& operator <<(const t_rect& _rc_area);        // updates status bar control window position in accordance with area  ;
		t_rect   operator = (const t_rect& _rc_area) const;  // returns calculated rectangle of status bar control for area provided;

	private:
		CLayout& operator = (const CLayout&) = delete;
		CLayout& operator = (CLayout&&) = delete;

	private:
		mutable
		CError    m_error ;
		CControl& m_ctrl  ;
		uint32_t  m_height; // this is status bar control height that has default value of 28px;
	};	

}}}}

#endif/*_SFXSTATUSLAY_H_INCLUDED*/