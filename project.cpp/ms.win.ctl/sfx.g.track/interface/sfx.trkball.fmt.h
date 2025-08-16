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

namespace format { // ToDo::CBorder and CColor class are copied from tabbed control project; perhaps some shared classes is would be better approch;
	class CColor {
	public:
		 CColor (void); CColor (const CColor&) = delete; CColor (CColor&&) = delete;
		~CColor (void);

		rgb_color Get  (const TStateValue) const;

	public:
		rgb_color Disabled (void) const;
		rgb_color Normal   (void) const;
		rgb_color Selected (void) const;

	public:
		CColor& operator = (const CColor&) = delete;
		CColor& operator = (CColor&&) = delete;
	};

	class CBorder {
	public:
		 CBorder (void); CBorder (const CBorder&) = delete; CBorder (CBorder&&) = delete;
		~CBorder (void);
	public:
		const
		CColor&  Color (void) const;
		CColor&  Color (void) ;

	public:
		CBorder& operator = (const CBorder&) = delete;
		CBorder& operator = (CBorder&&) = delete;
	private:
		CColor m_color;
	};
}

	class CFormat : public TBase {
	friend class  CControl;
	private:
		 CFormat (CControl&); CFormat (void) = delete; CFormat (const CFormat&); CFormat (CFormat&&) = delete;
		~CFormat (void);

	public:
		const
		format::CBorder&  Border (void) const;
		void      Default(void);

	private:
		CFormat&  operator = (const CFormat&) = delete;
		CFormat&  operator = (CFormat&&) = delete;

	private:
		CControl& m_ctrl;
		format::CBorder   m_border;
	};

}}}}

#endif/*_SFX_TRK_BALL_FMT_H_INCLUDED*/