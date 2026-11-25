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
		static _pc_sz Get_path (const uint32_t _cmd_id, const uint32_t _tab_ndx); // gets registry key path for input command identifier and tab index;

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

	class CMru {
	public:
		 CMru (void) = default; CMru (const CMru&) = delete; CMru (CMru&&) = delete;
		~CMru (void) = default;

		_pc_sz Name (void) const; // returns HTML file path registry key value name;
		_pc_sz Root (void) const; // returns a root path of MRU registry key;

	private:
		CMru&  operator = (const CMru&) = delete; CMru& operator = (CMru&&) = delete;
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
		using CMru  = route::CMru;
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
		CMru&  Mru (void) const;
		CMru&  Mru (void) ;
		const
		CRoot& Root (void) const;
		CRoot& Root (void) ;

	private:
		CReg_router& operator = (const CReg_router&) = delete; CReg_router& operator = (CReg_router&&) = delete;
		CApp  m_app ;
		CCmds m_cmds;
		CMru  m_mru ;
		CRoot m_root;
	};

	CReg_router&  Get_reg_router (void);

	// each command has an identifier, a path to HTML file and a tab page index to which this command is applied;
	// it not looks good and CCommand class possibly requires a review;
	class CCommand {
	public:
		 CCommand (const uint32_t _cmd_id = 0); CCommand (const CCommand&) = delete; CCommand (CCommand&&) = delete;
		~CCommand (void) = default;

		TError& Error (void) const;

		uint32_t Id (void) const;      // gets command identifier;
		err_code Id (const uint32_t);  // sets command identifier; if command identifier is not defined in shortcut menu, the error is returned;

		bool    Is_valid (void) const; // returns 'true' if this class object has the valid command identifier and tab index;
		static  bool  Is_valid (const uint32_t _cmd_id, CError&); // returns 'true' if the command identifier belongs to one of the shortcut menu items;
		static  bool  Is_valid (const uint32_t _cmd_id, const uint32_t _tab_ndx, CError&); // returns 'true' if command identifier and tab index are valid;

		CString  Get (void);                  // returns this command value; if string is empty, an error occurs;
		err_code Set (const CString& _value); // sets this comand value as a string; it is assumed the command identifier and tab index are already set;

		uint32_t  Tab (void) const;           // gets currently set tab index;
		err_code  Tab (const uint32_t);       // sets curremt tab index; if input value is out of (tabs' count - 1) range, the error is returned;

		CCommand& operator << (const uint32_t _cmd_id);  // sets command identifier;
		err_code  operator << (const _pc_sz _p_value);   // sets command value by using this::Set(...);
		CCommand& operator >> (const uint32_t _tab_ndx); // sets tab index;

	private:
		CCommand& operator = (const CCommand&) = delete; CCommand& operator = (CCommand&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_cmd_id;
		uint32_t m_tab_ndx; // by default it equals to 0, that is not truth for cases when no tab is added, Is_valid() function takes it into account;
	};
}}}

#endif/*_TEST_GUI_REG_H_INCLUDED*/