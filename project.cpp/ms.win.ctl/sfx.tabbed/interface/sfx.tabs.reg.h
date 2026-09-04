#ifndef _SFX_TABS_REG_H_INCLUDED
#define _SFX_TABS_REG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2026 at 17:36:18.060, UTC+4, Batumi, Thursday;
	The is SFX tabbed control registry storage wrapper interface declaration file;
*/
#include "ctl.base.reg.h"
#include "sfx.tabs.ctrl.h"

namespace ex_ui { namespace controls { namespace tabbed { namespace storage {

	using CRoot_ctrl = ::ex_ui::controls::storage::CRoot;

	class CRoot : public CRoot_ctrl { typedef CRoot_ctrl TBase;
	public:
		CRoot (void) = default; CRoot (const CRoot&) = delete; CRoot (CRoot&&) = delete; ~CRoot (void) = default;

		_pc_sz  Path (void) const;  // returns the root path to tabbed control's node;
		_pc_sz  Path (const uint32_t _ctrl_id) const; // returns the path of tabbed control by its identifier;
		const
		CRoot_ctrl& operator ()(void) const;
		CRoot_ctrl& operator ()(void) ;

	private:
		CRoot& operator = (const CRoot&) = delete; CRoot& operator = (CRoot&&) = delete;
	};
}
	using namespace ::ex_ui::controls;
	using TabCtrl = ::ex_ui::controls::sfx::tabbed::CControl;

	class CPersistent {
	public:
		class CActive {
		public:
			CActive (void); CActive (const CActive&) = delete; CActive (CActive&&) = delete; ~CActive (void) = default;

			TError&  Error (void) const;

			err_code Load (void);
			err_code Save (void);

			CActive& operator <<(TabCtrl*);

		private:
			CActive& operator = (const CActive&) = delete; CActive& operator = (CActive&&) = delete;
			CError   m_error;
			TabCtrl* m_p_ctrl;
		};
		class CAlign {
		public:
			CAlign (void); CAlign (const CAlign&) = delete; CAlign (CAlign&&) = delete; ~CAlign (void) = default;

			TError&  Error (void) const;

			err_code Load (void);
			err_code Save (void);

			CAlign& operator <<(TabCtrl*);

		private:
			CAlign& operator = (const CAlign&) = delete; CAlign& operator = (CAlign&&) = delete;
			CError   m_error;
			TabCtrl* m_p_ctrl;
		};
		class CSide {
		public:
			CSide (void); CSide (const CSide&) = delete; CSide (CSide&&) = delete; ~CSide (void) = default;

			TError&  Error (void) const;

			err_code Load (void);
			err_code Save (void);

			CSide& operator <<(TabCtrl*);

		private:
			CSide& operator = (const CSide&) = delete; CSide& operator = (CSide&&) = delete;
			CError   m_error;
			TabCtrl* m_p_ctrl;
		};

		CPersistent (void); CPersistent (const CPersistent&) = delete; CPersistent (CPersistent&&) = delete; ~CPersistent (void) = default;
	
		TError& Error (void) const;
		const
		CSide&  Side (void) const;
		CSide&  Side (void) ;

	private:
		CPersistent& operator = (const CPersistent&&) = delete; CPersistent& operator = (CPersistent&&) = delete;
		CError m_error;
		CSide  m_side ;
	};
}}}

#endif/*_SFX_TABS_REG_H_INCLUDED*/