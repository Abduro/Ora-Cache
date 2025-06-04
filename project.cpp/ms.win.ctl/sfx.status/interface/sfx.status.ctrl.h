#ifndef _SFXSTATUSCTRL_H_INCLUDED
#define _SFXSTATUSCTRL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-May-2009 at 10:02:53pm, GMT+3, Rostov-on-Don, Monday;
	This is ST Status Bar Control interface declaration file.
	-----------------------------------------------------------------------------
	Reincarnation to Ebo Pack is made on 22-Aug-2020 at 7:16:49a, UTC+7, Novosibirsk, Saturday;
*/
#if (0)
#include "shared.gen.sys.err.h"
#include "shared.uix.ctrl.defs.h"
#include "sfx.status.fmt.h"
#include "sfx.status.lay.h"
#include "sfx.status.ext.h"
#endif
namespace ST_Ctrls {
#if (0)
	using shared::sys_core::CError;
	using ex_ui::draw::defs::IRenderer;
	using ex_ui::controls::CBorders;
	using ex_ui::controls::CMargins;

	interface IStatusEvents : public ex_ui::controls::IControlEvent {
		virtual HRESULT  IStatusEvt_OnAppend (const CPanel& _added) PURE;
		virtual HRESULT  IStatusEvt_OnFormat (const TStatusFmt&) PURE;
		virtual HRESULT  IStatusEvt_OnRemove (const DWORD _panel_ndx) PURE;
	};

	class CStatusBar : public IStatusEvents {
	protected:
		IStatusEvents& m_evt_snk;
		HANDLE         m_wnd_ptr;
		CError         m_error  ;
		UINT           m_ctrl_id;
		TStatusLay     m_layout ;
		CPanels        m_panels ;
		CBorders       m_borders;

	public:
		 CStatusBar (IStatusEvents&);
		~CStatusBar (void);

	public:
		HRESULT      Create  (const HWND hParent, const UINT _ctrl_id);
		HRESULT      Destroy (void)      ;

	public:
		const
		CBorders&    Borders (void) const;
		CBorders&    Borders (void)      ;
		const
		TStatusFmt&  Format  (void) const;
		TStatusFmt&  Format  (void)      ;
		TErrorRef    Error   (void) const;
		const
		TStatusLay&  Layout  (void) const;
		TStatusLay&  Layout  (void)      ;
		const
		CPanels&     Panels  (void) const;
		CPanels&     Panels  (void)      ;
		HRESULT      Renderer(IRenderer*  const _p_parent_renderer);
		HRESULT      Refresh (void)      ;
		CWindow      Window  (void) const;

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
#endif
}
#if (0)
typedef ST_Ctrls::CStatusBar  TStatusCtrl;
#endif
#endif/*_SFXSTATUSCTRL_H_1BAC705D_DCAB_4BCA_99E0_6ADCC0305970_INCLUDED*/