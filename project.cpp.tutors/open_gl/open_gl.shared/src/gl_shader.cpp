/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2025 at 23:18:06.457, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' shader base interface implementation file;
*/
#include "gl_shader.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

CBase:: CBase (void) { this->m_error() >> __CLASS__ << __METHOD__ << __e_not_inited; }
CBase::~CBase (void) {}

TErr_ex& CBase::Error (void) const { return this->m_error; }