/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Apr-2026 at 14:43:55.388, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' data providers' unit test project module implementation file;
*/
#include "test_adap_$dat$.lib.module.h"

using namespace ebo::boo::test::data;

#if (1)
/* without specifying the namespace of procedures' location the linker cannot find their definitions and throws the exception:
   ...error LNK2001: unresolved external symbol "void __cdecl ebo::boo::test::open_gl::draw::OnLoad(void),,,;
   otherwise these methods must be declared in global namespace, because 'using namespace' does not work for linker, but for compiler only;
*/
namespace ebo { namespace boo { namespace test { namespace data {

	static CCoIniter g_co_initer;

	void OnLoad (void) {
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
#if (0) // the testhost has already made it;
		using c_com_init = shared::sys_core::c_com_init;
		using e_com_flags = shared::sys_core::c_com_init::e_flags;

		if (__failed(g_co_initer.Init(e_com_flags::e_co_threads)))
		     _out() += g_co_initer.Error();
		else _out() += TString().Format(_T("[impt] com-system is inited for mode: '%s';"), (_pc_sz) c_com_init::To_str(e_com_flags::e_co_threads));
#endif
		_out()();
	}

	void OnUnload (void) {
		_out()(true); // it can be turned off by one of the test cases;
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
#if (0)
		if (__failed(g_co_initer.Uninit()))
		     _out() += g_co_initer.Error();
		else _out() += _T("[impt] com-system is uninited successfully;");
#endif
		_out()();
	}

}}}}
#endif