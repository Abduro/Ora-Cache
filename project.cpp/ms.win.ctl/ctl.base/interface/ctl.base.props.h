#ifndef _UIXPROPS_H_INCLUDED
#define _UIXPROPS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Dec-2021 at 00:32:59.2008595, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX generic property collection interface declaration file;
*/
#include "ctl.base.defs.h"

namespace ex_ui { namespace controls { namespace properties {

	using namespace ex_ui::controls;
	using CProperty = shared::common::CProperty;
	using IProperty_Events = shared::common::IProperty_Events;

	class CAlign_Horz : public CProperty {
	                   typedef CProperty TBase;
	public:
		enum _value : uint32_t { eLeft = DT_LEFT, eCenter = DT_CENTER, eRight  = DT_RIGHT };

	public:
		 CAlign_Horz (const _value _n_value = _value::eLeft, _pc_sz _p_name = _T("#horz_align"), IProperty_Events* = nullptr);
		 CAlign_Horz (const CAlign_Horz&); CAlign_Horz (CAlign_Horz&&) = delete;
		~CAlign_Horz (void);
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	public:
		CAlign_Horz& operator = (const CAlign_Horz&);
		CAlign_Horz& operator = (CAlign_Horz&&) = delete; // not required yet;

		operator uint32_t (void) const; 
	};

	class CAlign_Vert : public CProperty {
	                   typedef CProperty TBase;
	public:
		enum _value : uint32_t { eMiddle = DT_VCENTER, eTop = DT_TOP , eBottom = DT_BOTTOM };

	public:
		 CAlign_Vert (const _value = _value::eMiddle,  _pc_sz _p_name = _T("#vert_align"), IProperty_Events* = nullptr);
		 CAlign_Vert (const CAlign_Vert&); CAlign_Vert (CAlign_Vert&&) = delete;
		~CAlign_Vert (void);
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	public:
		CAlign_Vert& operator = (const CAlign_Vert&);
		CAlign_Vert& operator = (CAlign_Vert&&) = delete; // not required yet;

		operator uint32_t (void) const;
	};

	class CAlign {
	public:
		 CAlign (void);
		 CAlign (const CAlign&);
		 CAlign (const CAlign_Horz&, const CAlign_Vert&);
		~CAlign (void);

	public:
		void ApplyTo (const t_rect& _rc_available, const t_size& _sz_accept, t_rect& _rc_aligned) const; // applies alignment setting to available rectangle;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	public:
		const
		CAlign_Horz&   Horz(void) const;
		CAlign_Horz&   Horz(void)      ;
		const
		CAlign_Vert&   Vert(void) const;
		CAlign_Vert&   Vert(void)      ;

	public:
		CAlign& operator = (const CAlign&);
		CAlign& operator <<(const CAlign_Horz&);
		CAlign& operator <<(const CAlign_Vert&);
		CAlign& operator <<(IProperty_Events* );
#if (0)
	public:
		CAlign& operator <<(_pc_sz _lp_sz_style); // creates this class object from XML fragment text; for example: {left|middle};
#endif
	protected:
		CAlign_Horz   m_horz;
		CAlign_Vert   m_vert;
	};

	class CState : public CProperty { typedef CProperty TBase;
	public:
		// TODO : unfortunately, mixing values is possible, there is no sense if disabled is mixed with selected value;
		enum e_states : uint32_t {
			eNormal   = 0x00, // default value that indicates no action, which is affected a state, if applied; 
			eDisabled = 0x01, eSelected = 0x02, eHovered = 0x04, ePressed = 0x08,
		};
	explicit
		 CState (const uint32_t _n_value = e_states::eNormal, _pc_sz _p_name = _T("#state"), IProperty_Events* = nullptr);
		 CState (const CState&); CState (CState&&) = delete;
		~CState (void);

	public:
		bool  IsDisabled (void) const;
		bool  IsHovered  (void) const;
		bool  IsPressed  (void) const;
		bool  IsSelected (void) const;          // not sure that it is right name of method; it can be used by button control in default state;
#if defined(_DEBUG)
		CString  Print (void) const;
#endif
	public:
		uint32_t Get (void) const;
		uint32_t Set (const CState::e_states);        // returns previous value;

	public:
		CState& operator = (const CState&);           // makes a copy;
		CState& operator <<(const CState::e_states);  // sets the current state;

	public:
		static size_t     EnumToIndex(const CState::e_states);
		static CString    EnumToName (const CState::e_states);
		static CState::e_states IndexToEnum(const size_t);
	};

	class CStyle : public CProperty { typedef CProperty TBase;
	public:
		enum e_styles : uint32_t {
			eNone   = 0x00,  // default, no style is applied;
			eBorder = 0x01,
		};
		 CStyle (void) = delete; CStyle (const CStyle&) = delete; CStyle (CStyle&&) = delete;
	public:
		 CStyle (const uint32_t _n_value = e_styles::eNone, _pc_sz _p_name = _T("#style"), IProperty_Events* = nullptr);
		~CStyle (void);

	public:
		bool   IsBordered(void) const;
		bool   IsBordered(const bool);  // returns true in case when the value is changhed;
	};
}}}

typedef ex_ui::controls::properties::CAlign            TAlign      ;
typedef ex_ui::controls::properties::CAlign_Horz       THorzAlign  ;
typedef ex_ui::controls::properties::CAlign_Vert       TVertAlign  ;
typedef ex_ui::controls::properties::CProperty         TProperty   ;
typedef ex_ui::controls::properties::CState            TState      ;
typedef ex_ui::controls::properties::CState::e_states  TStateValue ;
typedef ex_ui::controls::properties::CStyle            TStyle      ;
typedef ex_ui::controls::properties::CStyle::e_styles  TStyleValue ;

#define TStateCount (5)

#endif/*_UIXPROPS_H_INCLUDED*/