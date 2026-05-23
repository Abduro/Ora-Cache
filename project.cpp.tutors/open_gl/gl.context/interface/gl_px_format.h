#ifndef _GL_PX_FORMAT_H_INCLUDED
#define _GL_PX_FORMAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 12:55:04.373, UTC+4, Batumi, Saturday;
	This is OpenGL WinAPI pixel format wrapper interface declaration file; 
*/
#include "gl_ctx_base.h"

// it very looks like this pixel format wrapper should be moved to shared project for using by OpenGL and DirectX;
namespace win_api { using namespace shared::defs;
namespace format {

	struct s_bits {
		uint16_t m_u_clr, m_u_depth, m_u_stencil;
		s_bits (const uint16_t _u_clr = 0, const uint16_t _u_depth = 0, const uint16_t _u_stencil = 0);
		bool Is_valid  (void) const;
		CString To_str (const e_print = e_print::e_all) const;
	};
	// https://en.wikipedia.org/wiki/Multisample_anti-aliasing ; (MSAA)
	struct s_bits_ex : public s_bits {
		uint16_t m_u_msaa;
		s_bits_ex (const uint16_t _u_clr = 0, const uint16_t _u_depth = 0, const uint16_t _u_stencil = 0, const uint16_t _u_msaa = 0);
		bool Is_valid  (void) const;
		CString To_str (const e_print = e_print::e_all) const;

		const
		s_bits& operator ()(void) const;
		s_bits& operator ()(void) ;
	};
}
	typedef PIXELFORMATDESCRIPTOR px_fmt_desc_t;

	class CPxFormat {
	public:
		CPxFormat (void);
		CPxFormat (const CPxFormat&); CPxFormat (CPxFormat&&) = delete; ~CPxFormat (void) = default;

		const
		px_fmt_desc_t& Get (void) const;
		err_code Set (void); // sets the found pixel format descriptor to the target device context;

		TError&  Error (void) const;
		err_code Find  (const format::s_bits& _bits, uint32_t& _found_ndx); // finds by input params the required pixel format descriptor supported by device context;
		err_code Find  (const format::s_bits_ex& _bits); // finds by input params the required format descriptor supported by OpenGL ARB extension;

		uint32_t Index (void) const; // returns the index of found pixel format descriptor structure;

		bool  Is_found (void) const; // checks the internal pixel format descriptor field for emptiness;
		bool  Is_valid (void) const; // checks the target context device handle;

		static
		CString  To_str (const px_fmt_desc_t&);

		CPxFormat& operator = (const CPxFormat&);
		CPxFormat& operator = (CPxFormat&&) = delete; // not required yet;

		CPxFormat& operator <<(const HDC&); // sets device context for getting/setting its pixel format;
	protected:
		CPxFormat& operator <<(const px_fmt_desc_t&);
		CPxFormat& operator <<(const uint32_t _u_index); // sets the found index;

	private:
		mutable
		CError   m_error;
		HDC      m_hdc;    // target device context is for manipulating its pixel format;
		uint32_t m_found;  // this is the found index of the pixel format descriptor, one-based, 0 - means it's not found yet;
		px_fmt_desc_t m_desc;
	};
}

#endif/*_GL_FORMAT_H_INCLUDED*/