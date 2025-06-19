#ifndef _SFXTABSEXT_H_INCLUDED
#define _SFXTABSEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2020 at 9:35:07a, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack shared tabbed control tab items interface declaration file;
*/
#include "sfx.tabs.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { class CControl;

	class CLayersEx {
	public:
		 CLayersEx (void) {} CLayersEx (const CLayersEx&) = delete; CLayersEx (CLayersEx&&) = delete;
		~CLayersEx (void) {}
	};

	using TLayersEx = CLayersEx;

	class CTab {
	public:
		 CTab (const uint16_t _id = 0, _pc_sz _lp_sz_cap = nullptr); CTab (CTab&&);
		 CTab (const CTab&);
		~CTab (void);

	public:
		_pc_sz     Caption(void) const;
		CString&   Caption(void)      ;

		uint16_t   Id     (void) const;
		uint16_t&  Id     (void)      ;

		const
		TLayersEx& Layers (void) const;
		TLayersEx& Layers (void)      ;

		const
		t_rect&    Rect   (void) const;
		t_rect&    Rect   (void) ;

		const
		TState&    State  (void) const;
		TState&    State  (void)      ;

	public:
		CTab& operator =  (const CTab&  );
		CTab& operator =  (CTab&&);

		CTab& operator << (const TState&);
		CTab& operator << (const CString& _cs_cap);
		CTab& operator << (const uint16_t _tab_id);
		CTab& operator << (_pc_sz _lp_sz_cap);

	private:
		uint16_t   m_id    ;
		TLayersEx  m_layers;
		t_rect     m_rect  ;
		TState     m_state ;
		CString    m_cap   ;
	};

	typedef ::std::vector<CTab> TTabArray;

	interface ITabEvents;

	class CTabs {
	friend class  CControl;
	private:
		 CTabs (CControl&);    CTabs (void) = delete; 
		 CTabs (const CTabs&); CTabs (CTabs&&);
		~CTabs (void);

	public:
		int16_t  Active (void) const;            // returns an index of tab that has state selected, otherwise e_na (-1);
		err_code Active (const int16_t _ndx);    // no tab cannot be active, otherwise, it does not have a sense; updated: out of tab range makes no active tab;

		err_code Append (const CTab&);
		err_code Append (const uint16_t _id, _pc_sz _lp_sz_cap);

		int16_t  Count  (void) const;

		TError&  Error  (void) const;

		void        Events (ITabEvents*);         // needs to be thread safe;
		ITabEvents* Events (void) const;

		int16_t  Has (const t_point&) const;      // returns an index of tab if it's found, otherwise #na (-1);
		const
		CTab&    Tab (const int16_t _ndx ) const; // if input index is out of range of the tabs count, the reference to the fake tab is returned;
		CTab&    Tab (const int16_t _ndx )      ; // if input index is out of range of the tabs count, the reference to the fake tab is returned;
		const
		TTabArray& Raw   (void) const ;
		err_code   Remove(const uint16_t _id);
		err_code   Reset (void) ;

	public:
		CTabs& operator = (const CTabs&);
		CTabs& operator = (CTabs&&);

		CTabs& operator <<(const int16_t _active_ndx); // sets the current/active tab index;
		CTabs& operator <<(const TTabArray& );
		CTabs& operator <<(ITabEvents* );

		CTabs& operator +=(_pc_sz _lp_sz_cap);
		CTabs& operator +=(const CTab& );
		CTabs& operator -=(const uint16_t _id);

	private:
		CControl&   m_ctrl ;
		ITabEvents* m_sink ;
		TTabArray   m_tabs ;
		CError      m_error;
	};

}}}}

#endif/*_SFXTABSEXT_H_INCLUDED*/