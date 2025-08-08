#ifndef _DIRECT_X_VIEW_H_INCLUDED
#define _DIRECT_X_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 2-May-2025 at 00:59:34.953, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX generic view interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.format.h"           // this is what that defines a color format;
#include "direct_x.texture.h"          // this is what that is draw surface;
#include "device\direct_x.device.1.h"  // this is what that creates a view;

namespace ex_ui { namespace draw { namespace direct_x { namespace views {

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_viewport ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi#handling-window-resizing ;
	typedef D3D11_VIEWPORT TViewPort;
	/*
		for example, resolution is set to 800x600px, that will be abstracted as shown below:
		-1|-1__________+1|-1
		  |              |
		  |      0|0     |
		-1|+1__________+1|+1
	*/
	class CViewPort {
	public:
		 CViewPort (void); CViewPort (const CViewPort&) = delete; CViewPort (CViewPort&&) = delete;
		~CViewPort (void) {}

	public:
	#if defined(_DEBUG)
		static
		CString  Print (const TViewPort&, const e_print);
		CString  Print (const e_print);
	#endif
		const
		TViewPort& Raw (void) const;
		TViewPort& Raw (void) ;

		err_code   SetSize(HWND const _target);

	private:
		CViewPort& operator = (const CViewPort&) = delete;
		CViewPort& operator = (CViewPort&&) = delete;

	private:
		TViewPort m_port;
	};

namespace _11 {

	using namespace ex_ui::draw::direct_x;
	using namespace ex_ui::draw::direct_x::views;

	using CDevice  = ex_ui::draw::direct_x::_11::CDevice;
	using CTexture = ex_ui::draw::direct_x::_11::_2D::CTexture;

	
	typedef ::ATL::CComPtr<ID3D11Resource> TResPtr ; // https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11resource ;
	typedef ::ATL::CComPtr<ID3D11View>     TViewPtr; // https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11view ;
	
	class CView {
	public:
		 CView (void); CView (const CView&) = delete; CView (CView&&) = delete;
		~CView (void) = default;

	public:
		TError&  Error (void) const;
		bool  Is_valid (void) const;

		err_code  Get  (TResPtr&) const;    // gets resource pointer which the view is based on;
		err_code  Set  (const CDevice&);    // does care in case when a device is already cached;
		err_code  Set  (const CTexture&);   // does care in case when a texture is already cached;

		const
		TViewPtr& View (void) const;        // returns the pointer to base interface of all views;
		err_code  View (const TViewPtr&);   // sets view base interface pointer;

	private:
		CView&  operator = (const CView&) = delete;
		CView&  operator = (CView&&) = delete;

	protected:
		mutable
		CError   m_error  ;
		TViewPtr m_p_view ;
		CDevice  m_device ;  // cached device object;
		CTexture m_texture;  // cached texture object;
	};
}

}}}}

#endif/*_DIRECT_X_VIEW_H_INCLUDED*/