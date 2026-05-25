#ifndef _TEST_CASE_$D$_VER_H_INCLUDED
#define _TEST_CASE_$D$_VER_H_INCLUDED
/*
	Creatsd by Tech_dog (ebontrop@gmail.com) on 24-May-2026 at 11:22:32.207, UTC+4, Batumi, Sunday;
	This is OpenGL version wrapper unit test case interface declaration file for using in test cases adapters;
*/
#include "test_adap_$d$.defs.h"
#include "gl_version.h"

namespace test { namespace open_gl {

	using CVersion = ex_ui::draw::open_gl::CVersion;

	class CTstVersion {
	public:
		 CTstVersion (void); CTstVersion (const CTstVersion&) = delete; CTstVersion (CTstVersion&&) = delete;
		~CTstVersion (void) = default;
		// version info class loads data automatically in its constructor, but this function is just for print out of the version or an error that may occur;
		err_code Load (const bool _cls_out = true);

		const
		CVersion& operator ()(void) const;
		CVersion& operator ()(void) ;

	private:
		CTstVersion& operator = (const CTstVersion&) = delete; CTstVersion& operator = (CTstVersion&&) = delete;
		CVersion m_ver;
	};

}}

#endif/*_TEST_CASE_$D$_VER_H_INCLUDED*/