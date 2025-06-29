#ifndef _UIX_THEME_REG_H_INCLUDED
#define _UIX_THEME_REG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.con) on 29-Jun-2025 at 07:36:53.5666, UTC+4, Batumi, Sunday;
	This is Ebo Pack custom theme registry storage base interface declaration file;
*/
#include "uix.theme.inc.h"
#include "uix.theme.named.h"

namespace ex_ui { namespace theme { namespace storage {

	using namespace ex_ui::theme;

	class CRegistry {
	public:
		 CRegistry (void); CRegistry (const CRegistry&) = delete; CRegistry (CRegistry&&) = delete;
		~CRegistry (void);

	public:
		TError&  Error (void) const;

		err_code Load (CNamed_Enum&); // loads all registere custom themes from the system registry;

	public:
		CRegistry& operator = (const CRegistry&) = delete;
		CRegistry& operator = (CRegistry&&) = delete;

	private:
		CError   m_error;
	};

}}}

#endif/*_UIX_THEME_REG_H_INCLUDED*/