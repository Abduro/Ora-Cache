#ifndef _TEST_GUI_WINDOW_H_INCLUDED
#define _TEST_GUI_WINDOW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Aug-2026 at 08:31:06.800, UTC+4, Batumi, Thursday;
	This is virtual camera test cases' desktop GUI main window interface declaration file;
*/
#include "test.gui.defs.h"
#include "shared.timer.h"

namespace test { namespace app { using namespace ::test::draw::defs;

	using IWaitable_Events = ::shared::common::IWaitable_Events;
	using CStdTimer = ::shared::common::CStdTimer;

	class CFrame {
	public:
		 CFrame (void) = default; CFrame (const CFrame&) = delete; CFrame (CFrame&&) = delete;
		~CFrame (void) = default;

		class CIcons {
		public:
			CIcons (void); CIcons (const CIcons&) = delete; CIcons (CIcons&&) = delete; ~CIcons (void) = default;
			static
			err_code Set (const uint16_t _u_res_id, const HWND _h_wnd);
			err_code Set (const uint16_t _u_res_id);     // sets icons of both sizes (small: 16x16px & large: 32x32px) to the app window;

			CIcons& operator <<(const HWND _h_wnd);      // must be called before setting an resource identifier;
			CIcons& operator <<(const uint16_t _res_id); // calls this::Set() function; it is assumed the window handle is set;

		private:
			CIcons& operator = (const CIcons&) = delete; CIcons& operator = (CIcons&&) = delete;
			HWND     m_wnd;
			uint16_t m_res_id;
		};

		const
		CIcons& Icons (void) const;
		CIcons& Icons (void) ;

	private:
		CFrame& operator = (const CFrame&) = delete; CFrame& operator = (CFrame&&) = delete;
		CIcons  m_icons;
	};

	class CAppWnd  : public CWndBase, IDrawEvtSink, ILifeEvtSink, ISysEvtSink, IFormEvtSink, IWaitable_Events { typedef CWndBase TBase;
	public:
		 CAppWnd (_pc_sz _p_cls_name = nullptr); CAppWnd (const CAppWnd&) = delete; CAppWnd (CAppWnd&&) = delete;
		~CAppWnd (void) ;

		err_code Create (void);
		err_code Destroy(void);
		TError&  Error  (void) const;
		const
		CFrame&  Frame (void) const;
		CFrame&  Frame (void) ;

		bool  Is_valid (void) const;

	private: 
		// IDrawEvtSink override(s);
		err_code IEvtDraw_OnErase    (const HDC _dev_ctx) override final;
		err_code IEvtDraw_OnPaint    (const w_param, const l_param) override final;
		// ILifeEvtSink override(s);
		err_code IEvtLife_OnClose    (const w_param, const l_param) override final; // reminder: if result is __s_ok, this window is still open;
		err_code IEvtLife_OnCreate   (const w_param, const l_param) override final;
		err_code IEvtLife_OnDestroy  (const w_param, const l_param) override final;
		// ISysEvtSink override(s);
		err_code IEvtSys_OnSysCmd    (const w_param, const l_param) override final; // reminder: if result is __s_ok, this process will be ended up;
		// IFormEvtSink override(s);
		err_code IEvtFrame_OnActivate(const w_param, const l_param) override final;
		err_code IEvtFrame_OnSize    (const IFormEvtSink::eState, const SIZE) override final; // works on clicking window title buttons or system menu commands;
		err_code IEvtFrame_OnSizeInfo(MINMAXINFO&) override final;                            // works *before* changing a size of window;
		err_code IEvtFrame_OnSizing  (const IFormEvtSink::eEdges, LPRECT) override final;     // works on changing window size by mouse device;

		CAppWnd& operator = (const CAppWnd&) = delete;
		CAppWnd& operator = (CAppWnd&&) = delete;

		virtual void IWaitable_OnComplete(void) override final;

		CFrame    m_frame;
		CStdTimer m_wait;  // to-do: this timer is not used;
	};
}}


#endif/*_TEST_GUI_WINDOW_H_INCLUDED*/