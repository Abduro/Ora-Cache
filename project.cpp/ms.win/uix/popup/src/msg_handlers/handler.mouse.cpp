/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Oct-2021 at 4:43:16.0809007 am, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack UIX window mouse message handler base interface implementation file.
	-----------------------------------------------------------------------------
	Original Mouse Tracker class implementation is created on 8-Dec-2010 at 1:20:26am, GMT+3, Rostov-on-Don, Wednesday;
*/
#include "handler.mouse.h"

using namespace ex_ui::message::handlers::mouse;

/////////////////////////////////////////////////////////////////////////////

CEvents:: CEvents (void) { m_error >> __CLASS__ << __METHOD__; }
CEvents::~CEvents (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CBtnsHandler&  CEvents::Buttons (void) const { return m_evt_buttons; }
CBtnsHandler&  CEvents::Buttons (void)       { return m_evt_buttons; }

TErrorRef      CEvents::Error   (void) const { return this->m_error; }

const
CTrackHandler& CEvents::Tracker (void) const { return m_evt_tracker; }
CTrackHandler& CEvents::Tracker (void)       { return m_evt_tracker; }

#if (0)
err_code   CMsgMouseEvents::Arrogate (CMsgMouseEvents& _victim) {
	m_error << __METHOD__ << __s_ok;

	if (__failed(this->Buttons().Arrogate(_victim.Buttons())))
		return (m_error = this->Buttons().Error());

	if (__failed(this->Tracker().Arrogate(_victim.Tracker())))
		return (m_error = this->Tracker().Error());

	return m_error;
}
#endif