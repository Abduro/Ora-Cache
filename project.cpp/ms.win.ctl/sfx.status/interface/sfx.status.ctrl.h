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
#include "sfx.status.ext.h"

#include "ctl.base.image.h"

namespace ex_ui { namespace controls { namespace sfx { namespace status {

	using namespace ex_ui::controls::sfx;
	using CImages = ex_ui::controls::CImages;

	class CControl {
	public:
		 CControl (void); CControl (const CControl&) = delete; CControl (CControl&&) = delete;
		~CControl (void);

	public:
		/*
			A border is the line that already has such attributes or fields as: a color, a thickness and a position;
			that means this class has all required attributes for format, thus this control format class may to take care of formating all borders;
		*/
#if (0)
		const
		CBorders& Borders(void) const;
		CBorders& Borders(void) ;
#endif
		err_code  Create (const HWND hParent, const uint32_t _ctrl_id);
		err_code  Destroy(void) ;
		TError&   Error  (void) const;

		const
		CFormat&  Format (void) const;
		CFormat&  Format (void)      ;

		const
		CImages&  Images (void) const;
		CImages&  Images (void) ;

		const
		CLayout&  Layout (void) const;
		CLayout&  Layout (void) ;

		const
		CPanes&   Panes  (void) const;
		CPanes&   Panes  (void)      ;

		err_code  Refresh(void) ;
		CWindow   Window (void) const; // returns status bar control internal window handle;

	private:
		CControl& operator = (const CControl&) = delete;
		CControl& operator = (CControl&&) = delete;

	protected:
#if (0)
		CBorders m_borders;
#endif
		CFormat  m_format ;
		CError   m_error  ;
		CImages  m_images ; // ToDo: this field may be put inside this control window class;
		CLayout  m_layout ;
		CPanes   m_panes  ;
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
	public:
		
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