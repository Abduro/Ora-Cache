#ifndef _DIRECT_X_BUF_VERTEX_H_INCLUDED
#define _DIRECT_X_BUF_VERTEX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-May-2025 at 05:40:20.887, UTC+4, Batumi, Saturday;
	This is Ebo Pack DirectX device context vertex buffer wrapper interface declaration file; 
*/
#include "direct_x.buffer.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace buffers {
namespace _11 {
	// https://en.wikipedia.org/wiki/Vertex_(graph_theory) ;
	using namespace ex_ui::draw::direct_x;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11buffer-getdesc ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_buffer_desc ;
	typedef D3D11_BUFFER_DESC TVtxDesc;

	class CVtxDesc {
	public:
		 CVtxDesc (void) ; CVtxDesc (const CVtxDesc&) = delete; CVtxDesc (CVtxDesc&&) = delete;
		~CVtxDesc (void) = default;

	public:
#if defined(_DEBUG)
		static
		CString   Print (const TVtxDesc&, const e_print = e_print::e_all);
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TVtxDesc& Raw (void) const;
		TVtxDesc& Raw (void) ;

	private:
		CVtxDesc& operator = (const CVtxDesc&) = delete;
		CVtxDesc& operator = (CVtxDesc&&) = delete;

	private:
		TVtxDesc  m_desc;
	};
	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-resources-buffers-vertex-how-to ;
	class CVertex {
	public:
		 CVertex (void); CVertex (const CVertex&) = delete; CVertex (CVertex&&) = delete;
		~CVertex (void) = default;

	public:
		const
		CVtxDesc& Desc (void) const;
		CVtxDesc& Desc (void) ;

		TError&  Error (void) const;
		bool     Is_valid (void) const;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		const
		TBufferPtr&  Ptr (void) const;
		err_code Ptr (const TBufferPtr&); // when the pointer is set, the vertex buffer description is updated;

	private:
		CVertex& operator = (const CVertex&) = delete;
		CVertex& operator = (CVertex&&) = delete;
	private:
		CError     m_error;
		TBufferPtr m_p_buf;
		CVtxDesc   m_desc ;
	};
}
namespace _12 {
	using namespace ex_ui::draw::direct_x;
}

}}}}

#endif/*_DIRECT_X_BUF_VERTEX_H_INCLUDED*/