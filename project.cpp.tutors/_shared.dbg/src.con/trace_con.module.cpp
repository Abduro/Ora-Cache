/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Mar-2026 at 13:21:33.292, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorials' shared debug trace console entry point implementation file;
*/
#include "trace_con.module.h"
#include "trace_con.loader.h"

/*Enable Automatic Closing (Recommended):
  (1) Navigate to Settings: Go to Tools > Options from the top menu;
  (2) Debugging Section: Expand the Debugging category on the left and select General;
  (3) Toggle the Checkbox: Find the option 'Automatically close the console when debugging stops' and ensure it is checked;
*/

uint32_t _tmain (int argc, _TCHAR* argv[]) {
	argc; argv;
	using namespace shared::console;

	CLoader().Do_it();
	CPers pers;
	pers.Load();
#if (0)
	// https://stackoverflow.com/questions/21257544/c-wait-for-user-input ;
	out_t << _T("\n\tPress [Enter] key or click [x] button to exit;");
	in_t.get();
#else
	::_tprintf(_T("\n\n\tPress any key or click [x] button to exit;")); // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/printf-printf-l-wprintf-wprintf-l ;
	::_gettch();                                                        // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch ;
#endif
	return 0;
}