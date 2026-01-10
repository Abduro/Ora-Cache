/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Jan-2026 at 23:38:48.842, UTC+4, Batumi, Tauesday;
	Ebo Pack OpenGL draw context lib common definitions' uint test interface implementation file;
*/
#include "ebo_test_$d$.defs.h"

using namespace ebo::boo::test::open_gl::draw;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_3 { void __warning_lnk_4006 (void) {}}}}}

/* without specifying the namespace of procedures' location the linker cannot find their definitions and throws the exception:
   ...error LNK2001: unresolved external symbol "void __cdecl ebo::boo::test::open_gl::draw::OnLoad(void),,,;
   otherwise these methods must be declared in global namespace, because 'using namespace' does not work for linker, but for compiler only;
*/
namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
void OnLoad (void) {
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
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CError error((_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CString cs_path = shared::dbg::CModule::Get_path(error);
	if (error)
		_out() += error.Print(TError::e_print::e_req);
	else
		_out() += cs_path;

	_out()();
}
}}}}}