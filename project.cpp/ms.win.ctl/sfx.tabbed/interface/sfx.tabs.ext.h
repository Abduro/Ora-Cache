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
	using ex_ui::popup::CWndBase;

	using IDrawEvtSink = ex_ui::message::handlers::draw::IDrawEventSink;
	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;
	using ILifeEvtSink = ex_ui::message::handlers::life::ILifeEvtSink;

	typedef const CControl* TCtrlPtr;

	class CPage : public ex_ui::controls::CPane, IDrawEvtSink, ILifeEvtSink, IFormEvtSink, private CWndBase { // CWndBase is not copyable yet;
		typedef CWndBase TWindow;
		typedef ex_ui::controls::CPane TPane;
	public:
		 CPage (void); CPage (const CPage&) = delete; CPage (CPage&&) = delete;
		~CPage (void);

	public:
		err_code Create (const HWND hParent, const t_rect&, const bool _b_visible, const uint32_t _page_id = 0);
		err_code Destroy(void);
		const
		HWND     Handle (void) const;
		bool     Is_valid (void) const;
		err_code Is_visible (const bool _state);

		TCtrlPtr Get_ptr (void) const;  // gets the pointer to the tabbed control that owns this page;
		bool     Set_ptr (TCtrlPtr);    // sets the pointer to the tabbed control that owns this page; nullptr is also acceptable;

		const
		ex_ui::controls::pane::CLayout& Layout (void) const;
		ex_ui::controls::pane::CLayout& Layout (void) ;

#pragma region __msg_handler_callbacks__
	private:  // IDrawEvtSink override(s);
		err_code IEvtDraw_OnErase   (const HDC _dev_ctx) override final;
		err_code IEvtDraw_OnPaint   (const w_param, const l_param) override final;
	private:  // ILifeEvtSink override(s);
		err_code IEvtLife_OnCreate  (const w_param, const l_param) override final;
		err_code IEvtLife_OnDestroy (const w_param, const l_param) override final;
	private: // IFormEvtSink override(s); 
		err_code IEvtFrame_OnSize   (const IFormEvtSink::eState, const t_size) override final;
		err_code IEvtFrame_OnSizing (const IFormEvtSink::eEdges, t_rect*) override final;
#pragma endregion
	public:
		CPage& operator <<(TCtrlPtr);
	private:
		CPage& operator = (const CPage&) = delete; CPage& operator = (CPage&&) = delete;
		ex_ui::controls::pane::CLayout m_layout;
		TCtrlPtr m_p_ctrl;
	};

	class CTab { friend class CTabs;
	public:
		 CTab (const uint16_t _id = 0, _pc_sz _lp_sz_cap = nullptr); CTab (CTab&&);
		 CTab (const CTab&);
		~CTab (void);

	public:
		_pc_sz     Caption(void) const;
		CString&   Caption(void)      ;

		uint16_t   Id (void) const;
		uint16_t&  Id (void)      ;

		const bool Is_fake (void) const; // returns true in case if it is fake object that is returned ,for example, as active tab but there is none of them;

		const
		TLayersEx& Layers (void) const;
		TLayersEx& Layers (void)      ;

		const
		CPage&  Page (void) const;     // returns a reference to the content which this tab makes visible; (ro)
		CPage&  Page (void) ;          // returns a reference to the content which this tab makes visible; (rw)

		const
		t_rect&    Strip (void) const; // returns a reference to the rectangle of the tab bookmark or a visible part in the ribbon of tab control ;
		t_rect&    Strip (void) ;
		const bool Strip (const _long _left, const _long _top, const _long _right, const _long _bottom); // returns 'true' in case of change at least one of the rectangle values;

		const
		TState&    State (void) const;
		TState&    State (void)      ;

	public:
		CTab& operator = (const CTab&);
		CTab& operator = (CTab&&);

		CTab& operator <<(const TState&);
		CTab& operator <<(const CString& _cs_cap);
		CTab& operator <<(const uint16_t _tab_id);
		CTab& operator <<(_pc_sz _lp_sz_cap);

	private:
		bool       m_fake  ;  // indicates that this tab object is not valid, even does not exist in the tab set of this control;
		uint16_t   m_id    ;  // the tab identifier;
		TLayersEx  m_layers;  // for layered draw; not used yet;
		t_rect     m_strip ;  // the tab rectangle that does not include the tab page rectangle; it is just the visible element of tab panel/document/page;
		TState     m_state ;  // the tab current state: either selected or not;
		CString    m_cap   ;  // the tab caption;
		CPage      m_page  ;
	};

	typedef ::std::vector<CTab> TTabArray;

	interface ITabEvents;
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-tabctrl_getcursel ;
	class CTabs { friend class CControl;
	private:
		 CTabs (CControl&);    CTabs (void) = delete; 
		 CTabs (const CTabs&); CTabs (CTabs&&);
		~CTabs (void);

	public:
		static const int16_t not_avbl = -1;       // not available, i.e. there is no available tab for the method being invoked;
		// ToDo: it would be better to call the method below as 'SelectedIndex' or 'CurSelIndex', or TabCtrl_GetCurSel() as in common controls;
		int16_t  Active (void) const;             // returns an index of tab that has state selected, otherwise e_na (-1);
		err_code Active (const int16_t _ndx);     // no tab cannot be active, otherwise, it does not have a sense; updated: out of tab range makes no active tab;

		err_code Append (const CTab&);
		err_code Append (const uint16_t _id, _pc_sz _lp_sz_cap);

		uint16_t Count  (void) const;
		// if there's no active or currently selected tab in the tab control the reference to the fake tab object is returned: Is_fake() == true;
		const
		CTab&    Current(void) const;             // returns the reference to the currently selected tab or the currently active tab; (ro)
		CTab&    Current(void) ;                  // returns the reference to the currently selected tab or the currently active tab; (rw)

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