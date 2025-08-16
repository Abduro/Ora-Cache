#ifndef _SFX_TRK_BALL_LAY_H_INCLUDED
#define _SFX_TRK_BALL_LAY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Aug-2025 at 23:49:27.700,(UTC+4), Batumi, Monday;
	This is Ebo Pack trackball user control layout interface declaration file;
*/
#include "sfx.trkball.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace track { class CControl;

	using CSides = ex_ui::controls::layout::CMargins_of_rect::CSides;
	using TSide  = ex_ui::controls::layout::CMargins_of_rect::CSides::_part;

	using CPadding = ex_ui::controls::layout::CPadding_of_rect;

	class CLayout;

namespace layout {}

	class CLayout {
	friend class  CControl;
	private:
		 CLayout (CControl&); CLayout (void) = delete; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void);

	public:
		TError&   Error  (void) const;
		const
		CPadding& Padding(void) const;
		CPadding& Padding(void) ;
		const
		t_size&   Pref_Sz(void) const;    // gets preferable size of this control; by default is 64x64px;
		err_code  Pref_Sz(const t_size&); // sets preferable size of this control; the rule: must be a square and each size not less than 64px;

		err_code  Update (void) ;
		err_code  Update (const t_rect& _rc_area);

	private:
		CLayout&  operator = (const CLayout&) = delete;
		CLayout&  operator = (CLayout&&) = delete;

	private:
		mutable
		CError    m_error ;
		CControl& m_ctrl  ;
		CPadding  m_padding;
		t_size    m_pref_sz;
		t_rect    m_rect  ;  // cached client area rectangle;
	};

}}}}


#endif/*_SFX_TRK_BALL_LAY_H_INCLUDED*/