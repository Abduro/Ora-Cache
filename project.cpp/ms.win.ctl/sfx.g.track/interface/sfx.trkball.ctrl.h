#ifndef _SFX_TRACK_CTRL_H_INCLUDED
#define _SFX_TRACK_CTRL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Aug-2025 at 04:24:01.580, UTC+4, Batumi, Saturday;
	This is Ebo Pack trackball user control interface declaration file;
*/
#include "sfx.trkball.fmt.h"
#include "sfx.trkball.inc.h"
#include "sfx.trkball.lay.h"
namespace ex_ui { namespace controls { namespace sfx { namespace track {

	using namespace ex_ui::controls::sfx;

	class CControl {
	public:
		 CControl (void); CControl (const CControl&) = delete; CControl (CControl&&) = delete;
		~CControl (void);

	public:
		const
		CBorders& Borders(void) const;
		CBorders& Borders(void) ;

		err_code  Create (const HWND hParent, const uint32_t _ctrl_id);
		err_code  Destroy(void) ;
		TError&   Error  (void) const;
		const
		CFormat&  Format (void) const;
		CFormat&  Format (void)      ;

		bool    Is_valid (void) const;  // checks for: (1) window pointer; (2) this control window handle validity;
		const
		CLayout&  Layout (void) const;
		CLayout&  Layout (void) ;

	private:
		CControl& operator = (const CControl&) = delete;
		CControl& operator = (CControl&&) = delete;

	protected:
		CBorders  m_borders;
		CFormat   m_format ;
		CError    m_error  ;
		CLayout   m_layout ;
		HANDLE    m_wnd_ptr;
		uint32_t  m_ctrl_id;
	};
}}}}

#endif/*_SFX_TRACK_CTRL_H_INCLUDED*/