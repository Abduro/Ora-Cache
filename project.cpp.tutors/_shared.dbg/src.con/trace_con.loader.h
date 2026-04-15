#ifndef _TRACE_CON_LOADER_H_INCLUDED
#define _TRACE_CON_LOADER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Mar-2026 at 16:06:05.594, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL trace console loader interface declaration file.
*/
#include "shared.defs.h"
#include "shared.timer.h"
#include "console.pers.h"

namespace shared { namespace console { using namespace shared::defs; using namespace shared::common;

	class CPers : public IWaitable_Events, public persistent::CPosition { typedef persistent::CPosition TBase;
	public:
		 CPers (void); CPers (const CPers&) = delete; CPers (CPers&&) = delete;
		~CPers (void);

		err_code Load (void);

		void IWaitable_OnComplete (void) override final;

	private:
		CPers& operator = (const CPers&) = delete; CPers& operator = (CPers&&) = delete;
		CQueTimer m_timer; // standard timer, even without window, but with callback procedure, does not work without message loop;
	};

	class CLoader {
	public:
		 CLoader (void); CLoader (const CLoader&) = delete; CLoader (CLoader&&) = delete;
		~CLoader (void) = default;

		err_code Do_it (void);
		TError&  Error (void) const;


	private:
		CLoader& operator = (const CLoader&) = delete; CLoader& operator = (CLoader&&) = delete;
		CError m_error;
	};

}}

#endif/*_TRACE_CON_LOADER_H_INCLUDED*/