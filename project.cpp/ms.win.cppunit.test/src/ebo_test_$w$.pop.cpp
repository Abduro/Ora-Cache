/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Oct-2024 at 22:21:36.425, UTC+4, Batumi, Saturday;
	This is Ebo Pack window popup wrapper lib unit test interface implementation file; 
*/
#include "ebo_test_$w$.pop.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace shared::types;

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	namespace window {
	
		using TPopup = ex_ui::popup::CWndBase;
		using ILifeEvtSink = ex_ui::message::handlers::life::ILifeEvtSink;

		using namespace ex_ui::message::handlers;

		class CWindow : public TPopup, ILifeEvtSink {
		public:
			 CWindow (void) : TPopup() {
				 TPopup::Handlers().Live().Subscribe(this);
			 }
			 CWindow (const CWindow&) = delete; CWindow (CWindow&&) = delete;
			~CWindow (void) {
				TPopup::Handlers().Live().Unsubscribe(this);
			}

		private: // ILifeEvtSink
			err_code  IEvtLife_OnClose   (const w_param, const l_param) override final { // reminder: if result is __s_ok (0), this window is still open;
				_out() += TString().Format(_T("cls::[%s].%s();"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
				return __s_false;
			}
			err_code  IEvtLife_OnCreate  (const w_param, const l_param) override final {
				_out() += TString().Format(_T("cls::[%s].%s();"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
				return __s_false;
			}
			err_code  IEvtLife_OnDestroy (const w_param, const l_param) override final {
				_out() += TString().Format(_T("cls::[%s].%s();"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
				return __s_false;
			}
		};

		using TPosition = ex_ui::popup::layout::CPosition;
		using TPrimary  = ex_ui::popup::layout::CPrimary ;

		__class(CPosition) {
			__ctor(_ctor) {
				_out() +=  TLog_Acc::e_new_line;
				_out() +=  TPosition().Print(TPosition::e_all);
				_out()();
			}
		};

		__class(CPopup) {
			__ctor(_ctor) {
				_out() +=  TLog_Acc::e_new_line;
				_out() += _T("");
				_out()();
			}
#if (0)
			__method(Create){
				
				CWindow window;
				RECT rc_ = TWndLayout().Autosize();

				HWND h_wnd = window.Create(HWND_DESKTOP, &rc_, NULL, WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
				if ( h_wnd ) {
					while (window.IsWindow()) {
						window.ShowWindow(SW_SHOW);
						::Sleep(1000);
					}
				}
			}
#endif
		};
	}

}}}