#ifndef _SFXSTATUSCTRL_H_INCLUDED
#define _SFXSTATUSCTRL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-May-2009 at 10:02:53pm, GMT+3, Rostov-on-Don, Monday;
	This is ST Status Bar Control interface declaration file.
	-----------------------------------------------------------------------------
	Reincarnation to Ebo Pack is made on 22-Aug-2020 at 7:16:49a, UTC+7, Novosibirsk, Saturday;
*/
#include "sfx.status.fmt.h"
#include "sfx.status.inc.h"
#include "sfx.status.lay.h"
#if (0)

#include "sfx.status.ext.h"
#endif
namespace ex_ui { namespace controls { namespace sfx { namespace status {

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
		CWindow   Window (void) const; // returns status bar control internal window handle;

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
namespace ST_Ctrls {

	using ex_ui::draw::defs::IRenderer;

	interface IStatusEvents : public ex_ui::controls::IControlEvent {
		virtual HRESULT  IStatusEvt_OnAppend (const CPanel& _added) PURE;
		virtual HRESULT  IStatusEvt_OnFormat (const TStatusFmt&) PURE;
		virtual HRESULT  IStatusEvt_OnRemove (const DWORD _panel_ndx) PURE;
	};

	class CStatusBar : public IStatusEvents {
	protected:
		IStatusEvents& m_evt_snk;
		CPanels        m_panels ;

	public:
		
		
		const
		CPanels&     Panels  (void) const;
		CPanels&     Panels  (void)      ;
		HRESULT      Renderer(IRenderer*  const _p_parent_renderer);
	public:
		ex_ui::controls::IControlEvent&  MouseEvtSink(void);

	private: // IStatusEvents;
#pragma warning(disable: 4481)
		virtual HRESULT  IStatusEvt_OnAppend (const CPanel& _added) override sealed;
		virtual HRESULT  IStatusEvt_OnFormat (const TStatusFmt&) override sealed;
		virtual HRESULT  IStatusEvt_OnRemove (const DWORD _panel_ndx) override sealed;
#pragma warning(default: 4481)
	private: // non-copyable;
		CStatusBar (const CStatusBar&);
		CStatusBar&  operator = (const CStatusBar&);
	};
}
#endif
#if (0)
typedef ST_Ctrls::CStatusBar  TStatusCtrl;
#endif
#endif/*_SFXSTATUSCTRL_H_1BAC705D_DCAB_4BCA_99E0_6ADCC0305970_INCLUDED*/