/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Aug-2025 at 23:51:59.009,(UTC+4), Batumi, Monday;
	This is Ebo Pack trackball user control layout interface implementation file;
*/
#include "sfx.trkball.lay.h"
#include "sfx.trkball.ctrl.h"

using namespace ex_ui::controls::sfx::track;
using namespace ex_ui::controls::sfx::track::layout;

#ifndef __H
#define __H(rc) (rc.bottom - rc.top)
#endif

#ifndef __W
#define __W(rc) (rc.right - rc.left)
#endif

CLayout:: CLayout (CControl& _ctrl) : m_ctrl(_ctrl), m_padding(5,5,-5,-5) { m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CLayout::~CLayout (void) {}

TError&   CLayout::Error  (void) const { return this->m_error ; }

const
CPadding& CLayout::Padding(void) const { return this->m_padding; }
CPadding& CLayout::Padding(void)       { return this->m_padding; }