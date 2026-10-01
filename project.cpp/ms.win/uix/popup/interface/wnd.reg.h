#ifndef _WND_REG_H_INCLUDED
#define _WND_REG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2026 at 12:22:24.963, UTC+4, Batumi, Thursday;
	The is popup window  registry storage wrapper interface declaration file;
*/
#include "wnd.defs.h"
#include "sys.registry.h"

namespace ex_ui { namespace popup {  namespace storage {

	using namespace ::ex_ui::popup::defs;
	using CRoot_base = ::shared::sys_core::storage::CRoot;

namespace route {
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

	class CApp {
	public:
		class CWindow {
		public:
			enum class e_pos : uint32_t {
				e_left = 0x0, e_right, e_top, e_bottom
			};
			CWindow (void); CWindow (const CWindow&) = delete; CWindow (CWindow&&) = delete; ~CWindow (void) = default;
			_pc_sz Position (void) const;    // returns app main window position key path;
			_pc_sz Root (void) const;        // returns app main window root key path;
			_pc_sz Side (const e_pos) const; // returns app main window rectangle side value name;
		private:
			CWindow& operator = (const CWindow&) = delete; CWindow& operator = (CWindow&&) = delete;
		};
	public:
		CApp (void); CApp (const CApp&) = delete; CApp (CApp&&) = delete; ~CApp (void) = default;
		_pc_sz Root (void) const;
		const
		CWindow& Window (void) const;
		CWindow& Window (void) ;
	private:
		CApp& operator = (const CApp&) = delete; CApp& operator = (CApp&&) = delete;
		CWindow m_wnd;
	};
}
	using namespace route;

	class CReg_router {
	public:
		 CReg_router (void); CReg_router (const CReg_router&) = delete; CReg_router (CReg_router&&) = delete;
		~CReg_router (void);

		const
		CApp&  App (void) const;
		CApp&  App (void) ;
		const
		CRoot& Root (void) const;
		CRoot& Root (void) ;

	private:
		CReg_router& operator = (const CReg_router&) = delete; CReg_router& operator = (CReg_router&&) = delete;
		CApp  m_app;
		CRoot m_root;
	};

	CReg_router&  Get_reg_router (void);
}}}

#endif/*_WND_REG_H_INCLUDED*/