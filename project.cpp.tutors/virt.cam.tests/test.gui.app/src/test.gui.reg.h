#ifndef _TEST_GUI_REG_H_INCLUDED
#define _TEST_GUI_REG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Nov-2026 at 20:29:13.021, UTC+4, Batumi, Thursday;
	The is virtual camera test application  registry storage wrapper interface declaration file;
*/
#include "test.gui.defs.h"
#include "sys.registry.h"

namespace test { namespace app { namespace storage {

	using namespace ::test::app;
	using CRoot_base = ::shared::sys_core::storage::CRoot;
namespace route {

	class CCommand {
	public:
		 CCommand (void) = default; CCommand (const CCommand&) = delete; CCommand (CCommand&&) = delete;
		~CCommand (void) = default;

		static _pc_sz Get_name (const uint32_t _cmd_id); // gets registry value name for input command identifier;
		static _pc_sz Get_path (const uint32_t _cmd_id); // gets registry key path for input command identifier;

	private:
		CCommand& operator = (const CCommand&) = delete; CCommand& operator = (CCommand&&) = delete;
	};

	class CCommands {
	public:
		CCommands (void); CCommands (const CCommands&) = delete; CCommands (CCommands&&) = delete; ~CCommands (void) = default;

		static _pc_sz Root (void);

	private:
		CCommands& operator = (const CCommands&) = delete; CCommands& operator = (CCommands&&) = delete;
	};

	class CApp {
	public:
		using CCmds = CCommands;

		CApp (void); CApp (const CApp&) = delete; CApp (CApp&&) = delete; ~CApp (void) = default;
		_pc_sz Root (void) const;

	private:
		CApp&  operator = (const CApp&) = delete; CApp& operator = (CApp&&) = delete;
	};

	class CRoot : public CRoot_base { typedef CRoot_base TBase;
	public:
		CRoot (void) = default; CRoot (const CRoot&) = delete; CRoot (CRoot&&) = delete; ~CRoot (void) = default;

		_pc_sz  Path (void) const;  // returns the registry path to window popup root node;
		const
		CRoot_base& operator ()(void) const;
		CRoot_base& operator ()(void) ;

	private:
		CRoot& operator = (const CRoot&) = delete; CRoot& operator = (CRoot&&) = delete;
	};
}
	class CReg_router {
	public:
		using CApp  = route::CApp;
		using CCmds = route::CCommands;
		using CRoot = route::CRoot;

		 CReg_router (void); CReg_router (const CReg_router&) = delete; CReg_router (CReg_router&&) = delete;
		~CReg_router (void);
		const
		CApp&  App (void) const;
		CApp&  App (void) ;
		const
		CCmds& Cmds (void) const;
		CCmds& Cmds (void) ;
		const
		CRoot& Root (void) const;
		CRoot& Root (void) ;

	private:
		CReg_router& operator = (const CReg_router&) = delete; CReg_router& operator = (CReg_router&&) = delete;
		CApp  m_app ;
		CCmds m_cmds;
		CRoot m_root;
	};

	CReg_router&  Get_reg_router (void);

	class CCommand {
	public:
		 CCommand (const uint32_t _cmd_id = 0); CCommand (const CCommand&) = delete; CCommand (CCommand&&) = delete;
		~CCommand (void) = default;

		TError& Error (void) const;

		uint32_t Id (void) const;      // gets command identifier;
		err_code Id (const uint32_t);  // sets command identifier; if command identifier is not defined in shortcut menu, the error is returned;

		static
		bool  Is_valid (const uint32_t _cmd_id, CError&);
		bool  Is_valid (void) const;   // returns 'true' in case the command identifier is set;

		CString  Get (void);                  // returns this command value; if string is empty, an error occurs;
		err_code Set (const CString& _value); // sets this comand value as a string;

		CCommand& operator << (const uint32_t _cmd_id); // sets command identifier;
		err_code  operator << (const _pc_sz _p_value);  // sets command value by using this::Set(...);

	private:
		CCommand& operator = (const CCommand&) = delete; CCommand& operator = (CCommand&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_cmd_id;
	};
}}}

#endif/*_TEST_GUI_REG_H_INCLUDED*/