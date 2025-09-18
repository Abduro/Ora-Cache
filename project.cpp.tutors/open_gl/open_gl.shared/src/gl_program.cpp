/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:48:34.237, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface implementation file;
*/
#include "gl_program.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

CBase:: CBase (void) { this->m_error() >> __CLASS__ << __METHOD__ << __e_not_inited; }
CBase::~CBase (void) {}

TErr_ex& CBase::Error (void) const { return this->m_error; }