#ifndef _SHAREDUIXCTRLBASEFMT_H_INCLUDED
#define _SHAREDUIXCTRLBASEFMT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Aug-2020 at 6:02:47a, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack shared control format base interface declaration file.
*/
#include "ctl.base.defs.h"
#include "ctl.base.border.h"
#include "ctl.base.layout.h"
#include "ctl.base.props.h"

namespace ex_ui { namespace controls { namespace format {

	using namespace ex_ui::controls;
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsyscolor
	// https://www.abbreviations.com/abbreviation/background

	using CMargins = ex_ui::controls::layout::CMargins_of_rect;
	using CPadding = ex_ui::controls::layout::CPadding_of_rect;

	using CAlign   = ex_ui::controls::properties::CAlign;
	using CHAling  = ex_ui::controls::properties::CAlign_Horz;
	using CVAling  = ex_ui::controls::properties::CAlign_Vert;

	using CProperty = ex_ui::controls::properties::CProperty ;
	using CBorders  = ex_ui::controls::borders::CBorders_for_rect;

	class CBkgnd
	{
	public:
		 CBkgnd (void);
		 CBkgnd (const CBkgnd&); CBkgnd (CBkgnd&&) = delete;
		~CBkgnd (void);

	public:
		const
		CGradient&  Gradient(void) const;
		CGradient&  Gradient(void) ;

		uint16_t    ImageRes(void) const;     // returns an identifier of image resource, if any;
		bool        ImageRes(const uint16_t); // sets image resource identifier; returns 'true' in case of change value; 0 - no image;

		const
		CMargins&   Margins (void) const;
		CMargins&   Margins (void) ;
		const
		CPadding&   Padding (void) const;
		CPadding&   Padding (void) ;
#if defined(_DEBUG)
		CString     Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		TRgbQuad&   Solid (void) const;
		TRgbQuad&   Solid (void)      ;

	public:
		CBkgnd&  operator = (const CBkgnd& _src);     // makes a copy from the object provided;
		CBkgnd&  operator = (CBkgnd&&) = delete ;     // not is required yet;
		CBkgnd&  operator <<(const CGradient&  );     // sets gradient;
		CBkgnd&  operator <<(const CMargins&   );     // sets margins ;
		CBkgnd&  operator >>(const CPadding&   );     // sets padding ;
		CBkgnd&  operator <<(const uint16_t _res_id); // loads an image by resource identifier;
		CBkgnd&  operator <<(const TRgbQuad&   );     // sets solid color;

	protected:
		TRgbQuad    m_clr_solid;
		CGradient   m_clr_grad ;
		uint16_t    m_img_res  ; // background image resource identifier; when zero then is not applicable;
		CMargins    m_margins  ; // a control must provide margins for its background and all components;
		CPadding    m_padding  ;
	};

	class CFontSpec {
	public:
		 CFontSpec (void) ;
		 CFontSpec (const CFontSpec&) ; CFontSpec (CFontSpec&&) = delete;
		~CFontSpec (void);

	public:
		const
		CAlign&     Align  (void) const;
		CAlign&     Align  (void)      ;
		_pc_sz      Family (void) const;
		err_code    Family (_pc_sz _p_fnt_name);
		rgb_color   Fore   (void) const;
		rgb_color&  Fore   (void)      ;
		const
		TFontOpts&  Options(void) const;
		TFontOpts&  Options(void)      ;
#if defined(_DEBUG)
		CString     Print  (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		int32_t     Size   (void) const;
		int32_t&    Size   (void)      ;

	public:
		CFontSpec&  operator = (const CFontSpec&);
		CFontSpec&  operator = (CFontSpec&&) = delete;
		CFontSpec&  operator <<(const CAlign&);
		CFontSpec&  operator >>(const rgb_color _clr_fore); // error C2535: member function already defined or declared; there is a mix with DWORD of size attribute;
		CFontSpec&  operator <<(const int32_t  _dw_size );
		CFontSpec&  operator <<(const TFontOpts&);
		CFontSpec&  operator <<(_pc_sz _lp_sz_family);

	protected:
		CAlign      m_align   ;  // text alignment;
		rgb_color   m_fore    ;  // fore color of the font;
		CString     m_name    ;  // font name/family, by default 'verdana';
		TFontOpts   m_opts    ;  // include font options for creating a font in accordance with required options;
		int32_t     m_size    ;  // font size, by default it is a font size of desktop item labels: -12 pt; the size in logical units;
	};

	class CBase {
	public:
		 CBase (void);
		 CBase (const CBase&); CBase (CBase&&) = delete;
		~CBase (void);

	public:
		const
		CBkgnd&     Bkgnd (void) const;
		CBkgnd&     Bkgnd (void) ;
		const
		CBorders&   Borders (void) const;
		CBorders&   Borders (void) ;
		const
		CFontSpec&  Font (void) const;
		CFontSpec&  Font (void) ;
#if defined(_DEBUG)
		CString     Print  (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CBase&  operator = (const CBase& );
		CBase&  operator = (CBase&&) = delete;
		CBase&  operator <<(const CBkgnd&);
		CBase&  operator <<(const CBorders&);
		CBase&  operator <<(const CFontSpec&);

	protected:
		CBkgnd      m_bkgnd  ;
		CBorders    m_borders;
		CFontSpec   m_spec   ;
	};
}}}

#endif/*_SHAREDUIXCTRLBASEFMT_H_INCLUDED*/