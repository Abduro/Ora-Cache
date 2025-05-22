#ifndef _UIX_GDI_BLEND_H_INCLUDED
#define _UIX_GDI_BLEND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 09:58:01.060, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI blend function wrapper interface declaration file;
*/
#include "uix.gdi.defs.h"
#include "uix.gdi.object.h"

namespace ex_ui { namespace draw { namespace blend {

	using namespace ex_ui::draw::defs;
	// https://stackoverflow.com/questions/11645532/alphablend-function << just as the example of good explanation ;

	using CAnchor = geometry::_2D::base::CAnchor;
	using CPosition = geometry::_2D::base::CPosition;
	using CPos = CPosition;

	class CInput {
	public:
		 CInput (void); CInput (const CInput&) = delete; CInput (CInput&&) = delete;
		~CInput (void) = default;

	public:
		const HDC  Ctx (void) const;
		const bool Ctx (const HDC) ;

		TError&    Error (void) const;
		const bool Is_valid (void) const;

		const
		CPos&  Position (void) const;  const CPos& Pos (void) const;
		CPos&  Position (void)      ;        CPos& Pos (void)      ;  // just playing with shorter names of the properties;

	public:
		CInput&  operator <<(const HDC);
		CInput&  operator <<(const t_rect&);

	private:
		CInput&  operator = (const CInput&) = delete;
		CInput&  operator = (CInput&&) = delete;

	private:
		mutable
		CError  m_error ;
		HDC     m_h_dc  ;
		CPosition m_pos ;
	};

	class CIn_Out : public CInput { // this is a blend destination input data class;
	public:
		CIn_Out (void);
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
	};

	class CIn_Src : public CInput { // this is a blend source input data class;
	public:
		CIn_Src (void);
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-blendfunction ;

	typedef BLENDFUNCTION TBlendFun;

	// https://learn.microsoft.com/en-us/windows/win32/gdi/alpha-blending-a-bitmap << as a good sample;

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
		bool    PerPixelAlpha (void) const;    // returns an option of using premultiplied value of alpha channel;
		bool    PerPixelAlpha (const bool _b_use, const rgb_value _n_alpha); // returns 'true' in case of this field value is changed;
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
		bool       m_bPerPixelAlpha; // if set to 'true', alpha channel is applied, otherwise alpha value is calculated;
	};

	class CBlender {
	public:
		 CBlender (void); CBlender (const CBlender&) = delete; CBlender (CBlender&&) = delete;
		~CBlender (void);

	public:
		const
		CBlend_Wrap& Func (void) const; // returns a reference to blend function wrapper; (ra);
		CBlend_Wrap& Func (void) ;      // returns a reference to blend function wrapper; (rw);

		err_code  Draw  (void) ;

		TError&   Error (void) const;
		bool   Is_ready (void) const;   // checks input (source) and output (destination) data for validity;

		const
		CIn_Out&  Out (void) const;     // destination device context data wrapper; (ra);
		CIn_Out&  Out (void) ;          // destination device context data wrapper; (rw);
		const
		CIn_Src&  Src (void) const;     // source device context data wrapper; (ra);
		CIn_Src&  Src (void) ;          // source device context data wrapper; (rw);

	private:
		CBlender& operator = (const CBlender&) = delete;
		CBlender& operator = (CBlender&&) = delete;

	private:
		mutable
		CError  m_error;
		CBlend_Wrap m_bl_fun;
		CIn_Out m_in_out;
		CIn_Src m_in_src;
	};

}}}


#endif/*_UIX_GDI_BLEND_H_INCLUDED*/