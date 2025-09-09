#ifndef _GL_FORMAT_H_INCLUDED
#define _GL_FORMAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 12:55:04.373, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' format wrapper interface declaration file; 
*/
#include <vector>
#include "gl_defs.h"
#include "shared.dbg.h"

namespace ex_ui { namespace draw { namespace open_gl {

	// https://agrawalsuneet.github.io/blogs/enum-vs-enum-class-in-c++/ ;
	// https://learn.microsoft.com/en-us/cpp/cpp/enumerations-cpp ;

namespace format {

#define _gl_false uint32_t(0)
#define _gl_true  uint32_t(1)

	class CAtt {
	public:
		 CAtt (const uint32_t _u_key = 0, const uint32_t _u_value = 0, _pc_sz _p_name = nullptr); // the att key it is its some sort of 'name';
		 CAtt (const CAtt&);
		 CAtt (CAtt&&);
		~CAtt (void) = default;

	public:
		uint32_t Key (void) const;
		bool     Key (const uint32_t);   // returns 'true' in case of key change;

		uint32_t Value (void) const;
		bool     Value (const uint32_t); // returns 'true' in case of value change;

		CString  Print (const e_print = e_print::e_all) const;

		_pc_sz   Name  (void) const;
		bool     Name  (_pc_sz) ;        // returns 'true' in case of name is changed;

	public:
		CAtt& operator = (const CAtt&) ;
		CAtt& operator = (CAtt&&) ;

		CAtt& operator <<(const uint32_t _u_value);
		CAtt& operator >>(const uint32_t _u_key);
		CAtt& operator <<(_pc_sz _p_name);

	private:
		uint32_t m_key;
		uint32_t m_val;
		CString  m_name;
	};

	typedef ::std::vector<CAtt> TAtts;
	typedef ::std::vector<int>  TRawAtts_Int; // excerpt from the article: ...piAttribIList is a list of integer attributes. Every two elements in the list is an attribute/value pair... zero (0) ends up the list;
	typedef ::std::vector<float>  TRawAtts_Flt; // excerpt from the article: ...need to static-cast int to float or do other trickery to make C keep the bit-pattern between the integer and float form the same ;

namespace arb {

	// https://www.allacronyms.com/accel./Acceleration ;
	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	class CAccel : private no_copy {
	public:
		enum e_tokens : uint16_t {
		e_full = 0x2027, // WGL_FULL_ACCELERATION_ARB ; the pixel format is supported by an ICD driver ;
		e_none = 0x2025, // WGL_NO_ACCELERATION_ARB ; only the software renderer supports this pixel format;
		e_norm = 0x2026, // WGL_GENERIC_ACCELERATION_ARB ; the pixel format is supported by an MCD driver;
		e_supp = 0x2003, // WGL_ACCELERATION_ARB ; Indicates whether the pixel format is supported by the driver.
		};

		static CString To_str (const e_tokens);
	};

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	class CBuffer : private no_copy {
	public:
		enum e_tokens : uint16_t {
		e_double = 0x2011, // WGL_DOUBLE_BUFFER_ARB ; att name: att value is 'true' if the color buffer has back/front pairs;
		e_stereo = 0x2012, // WGL_STEREO_ARB ; att name: att value is 'true' if the color buffer has left/right pairs;
		};

		static CString To_str (const e_tokens);
	};
	
	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	class CColor : private no_copy {
	public:
		enum e_tokens : uint16_t {
		e_alpha = 0x201B, // WGL_ALPHA_BITS_ARB ; The number of alpha bitplanes in each RGBA color buffer.
		e_color = 0x2014, // WGL_COLOR_BITS_ARB ; The number of color bitplanes in each color buffer. For RGBA pixel types, it is the size of the color buffer, excluding the alpha bitplanes.
		e_depth = 0x2022, // WGL_DEPTH_BITS_ARB ; The depth of the depth (z-axis) buffer.
		};

		static CString To_str (const e_tokens);
	};

	// https://www.allacronyms.com/compatibility/abbreviated ;
	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
	class CContext : private no_copy {
	public:
		// WGL_CONTEXT_FLAGS ;
		enum e_tokens : uint16_t {
		     e_flags   = 0x2094, // WGL_CONTEXT_FLAGS_ARB ; this is the att token; the acceptable tokens for getting values are listed below;
		};

		static CString To_str (const e_tokens);

		class CDebug : private no_copy {
		public:
			enum e_tokens : uint16_t {
			e_debug   = 0x0001, // WGL_CONTEXT_DEBUG_BIT_ARB ; att value: a high-level description of the concept of "debug contexts";
			e_forward = 0x0002, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB ; att value: a <forward-compatible> context will be created;
			};

			static CString To_str (const e_tokens);
		};

		class CProfile : private no_copy {
		public:
			enum e_tokens : uint16_t {
			// *important*: it is 4 bytes data type number, but it looks like no cast is required;
			e_core = 0x0001, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB ; att value: if 'true' a context supports the <core> profile of OpenGL;
			e_comp = 0x0002, // WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ; att value: a context implements the <compatibility> profile;
			e_mask = 0x9126, // WGL_CONTEXT_PROFILE_MASK_ARB ; for requests an OpenGL context a specific <profile> of the API support;
			};

			static CString To_str (const e_tokens);
		};

