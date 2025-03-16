/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Aug-2024 at 01:35:22.1013935, UTC+4, Batumi, Friday;
	This is Ebo Pack system error (WinApi) wrapper library unit test implementation file; 
*/
#include "ebo_test_$1$.err.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using TError  = shared::sys_core::CError;
	using TParts  = shared::common::TParts;
	using TFormat = shared::sys_core::CErr_Format;

	using TString = shared::common::CString_Ex;

	namespace error {

		__class(CError) {
			__ctor(_ctor) {
			
				shared::sys_core::CError sys_err;

				Assert::IsFalse(sys_err.Is());

				sys_err >> (_pc_sz)__CLASS__ << (err_code) TErrCodes::eExecute::eInternal << (_pc_sz)__METHOD__;
#if(0)
				sys_err.Show();
#else
				_out().Cached() += TString().Format(_T("ns=%s::"),(_pc_sz)__SP_NAME__) + sys_err.Print(TError::e_req);
				_out().Cached()();
#endif
			}
		};

		using TCode = shared::sys_core::seh::CCode;

		__class(CCode) {
			__ctor(_ctor) {

				TCode empty_;
				_out().Cached() += empty_.Print(TCode::e_all);
				_out()();
			}
		};

		using TFake_code = shared::sys_core::seh::CCode_Fake;
		using errno_l = shared::sys_core::seh::errno_l;

		__class(CCode_Fake)  {
			__ctor(_ctor) {
				_out() << TFake_code::Ref().Print();
				_out()();
			}

			__method(Get) {

				TFake_code& fake = TFake_code::Ref();
				_out().Cached() += _T("Using exception code for finding the object:");
				const TCode found_0 = fake.Find((errno_l)TCode::e_acc_violate);  _out().Cached() += found_0.Print(TCode::e_all);
				const TCode found_1 = fake.Find((uint32_t)CONTROL_C_EXIT);       _out().Cached() += found_1.Print(TCode::e_all);
				_out()();
			}
		};

		using TFlag = shared::sys_core::seh::CFlag;

		__class(CFlag) {
			__ctor(_ctor) {
			
				TFlag none_;
				_out().Cached() += none_.Print(TFlag::e_all);
				_out()();
			}
		};

		using TFake_flag = shared::sys_core::seh::CFlag_Fake;

		__class(CFlag_Fake) {
			__ctor(_ctor) {
				_out() << TFake_flag::Ref().Print();
				_out()();
			}
		};

		using TNumber = shared::sys_core::seh::CNumber;

		__class(CNumber) {
			__ctor(_ctor) {

				TNumber empty_;
				_out().Cached() += empty_.Print(TNumber::e_all);
				_out()();
			}
		};

		using TFake_num = shared::sys_core::seh::CNumber_Fake;

		__class(CNumber_Fake) {
			__ctor(_ctor) {
				_out() << TFake_num::Ref().Print();
				_out()();
			}
			__method(Get) {
				_out().Cached() += TFake_num::Ref().Find(EINVAL).Print(TNumber::e_all);
				_out().Cached() += TFake_num::Ref().Find(EILSEQ).Print(TNumber::e_all);
				_out()();
			}
		};
	}

	/*
		***important***
		Handling system exception may be made on executable app only (for example, console app);
		For this puspose the test project 'ebo_test_con_v15' is created;
	*/

}}}