#ifndef _SFX_TRK_BALL_FMT_H_INCLUDED
#define _SFX_TRK_BALL_FMT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Aug-2025 at 23:46:16.454,(UTC+4), Batumi, Monday;
	This is Ebo Pack trackball user control format interface declaration file;
*/
#include "sfx.trkball.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace track { class CControl;

	using namespace ex_ui::controls::sfx;
	using TBase = ex_ui::controls::format::CBase;
	using CFontSpec = ex_ui::controls::format::CFontSpec;

namespace format {}

	class CFormat : public TBase {
	friend class  CControl;
	private:
		 CFormat (CControl&); CFormat (void) = delete; CFormat (const CFormat&); CFormat (CFormat&&) = delete;
		~CFormat (void);

	private:
		CFormat&  operator = (const CFormat&) = delete;
		CFormat&  operator = (CFormat&&) = delete;

	private:
		CControl& m_ctrl;
	};

}}}}

#endif/*_SFX_TRK_BALL_FMT_H_INCLUDED*/