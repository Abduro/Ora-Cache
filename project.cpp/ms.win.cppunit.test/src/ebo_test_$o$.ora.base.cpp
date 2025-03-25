/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2025 at 11:03:17.6721202, UTC+4, Batumi, Sunday;
	This is Ebo Pack Oracle database wrapper base lib unit test interface implementation file; 
*/
#include "ebo_test_$o$.ora.base.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	namespace data { namespace ole {

		using TProvider = ora::base::oledb::CProvider;
		using TProv_enum = ora::base::oledb::CProvider_enum;

		__class(CProvider) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("Default: %s"), (_pc_sz)TProvider().Print(TProvider::e_all));
				_out()();
			}
		};

		using TOraProv = ora::base::oledb::COraProvider;

		__class(COreProvider) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TOraProv().Print(TProvider::e_all);
				_out()();
			}
			__method(Is_installed) {

				TProv_enum prov_enum; prov_enum.Set();
				TOraProv ora_prov;

				const bool b_registered = (prov_enum.Registered(ora_prov.ClsId().Raw()));

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("Installed: %s>>%s"), (_pc_sz)ora_prov.Print(TProvider::e_no_ns), TStringEx().Bool(b_registered));
				_out()();
			}
		};

		__class(CProv_enum) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TProv_enum().Print(_T("\t\t")); // expected #empty collection of the data providers;
				_out()();
			}
			__method(Set) {
				TProv_enum prov_enum;

				prov_enum.Set();

				_out() += TLog_Acc::e_new_line;
				_out() += prov_enum.Print(_T("\t\t")); // a list of data providers which are registered is expected;
				_out()();
			}
		};
	}}

}}}