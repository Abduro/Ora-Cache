#ifndef _TEST_CASE_$P$_EXTS_H_INCLUDED
#define _TEST_CASE_$P$_EXTS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-May-2026 at 23:38:48.000, UTC+4, Batumi, Tuesday;
	This is OpenGL version 1.1 extensions' loading procedures wrapper interface declaration file for using in test cases adapters;
*/
#include "test_adap_$p$.defs.h"
#include "gl_context.h"
#include "gl_procs_ext.h"

namespace test { namespace open_gl { namespace procs {

	using ext_items_t = ex_ui::draw::open_gl::procs::ext_items_t;

	class CTstProcExt {
	public:
		 CTstProcExt (void); CTstProcExt (const CTstProcExt&) = delete; CTstProcExt (CTstProcExt&&) = delete;
		~CTstProcExt (void) = default;

		bool Is_arb (void) const;    // this is some sort of shortcut of using Is_remote();
		bool Is_remote (void) const; // if OpenGL runs under MS Windows remote desktop, ARB extension is not supported definitely;
		err_code  Load (void);       // loads OpenGL extensions;

		const
		TProcExtEnum&  operator ()(void) const;
		TProcExtEnum&  operator ()(void) ;

	private:
		CTstProcExt& operator = (const CTstProcExt&) = delete; CTstProcExt& operator = (CTstProcExt&&) = delete;
	};

}}}

#endif/*_TEST_CASE_$P$_EXTS_H_INCLUDED*/