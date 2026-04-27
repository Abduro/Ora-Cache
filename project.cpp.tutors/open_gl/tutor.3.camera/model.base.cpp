/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2026 at 08:41:40.435, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' model base interface implementation file;
*/
#include "model.base.h"

using namespace ex_ui::draw::open_gl::models;

#pragma region cls::CBase{}

CBase::CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_state: base model is not created"); }

TError& CBase::Error (void) const { return this->m_error; }
const
CGrid&  CBase::Grid (void) const { return this->m_grid; }
CGrid&  CBase::Grid (void)       { return this->m_grid; }
const
CViewPort& CBase::ViewPort (void) const { return this->m_v_port; }
CViewPort& CBase::ViewPort (void)       { return this->m_v_port; }     

#pragma endregion