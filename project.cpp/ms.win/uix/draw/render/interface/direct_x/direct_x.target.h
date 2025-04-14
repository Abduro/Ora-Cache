#ifndef _DIRECT_X_TARGET_H_INCLUDED
#define _DIRECT_X_TARGET_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Apr-2025 at 18:26:29.828, UTC+4, Batumi, Saturday;
	This is Ebo Pack DirectX renderer target view wrapper interface declaration file; 
*/
#include "direct_x._iface.h"
#include "direct_x.device.1.h"
#include "direct_x.swap.1.h"
#include "direct_x.swap.2.h"

namespace ex_ui { namespace draw { namespace direct_x {

namespace _11 {
	using namespace ex_ui::draw::direct_x;
	using ex_ui::draw::direct_x::_11::CDevice;
	using ex_ui::draw::direct_x::_11::CSwapChain;

	typedef ::ATL::CComPtr<IDXGIOutput> TOutputPtr;

	class COutput {
	public:
		 COutput (void); COutput (const COutput&) = delete; COutput (COutput&&) = delete;
		~COutput (void) = default;
	public:
		TError&   Error (void) const;
		bool   Is_valid (void) const;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TOutputPtr& Ptr (void) const;
		err_code    Ptr (const TOutputPtr&);

	private:
		COutput&  operator = (const COutput&) = delete;
		COutput&  operator = (COutput&&) = delete;

	private:
		CError  m_error;
		TOutputPtr  m_p_out;
	};

	// this is a render target for drawing;
	class CTarget {
	public:
		 CTarget (void) ; CTarget (const CTarget&) = delete; CTarget (CTarget&&) = delete;
		~CTarget (void) = default;

	public:
		// https://learn.microsoft.com/en-us/windows/win32/direct3dgetstarted/work-with-dxgi#create-a-render-target-for-drawing ;
		err_code  Create(void) ;
		TError&   Error (void) const;
		bool   Is_valid (void) const;

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		err_code  Set (const CDevice&);     // does care in case when a device is already cached;
		err_code  Set (const CSwapChain&);  // does care in case when a swap chain is already cached;

	public:
		CTarget&  operator <<(const CDevice&);
		CTarget&  operator <<(const CSwapChain&);

	private:
		CTarget&  operator = (const CTarget&) = delete;
		CTarget&  operator = (CTarget&&) = delete;

	private:
		CError     m_error;
		CDevice    m_device; // cached device object;
		CSwapChain m_swap;   // cached swap chain object;
	};

}
namespace _12 {}

}}}

#endif/*_DIRECT_X_TARGET_H_INCLUDED*/