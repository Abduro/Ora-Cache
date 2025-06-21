#ifndef _UIX_GDI_TEXT_H_INCLUDED
#define _UIX_GDI_TEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 01:44:14.173, UTC+4, Batumi;
	This is Ebo Pack GDI genetric output text block interface declaration file;
*/
#include "uix.gdi.defs.h"

namespace ex_ui { namespace draw { namespace text {

	using namespace ex_ui::draw::defs;

	using CProperty = shared::common::CProperty;

	class CProperty_U : public CProperty { typedef CProperty TBase;
	public:
		 CProperty_U (const uint32_t _n_value, _pc_sz _p_name);
		 CProperty_U (const CProperty_U& );
		 CProperty_U (CProperty_U&&) = delete; // not required yet;
		~CProperty_U (void);

	public:
		const
		CProperty& Base (void) const;
		CProperty& Base (void) ;

		TError&    Error(void) const;

	private:
		CProperty_U&  operator = (const CProperty_U&) = delete;
		CProperty_U&  operator = (CProperty_U&&) = delete;

	protected:
		CError  m_error;
	};

namespace output { namespace horizontal {

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gettextalign ;

	class CAlign_Horz {
	public:
		enum e_value : uint32_t {
		     e_center = TA_CENTER, // The reference point is aligned horizontally with the center of the bounding rectangle;
		     e_left   = TA_LEFT  , // The reference point is on the left edge of the bounding rectangle;
		     e_right  = TA_RIGHT , // The reference point is on the right edge of the bounding rectangle;
		};
	};

	class CAlign_Vert {
	public:
		enum e_value : uint32_t {
		     e_base   = TA_BASELINE, // The reference point is on the base line of the text ;
		     e_bottom = TA_BOTTOM  , // The reference point is on the bottom edge of the bounding rectangle ;
		     e_top    = TA_TOP     , // The reference point is on the top edge of the bounding rectangle ;
		};
	};

	class CAlign {
	public:
		enum e_value : uint32_t {
		     e_update_cp = TA_UPDATECP  , // The current position is updated after each text output call;
		     e_no_update = TA_NOUPDATECP, // The current position is not updated after each text output call;
		};
	
	private:
		CAlign_Horz m_horz;
		CAlign_Vert m_vert;
	};
}}

namespace output { namespace vertical {

	class CAlign_Horz : public CProperty { typedef CProperty TBase;
	public:
		enum e_value : uint32_t {
		     e_center = VTA_BASELINE, // The reference point is on the base line of the text ;
		     e_left   = TA_LEFT     , // The reference point is on the left edge of the bounding rectangle;
		     e_right  = TA_RIGHT    , // The reference point is on the right edge of the bounding rectangle;
		};
	public:
		 CAlign_Horz (const uint32_t = e_value::e_left); CAlign_Horz (const CAlign_Horz&) = delete; CAlign_Horz (CAlign_Horz&&) = delete;
		~CAlign_Horz (void);

	public:
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
	private:
		CAlign_Horz& operator = (const CAlign_Horz&) = delete;
		CAlign_Horz& operator = (CAlign_Horz&&) = delete;
	};

	class CAlign_Vert : public CProperty { typedef CProperty TBase;
	public:
		enum e_value : uint32_t {
		     e_bottom = TA_BOTTOM  , // The reference point is on the bottom edge of the bounding rectangle ;
		     e_center = VTA_CENTER , // The reference point is aligned vertically with the center of the bounding rectangle ;
		     e_top    = TA_TOP     , // The reference point is on the top edge of the bounding rectangle ;
		};
	public:
		 CAlign_Vert (const uint32_t = e_value::e_top); CAlign_Vert (const CAlign_Vert&) = delete; CAlign_Vert (CAlign_Vert&&) = delete;
		~CAlign_Vert (void);

	public:
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
	private:
		CAlign_Vert& operator = (const CAlign_Vert&) = delete;
		CAlign_Vert& operator = (CAlign_Vert&&) = delete;
	};

	class CAlign : public CProperty_U { typedef CProperty_U TBase;
	public:
		enum e_value : uint32_t {
		     e_update_cp = TA_UPDATECP  , // The current position is updated after each text output call;
		     e_no_update = TA_NOUPDATECP, // The current position is not updated after each text output call;
		};
	public:
		 CAlign (const HDC&);  // sets the target context decice handle for dealing with;
		 CAlign (const uint32_t = e_value::e_no_update); CAlign (const CAlign&) = delete; CAlign (CAlign&&) = delete;
		~CAlign (void);

	public:
		err_code Ctx (const HDC&);  // sets target device context handle to deal with;
		err_code Get (void);        // gets alignment flags of the target device context;
		err_code Set (const uint32_t _flags);

	public:
		const
		CAlign_Horz& Horz (void) const;
		CAlign_Horz& Horz (void) ;
#if defined(_DEBUG)
		CString      Print(const e_print = e_print::e_all) const;
#endif
		const
		CAlign_Vert& Vert (void) const;
		CAlign_Vert& Vert (void) ;

	public:
		CAlign& operator <<(const HDC&);

	private:
		CAlign& operator = (const CAlign&) = delete;
		CAlign& operator = (CAlign&&) = delete;
	private:
		CAlign_Horz m_horz;
		CAlign_Vert m_vert;
	private:
		HDC  m_h_dc; // target device context handle;
	};
}}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-textouta ;

	class CTextOut {
	public:
		 CTextOut (void); CTextOut (const CTextOut&) = delete; CTextOut (CTextOut&&) = delete;
		~CTextOut (void);

	private:
		CTextOut&  operator = (const CTextOut&) = delete;
		CTextOut&  operator = (CTextOut&&) = delete;

	};

}}}

#endif/*_UIX_GDI_TEXT_H_INCLUDED*/