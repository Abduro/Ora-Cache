#ifndef _DIRECT_X_TEXTURE_H_INCLUDED
#define _DIRECT_X_TEXTURE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Apr-2025 at 02:13:18.338, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX texture wrapper interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.format.h"
#include "direct_x.swap.h"

namespace ex_ui { namespace draw { namespace direct_x {

namespace _11 {
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_bind_flag ;
	typedef D3D11_BIND_FLAG TBindFlag; // identifies how to bind a resource to the pipeline;

	class CBind {
	public:
		enum ToCoders : uint32_t {
		e_decoder  = D3D11_BIND_DECODER         , // used to set receiving output from the decoder;
		e_encoder  = D3D11_BIND_VIDEO_ENCODER   , // used to set receiving input from the video encoder;
		};
		enum ToBuffer : uint32_t {
		e_const    = D3D11_BIND_CONSTANT_BUFFER , // binds a buffer as a constant buffer to a shader stage; is not be combined with others;
		e_index    = D3D11_BIND_INDEX_BUFFER    , // binds a buffer as an index buffer to the input-assembler stage;
		e_vertex   = D3D11_BIND_VERTEX_BUFFER   , // binds a buffer as a vertex buffer to the input-assembler stage;
		};
		enum ToMerger : uint32_t {
		e_stencil = D3D11_BIND_DEPTH_STENCIL    , // binds a texture as a depth-stencil target for the output-merger stage;
		e_target  = D3D11_BIND_RENDER_TARGET    , // binds a texture as a render target for the output-merger stage;
		};
		enum ToStage : uint32_t {
		e_shader  = D3D11_BIND_SHADER_RESOURCE  , // binds a buffer or texture to a shader stage; this flag cannot be used with the overwrite;
		e_stream  = D3D11_BIND_STREAM_OUTPUT    , // binds an output buffer for the stream-output stage;
		};
	public:
		enum e_flag : uint32_t { // just playing with names, creating  shortcuts or aliases, doesn't matter;
		e_access  = D3D11_BIND_UNORDERED_ACCESS , // binds an unordered access resource;
		e_unset   = 0x0,
		};
	public:
		 CBind (void) = default; CBind (const CBind&) = delete; CBind (CBind&&) = delete;
		~CBind (void) = default;

