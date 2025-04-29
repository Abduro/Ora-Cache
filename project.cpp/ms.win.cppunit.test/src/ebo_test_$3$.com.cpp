/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Aug-2024 at 22:03:17.6392858, UTC+4, Batumi, Monday;
	This is Ebo pack system COM service base wrapper library unit test implementation file; 
*/
#include "ebo_test_$3$.com.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using TString = shared::common::CString_Ex;

	namespace com {
#if (0)
		using TGuid = shared::sys_core::com::CGuid;

		__class(CGuid) {
			__ctor(_ctor) {
				_out().Opts() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("Default: %s"), (_pc_sz) TGuid().Print(TGuid::e_all));
				_out()();
			}

			__method(Create_new) {

				TGuid t_guid; t_guid.Create();

				_out().Opts() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("New guid: %s"), (_pc_sz) t_guid.Print(TGuid::e_all));
				_out()();

			}

			__method(Singleton) {

				_out().Opts() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("Singleton: %s"), (_pc_sz) TGuid::Ref().Print(TGuid::e_all));
				_out()();

			}
		};

		using TComProp = shared::sys_core::com::CProperty;

		__class(CProperty) {
			__ctor(_ctor) {
				_out().Opts() += TLog_Acc::e_new_line;
				_out()();
			}
		};

		using TUnk_default = shared::sys_core::com::CDefault_unknown;

		__class(CUnknown) {
			__ctor(_ctor) {

				TUnk_default unk_loc;
				TUnk_default* p_dynamic = new TUnk_default();

				_out().Opts() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("IUnknown impl: %s") , (_pc_sz) this->m_default.Print());
				_out() += TString().Format(_T("IUnknown new: %s")  , p_dynamic ? (_pc_sz) p_dynamic->Print() : _T("#undef"));
				_out() += TString().Format(_T("IUnknown local: %s"), (_pc_sz) unk_loc.Print());

				if (p_dynamic) {
					p_dynamic->Release();
				}
				_out()();

			}

			__dtor(_dtor) {

				const u_long u_refs = this->m_default.Release();

				_out().Opts() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("After release(): %s"), (_pc_sz) this->m_default.Print());
				_out()();
			}

			private:
				TUnk_default m_default;
		};
#endif
		namespace identity {

			using TClsId = shared::sys_core::com::CClsId;

			__class(CClsId) {
				__ctor(_ctor) {
					TClsId cls_id;

					_out().Opts() += TLog_Acc::e_new_line;
					_out() << cls_id.Print(::e_print::e_all);
					_out()();
				}
			};

			using TProgId = shared::sys_core::com::CProgId;

			__class(CProgId) {
				__ctor(_ctor) {
					TProgId prog_id(__guid_null); // #no_set value is expected due to no program id is registered for null guid;

					_out().Opts() += TLog_Acc::e_new_line;
					_out() << prog_id.Print(::e_print::e_all);
					_out()();
				}
			};
		}
		namespace service {

			using TMode  = shared::sys_core::com::CCoMode;
			using TModes = shared::sys_core::com::CCoMode_enum;

			__class(CMode) {
				__ctor(_ctor) {
					_out().Opts() += TLog_Acc::e_new_line;
					_out() << TMode().Print(::e_print::e_all);
					_out()();
				}
			};

			__class(CMode_enum) {
				__ctor(_ctor) {
					_out().Opts() += TLog_Acc::e_new_line;
					_out() << TModes::Ref().Print();
					_out()();
				}
				__method(Get) {
					_out() += TLog_Acc::e_new_line;
					_out().Cached() += _T("Finding co-init modes:");
					_out().Cached() += TModes::Ref().Find(TModeAccept::e_default).Print(::e_print::e_all);
					_out().Cached() += TModes::Ref().Find(TModeAccept::e_the_fake).Print(::e_print::e_all);
					_out()();
				}
			};

			__class(CModel) {
				__ctor(_ctor) {
					_out() += TLog_Acc::e_new_line;
					_out().Cached() += _T("Available concurrent models:");
					_out().Cached() +=  TCoModel(TCoModelCfg::e_fast).Print();
					_out().Cached() +=  TCoModel(TCoModelCfg::e_gui ).Print();
					_out().Cached() +=  TCoModel(TCoModelCfg::e_none).Print();
					_out().Cached() +=  TCoModel(TCoModelCfg::e_task).Print();
					_out()();
				}
			};

			class CGuard_debug : public TCoGuard { typedef TCoGuard TBase;
			public:
				 CGuard_debug (void) : TBase() {} // no aut-init is invoked;
				 CGuard_debug (const CGuard_debug&) = delete; CGuard_debug (CGuard_debug&&) = delete;
				~CGuard_debug (void) {}

			public:
				err_code Create (void) { return TBase::OnCreate(); }
				err_code Destroy(void) { return TBase::OnDestroy(); }

			private:
				CGuard_debug& operator = (const CGuard_debug&) = delete;
				CGuard_debug& operator = (CGuard_debug&&) = delete;
			};

			using CCo_dbg = CGuard_debug;

			/*
				https://learn.microsoft.com/en-us/windows/win32/api/objbase/nf-objbase-coinitialize >> states the following (excerpt):
				...
				because there is no way to control the order in which in-process servers are loaded or unloaded,
				do not call CoInitialize...
				...
				thus, the test below throws an *expected* error of trying to call co-init function, due to the cpp unit test is dynalib;
				moreover, dyna-lib module is loaded in process, that is already created and co-init is very possibly called in main thread of the app;
				what can be done:
				to use console test application that creates main thread for GUI(i.e. main window) messages' pump;
			*/
			__class(CGuard) {
				__ctor(_ctor) {
					_out() += TLog_Acc::e_new_line;
					{
						CString cs_out;
						CCo_dbg co_dbg;
						cs_out  = _T("Before co-init():");
						cs_out += co_dbg.Print(::e_print::e_req); _out().Cached() += cs_out;
						co_dbg.Create();
						cs_out  = _T("After co-init():" );
						cs_out += co_dbg.Print(::e_print::e_all); _out().Cached() += cs_out;
						co_dbg.Destroy();
						cs_out  = _T("After co-un-init():");
						cs_out += co_dbg.Print(::e_print::e_req); _out().Cached() += cs_out;
					}
					_out()();
				}
			};
		}
	}
}}}