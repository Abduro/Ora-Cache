#ifndef _CONSOLE_CMD_H_INCLUDED
#define _CONSOLE_CMD_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Apr-2026 on 22:19:25.371, UTC+4, Batumi, Sunday;
	This is Ebo Pack trace console command interface declaration file;
*/
#include "console.defs.h"
namespace shared { namespace console { namespace cmds { using namespace shared::defs;

	class CCmd_Base {
	public:
		CCmd_Base (const uint32_t _cmd_id = 0, _pc_sz _p_name = nullptr);
		CCmd_Base (const CCmd_Base&); CCmd_Base (CCmd_Base&&); ~CCmd_Base (void) = default;

		TError& Error (void) const;

		uint32_t Get_id (void) const;
		err_code Set_id (const uint32_t);

		bool  Is_valid (void) const;

		_pc_sz   Name (void) const;
		err_code Name (_pc_sz);

		CString  To_str (void) const;

		CCmd_Base& operator = (const CCmd_Base&); CCmd_Base& operator = (CCmd_Base&&);
		CCmd_Base& operator <<(const uint32_t _u_id);
		CCmd_Base& operator <<(const CString& _cs_name);
		CCmd_Base& operator <<(_pc_sz _p_sz_name);

	protected:
		CError   m_error;
		uint32_t m_id;
		CString  m_name;
	};

	// useless class declaration: Exec() must be specific, thus without virtual method there is no way;
	class CCmd_Clear : public CCmd_Base { typedef CCmd_Base TBase;
	public:
		CCmd_Clear (void);

		const
		CCmd_Base& operator ()(void) const;
		CCmd_Base& operator ()(void) ;

		err_code Exec (void);
	};

}}}

#endif/*_CONSOLE_CMD_H_INCLUDED*/