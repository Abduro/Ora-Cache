#ifndef _HANDLER_MOUSE_H_INCLUDED
#define _HANDLER_MOUSE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Oct-2021 at 4:27:28.3170988 am, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack UIX window mouse message handler base interface declaration file.
	-----------------------------------------------------------------------------
	Original Mouse Tracker class declaration is created on 8-Dec-2010 at 1:13:12am, GMT+3, Rostov-on-Don, Wednesday;
*/
#include "handler.base.h"
#include "handler.mouse.button.h"
#include "handler.mouse.track.h"

namespace ex_ui { namespace message { namespace handlers { namespace mouse {

	using shared::sys_core::CError;
	using CBtnsHandler = buttons::CHandler;

	class CEvents {
	public:
		 CEvents (void);
		 CEvents (const CEvents&) = delete;
		 CEvents (CEvents&&) = delete;
		~CEvents (void);

	public:
		BEGIN_MSG_MAP(CEvents)
			CHAIN_MSG_MAP_MEMBER(m_evt_buttons)
			CHAIN_MSG_MAP_MEMBER(m_evt_tracker)
		END_MSG_MAP()

	public:
		const
		CBtnsHandler&   Buttons (void) const;
		CBtnsHandler&   Buttons (void) ;

		TErrorRef Error (void) const;

		const
		CTrackHandler&  Tracker (void) const;
		CTrackHandler&  Tracker (void) ;

	private:
		CEvents& operator = (const CEvents&) = delete;
		CEvents& operator = (CEvents&&) = delete;

	private:
		CBtnsHandler  m_evt_buttons;
		CTrackHandler m_evt_tracker;
		CError        m_error;
	};

#if (0)
	err_code   Arrogate (CMsgMouseEvents& _victim);  // fore move operation;
#endif
}}}}

//typedef ex_ui::message::handlers::CMsgMouseEvents  TMouseEventSrc;

#endif/*_HANDLER_MOUSE_H_INCLUDED*/