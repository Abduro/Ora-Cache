#ifndef _TEST_CASE_$U$_VSYNC_H_INCLUDED
#define _TEST_CASE_$U$_VSYNC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Jun-2026 at 15:23:49.222, UTC+4, Batumi, Wednesday;
	This is OpenGL version 1.1 buffers' swap wrapper interface declaration file for using in test cases adapters;
*/
#include "test_adap_$p$.defs.h"
#include "utils\gl_procs_vsync.h"

namespace test { namespace open_gl { namespace utils { namespace ver_1_1 {

	using namespace ::open_gl::procs::ver_1_1;
	using namespace ::open_gl::procs::utils::ver_1_1;

	class CTstVSync {
	public:
		CTstVSync (const bool _b_verbose); CTstVSync (const CTstVSync&) = delete; CTstVSync (CTstVSync&&) = delete; ~CTstVSync (void) = default;

		err_code Get (int32_t& _intervals);
		err_code Set (const uint32_t _intervals);

		const
		CVSync& operator ()(void) const;
		CVSync& operator ()(void) ;

		CTstVSync& operator <<(const bool _verbose);

	private:
		CTstVSync& operator = (const CTstVSync&) = delete; CTstVSync& operator = (CTstVSync&&) = delete;
		CVSync m_vsync;
		bool m_verbose;
	};

}}}}

#endif/*_TEST_CASE_$U$_VSYNC_H_INCLUDED*/