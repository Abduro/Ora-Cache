#ifndef _HANDLERS_H_INCLUDED
#define _HANDLERS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Oct-2021 at 11:31:02.8909820 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX window message handler adapter base interface declaration file.
*/

#include "handler.base.h"
#include "handler.client.h"
#include "handler.draw.h"
#include "handler.frame.h"
#include "handler.life.h"
#include "handler.menu.h"
#include "handler.mouse.h"
#include "handler.sys.h"

namespace ex_ui { namespace message { namespace handlers {

	using shared::sys_core::CError;

	using ClnHandler  = cl_area::CHandler;
	using DrawHandler = draw::CHandler   ;
	using FrmHandler  = frame::CHandler  ;
	using LivHandler  = life::CHandler   ;
	using MnuHandler  = menu::CHandler   ;
	using MouHandler  = mouse::CEvents   ;
	using SysHandler  = CMsgSystem       ;

#if (1)
	class CHandlers : public CBase { typedef CBase TBase; // ToDo: for what reason is the parent class assigned?
	public:
		 CHandlers (void);
		 CHandlers (const CHandlers&) = delete; // not is used yet ;
		 CHandlers (CHandlers&&) = delete;      // not is used yet ;
		 virtual
		~CHandlers (void);

	public:
		BEGIN_MSG_MAP(CHandlers) // the map is made in accordance on message frequency: the most frequent used first;
			CHAIN_MSG_MAP_MEMBER(m_draw  )
			CHAIN_MSG_MAP_MEMBER(m_mouse )
			CHAIN_MSG_MAP_MEMBER(m_menu  )
			CHAIN_MSG_MAP_MEMBER(m_client)
			CHAIN_MSG_MAP_MEMBER(m_frame )
			CHAIN_MSG_MAP_MEMBER(m_live  )
			CHAIN_MSG_MAP_MEMBER(m_system)
		END_MSG_MAP()

	public:
		const
		ClnHandler&  Client (void) const;
		ClnHandler&  Client (void) ;
		const
		DrawHandler& Draw (void) const;
		DrawHandler& Draw (void) ;
		const
		FrmHandler&  Frame (void) const;
		FrmHandler&  Frame (void) ;
		const
		LivHandler&  Live (void) const;
		LivHandler&  Live (void) ;
		const
		MnuHandler&  Menu (void) const;
		MnuHandler&  Menu (void) ;
		const
		MouHandler&  Mouse(void) const;
		MouHandler&  Mouse(void) ;
		const
		SysHandler&  System (void) const;
		SysHandler&  System (void) ;

	private:
		CHandlers&  operator = (const CHandlers&) = delete;  // not is used yet ;
		CHandlers&  operator = (CHandlers&&) = delete;       // not is used yet ;

	protected:
		ClnHandler  m_client;
		DrawHandler m_draw  ;
		FrmHandler  m_frame ;
		LivHandler  m_live  ;
		MnuHandler  m_menu  ;
		MouHandler  m_mouse ;
		SysHandler  m_system;
	};
#endif
}}}

typedef ex_ui::message::handlers::CHandlers  TMsgHandlers;

#endif/*_HANDLERS_H_INCLUDED*/