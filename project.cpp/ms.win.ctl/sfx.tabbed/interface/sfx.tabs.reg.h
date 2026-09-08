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

	using TabCtrl = ::ex_ui::controls::sfx::tabbed::CControl;
	class CBase {
	protected:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;
	public:
		static
		_pc_sz   Class (void);

		TError&  Error (void) const;
		bool  Is_valid (void) const;

		CBase&   operator <<(TabCtrl*);
		bool     operator ()(void) const;

	protected:
		CBase&   operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		CError   m_error;
		TabCtrl* m_p_ctrl;
	};
}
	using namespace ::ex_ui::controls;
	using TabCtrl = ::ex_ui::controls::sfx::tabbed::CControl;

	class CPersistent : public storage::CBase { typedef storage::CBase TBase;
	public:
		class CActive : public storage::CBase { typedef storage::CBase TBase;
		public:
			CActive (void); ~CActive (void) = default;

			err_code Load (void);
			err_code Save (void);
		};
		class CAlign : public storage::CBase { typedef storage::CBase TBase;
		public:
			CAlign (void); ~CAlign (void) = default;

			err_code Load (void);
			err_code Save (void);
		};

		class CCaption : public storage::CBase { typedef storage::CBase TBase;
		public:
			CCaption (void); ~CCaption (void) = default;

			err_code Load (void);
			err_code Save (void);
		};

		class CSide : public storage::CBase { typedef storage::CBase TBase;
		public:
			CSide (void); ~CSide (void) = default;

			err_code Load (void);
			err_code Save (void);
		};

		class CSize : public storage::CBase { typedef storage::CBase TBase;
		public:
			CSize (void); ~CSize (void) = default;

			err_code Load (void);
			err_code Save (void);
		};

		CPersistent (void); ~CPersistent (void) = default;

		err_code Load (void);
		err_code Save (void);
	};
}}}

#endif/*_SFX_TABS_REG_H_INCLUDED*/