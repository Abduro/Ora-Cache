#ifndef _CTL_BASE_PANE_H_INCLUDED
#define _CTL_BASE_PANE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-May-2025 at 11:36:46.866, UTC+4, Batumi, Tuesday;
	This is Ebo Pack user control base pane interface declaration file;
*/
#include "ctl.base.defs.h"
#include "ctl.base.border.h"

namespace ex_ui { namespace controls {

	using CBorders = ex_ui::controls::borders::CSet;

	class CPane {
	public:
		 CPane (void); CPane (const CPane&) = delete; CPane (CPane&&) = delete;
		~CPane (void);

	public:
		CPane& operator = (const CPane&) = delete;
		CPane& operator = (CPane&&) = delete;

	protected:
		CBorders m_borders;
	};
}}


#endif/*_CTL_BASE_PANE_H_INCLUDED*/