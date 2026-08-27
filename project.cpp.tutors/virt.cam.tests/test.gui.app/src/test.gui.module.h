#ifndef _TEST_GUI_MODULE_H_INCLUDED
#define _TEST_GUI_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Aug-2026 at 21:22:48.638, UTC+4, Batumi, Tuesday;
	This is virtual camera test cases' desktop GUI app module interface declaration file;
*/
#include "common.defs.h"
#include "test.gui.window.h"

namespace test { namespace app { using namespace ::test::draw::defs;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CModule : public ATL::CAtlExeModuleT<CModule> { typedef ATL::CAtlExeModuleT<CModule> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};

}}


#endif/*_TEST_GUI_MODULE_H_INCLUDED*/