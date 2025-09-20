/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:32:59.316, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' shader vertex base interface implementation file;
*/
#include "gl_vertex.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vertex;

CBase:: CBase (void) { this->m_error() >> __CLASS__ << __METHOD__ << __e_not_inited; }
CBase::~CBase (void) {}

TErr_ex& CBase::Error (void) const { return this->m_error; }