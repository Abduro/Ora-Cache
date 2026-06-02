/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-May-2026 at 23:15:24.474, UTC+4, Batumi, Tuesday;
	This is OpenGL version 1.1 procedures' wrappers common declarations' uint test case implementation file;
*/
#include "test_adap_$p$.defs.h"

using namespace test::open_gl;

namespace test { namespace open_gl {

_pc_sz To_str (const t_rect& _rect) {
	_rect;
	static _pc_sz p_rect_pat = _T("[left=%04d;top=%04d;right=%04d;bottom=%04d]");
	static  CString cs_out; cs_out.Format(p_rect_pat, _rect.left, _rect.top, _rect.right, _rect.bottom);
	return (_pc_sz) cs_out;
}

namespace _impl_3 { void __warning_lnk_4006 (void) {}}

}}