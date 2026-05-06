/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 11:10:36.540, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL fake (message-only) window interface implementation file;
*/
#include "open_gl_tutor.0.fake.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::fake;

#ifndef _T
#ifndef  _UNICODE
#define _T(x)      x
#else
#define _T(x) L ## x
#endif
#endif

namespace ex_ui { namespace draw { namespace open_gl { namespace fake { namespace _impl {

	using namespace shared::defs;

}}}}}
using namespace ex_ui::draw::open_gl::fake::_impl;

CWnd:: CWnd (void) : TWindow() { TWindow::m_error >> __CLASS__; }

CWnd::~CWnd (void) {}