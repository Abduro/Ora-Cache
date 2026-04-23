/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Jan-2026 at 23:38:48.842, UTC+4, Batumi, Tauesday;
	Ebo Pack OpenGL draw context lib common definitions' uint test interface implementation file;
*/
#include "ebo_test_$d$.defs.h"

using namespace test::draw::open_gl;

namespace test { namespace draw { namespace open_gl { namespace _impl_3 { void __warning_lnk_4006 (void) {}}}}}

#pragma region cls::CTstVersion{}

err_code  CTstVersion::Load (const bool _cls_out/* = true*/) {
	if (_cls_out)
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	if ((*this)().Error()) // an error may occur in version constructor class while trying to get version info of OpenGL installed on OS;
		_out() += (*this)().Error();
	else
		_out() += (*this)().Print_2();

	return (*this)().Error();
}

const
CVersion& CTstVersion::operator ()(void) const { return this->m_ver; }
CVersion& CTstVersion::operator ()(void)       { return this->m_ver; }

#pragma endregion