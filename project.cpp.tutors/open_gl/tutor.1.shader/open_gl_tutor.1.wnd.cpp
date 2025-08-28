/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2025 at 03:01:10.215, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shader window interface implementation file;
*/
#include "open_gl_tutor.1.wnd.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::shade;

CWnd:: CWnd (void) : TWindow() { TWindow::m_error >>__CLASS__; }
CWnd::~CWnd (void) { } // parent class object will destroy window created automatically on its (parent) destruction;
