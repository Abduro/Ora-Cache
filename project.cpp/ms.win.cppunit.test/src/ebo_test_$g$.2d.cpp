/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2024 at 09:21:38.324, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry lib unit test interface implementation file; 
*/
#include "ebo_test_$g$.2d.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	namespace outline { namespace _2D { // 'outline' namespace is declared here in order do not intercept with 'geometry' namespace;

		__class(CPoint) {
			__ctor(_ctor) {

				_out() += TLog_Acc::e_new_line;
				_out() += TPoint().Print(e_print::e_all);
				_out()();

			}

			__method(Operators) {

				TPoint pt_0(0,0),pt_1(1,1);
				
				_out() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("Points: %s & %s are equal to each other >> %s"),
					(_pc_sz)pt_0.Print(e_print::e_req), (_pc_sz)pt_1.Print(e_print::e_req), TStringEx().Bool(pt_0 == pt_1));

				pt_0 << 2 >> -2;
				pt_1 << 3 >> -3;

				TPoint pt_result = (pt_0 + pt_1);

				_out() += TString().Format(_T("%s + %s = %s"),
					(_pc_sz)pt_0.Print(e_print::e_req), (_pc_sz)pt_1.Print(e_print::e_req), (_pc_sz) pt_result.Print(e_print::e_req));

				pt_0 << 4 >> -4;
				pt_1 << 6 >> -6;

				pt_result = (pt_0 - pt_1);

				_out() += TString().Format(_T("%s - %s = %s"),
					(_pc_sz)pt_0.Print(e_print::e_req), (_pc_sz)pt_1.Print(e_print::e_req), (_pc_sz) pt_result.Print(e_print::e_req));

				_out()();

			}
		};

		__class(CPoints) {

			__ctor(_ctor) {

				TPoints pts_;

				pts_.Raw().push_back(TPoint(0,0));
				pts_.Raw().push_back(TPoint(1,1));
				pts_.Raw().push_back(TPoint(2,2));
				pts_.Raw().push_back(TPoint(3,3));
			
				_out() += TLog_Acc::e_new_line;
				_out() += pts_.Print();
				_out()();

			}
		};

		using TPoint_2 =  geometry::base::_2D::CPoint_2; // this is the point class extended by marker;  

		__class(CPoint_2) {
			__ctor(_ctor) {

				_out() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("Default: %s"), (_pc_sz)TPoint_2().Print(e_print::e_all));
				_out()();

			}
		};

		__class(CSize) {
			__ctor(_ctor) {

				_out() += TLog_Acc::e_new_line;
				_out() += TSize().Print(e_print::e_all);
				_out()();

			}

			__method(Operators) {

				TSize sz_0(0,0),sz_1(1,1);
				
				_out() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("Sizes: %s & %s are equal to each other >> %s"),
					(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), TStringEx().Bool(sz_0 == sz_1));


				sz_0 << 2 >> -2;
				sz_1 << 3 >> -3;

				TSize sz_result = (sz_0 + sz_1);

				_out() += TString().Format(_T("%s + %s = %s"),
					(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), (_pc_sz) sz_result.Print(e_print::e_req));

				sz_0 << 4 >> -4;
				sz_0 << 6 >> -6;

				sz_result = (sz_0 - sz_1);

				_out() += TString().Format(_T("%s - %s = %s"),
					(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), (_pc_sz) sz_result.Print(e_print::e_req));

				_out()();

			}
		};

		__class(CSizeU) {
			__ctor(_ctor) {

				_out() += TLog_Acc::e_new_line;
				_out() += TSizeU().Print(e_print::e_all);
				_out()();

			}

			__method(Operators) {

				TSizeU sz_0(0,0),sz_1(1,1);
				
				_out() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("Sizes: %s & %s are equal to each other >> %s"),
					(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), TStringEx().Bool(sz_0 == sz_1));

				sz_0 << 2 >> 2;
				sz_1 << 3 >> 3;

				TSizeU sz_result = (sz_0 + sz_1);

				_out() += TString().Format(_T("%s + %s = %s"),
					(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), (_pc_sz) sz_result.Print(e_print::e_req));

				sz_0 << 4 >> 4;
				sz_0 << 6 >> 6;

				sz_result = (sz_0 - sz_1);

				_out() += TString().Format(_T("%s - %s = %s"),
					(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), (_pc_sz) sz_result.Print(e_print::e_req));

				_out()();
			}
		};
	}}

	namespace outline { namespace _2D {

		__class(CMarker) {

			__ctor(_ctor) {

				_out() += TLog_Acc::e_new_line;
				_out() += TMarker().Print(e_print::e_all);
				_out()();
			}

			__method(Operators) {
			
				TMarker mark_0(6, _T("The 1st one"), true);
				TMarker mark_1(7, _T("The 2nd one"), true);

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(
					_T("Marker %s equals to %s one >> %s"), (_pc_sz) mark_0.Print(e_print::e_req), (_pc_sz) mark_1.Print(e_print::e_req), TStringEx().Bool(mark_0 == mark_1));
				_out()();
			}

		};

		__class(CSide) {

			__ctor(_ctor) {

				TSide a_side;
				// It is prefereble to use appropriate constructor, otherwise validity flag of the marker remains false by default;
				a_side.Marker() << (uint32_t) 1 << _T("left") << true; // error C2666: requires specific data type definition for marker identifier :( ;

				a_side.Begin() = TPoint(0,0);
				a_side.End() = TPoint(1,1);

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("Default: %s"), (_pc_sz) TSide().Print(e_print::e_all));
				_out() += TStringEx().Format(_T("Inited : %s"), (_pc_sz) a_side.Print(e_print::e_all));
				_out()();
			}

		};

		__class(CSides) {

			__ctor(_ctor) {

				TSides sides;
				TSide  side ;
				
				side.Marker() << (uint32_t)1 << _T("The 1st marker") << true; sides.Append(side);
				side.Marker() << (uint32_t)2 << _T("The 2nd marker") << true; sides.Append(side);

				_out() += TLog_Acc::e_new_line;
				_out() += sides.Print(e_print::e_all, _T("\n\t"), _T(""));
				_out()();
			}
		};
	}}

	namespace outline { namespace _2D {

		using TRect = geometry::shape::_2D::CRectangle;

		__class(CRect) {
			__ctor(_ctor) {

				_out() += TLog_Acc::e_new_line;
				_out() += TString().Format(_T("Default: %s"), (_pc_sz)TRect().Print(e_print::e_req));
				_out()();

			}
		};
	}}
}}}