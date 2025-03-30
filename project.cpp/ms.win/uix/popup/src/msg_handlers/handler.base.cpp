/*
	Created by Tech_dog (ebontrop@gmail.com) on 4-Nov-2021 at 4:19:14.6635546 pm, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack UIX window message handler base interface implementation file.
*/
#include "handler.base.h"

using namespace ex_ui::message::handlers;

/////////////////////////////////////////////////////////////////////////////

CBase:: CBase (void) { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CBase::~CBase (void) {}

/////////////////////////////////////////////////////////////////////////////

TErrorRef  CBase::Error(void) const { return this->m_error; }
err_code   CBase::Lock (void) {
	m_error << __METHOD__ << TErrCodes::no_error;

//	if (false == m_guard.IsValid()) 
//		return (m_error << __e_not_inited);

	this->m_guard.Lock();

	return m_error;
}

err_code   CBase::Unlock (void) {
	m_error << __METHOD__ << TErrCodes::no_error;

//	if (false == m_guard.IsValid())
//		return (m_error << __e_not_inited);

	this->m_guard.Unlock();

	return m_error;
}