#ifndef _OPEN_GL_TUTOR_0_FAKE_H_INCLUDED
#define _OPEN_GL_TUTOR_0_FAKE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 11:16:27.485, UTC+4, Batumi, Monday;
	This is OpenGL tutorial of the creating fake content interface declaration file;
*/
#include "open_gl_tutor.0.module.h"

namespace ex_ui { namespace draw { namespace open_gl {  namespace fake {

	class CWnd : public ::ATL::CWindowImpl<CWnd> { typedef ::ATL::CWindowImpl<CWnd> TWindow;
	public:
		 CWnd (void); CWnd (const CWnd&) = delete; CWnd (CWnd&&) = delete;
		~CWnd (void);

		 static
		 const uint32_t u_style = CS_DBLCLKS | CS_OWNDC; // cs_owndc is important for creating open_gl window content;

		 DECLARE_WND_CLASS_EX(_T("open_gl::fake::CWnd"), u_style, COLOR_ACTIVECAPTION);
		 DECLARE_EMPTY_MSG_MAP();

		 TError& Error (void) const;
		 bool    Is_valid (void) const;

		 const
		 HDC&    Get_ctx  (void) const; // gets the reference to device context; read-only;
		 const
		 HGLRC&  Renderer (void) const;

		 operator const HDC& (void) const;

	private:
		 CWnd& operator = (const CWnd&) = delete; CWnd& operator = (CWnd&&) = delete;

		 mutable
		 CError  m_error;
		 HDC     m_h_dc ;
		 HGLRC   m_h_render; // the render context;
	};
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
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all, const bool _b_trace = true) const;
#endif
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
		 const
		 CVer_Att& GetAtt(const e_atts) const; // if input attribute value is out of enum range, the reference to fake object is returned;
#if defined(_DEBUG)
		 CString   Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t"), _pc_sz _p_sfx = _T("\n"), const bool _b_trace = true) const;
#endif
	private:
		 CVersion& operator = (const CVersion&) = delete; CVersion& operator = (CVersion&&) = delete;

	private:
		 CError    m_error;
		 CVer_Att  m_atts[CVersion::n_atts_count];
	};

}}}}

#endif/*_OPEN_GL_TUTOR_0_FAKE_H_INCLUDED*/