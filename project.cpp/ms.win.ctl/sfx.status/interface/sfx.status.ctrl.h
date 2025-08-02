#ifndef _SFXSTATUSCTRL_H_INCLUDED
#define _SFXSTATUSCTRL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-May-2009 at 10:02:53pm, GMT+3, Rostov-on-Don, Monday;
	This is ST Status Bar Control interface declaration file.
	-----------------------------------------------------------------------------
	Reincarnation to Ebo Pack is made on 22-Aug-2020 at 7:16:49a, UTC+7, Novosibirsk, Saturday;
*/
#include "sfx.status.fmt.h"
#include "sfx.status.inc.h"
#include "sfx.status.lay.h"
#include "sfx.status.ext.h"

#include "ctl.base.border.h"
#include "ctl.base.image.h"

namespace ex_ui { namespace controls { namespace sfx { namespace status {

	using namespace  ex_ui::controls::sfx;
	using CImages  = ex_ui::controls::CImages;
	using CBorders = ex_ui::controls::borders::CBorders_for_rect;

	class CControl {
	public:
		 CControl (void); CControl (const CControl&) = delete; CControl (CControl&&) = delete;
		~CControl (void);

	public:
		const
		CBorders& Borders(void) const;
		CBorders& Borders(void) ;

		err_code  Create (const HWND hParent, const uint32_t _ctrl_id); // returns the error code, if this control window is already created;
		err_code  Destroy(void) ;
		TError&   Error  (void) const;

		const
		CFormat&  Format (void) const;
		CFormat&  Format (void)      ;

		const
		CImages&  Images (void) const;
		CImages&  Images (void) ;

		bool    Is_valid (void) const;  // checks for: (1) window pointer; (2) this control window handle validity;

		const
		CLayout&  Layout (void) const;
		CLayout&  Layout (void) ;

		const
		CPanes&   Panes  (void) const;
		CPanes&   Panes  (void)      ;

		err_code  Refresh(void) ;
		CWindow   Window (void) const; // returns status bar control internal window handle;

	private:
		CControl& operator = (const CControl&) = delete;
		CControl& operator = (CControl&&) = delete;

	protected:
		CBorders m_borders;
		CFormat  m_format ;
		CError   m_error  ;
		CImages  m_images ; // ToDo: this field may be put inside this control window class;
		CLayout  m_layout ;
		CPanes   m_panes  ;
		HANDLE   m_wnd_ptr;
		uint32_t m_ctrl_id;
	};

}}}}
#endif/*_SFXSTATUSCTRL_H_1BAC705D_DCAB_4BCA_99E0_6ADCC0305970_INCLUDED*/