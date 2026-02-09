/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Feb-2026 at 10:55:26.765, UTC+4, Batumi, Sunday;
	This is Ebo Pack shared window popup menu wrapper base interface implementation file;
*/
#include "shared.menu.base.h"
#include "shared.preproc.h"

using namespace shared::gui::menus;

#pragma region cls::CBase{}

CBase:: CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CBase:: CBase (const CBase& _src) : CBase() { *this = _src; }
CBase:: CBase (CBase&& _victim) : CBase() { *this = _victim; }
CBase::~CBase (void) { /*does nothing*/}

TError& CBase::Error (void) const { return this->m_error; }

CBase&  CBase::operator = (const CBase& _src) { this->m_error = _src.Error(); return *this; }
CBase&  CBase::operator = (CBase&& _victim) { *this = (const CBase&)_victim; return *this; }

#pragma endregion