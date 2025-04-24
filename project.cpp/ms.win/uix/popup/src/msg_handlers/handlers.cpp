/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Oct-2021 at 11:48:47.8172601 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX window message handler adapter base interface implementation file.
*/
#include "handlers.h"

using namespace ex_ui::message::handlers;

/////////////////////////////////////////////////////////////////////////////

CHandlers:: CHandlers (void) { TBase::m_error >> __CLASS__ << __METHOD__; }
CHandlers::~CHandlers (void) {}

/////////////////////////////////////////////////////////////////////////////

const ClnHandler&   CHandlers::Client (void) const { return this->m_client; } ClnHandler&   CHandlers::Client (void) { return this->m_client; }
const DrawHandler&  CHandlers::Draw   (void) const { return this->m_draw  ; } DrawHandler&  CHandlers::Draw   (void) { return this->m_draw  ; }
const FrmHandler&   CHandlers::Frame  (void) const { return this->m_frame ; } FrmHandler&   CHandlers::Frame  (void) { return this->m_frame ; }
const LivHandler&   CHandlers::Live   (void) const { return this->m_live  ; } LivHandler&   CHandlers::Live   (void) { return this->m_live  ; }
const MnuHandler&   CHandlers::Menu   (void) const { return this->m_menu  ; } MnuHandler&   CHandlers::Menu   (void) { return this->m_menu  ; }
const MouHandler&   CHandlers::Mouse  (void) const { return this->m_mouse ; } MouHandler&   CHandlers::Mouse  (void) { return this->m_mouse ; }
const SysHandler&   CHandlers::System (void) const { return this->m_system; } SysHandler&   CHandlers::System (void) { return this->m_system; }