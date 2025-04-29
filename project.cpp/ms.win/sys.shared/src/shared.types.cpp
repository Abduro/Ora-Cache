/*
	Created by Tech_dog (ebontrop@gmail.com) on 5-Feb-2025 at 11:57:04.352, UTC+4, Batumi, Wednesday;
	This Ebo Pack shared data types definition file;
*/
#include "shared.types.h"
#if (0)
#include "shared.string.h"
#endif
using namespace shared::types;

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG_)

namespace shared { namespace types {
	CString e_print_to_str (void) {

		static _pc_sz pc_sz_pat = _T("e_print={%d(e_all)|%d(e_no_ns)|%d(e_req)}");

		CString cs_out; cs_out.Format(pc_sz_pat, e_print::e_all, e_print::e_no_ns, e_print::e_req);
		return  cs_out;
	}
}}
#endif
void _dummy_2025_02_05_11_57_04_u4 (void) {}