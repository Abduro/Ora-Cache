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
	}

}}}