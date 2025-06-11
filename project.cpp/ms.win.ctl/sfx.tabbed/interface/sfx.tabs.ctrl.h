#ifndef _SFX_TABS_CTRL_H_INCLUDED
#define _SFX_TABS_CTRL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) at 30-Apr-2009 8:04:27am, GMT+3, Rostov-on-Don, Thursday;
	This is ST Tab control interface defenition file.
	-----------------------------------------------------------------------------
	Adopted to Pulsepay project on 21-May-2012 at 12:02:47pm, GMT+3, Rostov-on-Don, Monday;  
	Adopted to Ebo Pack on 12-Jul-2020 at 8:23:49p, UTC+7, Novosibirsk, Sunday;
*/
#include "sfx.tabs.fmt.h"
#include "sfx.tabs.inc.h"
#include "sfx.tabs.lay.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed {

	using namespace ex_ui::controls::sfx;

	class CControl {
	public:
		 CControl (void); CControl (const CControl&) = delete; CControl (CControl&&) = delete;
		~CControl (void);

	public:
		const
		CBorders& Borders(void) const;
		CBorders& Borders(void) ;

		err_code  Create (const HWND hParent, const uint32_t _ctrl_id);
		err_code  Destroy(void) ;
		TError&   Error  (void) const;

		const
		CFormat&  Format (void) const;
		CFormat&  Format (void)      ;

		const
		CLayout&  Layout (void) const;
		CLayout&  Layout (void) ;

		err_code  Refresh(void) ;
		CWindow   Window (void) const; // returns tabbed control internal window handle;

	private:
		CControl& operator = (const CControl&) = delete;
		CControl& operator = (CControl&&) = delete;

	protected:
		CBorders m_borders;
		CFormat  m_format ;
		CError   m_error  ;
		CLayout  m_layout ;
		HANDLE   m_wnd_ptr;
		uint32_t m_ctrl_id;
	};

}}}}

#if (0)
#include "shared.gen.sys.err.h"
#include "shared.uix.ctrl.defs.h"
#include "sfx.tabs.fmt.h"
#include "sfx.tabs.ext.h"
#include "sfx.tabs.lay.h"

namespace ST_Ctrls {

	using shared::sys_core::CError;
	using ex_ui::draw::defs::IRenderer;
	using ex_ui::controls::IControlEvent;

	interface ITabEvents : public IControlEvent {
		virtual HRESULT  ITabEvent_OnAppend (const CTab& _added  ) PURE;
		virtual HRESULT  ITabEvent_OnFormat (const TTabbedFmt&   ) PURE;
		virtual HRESULT  ITabEvent_OnSelect (const DWORD _tab_ndx) PURE;
	};

	class CTabbed : private ITabEvents {
	protected:
		ITabEvents&  m_evt_snk;  // tab control owner event sink;
		HANDLE       m_wnd_ptr;
		CError       m_error  ;
		UINT         m_ctrl_id;
		TTabsLay     m_layout ;
		CTabs        m_tabs   ;
	
	public:
		 CTabbed (ITabEvents& _evt_sink);
		~CTabbed (void);

	public:
		HRESULT      Create  (const HWND hParent, const RECT& _rc_area, const UINT _ctrl_id);
		HRESULT      Destroy (void)      ;
		TErrorRef    Error   (void) const;
		const
		TTabbedFmt&  Format  (void) const;
		TTabbedFmt&  Format  (void)      ;
		HRESULT      ParentRenderer (IRenderer*  const );
		HRESULT      Refresh (void)      ;
		const CTabs& Tabs    (void) const;
		      CTabs& Tabs    (void)      ;
		CWindow      Window  (void) const;

	private: // ITabEvents
#pragma warning(disable: 4481)
		virtual HRESULT  ITabEvent_OnAppend (const CTab& _added  ) override sealed;
		virtual HRESULT  ITabEvent_OnFormat (const TTabbedFmt&   ) override sealed;
		virtual HRESULT  ITabEvent_OnSelect (const DWORD _tab_ndx) override sealed;
#pragma warning(default: 4481)
	private: // IControlEvent
#pragma warning(disable:4481)
		virtual HRESULT  IControlEvent_OnClick(const UINT ctrlId) override sealed;
		virtual HRESULT  IControlEvent_OnClick(const UINT ctrlId, const LONG_PTR nData) override sealed;
#pragma warning(default:4481)
	private: // copy protected;
		CTabbed (const CTabbed&);
		CTabbed& operator= (const CTabbed&);
	};
}

typedef ST_Ctrls::CTabbed  TTabCtrl;
#endif
#endif/*_SFX_TABS_CTRL_H_INCLUDED*/