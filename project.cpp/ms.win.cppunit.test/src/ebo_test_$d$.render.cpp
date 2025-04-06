/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2025 at 04:41:06.363, UTC+4, Batumi, Wednesday;
	This is Ebo Pack 2D/3D draw renderer lib unit test interface implementation file; 
*/
#include "ebo_test_$d$.render.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace shared::types;

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	namespace draw {

		using e_print = ex_ui::draw::direct_x::e_print;
		using TAlphaMode = ex_ui::draw::direct_x::CAlphaMode;

		__class(CAlhaMode) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TAlphaMode().Print(e_print::e_all);
				_out()();
			}
		};

		using TBuffer = ex_ui::draw::direct_x::CBuffer;
		__class(CBuffer) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TBuffer().Print(e_print::e_all);
				_out()();
			}
		};

		using TEffect = ex_ui::draw::direct_x::CEffect;
		__class(CEffect) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TEffect().Print(e_print::e_all);
				_out()();
			}
		};
	
		using TAdapter  = ex_ui::draw::direct_x::CAdapter;
		using TAda_enum = ex_ui::draw::direct_x::CAdapter_Enum;
		using TAdapters = ex_ui::draw::direct_x::TAdapters;

		__class(CAdapter) {
			__ctor(_ctor) {
				_out() +=  TLog_Acc::e_new_line;
				_out() +=  TAdapter().Print();
				_out()();
			}
		};

		__class(CAda_enum) {
			__ctor(_ctor) {
				_out() +=  TLog_Acc::e_new_line;
				_out() += _T("");
				_out()();
			}

			__method(Get) {
				TAda_enum ada_enum;

				if (__succeeded(ada_enum.Set())) {

					_out() += TLog_Acc::e_new_line;

					const TAdapters& adapters = ada_enum.Get();
					for (size_t i_ = 0; i_ < adapters.size(); i_++) {
						const TAdapter& adapter = adapters.at(i_);
						_out() += adapter.Print();
					}
					_out()();
				}
				else {

				}
			}
		};

		using TAda_Warp = ex_ui::draw::direct_x::CAda_Warp;
		using TWarp_enum = ex_ui::draw::direct_x::CEnum_Warp;

		using TPxFormat = ex_ui::draw::direct_x::CPxFormat;

		__class(CPxFormat) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TPxFormat().Print(e_print::e_all);
				_out()();
			}
		};

		using TSample = ex_ui::draw::direct_x::CSample;

		__class(CSample) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TSample().Print(e_print::e_all);
				_out()();
			}
		};

		using TSize = ex_ui::draw::direct_x::CSize;

		__class(CSize) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TSize().Print(e_print::e_all);
				_out()();
			}
		};

		__class(CWarp_enum) {

			__method(Get) {
				TWarp_enum warp_enum;
				warp_enum.Set();
				warp_enum.Get();
			}
		};

		using TWarpDev = ex_ui::draw::direct_x::CDevice_Warp;

		__class(CDev_warp) {

			__method(Get) {

				TWarp_enum warp_enum;
				TWarpDev   wrap_dev ;
				if (warp_enum.Set()) {
					wrap_dev.Create(warp_enum.Get());
				}
			}

		};
	}

}}}