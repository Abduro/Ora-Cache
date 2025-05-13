#ifndef _UIX_GDI_BLEND_H_INCLUDED
#define _UIX_GDI_BLEND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 09:58:01.060, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI blend function wrapper interface declaration file;
*/
#include "uix.gdi.defs.h"

namespace ex_ui { namespace draw { namespace blend {

	using namespace ex_ui::draw::defs;
	// https://stackoverflow.com/questions/11645532/alphablend-function << just as the example of good explanation ;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-blendfunction ;

	typedef BLENDFUNCTION TBlendFun;

	class CBlend_Wrap {
	public:
		 CBlend_Wrap (void); CBlend_Wrap (const CBlend_Wrap&) = delete; CBlend_Wrap (CBlend_Wrap&&) = delete;
		~CBlend_Wrap (void) = default;

	public:
#if defined(_DEBUG)
		static
		CString Print (const TBlendFun&, const e_print = e_print::e_all);
		CString Print (const e_print = e_print::e_all) const;
#endif
		const
		TBlendFun&  Ref (void) const;
		TBlendFun&  Ref (void) ;

	public:
		operator const TBlendFun& (void) const;
		operator       TBlendFun& (void) ;

	private:
		CBlend_Wrap& operator = (const CBlend_Wrap&) = delete;
		CBlend_Wrap& operator = (CBlend_Wrap&&) = delete;

	private:
		TBlendFun  m_bl_fun;
	};

	class CBlender {
	public:
		 CBlender (void); CBlender (const CBlender&) = delete; CBlender (CBlender&&) = delete;
		~CBlender (void);

	public:
		TError&   Error (void) const;

	private:
		CBlender& operator = (const CBlender&) = delete;
		CBlender& operator = (CBlender&&) = delete;

	private:
		CError  m_error;
	};

}}}


#endif/*_UIX_GDI_BLEND_H_INCLUDED*/