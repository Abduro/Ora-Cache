#ifndef _EBO_TEST_$D$_RENDER_IMPL_H_INCLUDED
#define _EBO_TEST_$D$_RENDER_IMPL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Apr-2025 at 18:51:39.493, UTC+4, Batumi, Sunday;
	This is Ebo Pack 2D/3D draw renderer lib unit test helper interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "_log.h"
#include "direct_x.device.h"
#include "direct_x.factory.h"
#include "direct_x.swap.h"
#include "direct_x.swap.1.h"
#include "direct_x.swap.2.h"

namespace ebo { namespace boo { namespace test { namespace _impl {

	using CWindow = ::ATL::CWindow;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

	using IBufferSink = ex_ui::draw::direct_x::IBuffer_Sync;

	class CBuff_Sync : public IBufferSink {
	public:
		 CBuff_Sync (void) {} CBuff_Sync (const CBuff_Sync&) = delete; CBuff_Sync (CBuff_Sync&&) = delete;
		~CBuff_Sync (void) = default;

	private:
		virtual bool IBuffer_OnCount (const uint32_t _n_value) override final;
		virtual bool IBuffer_OnUsage (const uint32_t _n_value) override final;

	private:
		CBuff_Sync& operator = (const CBuff_Sync&) = delete;
		CBuff_Sync& operator = (CBuff_Sync&&) = delete;
	};

	using ISample_Sync = ex_ui::draw::direct_x::ISample_Sync;

	class CSample_Sync : public ISample_Sync {
	public:
		 CSample_Sync (void) {} CSample_Sync (const CSample_Sync&) = delete; CSample_Sync (CSample_Sync&&) = delete;
		~CSample_Sync (void) = default;

	private:
		virtual bool ISample_OnCount (const uint32_t _n_value) override final;
		virtual bool ISample_OnQuality (const uint32_t _n_value) override final;

	private:
		CSample_Sync& operator = (const CSample_Sync&) = delete;
		CSample_Sync& operator = (CSample_Sync&&) = delete;
	};

	class CFake_Wnd : public ::ATL::CWindowImpl<CFake_Wnd> { typedef ::ATL::CWindowImpl<CFake_Wnd> TBase;
	public:
		  CFake_Wnd (const bool _b_verb = false);
		 ~CFake_Wnd (void);

	public:
		DECLARE_EMPTY_MSG_MAP();

		TError&  Error (void) const;

	private:
		CFake_Wnd (const CFake_Wnd&) = delete;
		CFake_Wnd (CFake_Wnd&&) = delete;
		CFake_Wnd& operator = (const CFake_Wnd&) = delete;
		CFake_Wnd& operator = (CFake_Wnd&&) = delete;

	private:
		bool    m_verb ;
		CError  m_error;
	};

namespace _11 {

	using CFake_Wnd = ebo::boo::test::_impl::CFake_Wnd;
	using TSwapDesc = ex_ui::draw::direct_x::_11::CDesc_Wrap;

	class CFake_Desc {
	public:
		 CFake_Desc (const bool _b_verb = false);
		 CFake_Desc (const CFake_Desc&) = delete; CFake_Desc (CFake_Desc&&) = delete;
		~CFake_Desc (void);

	public:
		TError&  Error (void) const;
		err_code Trick (void) ;

		const
		TSwapDesc&  Ref (void) const;
		TSwapDesc&  Ref (void)      ;

	private:
		CFake_Desc& operator = (const CFake_Desc&) = delete;
		CFake_Desc& operator = (CFake_Desc&&) = delete;

	private:
		bool      m_verb;
		CError    m_error;
		CFake_Wnd m_wnd;
		TSwapDesc m_desc;
	};

	using CDev_HW = ex_ui::draw::direct_x::_11::CDevice_HW;
	using CFac_2  = ex_ui::draw::direct_x::_11::CFac_2;
	using TSwap   = ex_ui::draw::direct_x::_11::CSwapChain; // just playing with names;

	class CFake_Swap {
	public:
		 CFake_Swap (void);
		 CFake_Swap (const CFake_Swap&) = delete; CFake_Swap (CFake_Swap&&) = delete;
		~CFake_Swap (void);

	public:
		err_code Create(void) ;
		TError&  Error (void) const;
		const
		TSwap&   Ref (void) const;
		err_code Set (const CFac_2&);

	private:
		CFake_Swap& operator = (const CFake_Swap&) = delete;
		CFake_Swap& operator = (CFake_Swap&&) = delete;

	private:
		CError m_error;
		TSwap  m_chain;
		CFac_2 m_fac_2;
	};
}

namespace _12 {}
}}}}

#endif/*_EBO_TEST_$D$_RENDER_IMPL_H_INCLUDED*/