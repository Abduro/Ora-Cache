#ifndef _EBO_TEST_$D$_RENDER_1_H_INCLUDED
#define _EBO_TEST_$D$_RENDER_1_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 14:13:19.457, UTC+4, Batumi, Monday;
	This is Ebo Pack DirectX.11 draw renderer lib unit test interface declaration file;
*/
#include "ebo_test_$d$.render.h"
#include "ebo_test_$d$.render.impl.h"

namespace ebo { namespace boo { namespace test { namespace draw { namespace _11 {

	using namespace ebo::boo::test::draw;
	using namespace ebo::boo::test::_impl::_11;

	using TClrBits  = ex_ui::draw::direct_x::TClrBits;
	using TAdapter  = ex_ui::draw::direct_x::_11::CAdapter;
	using TAda_Warp = TAdapter;
	using TOutput   = ex_ui::draw::direct_x::_11::COutput;
	using TOutputs  = ex_ui::draw::direct_x::_11::TOutputs;

	__class(CAdapter) {
	public:
		 CAdapter (const bool _b_verb = false);
		~CAdapter (void) = default;

	public:
		TError&  Error (void) const;
		err_code Set (const TAdapter&);

	private:
		bool m_b_verb;
		TAdapter m_adapter;
		CError   m_error;
	};

	using TAdapters = ex_ui::draw::direct_x::_11::TAdapters;
	using TAdapter_enum = ex_ui::draw::direct_x::_11::CAdapter_Enum;

	__class(CAdapter_enum) {
	public:
		 CAdapter_enum (const bool _b_verb = false);
		~CAdapter_enum (void) = default;

	public:
		__method (Set);  // retrieves all adapters;

	private:
		bool m_b_verb;
		TAdapter_enum m_enum;
	};
	// step #1: creating a device and its context:
	// https://learn.microsoft.com/en-us/windows/win32/direct3dgetstarted/work-with-dxgi ;

	// it looks like any typedef element name is suffexed by '_t', for example, wchar_t; https://en.wikipedia.org/wiki/Typedef ;
	
	using TContext   = ex_ui::draw::direct_x::_11::CContext;
	using TDescWrap  = ex_ui::draw::direct_x::_11::CDesc_Wrap;
	using TDevice    = ex_ui::draw::direct_x::_11::CDevice;
	using TDevCfg    = ex_ui::draw::direct_x::_11::CDev_Cfg;

	using TSwapChain = ex_ui::draw::direct_x::_11::CSwapChain;
	using TSwapDesc  = ex_ui::draw::direct_x::_11::TSwapDesc;

	using TDescRaw   = ex_ui::draw::direct_x::_11::_2D::TTexDesc;
	using TDesc_2D   = ex_ui::draw::direct_x::_11::_2D::CTexDesc;
	using TTex_2D    = ex_ui::draw::direct_x::_11::_2D::CTexture;

	using TFeature        = ex_ui::draw::direct_x::_11::CFeature;
	using TFeature_Thread = ex_ui::draw::direct_x::_11::CFeature_Thread;
	using TFeature_Format = ex_ui::draw::direct_x::_11::CFeature_Format;

	__class(CDevice) { // the bace device class unit tests;
	public:
		 CDevice (const bool _b_verb = false); // *attention*: the constructor may be called twice by MSTest framework;
		~CDevice (void);

	public:
		__method (Create);      // by default it creates ref-device with swap&chain object; it is required for testing other methods of this class;
#pragma region _gets-obj-by-ref-dev-&-swap&chain
		__method (GetAdapter_ref);
		__method (GetContext_ref);
		__method (GetFeature_ref);  
		__method (GetTexture_ref);
#pragma endregion
#pragma region _gets-obj-by-ref-dev-no-swap&chain
		__method (GetAdapter_no_swap);
		__method (GetContext_no_swap);
		__method (GetFeature_no_swap);
		__method (GetTexture_no_swap);
#pragma endregion
#pragma region _gets-obj-by-hard-dev-no-swap&chain
		__method (GetAdapter_hw);
		__method (GetContext_hw);
		__method (GetFeature_hw);  
		__method (GetTexture_hw);
#pragma endregion
		
		const
		TDevCfg& Cfg (void) const;
		TDevCfg& Cfg (void);

		const
		TDevice& Ref (void) const;
		TDevice& Ref (void);

		err_code Create(const TDrv_type, const bool _b_swap); // this is the base device class create wrapper;

	private:
		TDevice  m_device;
		bool m_b_verb;
	};

	using TDevice_HW  = ex_ui::draw::direct_x::_11::CDevice_HW;
	using TDevice_ref = ex_ui::draw::direct_x::_11::CDevice_Ref;

	__class(CDevice_HW) {
	public:
		__method(Create); // creates a hardware device with swap&chain object;

		const
		TDevice_HW& Ref (void) const;
		TDevice_HW& Ref (void) ;

	private:
		TDevice_HW m_dev_hw;
	};

	__class(CDevice_Ref) {
	public:
		__method(Create); // creates a reference device with swap&chain object;

		const
		TDevice_ref& Ref (void) const;
		TDevice_ref& Ref (void) ;

	private:
		TDevice_ref m_dev_ref;
	};

	using TDisplay = ex_ui::draw::direct_x::_11::CDisplay;

	__class(CDisplay) {
	public:
		 CDisplay (const bool _b_verb = false);
		~CDisplay (void) = default;

	public:
		__method (GetRez);

	private:
		bool     m_b_verb;
		TDisplay m_display;
	};
	
	using TFac_2 = ex_ui::draw::direct_x::_11::CFac_2;

	__class(CFac_2) {
	public:
		 CFac_2 (const bool _b_verb = false);
		~CFac_2 (void) = default;

	public:
		__method (Create);
		__method (GetSwapChain);

	private:
		bool m_b_verb;
		TFac_2 m_fac_2;
	};

	using TZBuffer  = ex_ui::draw::direct_x::_11::_2D::CTexture;
	using TZBuffPtr = ex_ui::draw::direct_x::_11::_2D::TTexPtr ;

	__class(CSwapChain) {
	public:
		 CSwapChain (const bool _b_verb = false);
		~CSwapChain (void) = default;

	public:
	#if (0)
		__method (Create); // it is created by the CDevice_HW; (1) the device is created itself; (2) it creates this swap chain;
	#endif
	private:
		bool       m_b_verb;
		TSwapChain m_swp_chain;
	};

	using TTarget = ex_ui::draw::direct_x::_11::CTarget;

	__class(CTarget) {
	public:
		 CTarget (const bool _b_verb = false);
		~CTarget (void) = default;

	public:
		__method (Create);

	private:
		bool m_b_verb;
		TTarget m_target;
	};

	using TWarp_enum = TAdapter_enum;

	__class(CWarp_enum) {
	public:
		 CWarp_enum (const bool _b_verb = false);
		~CWarp_enum (void) = default;

	public:
		__method (Do);

	private:
		bool m_b_verb;
		TWarp_enum m_enum;
	};

}}}}}

#endif/*_EBO_TEST_$D$_RENDER_1_H_INCLUDED*/