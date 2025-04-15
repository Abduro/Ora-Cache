#ifndef _EBO_TEST_$D$_RENDER_2_H_INCLUDED
#define _EBO_TEST_$D$_RENDER_2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2025 at 03:37:11.884, UTC+4, Batumi, Tuesday;
	This is Ebo Pack DirectX.12 draw renderer lib unit test interface declaration file;
*/
#include "ebo_test_$d$.render.h"
#include "ebo_test_$d$.render.impl.h"

namespace ebo { namespace boo { namespace test { namespace draw { namespace _12 {

	using namespace ebo::boo::test::draw;
	using namespace ebo::boo::test::_impl::_12;

	using TAdapter  = ex_ui::draw::direct_x::_12::CAdapter;
	using TAda_enum = ex_ui::draw::direct_x::_12::CAdapter_Enum;
	using TAdapters = ex_ui::draw::direct_x::_12::TAdapters;

	__class(CAdapter) {
	public:
		 CAdapter (const bool _b_verb = false);
		~CAdapter (void);

	public:
		__ctor (_ctor);

	private:
		bool m_b_verb;
	};

	__class(CAda_enum) {
	public:
		__method (Do);
	};

	using TAlphaMode = ex_ui::draw::direct_x::_12::CAlphaMode;

	__class(CAlphaMode) {
	public:
		 CAlphaMode (const bool _b_verb = false);
		~CAlphaMode (void) = default;

	public:
		bool Set (const TAlphaMode::e_mode = TAlphaMode::e_mode::e_premulti);
		__method (Set);

	private:
		uint32_t   m_sync = 0;
		TAlphaMode m_mode;
		bool       m_b_verb;
	};

	using TDev_Warp  = ex_ui::draw::direct_x::_12::CDevice_Warp;
	using TWarp_ada  = ex_ui::draw::direct_x::_11::CAda_Warp;
	using TWarp_Enum = ex_ui::draw::direct_x::_11::CWarp_Enum;

	__class(CDev_warp) {
	public:
		 CDev_warp (const bool _b_varp = false);
		~CDev_warp (void) = default;

	public:
		__method (Create);
		
	private:
		bool m_b_verb;
		TDev_Warp m_device;
	};

	using TCmdQueue  = ex_ui::draw::direct_x::_12::CCmdQueue;
	using TSwapChain = ex_ui::draw::direct_x::_12::CSwapChain;
	using TFac_4 = ex_ui::draw::direct_x::_12::CFac_4;
	// using device that is created from default adapter is not good idea, because this adapter may not be accepted for
	// creating a swap chain object, thus a device of dx-11 is not acceptable;
	using TDevice_HW = ex_ui::draw::direct_x::_12::CDevice_HW; 

	__class(CFac_4) {
	public:
		 CFac_4 (const bool _b_verb = false);
		~CFac_4 (void);

	public:
		__method (Create);
		__method (GetAdapter);
		__method (GetSwapChain);

	private:
		bool   m_b_verb;
		TFac_4     m_fac_4;
		TSwapChain m_swap_chain;
	};

	using TFac_6 = ex_ui::draw::direct_x::_12::CFac_6;

	__class(CFac_6) {
	public:
		 CFac_6 (const bool _b_verb = false);
		~CFac_6 (void) = default;

	public:
		__method (Create);
		__method (Enum_Hi_perf);
		__method (Enum_Lo_power);

	private:
		bool   m_b_verb;
		TFac_6 m_fac_6;
	};

	using TClrBits  = ex_ui::draw::direct_x::TClrBits;
	using TPxFormat = ex_ui::draw::direct_x::_12::CPxFormat;
	using TWrapper  = ex_ui::draw::direct_x::_12::CDesc_Wrap;
	using TWrapPtr  = ex_ui::draw::direct_x::_12::TDescWrapPtr;

	__class(CPxFormat) {
	public:
		 CPxFormat (const bool _b_verb = false);
		~CPxFormat (void) = default;
	public:
		__method (Set);

	private:
		bool m_b_verb;
		TPxFormat m_px_fmt;
		TWrapper  m_wrapper;
	};

	using TSize = ex_ui::draw::direct_x::_12::CSize;

	__class(CSize) {
	public:
		 CSize (const bool _b_verb = false);
		~CSize (void) = default;

	public:
		__method (Set);

	private:
		bool   m_b_verb;
		TSize    m_size;
		TWrapper m_wrapper;
	};

}}}}}

#endif/*_EBO_TEST_$D$_RENDER_2_H_INCLUDED*/