		class CVersion : private no_copy {
		public:
			enum e_tokens : uint16_t {
			e_major = 0x2091, // WGL_CONTEXT_MAJOR_VERSION_ARB ; att value: the actual major number of the version supported by a context;
			e_minor = 0x2092, // WGL_CONTEXT_MINOR_VERSION_ARB ; att value: the actual minor number of the version supported by a context;
			};

			static CString To_str (const e_tokens);
		};
	};

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	class CDraw : private no_copy {
	public:
		enum e_tokens : uint16_t {
		e_bitmap  = 0x2002, // WGL_DRAW_TO_BITMAP_ARB ; True if the pixel format can be used with a memory bitmap. The <iLayerPlane> parameter is ignored if this attribute is specified.
		e_window  = 0x2001, // WGL_DRAW_TO_WINDOW_ARB ; True if the pixel format can be used with a window. The <iLayerPlane> parameter is ignored if this attribute is specified.
		e_formats = 0x2000, // WGL_NUMBER_PIXEL_FORMATS_ARB ; The number of pixel formats for the device context. The <iLayerPlane> and <iPixelFormat> parameters are ignored if this attribute is specified.
		};

		static CString To_str (const e_tokens);
	};

	// https://registry.khronos.org/OpenGL/extensions/ARB/ARB_multisample.txt ;
	class CSample : private no_copy {
	public:
		enum e_tokens : uint16_t {
		e_multi = 0x2041, // WGL_SAMPLE_BUFFERS_ARB ; it returns the number of multisample buffers included in the pixel format: 0 - normal, 1 - one multisample buffer;
		e_count = 0x2042, // WGL_SAMPLES_ARB ; the number of samples per pixel; if WGL_SAMPLE_BUFFERS_ARB is zero, it is also zero;
		};

		static CString To_str (const e_tokens);
	};

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	class CSupport : private no_copy {
	public:
		enum e_tokens : uint16_t {
		e_gdi    = 0x200F, // WGL_SUPPORT_GDI_ARB ; 'true' if GDI rendering is supported;
		e_opengl = 0x2010, // WGL_SUPPORT_OPENGL_ARB ; 'true' if OpenGL is supported; *important*: it must be passed on choosing color format for context creation;
		};

		static CString To_str (const e_tokens);
	};

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	class CSwap : private no_copy {
	public:
		enum e_tokens : uint16_t {
		     e_copy     = 0x2029, // WGL_SWAP_COPY_ARB ; the swapping copies the back buffer contents to the front buffer;
		     e_exchange = 0x2028, // WGL_SWAP_EXCHANGE_ARB ; the swapping exchanges the front and back buffer contents;
			 e_layers   = 0x2006, // WGL_SWAP_LAYER_BUFFERS_ARB ; 'True' if the pixel format supports swapping layer planes independently of the main planes. If the pixel format does not support a back buffer then this is set to 'False'.
		     e_method   = 0x2007, // WGL_SWAP_METHOD_ARB ; If the pixel format supports a back buffer, then this indicates how they are swapped.
		     e_undef    = 0x202A, // WGL_SWAP_UNDEFINED_ARB ; the pixel format does not support a back buffer;
		};

		static CString To_str (const e_tokens);
	};

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	class CType : private no_copy {
	public:
		enum e_tokens : uint16_t {
		e_pixel =  0x2013, // WGL_PIXEL_TYPE_ARB ; att name of the type of pixel data;
		e_rgba  =  0x202B, // WGL_TYPE_RGBA_ARB ; att value;
		e_index =  0x202C, // WGL_TYPE_COLORINDEX_ARB ; att value;
		};

		static CString To_str (const e_tokens);
	};
}

	interface IAtt_Set_Base {
		virtual const float* const IAtt_Get_Flt_Ptr (void) const { return (float*)nullptr; }
		virtual const int* const IAtt_Get_Int_Ptr (void) const { return (int*)nullptr; }
	};

	class CAtt_set_base : public IAtt_Set_Base, private no_copy {
	protected:
		 CAtt_set_base (void);
		~CAtt_set_base (void) = default;

	public:
		const float* const IAtt_Get_Flt_Ptr (void) const override;
		const int* const IAtt_Get_Int_Ptr (void) const override;

	public:
		err_code Append (const CAtt&); //  no check for attributes duplication; adds the input attribute to the internal cache;
		err_code Append (const uint32_t _u_key, uint32_t _u_val, _pc_sz _p_name);

		CString  Print  (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t"), _pc_sz _p_sfx = _T("\n")) const;

	public:
		CAtt_set_base& operator += (const CAtt&);

	protected:
		TAtts   m_atts;
		mutable TRawAtts_Int m_raw_int; // this vector must have the last element as (int)0;
		mutable TRawAtts_Flt m_raw_flt; // this vector must have the last element as (float)0.0;
	};

	class CAtt_set_ctx : public CAtt_set_base { typedef CAtt_set_base TBase;
	public:
		CAtt_set_ctx (const uint32_t _u_major = 1, const uint32_t _u_minor = 1) ; // creates the set;
	};

	// this is minimal attribute set which is required for creating OpenGL render context;
	// *important*: arb::CSupport::e_opengl is required for being included, otherwise 'wglChoosePixelFormatARB' fails;
	class CAtt_set_pixels : public CAtt_set_base { typedef CAtt_set_base TBase;
	public:
		CAtt_set_pixels (void) ; // creates the set;
	};
}
}}}
#endif/*_GL_FORMAT_H_INCLUDED*/