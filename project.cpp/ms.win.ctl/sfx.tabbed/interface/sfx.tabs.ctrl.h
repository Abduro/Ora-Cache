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
#include "sfx.tabs.ext.h"
#include "sfx.tabs.inc.h"
#include "sfx.tabs.lay.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed {

	using namespace ex_ui::controls::sfx;

	interface ITabEvents {
		virtual err_code ITabEvent_OnAppend (const CTab&)    = 0;
		virtual err_code ITabEvent_OnFormat (const CFormat&) = 0;
		virtual err_code ITabEvent_OnRemove (const uint16_t _tab_id) = 0; 
		virtual err_code ITabEvent_OnSelect (const int16_t _tab_ndx) = 0;
	};

	// https://learn.microsoft.com/en-us/windows/win32/controls/create-a-tabbed-dialog-box ;
	// https://learn.microsoft.com/en-us/previous-versions/visualstudio/visual-basic-6/aa228545(v=vs.60)?redirectedfrom=MSDN ;

	class CControl : public ITabEvents { // ITabEvents interface is used as a callback internally between different parts of this control;
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

		bool    Is_valid (void) const;  // checks for: (1) window pointer; (2) this control window handle validity;

		const
		CLayout&  Layout (void) const;
		CLayout&  Layout (void) ;

		err_code  Refresh(void) ;
		CWindow   Window (void) const; // returns tabbed control internal window handle;

		const CTabs& Tabs(void) const;
		      CTabs& Tabs(void)      ;

	private: // ITabEvents
#pragma warning(disable: 4481)
		virtual err_code ITabEvent_OnAppend (const CTab& _added ) override sealed;
		virtual err_code ITabEvent_OnFormat (const CFormat&) override sealed;
		virtual err_code ITabEvent_OnRemove (const uint16_t _tab_id) override sealed;
		virtual err_code ITabEvent_OnSelect (const int16_t _tab_ndx) override sealed;
#pragma warning(default: 4481)

	private:
		CControl& operator = (const CControl&) = delete;
		CControl& operator = (CControl&&) = delete;

	protected:
		CBorders  m_borders;
		CFormat   m_format ;
		CError    m_error  ;
		CLayout   m_layout ;
		CTabs     m_tabs   ;
		HANDLE    m_wnd_ptr;
		uint32_t  m_ctrl_id;
	};

}}}}

#if (0)

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
	public:
		 CTabbed (ITabEvents& _evt_sink);
		~CTabbed (void);

	public:
		HRESULT      ParentRenderer (IRenderer*  const );

	
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