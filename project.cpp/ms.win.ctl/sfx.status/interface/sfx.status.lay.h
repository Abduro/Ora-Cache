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
	class cPanel {
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
		mutable
		CError    m_error ;
		CControl& m_ctrl  ;
		uint32_t  m_height; // this is status bar control height that has default value of 28px;
	};	

}}}}

#endif/*_SFXSTATUSLAY_H_INCLUDED*/