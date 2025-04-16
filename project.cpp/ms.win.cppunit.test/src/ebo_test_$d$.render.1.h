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

	using TClrBits = ex_ui::draw::direct_x::TClrBits;

	__class(CAda_Warp) {
	};

	// step #1: creating a device and its context:
	// https://learn.microsoft.com/en-us/windows/win32/direct3dgetstarted/work-with-dxgi ;

	// it looks like any typedef element name is suffexed by '_t', for example, wchar_t; https://en.wikipedia.org/wiki/Typedef ;
	using TAda_Warp  = ex_ui::draw::direct_x::_11::CAda_Warp;
	using TSwapChain = ex_ui::draw::direct_x::_11::CSwapChain;
	using TContext   = ex_ui::draw::direct_x::_11::CContext;
	using TDevice_HW = ex_ui::draw::direct_x::_11::CDevice_HW;

	using TFeature        = ex_ui::draw::direct_x::_11::CFeature;
	using TFeature_Thread = ex_ui::draw::direct_x::_11::CFeature_Thread;
	using TFeature_Format = ex_ui::draw::direct_x::_11::CFeature_Format;

	__class(CDevice) {
	public:
		 CDevice (const bool _b_verb = false); // *attention*: the constructor may be called twice by MSTest framework;
		~CDevice (void);

	public:
		__method (GetAdapter);
		__method (GetContext);
		__method (GetFeature);
		__method (GetSwapChain);

	private:
		TDevice_HW  m_device;
		bool m_b_verb;
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

	using TWarp_enum = ex_ui::draw::direct_x::_11::CWarp_Enum;

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