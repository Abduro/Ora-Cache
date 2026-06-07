/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-May-2026 at 19:19:18.767, UTC+4, Batumi, Sunday;
	This is OpenGL tutorials' draw components unit test project module implementation file;
*/
#include "test_adap_$p$.module.h"
#include <locale>
#include <memory> // https://en.cppreference.com/cpp/memory/unique_ptr ;

using namespace test::open_gl;

#define __use_it 0

#if (1)
/* without specifying the namespace of procedures' location the linker cannot find their definitions and throws the exception:
   ...error LNK2001: unresolved external symbol "void __cdecl ebo::boo::test::open_gl::draw::OnLoad(void),,,;
   otherwise these methods must be declared in global namespace, because 'using namespace' does not work for linker, but for compiler only;
*/
namespace test { namespace open_gl {

static ::std::unique_ptr<::open_gl::CFake_Ctx> p_fk_ctx;

void OnLoad (void) {

	const char* p_result = ::setlocale(LC_ALL, "en-US");
	if (nullptr == p_result) { /*the error*/ }
	else {/*is set*/}
#if defined(__use_it) && (__use_it != 0)
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CError error((_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CString cs_path = shared::dbg::CModule::Get_path(error);
	if (error)
		_out() += error.Print(TError::e_print::e_req);
	else
		_out() += cs_path;
#else
	p_fk_ctx = ::std::make_unique<::open_gl::CFake_Ctx>();
	if (p_fk_ctx.get())
		if (__failed((*p_fk_ctx).Create())) _out() += (*p_fk_ctx).Error();
		else
			_out() += TString().Format(_T("[impt] %s"), (_pc_sz)(*p_fk_ctx).To_str());
#endif
	_out()();
}

void OnUnload (void) {

#if defined(__use_it) && (__use_it != 0)
	_out()(true); // it can be turned off by one of the test cases;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CError error((_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CString cs_path = shared::dbg::CModule::Get_path(error);
	if (error)
		_out() += error.Print(TError::e_print::e_req);
	else
		_out() += cs_path;
#else
	if (p_fk_ctx.get()) {
		if (__failed((*p_fk_ctx).Destroy())) _out() += (*p_fk_ctx).Error();
		p_fk_ctx = nullptr;
	}
#endif
	_out()();
}

}}

#endif