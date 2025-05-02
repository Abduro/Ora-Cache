#ifndef _DIRECT_X_RES_FLAG_H_INCLUDED
#define _DIRECT_X_RES_FLAG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2025 at 11:39:59.352, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX resource flag enums wrapper interface declaration file;
*/
#include "direct_x._iface.h"

namespace ex_ui { namespace draw { namespace direct_x {

namespace _11 { using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_bind_flag ;
	typedef D3D11_BIND_FLAG TBindFlag; // identifies how to bind a resource to the pipeline;

	class CBind {
	public:
		enum ToCoders : uint32_t {
		     e_decoder = D3D11_BIND_DECODER         , // used to set receiving output from the decoder;
		     e_encoder = D3D11_BIND_VIDEO_ENCODER   , // used to set receiving input from the video encoder;
		};
		enum ToBuffer : uint32_t {
		     e_const   = D3D11_BIND_CONSTANT_BUFFER , // binds a buffer as a constant buffer to a shader stage; is not be combined with others;
		     e_index   = D3D11_BIND_INDEX_BUFFER    , // binds a buffer as an index buffer to the input-assembler stage;
		     e_vertex  = D3D11_BIND_VERTEX_BUFFER   , // binds a buffer as a vertex buffer to the input-assembler stage;
		};
		enum ToMerger : uint32_t {
		     e_stencil = D3D11_BIND_DEPTH_STENCIL   , // binds a texture as a depth-stencil target for the output-merger stage;
		     e_target  = D3D11_BIND_RENDER_TARGET   , // binds a texture as a render target for the output-merger stage;
		};
		enum ToStage : uint32_t {
		     e_shader  = D3D11_BIND_SHADER_RESOURCE , // binds a buffer or texture to a shader stage; this flag cannot be used with the overwrite;
		     e_stream  = D3D11_BIND_STREAM_OUTPUT   , // binds an output buffer for the stream-output stage;
		};
	public:
		enum e_flag : uint32_t { // just playing with names, creating  shortcuts or aliases, doesn't matter;
		     e_access  = D3D11_BIND_UNORDERED_ACCESS, // binds an unordered access resource;
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

#define AccessGuarded  D3D11_RESOURCE_MISC_GUARDED
#define AccessProtect  D3D11_RESOURCE_MISC_HW_PROTECTED

		enum ToAccess : uint32_t {
		     e_guarded = TMiscFlag::AccessGuarded     , // indicates that the resource is guarded;
		     e_protect = TMiscFlag::AccessProtect     , // indicates that the resource is protected by the hardware;
		};

#define BufferAsView   D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS
#define BufferAsStruct D3D11_RESOURCE_MISC_BUFFER_STRUCTURED

		enum ToBuffer : uint32_t {
		     e_view   = TMiscFlag::BufferAsView       , // enables a resource as a byte address buffer;
		     e_struct = TMiscFlag::BufferAsStruct     , // enables a resource as a structured buffer;
		};

#define DrawInderect   D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS
#define DrawCompatible D3D11_RESOURCE_MISC_GDI_COMPATIBLE
#define DrawGenMips    D3D11_RESOURCE_MISC_GENERATE_MIPS
#define DrawClampRes   D3D11_RESOURCE_MISC_RESOURCE_CLAMP
#define DrawTexCube    D3D11_RESOURCE_MISC_TEXTURECUBE

		enum ToDraw : uint32_t {
		     e_inderect  = TMiscFlag::DrawInderect    , // enables instancing of GPU-generated content;
		     e_gdi_comp  = TMiscFlag::DrawCompatible  , // enables a resource compatible with GDI;
		     e_gen_mips  = TMiscFlag::DrawGenMips     , // enables MIP map generation;
		     e_res_clamp = TMiscFlag::DrawClampRes    , // enables a resource with MIP map clamping for use with;
		     e_tex_cude  = TMiscFlag::DrawTexCube     , // sets a cube texture created from a Texture2DArray() that contains 6 textures;
		};

#define RestrictContent   D3D11_RESOURCE_MISC_RESTRICTED_CONTENT
#define RestrictSharedDrv D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER
#define RestrictSharedRes D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE

		enum ToRestrict : uint32_t {
		     e_content  = TMiscFlag::RestrictContent  , // indicates that the resource might contain protected content;
		     e_driver   = TMiscFlag::RestrictSharedDrv, // the driver restricts access to the shared surface;
		     e_resource = TMiscFlag::RestrictSharedRes, // the operating system restricts access to the shared surface;
		};

#define ShareDevice  D3D11_RESOURCE_MISC_SHARED
#define ShareMutex   D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX
#define ShareHandle  D3D11_RESOURCE_MISC_SHARED_NTHANDLE

		enum ToShare : uint32_t {
		     e_device   = TMiscFlag::ShareDevice      , // enables resource data sharing between devices;
		     e_mutex    = TMiscFlag::ShareMutex       , // enables the resource to be synchronized;
		     e_handle   = TMiscFlag::ShareHandle      , // enables the use of NT HANDLE values for creating a shared resource;
		};

#define TilePool  D3D11_RESOURCE_MISC_TILE_POOL
#define TileMade  D3D11_RESOURCE_MISC_TILED

		enum ToTile : uint32_t {
		     e_pool = TMiscFlag::TilePool             , // indicates the resource is a tile pool;
		     e_made = TMiscFlag::TileMade             , // indicates the resource is tiled;
		};

	public:
		 CMiscFlags (void) = default; CMiscFlags (const CMiscFlags&) = delete; CMiscFlags (CMiscFlags&&) = delete;
		~CMiscFlags (void) = default;

	public:
#if defined(_DEBUG)
		static
		CString   Print (const uint32_t _n_flags, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n"));
#endif

	private:
		CMiscFlags&  operator = (const CMiscFlags&) = delete;
		CMiscFlags&  operator = (CMiscFlags&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_usage ;
	typedef D3D11_USAGE TResUsage;

	class CResUsage {
	public:
		 CResUsage (void) = default; CResUsage (const CResUsage&) = delete; CResUsage (CResUsage&&) = delete;
		~CResUsage (void) = default;

	public:
#if defined(_DEBUG)
		static
		CString   Print (const uint32_t _n_usage);
#endif
	private:
		CResUsage& operator = (const CResUsage&) = delete;
		CResUsage& operator = (CResUsage&&) = delete;
	};
}
namespace _12 { using namespace ex_ui::draw::direct_x;
}

}}}

#endif/*_DIRECT_X_RES_FLAG_H_INCLUDED*/