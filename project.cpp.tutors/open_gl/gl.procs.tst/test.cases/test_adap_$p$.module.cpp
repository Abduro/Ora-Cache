/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-May-2026 at 19:19:18.767, UTC+4, Batumi, Sunday;
	This is OpenGL tutorials' draw components unit test project module implementation file;
*/
#include "test_adap_$p$.module.h"
#include <locale>

using namespace test::open_gl;

#if (1)
/* without specifying the namespace of procedures' location the linker cannot find their definitions and throws the exception:
   ...error LNK2001: unresolved external symbol "void __cdecl ebo::boo::test::open_gl::draw::OnLoad(void),,,;
   otherwise these methods must be declared in global namespace, because 'using namespace' does not work for linker, but for compiler only;
*/
namespace test { namespace open_gl {

void OnLoad (void) {

	const char* p_result = ::setlocale(LC_ALL, "en-US");
	if (nullptr == p_result) { /*the error*/ }
	else {/*is set*/}

	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CError error((_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CString cs_path = shared::dbg::CModule::Get_path(error);
	if (error)
		_out() += error.Print(TError::e_print::e_req);
	else
		_out() += cs_path;

	_out()();
}

void OnUnload (void) {
	_out()(true); // it can be turned off by one of the test cases;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CError error((_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CString cs_path = shared::dbg::CModule::Get_path(error);
	if (error)
		_out() += error.Print(TError::e_print::e_req);
	else
		_out() += cs_path;

	_out()();
}
}}

#endif