/*
	Creatsd by Tech_dog (ebontrop@gmail.com) on 24-May-2026 at 11:23:51.682, UTC+4, Batumi, Sunday;
	This is OpenGL version wrapper unit test case interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.ver.h"

using namespace test::open_gl;

#pragma region cls::CTstVersion{}

CTstVersion::CTstVersion (void) { _out().Clear(); /*clears messages received from fake context creation*/ }

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