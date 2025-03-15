/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Apr-2024 at 09:28:46.1834066, UTC+7, Novosibirsk, Wednesday;
	This is Ebo pack shared base interface(s) library unit test implementation file; 
*/
#include "ebo_test_$0$.base.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	
	using TParts  = shared::common::TParts;
	using TString = shared::common::CString_Ex;

	using shared::common::dword;

	namespace common {

		__class(CPreproc) {
			__method(Parse) {
		
				TStringEx cs_out;
				cs_out.Format(_T("%s::%s::%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__); _out() << cs_out;
			}
		};

		__class(CString) {
			__ctor(_ctor) {

				TStringEx cs_out;

				cs_out.Format(_T("CString_Ex((bool) :false != true) >> '%s'"), TStringEx(false != true)); _out().Cached() += cs_out;
				cs_out.Format(_T("CString_Ex((dword):13) >> '%s'"), TStringEx((dword)13)); _out().Cached() += cs_out;
				cs_out.Format(_T("CString_Ex((float):0.013f) >> '%s'"), TStringEx(0.013f)); _out().Cached() += cs_out;
				cs_out.Format(_T("CString_Ex((long) :static_cast<long>(0.013)) >> '%s'"), TStringEx(static_cast<long>(0.013))); _out().Cached() += cs_out;
				cs_out.Format(_T("CString_Ex((text) :0.013f) >> '%s'"), TStringEx(_T("0.013f"))); _out().Cached() += cs_out;
				_out()();
			}

			__method(Split) {

				_pc_sz sz_sep = _T("|");
				_pc_sz sz_array = _T("0|1|2|3|");
				TParts parts = TStringEx(sz_array).Split(sz_sep);

				_out().Cached() += TString().Format(_T("splitting: what='%s';sep='%s';result:"), sz_array, sz_sep);
				_out().Cached() += parts;
				_out()();
			}
		};
	}

	namespace core {

		using CDateTime = shared::sys_core::CDateTime;

		__class(CTime) {
			__ctor(_ctor) {

				CDateTime dt_;

				_out().Cached() += TString().Format(_T("current timestamp is=%s"), dt_.Print().GetString());
				_out().Cached()();
			}
		};
	}
}}}