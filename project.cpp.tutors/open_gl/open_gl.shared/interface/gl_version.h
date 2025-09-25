#ifndef _GL_VERSION_H_INCLUDED
#define _GL_VERSION_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Sep-2025 at 02:10:53.758, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL version wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_error.h"
#include "shared.dbg.h"

namespace ex_ui { namespace draw { namespace open_gl {

	// https://stackoverflow.com/questions/7909358/how-do-i-know-which-version-of-opengl-i-am-using ;

	class CVer_Att {
	public:
		CVer_Att (const uint32_t _n_id = 0, _pc_sz _p_name = _T("#undef"), _pc_sz _p_value = _T("#unset"));
		CVer_Att (const CVer_Att&); CVer_Att (CVer_Att&&); ~CVer_Att (void) = default;

		uint32_t Id (void) const;
		bool     Id (const uint32_t);

		_pc_sz Name (void) const;
		bool   Name (_pc_sz);

		_pc_sz Value(void) const;
		bool   Value(_pc_sz);

		CString  Print (const e_print = e_print::e_all, const bool _b_trace = true) const;

	public:
		CVer_Att& operator = (const CVer_Att&); CVer_Att& operator = (CVer_Att&&);
		CVer_Att& operator <<(const uint32_t _n_id);
		CVer_Att& operator <<(_pc_sz _p_name);
		CVer_Att& operator >>(_pc_sz _p_value);
		CVer_Att& operator >>(const char* _p_value); // used for assining the value returned by glGetString();

	private:
		uint32_t m_n_id;
		CString  m_name;
		CString  m_value;
	};

	/* important:
		the version can be checked in case when fake (based on regular GDI) or OpenGL draw renderer context is set current (by wglMakeCurrent);
		(1) for the 'fake' aka 'false' context the version number is always '1.1'; (possibly it is not correct assumption);
		(2) for the 'driver' context that is dependable on installed hardware driver of particular GPU vendor, the version is expected at least '3.1';
		otherwise,
		without setting the draw context to be current the version number is '#unset';

		it very looks like the above statement is not correct, but this one:
		(1) creating win32 device context and setting desirable pixel format to it; *fake* window is helpful for this case;
		(2) creating a draw renderer context of OpenGL that is compatible to win32 GDI; *mandatory*: making the context of that renderer to be current;
		(3) finally, getting the version of OpenGL loads dynamic link library of the video card vendor and full information is *received*;
	*/

	class CVersion {
	public:
		enum e_atts : uint32_t {
		e_undef   = 0x0, // no recognizable version attribute;
		e_render  = 0x1, // GL_RENDERER;
		e_shader  = 0x2, // GL_SHADING_LANGUAGE_VERSION ;
		e_vendor  = 0x3, // GL_VENDOR  ;
		e_version = 0x0, // GL_VERSION ;
		};
		static const uint32_t n_atts_count = e_atts::e_vendor + 1;

	public:
		 CVersion (void); CVersion (const CVersion&) = delete; CVersion (CVersion&&) = delete;
		~CVersion (void);

		 TError& Error (void) const;
		 CString   Get (void) const; // gets version info by using glGetIntegerv();

		 err_code  Get_ex (void);     // creates device context based on a fake window and after that receives all attribute values;

		 const
		 CVer_Att& GetAtt(const e_atts) const; // if input attribute value is out of enum range, the reference to fake object is returned;

		 int32_t   Major (void) const;
		 int32_t   Minor (void) const;

		 CString   Print  (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t"), _pc_sz _p_sfx = _T("\n"), const bool _b_trace = false) const;
		 CString   Print_2(const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t"), _pc_sz _p_sfx = _T("\n")) const; // uses the internal print template;

	private:
		 CVersion& operator = (const CVersion&) = delete; CVersion& operator = (CVersion&&) = delete;

	private:
		 CError    m_error;
		 CVer_Att  m_atts[CVersion::n_atts_count];
	};

}}}

#endif/*_GL_VERSION_H_INCLUDED*/