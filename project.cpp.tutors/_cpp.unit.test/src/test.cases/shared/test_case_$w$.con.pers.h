#ifndef _TEST_CASE_$W$_CON_PERS_H_INCLUDED
#define _TEST_CASE_$W$_CON_PERS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2026 at 20:14:27.673, UTC+4, Batumi, Wednesday;
	This is Ebo Pack console persistent test case interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$w$.defs.h"
#include "console.pers.h"

namespace test { namespace win_api { namespace console {
	using namespace ebo::boo::test::win_api;

	using CPin = shared::console::persistent::CPin;
	using CPos = shared::console::persistent::CPosition;

	class CTstPers {
	public:
		 CTstPers (void) = default; CTstPers (const CTstPers&) = delete; CTstPers (CTstPers&&) = delete;
		~CTstPers (void) = default;

		err_code  Load (const bool _b_cls_out = true);
		err_code  Save (const bool _b_cls_out = true);

		const
		TConPers& operator ()(void) const;
		TConPers& operator ()(void) ;

	private:
		CTstPers& operator = (const CTstPers&) = delete; CTstPers& operator = (CTstPers&&) = delete;
	};

}}}
#endif/*_TEST_CASE_$W$_CON_PERS_H_INCLUDED*/