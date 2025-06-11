#ifndef _SFXTABSEXT_H_INCLUDED
#define _SFXTABSEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2020 at 9:35:07a, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack shared tabbed control tab items interface declaration file;
*/
#if (0)
#include "shared.gen.sys.err.h"
#include "shared.uix.ctrl.defs.h"
#include "shared.uix.ctrl.base.rnd.h"
#include "shared.uix.ctrl.base.lay.h"

namespace ST_Ctrls { namespace layout { class CTabLayout; }

	using shared::sys_core::CError;
	using ex_ui::controls::CAlign ;
	using ex_ui::controls::CState ;

	class CTab { friend class ST_Ctrls::layout::CTabLayout;
	private:
		DWORD      m_id    ;
		TLayersEx  m_layers;
		CState     m_state ;

	public:
		 CTab (void);
		 CTab (const CTab&);
		 CTab (LPCWSTR _lp_sz_cap);
		~CTab (void);

	public:
		LPCWSTR    Caption(void) const;
		CStringW&  Caption(void)      ;
		DWORD      Id     (void) const;
		DWORD&     Id     (void)      ;
		const
		TLayersEx& Layers (void) const;
		TLayersEx& Layers (void)      ;
		const
		CState&    State  (void) const;
		CState&    State  (void)      ;

	public:
		CTab& operator =  (const CTab&  );
		CTab& operator << (const CState&);
		CTab& operator << (const CStringW& _cs_cap);
		CTab& operator << (const DWORD _tab_id);
		CTab& operator << (LPCWSTR _lp_sz_cap);
	};

	typedef ::std::vector<CTab> TTabArray;

	interface ITabEvents;
	class CTabs {
	public:
		enum _na : INT { e_na = -1 };
	private:
		ITabEvents* m_sink ;
		TTabArray   m_tabs ;
		CError      m_error;

	public:
		 CTabs (void);
		 CTabs (const CTabs&);
		~CTabs (void);

	public:
		const INT   Active (void) const    ;        // returns an index of tab that has state selected, otherwise e_na (-1);
		HRESULT     Active (const INT _ndx);        // no tab cannot be active, otherwise, it does not have a sense; updated: out of tab range makes no active tab; 
		HRESULT     Append (const CTab&)   ;
		HRESULT     Append (LPCWSTR _lp_sz_cap);
		size_t      Count  (void) const    ;
		TErrorRef   Error  (void) const    ;
		VOID        Events (ITabEvents*)   ;
		const INT   Has    (const POINT& pt) const; // returns an index of tab if it's found, otherwise e_na (-1);
		const
		CTab&       Tab    (const INT _ndx ) const;
		CTab&       Tab    (const INT _ndx )      ;
		const
		TTabArray&  RawTabs(void) const ;
		HRESULT     Reset  (void)       ; // removes all tabs;

	public:
		CTabs& operator = (const CTabs&);
		CTabs& operator <<(const CTab& );
		CTabs& operator <<(const DWORD _active_ndx);
		CTabs& operator <<(ITabEvents* );
		CTabs& operator <<(LPCWSTR _lp_sz_cap);
	};
}
#endif
#endif/*_SFXTABSEXT_H_INCLUDED*/