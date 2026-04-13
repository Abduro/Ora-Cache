#ifndef _TEST_CASE_$D$_PROCS_H_INCLUDED
#define _TEST_CASE_$D$_PROCS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Apr-2026 at 08:18:00.941, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL API  procedure loader wrapper interface declaration file for using in test cases adapters;
*/
#include "test_adap_$d$.defs.h"
#include "gl_context.h"
#include "gl_procs_ext.h"
#include "shared.wnd.fake.h"

namespace test { namespace draw { namespace open_gl {

	using CProc_Ext = ex_ui::draw::open_gl::procs::CExtension;

	class CTstProcExt {
	public:
		 CTstProcExt (void) = default; CTstProcExt (const CTstProcExt&) = delete; CTstProcExt (CTstProcExt&&) = delete;
		~CTstProcExt (void) = default;

		err_code Load (void); // loads OpenGL extensions;
		err_code Unload (void); // unloads OpenGL extension;

		const
		CProc_Ext&  operator ()(void) const;
		CProc_Ext&  operator ()(void) ;

	private:
		CTstProcExt& operator = (const CTstProcExt&) = delete; CTstProcExt& operator = (CTstProcExt&&) = delete;
	};

}}}


#endif/*_TEST_CASE_$D$_PROCS_H_INCLUDED*/