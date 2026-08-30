/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Aug-2026 at 23:26:30.688, UTC+4, Batumi, Saturday;
	This is virtual camera test desktop app main window layout interface implementation file;
*/
#include "test.gui.layout.h"

using namespace ::test::app;

#pragma region cls::CLayout{}

const
CWindow& CLayout::Window (void) const { return this->m_wnd; }
CWindow& CLayout::Window (void)       { return this->m_wnd; }


CLayout& CLayout::operator <<(const HWND _h_app_wnd) { this->m_wnd = _h_app_wnd;  return *this; }


#pragma endregion