#ifndef _GL_PX_FORMAT_ARB_H_INCLUDED
#define _GL_PX_FORMAT_ARB_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 12:55:04.373, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' format wrapper interface declaration file; 
*/
#include "gl_px_format.h"
#include "gl_px_format_att.h"

namespace open_gl { namespace arb { using namespace shared::defs;

	// this class is to initialize a pixel format descriptor for ARB extension, and it uses win_api::CFormat class for setting required pixel format to GDI first;
	class CPxFormat {
	public:
		CPxFormat (void);
		CPxFormat (const CPxFormat&) = delete; CPxFormat (CPxFormat&&) = delete; ~CPxFormat (void) = default;

		TError&  Error (void) const;
		err_code Find  (const format::s_bits_ex& _bits); // finds by input params the required format descriptor supported by OpenGL ARB extension;

		CPxFormat& operator <<(const HDC&); // sets device context for setting its pixel format;

	private:
		CPxFormat& operator = (const CPxFormat&) = delete; CPxFormat& operator = (CPxFormat&&) = delete;
		CError   m_error;
		HDC      m_hdc;    // target device context is for manipulating its pixel format;
	};

}}

#endif/*_GL_FORMAT_H_INCLUDED*/