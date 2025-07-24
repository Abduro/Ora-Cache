/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Jul-2025 at 20:52:14.500, UTC+4, Batumi, Wednesday;
	This is Ebo Pack user base control image interface implementation file;
*/
#include "ctl.base.image.h"

using namespace ex_ui::controls;

/////////////////////////////////////////////////////////////////////////////

CImages:: CImages (void) {}
CImages::~CImages (void) {}

const
CImgList& CImages::List (void) const { return this->m_list; }
CImgList& CImages::List (void)       { return this->m_list; }