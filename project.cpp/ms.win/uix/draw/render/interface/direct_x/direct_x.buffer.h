#ifndef _DIRECT_X_BUFFER_H_INCLUDED
#define _DIRECT_X_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2025 at 23:15:10.740, UTC+4, Batumi, Saturday;
	This is Ebo Pack DirectX device context buffers' wrapper interface declaration file; 
*/
#include "direct_x._iface.h"
#include "direct_x.res.flag.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace buffers {
	/*
	// https://www.abbreviations.com/abbreviation/buffer ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-resources-buffers-intro :
		Vertex Buffer;
		Index Buffer ;
		Constant Buffer;
	*/
namespace _11 {

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11buffer ;
	typedef ::ATL::CComPtr<ID3D11Buffer> TBufferPtr;
	/*
		There are three types of buffers: vertex, index, or a shader-constant buffer,
		which can be created by calling ID3D11Device::CreateBuffer();
	*/
}
namespace _12 {
	using namespace ex_ui::draw::direct_x;
}

}}}}

#endif/*_DIRECT_X_BUFFER_H_INCLUDED*/