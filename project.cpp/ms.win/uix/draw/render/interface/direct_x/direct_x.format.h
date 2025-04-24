#ifndef _DIRECT_X_FORMAT_H_INCLUDED
#define _DIRECT_X_FORMAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Apr-2025 at 15:59:06.100, UTC+4, Batumi, Tuesday;
	This is Ebo pack DirectX data format base interface declaration file;
*/
#include "direct_x._iface.h"

namespace ex_ui { namespace draw { namespace direct_x {

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dcommon/ns-dcommon-d2d1_pixel_format ; << D2D1_PIXEL_FORMAT struct;

	typedef DXGI_FORMAT TClrBits;        // how to format color channels;
	typedef D2D1_PIXEL_FORMAT TPxFormat; // includes color channel layout and alpha value acceptance;
	// the color bits' enumeration represents only those bits' formats which are used in this project;
	class CClrBits {
	public:
		enum e_clr_bits : uint32_t {
		     e__unknown  = TClrBits::DXGI_FORMAT_UNKNOWN       , // is not acceptable actually;
		     e_rgba_norm = TClrBits::DXGI_FORMAT_R8G8B8A8_UNORM, // the commonly used format; very often;
			 e_bgra_norm = TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM,
		};
	public:
		 CClrBits (void); CClrBits (const CClrBits&) = delete; CClrBits (CClrBits&&) = delete;
		~CClrBits (void) = default;

	public:
		// https://lomont.org/posts/2023/accuratecolorconversions/ ; thanks Chris Lomont for good and clear article ;
		static constexpr float U8ToF32(const uint8_t _u_value);
		static constexpr uint8_t F32ToU8(const float _f_value);

		static ::std::vector<float> rgba_to_float (const dword _clr);
		static dword float_to_rgba (const ::std::vector<float>& _clr);

#if defined(_DEBUG)
		CString    Print (const uint32_t _n_format) const;
#endif
	private:
		CClrBits&  operator = (const CClrBits&) = delete;
		CClrBits&  operator = (CClrBits&&) = delete;
	};
namespace _11 {
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_format_support ;

	typedef D3D11_FORMAT_SUPPORT TResFormat;

	class CResFormat {
	public:
		enum e_buffer : uint32_t {
		e_back_cast  = TResFormat::D3D11_FORMAT_SUPPORT_BACK_BUFFER_CAST, //
		e_buffer_nm  = TResFormat::D3D11_FORMAT_SUPPORT_BUFFER          , // buffer resources supported;
		e_buffer_so  = TResFormat::D3D11_FORMAT_SUPPORT_SO_BUFFER       , // streaming output buffers supported;
		e_ia_index   = TResFormat::D3D11_FORMAT_SUPPORT_IA_INDEX_BUFFER , // index buffers supported;
		e_ia_vertex  = TResFormat::D3D11_FORMAT_SUPPORT_IA_VERTEX_BUFFER, // vertex buffers supported;
		};

		enum e_mip : uint32_t {
		e_auto = D3D11_FORMAT_SUPPORT_MIP_AUTOGEN, //
		e_maps = D3D11_FORMAT_SUPPORT_MIP,         //
		};

		enum e_multismp : uint32_t {
		e_loaded  = TResFormat::D3D11_FORMAT_SUPPORT_MULTISAMPLE_LOAD        , //
		e_render  = TResFormat::D3D11_FORMAT_SUPPORT_MULTISAMPLE_RENDERTARGET, //
		e_resolve = TResFormat::D3D11_FORMAT_SUPPORT_MULTISAMPLE_RESOLVE     , //
		};

		enum e_shader : uint32_t {
		e_gather     = TResFormat::D3D11_FORMAT_SUPPORT_SHADER_GATHER           , // format can be used with the HLSL gather function;
		e_gather_cmp = TResFormat::D3D11_FORMAT_SUPPORT_SHADER_GATHER_COMPARISON, // format can be used with the HLSL gather function and comparison;
		e_load       = TResFormat::D3D11_FORMAT_SUPPORT_SHADER_LOAD             , //
		e_sample     = TResFormat::D3D11_FORMAT_SUPPORT_SHADER_SAMPLE           , //
		e_sample_cmp = TResFormat::D3D11_FORMAT_SUPPORT_SHADER_SAMPLE_COMPARISON, //
		e_mono_rext  = TResFormat::D3D11_FORMAT_SUPPORT_SHADER_SAMPLE_MONO_TEXT , //
		};

		enum e_texture : uint32_t {
		e_1d   = TResFormat::D3D11_FORMAT_SUPPORT_TEXTURE1D  , //
		e_2d   = TResFormat::D3D11_FORMAT_SUPPORT_TEXTURE2D  , //
		e_3d   = TResFormat::D3D11_FORMAT_SUPPORT_TEXTURE3D  , //
		e_cube = TResFormat::D3D11_FORMAT_SUPPORT_TEXTURECUBE, //
		};

		enum e_video : uint32_t {
		e_encoder   = TResFormat::D3D11_FORMAT_SUPPORT_VIDEO_ENCODER         , //
		e_proc_in   = TResFormat::D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_OUTPUT, //
		e_proc_out  = TResFormat::D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_INPUT , //
		};
	public:
		 CResFormat (void); CResFormat (const CResFormat&) = delete; CResFormat (CResFormat&&) = delete;
		~CResFormat (void) = default;

	public:
#if defined(_DEBUG)
		CString   Print (const uint32_t _n_flags, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	private:
		CResFormat& operator = (const CResFormat&) = delete;
		CResFormat& operator = (CResFormat&&) = delete;
	};
}
namespace _12 {
	// https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-enumerations ;
	typedef D3D12_FORMAT_SUPPORT1 TResFormat1; // https://learn.microsoft.com/en-us/windows/win32/api/d3d12/ne-d3d12-d3d12_format_support1 ;
	typedef D3D12_FORMAT_SUPPORT2 TResFormat2; // https://learn.microsoft.com/en-us/windows/win32/api/d3d12/ne-d3d12-d3d12_format_support2 ;
}
}}}

#endif/*_DIRECT_X_FORMAT_H_INCLUDED*/