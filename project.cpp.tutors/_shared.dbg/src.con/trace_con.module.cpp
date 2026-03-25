/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Mar-2026 at 13:21:33.292, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorials' shared debug trace console entry point implementation file;
*/
#include "trace_con.module.h"
uint32_t _tmain (void) {

	// https://stackoverflow.com/questions/21257544/c-wait-for-user-input ;
	out_t << _T("\n\tPress [Enter] key or click [x] button to exit;");
	in_t.get();

	return 0;
}