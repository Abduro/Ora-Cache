/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Apr-2026 at 14:30:48.038, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL extension wrapper interface implementation file;
*/
#include "gl_procs_ext.h"
#include "shared.preproc.h"
#include "shared.wnd.fake.h"

using namespace ex_ui::draw::open_gl::procs;

#pragma region cls::CExtension{}

CExtension::CExtension (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

TError& CExtension::Error (void) const { return this->m_error; }

err_code CExtension::Init (void) {
	this->m_error <<__METHOD__<<__s_ok;

	return this->Error();
}

#pragma endregion

TProcsExt&  ::Get_ProcExt (void) {
	static
	TProcsExt proc_ext;
	return proc_ext;
}