	public:
#if defined(_DEBUG)
	static
	CString Print(const uint32_t _n_flags, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n"));
#endif

	private:
		CBind& operator = (const CBind&) = delete;
		CBind& operator = (CBind&&) = delete;
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_resource_misc_flag ;
	typedef D3D11_RESOURCE_MISC_FLAG TMiscFlag;  // mostly concerns texture related resources;
	class CMiscFlags {
	public:
		enum ToAccess : uint32_t {
		e_guarded = TMiscFlag::D3D11_RESOURCE_MISC_GUARDED     , // indicates that the resource is guarded;
		e_protect = TMiscFlag::D3D11_RESOURCE_MISC_HW_PROTECTED, // indicates that the resource is protected by the hardware;
		};
		enum ToBuffer : uint32_t {
		e_view   = TMiscFlag::D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS, // enables a resource as a byte address buffer;
		e_struct = TMiscFlag::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED     , // enables a resource as a structured buffer;
		};
		enum ToDraw : uint32_t {
		e_inderect  = TMiscFlag::D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS, // enables instancing of GPU-generated content;
		e_gdi_comp  = TMiscFlag::D3D11_RESOURCE_MISC_GDI_COMPATIBLE   , // enables a resource compatible with GDI;
		e_gen_mips  = TMiscFlag::D3D11_RESOURCE_MISC_GENERATE_MIPS    , // enables MIP map generation;
		e_res_clamp = TMiscFlag::D3D11_RESOURCE_MISC_RESOURCE_CLAMP   , // enables a resource with MIP map clamping for use with;
		e_tex_cude  = TMiscFlag::D3D11_RESOURCE_MISC_TEXTURECUBE      , // sets a cube texture created from a Texture2DArray() that contains 6 textures;
		};
		enum ToRestrict : uint32_t {
		e_content  = TMiscFlag::D3D11_RESOURCE_MISC_RESTRICTED_CONTENT             , // indicates that the resource might contain protected content;
		e_driver   = TMiscFlag::D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER, // the driver restricts access to the shared surface;
		e_resource = TMiscFlag::D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE       , // the operating system restricts access to the shared surface;
		};
		enum ToShare : uint32_t {
		e_device   = TMiscFlag::D3D11_RESOURCE_MISC_SHARED            , // enables resource data sharing between devices;
	//	e_display  = TMiscFlag::D3D11_RESOURCE_MISC_SHARED_DISPLAYABLE, // enables the resource to work with the displayable surfaces;
	//	e_writer   = TMiscFlag::D3D11_RESOURCE_MISC_SHARED_EXCLUSIVE_WRITER,
		e_mutex    = TMiscFlag::D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX , // enables the resource to be synchronized;
		e_handle   = TMiscFlag::D3D11_RESOURCE_MISC_SHARED_NTHANDLE   , // enables the use of NT HANDLE values for creating a shared resource;
		};
		enum ToTile : uint32_t {
		e_pool = TMiscFlag::D3D11_RESOURCE_MISC_TILE_POOL, // indicates the resource is a tile pool;
		e_made = TMiscFlag::D3D11_RESOURCE_MISC_TILED    , // indicates the resource is tiled;
		};
	public:
		 CMiscFlags (void) = default; CMiscFlags (const CMiscFlags&) = delete; CMiscFlags (CMiscFlags&&) = delete;
		~CMiscFlags (void) = default;
	public:
#if defined(_DEBUG)
		CString   Print (const uint32_t _n_flags, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif

	private:
		CMiscFlags&  operator = (const CMiscFlags&) = delete;
		CMiscFlags&  operator = (CMiscFlags&&) = delete;
	};
}
namespace _11 { namespace _2D {

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_usage ;
	typedef D3D11_USAGE TTexUsage;

	class CTexUsage {
	public:
		 CTexUsage (void) = default; CTexUsage (const CTexUsage&) = delete; CTexUsage (CTexUsage&&) = delete;
		~CTexUsage (void) = default;

	public:
#if defined(_DEBUG)
		static
		CString   Print (const uint32_t _n_usage);
#endif

	private:
		CTexUsage& operator = (const CTexUsage&) = delete;
		CTexUsage& operator = (CTexUsage&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_texture2d_desc ;
	typedef D3D11_TEXTURE2D_DESC TTexDesc;

	class CTexDesc {
	public:
		 CTexDesc (void) = default; CTexDesc (const CTexDesc&) = delete;  CTexDesc (CTexDesc&&) = delete;
		~CTexDesc (void) = default;

	public:
#if defined (_DEBUG)
		static
		CString   Print (const TTexDesc& _raw);
#endif
	private:
		CTexDesc& operator = (const CTexDesc&) = delete;
		CTexDesc& operator = (CTexDesc&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11texture2d ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11texture2d-getdesc ;
	typedef ::ATL::CComPtr<ID3D11Texture2D> TTexPtr;

	class CTexture {
	public:
		 CTexture (void); CTexture (const CTexture&) = delete; CTexture (CTexture&&) = delete;
		~CTexture (void) = default;

	public:
		TError&  Error (void) const;
		bool  Is_valid (void) const;
#if defined (_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		const
		TTexPtr&  Ptr (void) const;
		err_code  Ptr (const TTexPtr&);

	private:
		CError    m_error;
		TTexPtr   m_p_tex;

	private:
		CTexture& operator = (const CTexture&) = delete;
		CTexture& operator = (CTexture&&) = delete;
	};

}}

namespace _12 {
}

}}}


#endif/*_DIRECT_X_TEXTURE_H_INCLUDED*/