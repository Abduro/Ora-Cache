/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2025 at 04:41:06.363, UTC+4, Batumi, Wednesday;
	This is Ebo Pack 2D/3D draw renderer lib unit test interface implementation file; 
*/
#include "ebo_test_$d$.render.h"
#include "ebo_test_$d$.render.impl.h"

namespace ebo { namespace boo { namespace test { namespace draw {

	using namespace ebo::boo::test::_impl;

	using TClrBits = ex_ui::draw::direct_x::TClrBits;

	using IBufferSink = ex_ui::draw::direct_x::IBuffer_Sync;
	using TBuffer = ex_ui::draw::direct_x::CBuffer;
	using TUsage = ex_ui::draw::direct_x::CBuff_Usage::e_usage;

	__class(CBuffer) {
	private:
		CBuff_Sync m_sync;
		TBuffer    m_buffer;

	public:
		CBuffer(void) {
			this->m_buffer << (IBufferSink* const)&this->m_sync;
		}
		~CBuffer(void) {
		}

		__method(Set) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("swap desc value sync before: count=%d;usage=%d"),
				this->m_buffer.Count(), this->m_buffer.Usage()
			);

			this->m_buffer.Set(3, TUsage::e_read);

			_out() += this->m_buffer.Print(e_print::e_all);
			_out() += TStringEx().Format(_T("swap desc value sync after: count=%d;usage=%d"),
				this->m_buffer.Count(), this->m_buffer.Usage()
			);
			_out()();
		}
	};

	using TEffect = ex_ui::draw::direct_x::CEffect;

	__class(CEffect) {
	private:
		uint32_t m_sync = 0;
		TEffect  m_effect;

	public:
		 CEffect (void) {
			this->m_effect << (uint32_t* const)&this->m_sync;
		}
		~CEffect (void) {
		}

		__method(Set) {

			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("effect value sync before: %d"), this->m_sync);

			this->m_effect.Set(TEffect::e_value::e_flp_seq);

			_out() += this->m_effect.Print(e_print::e_all);
			_out() += TStringEx().Format(_T("effect value sync after: %d"), this->m_sync);
			_out()();
		}
	};

	using ISample_Sync = ex_ui::draw::direct_x::ISample_Sync;
	using TSample = ex_ui::draw::direct_x::CSample;

	__class(CSample) {
	private:
		CSample_Sync m_sync;
		TSample m_sample;

	public:
		 CSample (void) {
			this->m_sample << (ISample_Sync* const)&this->m_sync;
		}
		~CSample (void) {
		}

		__method(Set) {

			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("sample sync values before: count=%d;quality=%d"),
				this->m_sample.Count(), this->m_sample.Quality()
			);

			this->m_sample.Set(1, 2);

			_out() += this->m_sample.Print(e_print::e_all);
			_out() += TStringEx().Format(_T("sample sync values after: count=%d;quality=%d"),
				this->m_sample.Count(), this->m_sample.Quality()
			);
			_out()();
		}
	};

	using TSwapFlag = ex_ui::draw::direct_x::TSwapFlag;

namespace _11 {

	using namespace ebo::boo::test::_impl::_11;

	using TAda_Warp = ex_ui::draw::direct_x::_11::CAda_Warp;
	using TWarp_enum = ex_ui::draw::direct_x::_11::CWarp_Enum;
	using TParent_Fac = ex_ui::draw::direct_x::_11::CAda_Warp::CParent;

	using TDevice_HW = ex_ui::draw::direct_x::_11::CDevice_HW;
	
	using TSwap = ex_ui::draw::direct_x::_11::CSwapChain;

	using TSwapDesc = ex_ui::draw::direct_x::_11::CDesc_Wrap;
	using TFac_2 = ex_ui::draw::direct_x::_11::CFac_2;

	__class(CFac_2) {
	private:
		TFac_2 m_fac_2;

	public:
#if (0)
		 CFac_2 (void) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			this->m_fac_2.Create();
			if (this->m_fac_2.Is_valid())
				_out() += this->m_fac_2.Print(e_print::e_all);
			else
				_out() += this->m_fac_2.Error().Print(TError::e_print::e_req);

			_out()();
		}
		~CFac_2 (void) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
			_out()();
		}
#endif
		__method(GetSwapChain) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			this->m_fac_2.Create();
			if (this->m_fac_2.Is_valid())
				_out() += this->m_fac_2.Print(e_print::e_all);
			else {
				_out() += this->m_fac_2.Error().Print(TError::e_print::e_req);
				_out()();
				return;
			}

			TDevice_HW device;
			device.Create();
			if (device.Error()) {
				_out() += this->m_fac_2.Error().Print(TError::e_print::e_req);
				_out()();
				return;
			}

			CFake_Desc desc;
			if (desc.Error()) {
				_out() += desc.Error().Print(TError::e_print::e_req);
				_out()();
				return;
			}

			TSwap chain;

			this->m_fac_2.Get(device, desc.Ref(), chain);
			if (this->m_fac_2.Error())
				_out() += this->m_fac_2.Error().Print(TError::e_print::e_req);
			else
				_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz)chain.Print(e_print::e_all));
			_out()();
		}
	};

	using TTarget = ex_ui::draw::direct_x::_11::CTarget;

	__class(CTarget) {
	private:
		TTarget m_target;

	public:
		__method(Create) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			TDevice_HW device;
			device.Create();
			if (device.Error()) {
				_out() += device.Error().Print(TError::e_print::e_req);
				_out()();
				return;
			}
			this->m_target << device;

			CFake_Desc desc;
			CFake_Swap swap;
			swap.Create();
			if (swap.Error()) {
				_out() += swap.Error().Print(TError::e_print::e_req);
				_out()();
				return;
			}

			TSwap chain_;
			chain_.Desc().ref() = desc.Ref();
			chain_.Ptr (swap.Ref().Ptr());

			this->m_target.Set(chain_);

			this->m_target.Create();
			if (this->m_target.Error()) {
				_out() += this->m_target.Error().Print(TError::e_print::e_req);
			}
			else
				_out() += this->m_target.Print(e_print::e_all);

			_out()();
		}
	};

	__class(CWarp_enum) {
	private:
		TWarp_enum m_enum;

	public:
		__method(Do) {
			_out() += TLog_Acc::e_new_line;
			this->m_enum.Set();
			if (this->m_enum.Error()) {
				_out() += this->m_enum.Error().Print(TError::e_print::e_req);
			}
			else if (this->m_enum.Get().Error()) {
				_out() += this->m_enum.Get().Error().Print(TError::e_print::e_req);
			}
			else {
				const TAda_Warp& adapter = this->m_enum.Get();
				_out() += adapter.Print(e_print::e_all);
			}
			_out()();
		}
	};
}

namespace _12 {
	using TAdapter = ex_ui::draw::direct_x::_12::CAdapter;
	using TAda_enum = ex_ui::draw::direct_x::_12::CAdapter_Enum;
	using TAdapters = ex_ui::draw::direct_x::_12::TAdapters;

	__class(CAdapter) {
	public:
#if (0)
		 CAdapter(void) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
			_out()();
		}
		~CAdapter(void) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
			_out()();
		}
#endif
		__ctor(_ctor) {
			_out() += TLog_Acc::e_new_line;
			_out() += TAdapter().Print();
			_out()();
		}
	};

	__class(CAda_enum) {
		__method(Do) {
			TAda_enum ada_enum;

			if (__succeeded(ada_enum.Set())) {

				_out() += TLog_Acc::e_new_line;

				const TAdapters& adapters = ada_enum.Get();
				for (size_t i_ = 0; i_ < adapters.size(); i_++) {
					const TAdapter& adapter = adapters.at(i_);
					_out() += adapter.Print();
				}
			}
			else {
				_out() += ada_enum.Error().Print(TError::e_print::e_req);
			}
			_out()();
		}
	};
		
	using TAlphaMode = ex_ui::draw::direct_x::_12::CAlphaMode;

	__class(CAlphaMode) {
	private:
		uint32_t   m_sync = 0;
		TAlphaMode m_mode;

	public:
		 CAlphaMode (void) {
			this->m_mode << (uint32_t* const)&this->m_sync;
		}
		~CAlphaMode (void) {
		}

		__method(Set) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("alpha value sync before: %d"), this->m_sync);

			this->m_mode.Set(TAlphaMode::e_mode::e_premulti);

			_out() += this->m_mode.Print(e_print::e_all);
			_out() += TStringEx().Format(_T("alpha value sync after: %d"), this->m_sync);
			_out()();

		}
	};

	using TFac_6 = ex_ui::draw::direct_x::_12::CFac_6;

	__class(CFac_6) {
	private:
		TFac_6 m_fac_6;

	public:
		__method(Create) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			this->m_fac_6.Create();
			if (this->m_fac_6.Is_valid())
				_out() += this->m_fac_6.Print(e_print::e_all);
			else
				_out() += this->m_fac_6.Error().Print(TError::e_print::e_req);
			_out()();
		}
		__method(Enum_Hi_perf) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			this->m_fac_6.Create();
			if (this->m_fac_6.Is_valid()) {
				if (__succeeded(this->m_fac_6.Get_Hi_Perf())) {
					const TAdapters& a_set = this->m_fac_6.Cached();
					if (a_set.size()) { // expected to be not 0;
						const TAdapter& a_hi_perf = a_set.at(0); // the best is the first one;
						_out() += a_hi_perf.Print();
					}
				}
			}
			if (this->m_fac_6.Error())
				_out() += this->m_fac_6.Error().Print(TError::e_print::e_req);
			_out()();
		}
		__method(Enum_Lo_power) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			this->m_fac_6.Create();
			if (this->m_fac_6.Is_valid()) {
				if (__succeeded(this->m_fac_6.Get_Lo_Power())) {
					const TAdapters& a_set = this->m_fac_6.Cached();
					if (a_set.size()) { // expected to be not 0;
						const TAdapter& a_hi_perf = a_set.at(0); // the best is the first one;
						_out() += a_hi_perf.Print();
					}
				}
			}
			if (this->m_fac_6.Error())
				_out() += this->m_fac_6.Error().Print(TError::e_print::e_req);
			_out()();
		}
	};

	using TDev_Warp = ex_ui::draw::direct_x::_12::CDevice_Warp;
	using TWarp_ada = ex_ui::draw::direct_x::_11::CAda_Warp;
	using TWarp_Enum = ex_ui::draw::direct_x::_11::CWarp_Enum;

	__class(CDev_warp) {
	private:
		TDev_Warp m_device;

	public:
		__method(Create) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
			// it is expected to receive the error: 'No such interface supported';
			// in case when this project is tested on virtual remote machine;
			TWarp_Enum warp_enum;
			warp_enum.Set();
			if (warp_enum.Error()) {
				_out() += warp_enum.Error().Print(TError::e_print::e_req);
			}
			else {
				const TWarp_ada& warp_ada = warp_enum.Get();
				this->m_device.Create(warp_ada);

				if (this->m_device.Error())
					_out() += this->m_device.Error().Print(TError::e_print::e_req);
				else
					_out() += _T("The device is created successfully;");
			}
			_out()();
		}
	};
			
	using TWrapper = ex_ui::draw::direct_x::_12::CDesc_Wrap;
	using TWrapPtr = ex_ui::draw::direct_x::_12::TDescWrapPtr;

	using TClrBits = ex_ui::draw::direct_x::TClrBits;
	using TPxFormat = ex_ui::draw::direct_x::_12::CPxFormat;

	__class(CPxFormat) {
	private:
		TPxFormat m_px_fmt;
		TWrapper  m_wrapper;

	public:
		 CPxFormat (void) {
			TWrapPtr wrp_ptr(new TWrapper);
			this->m_px_fmt << wrp_ptr;
		}
		~CPxFormat (void) {
		}

		__method(Set) {
			_out() += TLog_Acc::e_new_line;
			if (nullptr == this->m_px_fmt.Sync()) {
				_out() += _T("Px-format sync wrapper is not set;");
				_out()();
				return;
			}

			_out() += TStringEx().Format(_T("px-format sync values before: alpha=%d;format=%d"),
				this->m_px_fmt.Sync()->ref().AlphaMode, this->m_px_fmt.Sync()->ref().Format
			);

			this->m_px_fmt.Alpha() << TAlphaMode::e_mode::e_straith;
			this->m_px_fmt << TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM;

			_out() += this->m_px_fmt.Print(e_print::e_all);
			_out() += TStringEx().Format(_T("px-format sync values after: alpha=%d;format=%d"),
				this->m_px_fmt.Sync()->ref().AlphaMode, this->m_px_fmt.Sync()->ref().Format
			);
			_out()();
		}
	};

	using TSize = ex_ui::draw::direct_x::_12::CSize;

	__class(CSize) {
	private:
		TSize    m_size;
		TWrapper m_wrapper;

	public:
		 CSize (void) {
			TWrapPtr wrp_ptr(new TWrapper);
			this->m_size << wrp_ptr;
		}
		~CSize (void) {
		}

		__method(Set) {
			_out() += TLog_Acc::e_new_line;
			if (nullptr == this->m_size.Sync()) {
				_out() += _T("surface size sync wrapper is not set;");
				_out()();
				return;
			}

			_out() += TStringEx().Format(_T("surface size sync values before: height=%d;width=%d"),
				this->m_size.Sync()->ref().Height, this->m_size.Sync()->ref().Width
			);

			this->m_size.Set(800, 600);

			_out() += this->m_size.Print(e_print::e_all);
			_out() += TStringEx().Format(_T("surface size sync values after: height=%d;width=%d"),
				this->m_size.Sync()->ref().Height, this->m_size.Sync()->ref().Width
			);
			_out()();
		}
	};

	using TSwapDesc = ex_ui::draw::direct_x::_12::CSwapDesc;
	using TScale    = ex_ui::draw::direct_x::_12::TScale;

	__class(CSwapDesc) {
	private:
		TSwapDesc m_desc; // alpha mode must receive pointer to sync value;

	public:
		 CSwapDesc (void) {}
		~CSwapDesc (void) {}
				
		__method(Set) {
			static
			_pc_sz pc_sz_pat = _T("swap desc value sync %s: "
				"\n\t\talpha=%d;"
				"\n\t\tbuffer=%s;"
				"\n\t\teffect=%s;"
				"\n\t\tflags=%s;"
				"\n\t\tpixels=%s;"
				"\n\t\tsample=%s;"
				"\n\t\tsize=%s;"
				"\n\t\tscale=%d;stereo=%s");

			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(pc_sz_pat, _T("before"),
				this->m_desc.Alpha().Get(),
				(_pc_sz)this->m_desc.Buffer().Print(e_print::e_req),
				(_pc_sz)this->m_desc.Effect().Print(e_print::e_req), TStringEx().Dword(this->m_desc.Flags()),
				(_pc_sz)this->m_desc.Pixels().Print(e_print::e_req),
				(_pc_sz)this->m_desc.Sample().Print(e_print::e_req),
				(_pc_sz)this->m_desc.Size().Print(e_print::e_req)  , this->m_desc.Scale(),
				(_pc_sz)TStringEx().Bool(this->m_desc.Stereo())
			);

			this->m_desc.Alpha() << TAlphaMode::e_mode::e_ignore;
			this->m_desc.Buffer().Set(3, TUsage::e_shader);

			this->m_desc.Effect().Set(TEffect::e_value::e_discard);
			this->m_desc.Flags(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE | TSwapFlag::DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY);

			this->m_desc.Pixels().Alpha() << TAlphaMode::e_unspec;
			this->m_desc.Pixels() << TClrBits::DXGI_FORMAT_UNKNOWN;

			this->m_desc.Sample().Set(1, 1);
			this->m_desc.Size().Set(555, 333);
			this->m_desc.Stereo(true);
			this->m_desc.Scale(TScale::DXGI_SCALING_ASPECT_RATIO_STRETCH);

			_out() += this->m_desc.Print(e_print::e_all);
			_out() += TStringEx().Format(pc_sz_pat, _T("after"),
				this->m_desc.Alpha().Get(),
				(_pc_sz)this->m_desc.Buffer().Print(e_print::e_req),
				(_pc_sz)this->m_desc.Effect().Print(e_print::e_req), TStringEx().Dword(this->m_desc.Flags()),
				(_pc_sz)this->m_desc.Pixels().Print(e_print::e_req),
				(_pc_sz)this->m_desc.Sample().Print(e_print::e_req),
				(_pc_sz)this->m_desc.Size().Print(e_print::e_req)  , this->m_desc.Scale(),
				(_pc_sz)TStringEx().Bool(this->m_desc.Stereo())
			);
			_out()();
		}
	};
}

#if (0)
	using TCmdQueue = ex_ui::draw::direct_x::_12::CCmdQueue;
	using TFactory = ex_ui::draw::direct_x::_12::CFac_4;

	__class(CFactory) {
	private:
		TFactory m_factory;

	public:
		CFactory (void) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
			if (false == this->m_factory.Is_valid()) {
				this->m_factory.Create();
				if (this->m_factory.Error())
					_out() += this->m_factory.Error().Print(TError::e_print::e_req);
				else
					_out() += _T("The factory is created successfully;");
			}
			_out()();
		}

		~CFactory (void) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
			_out()();
		}

	public:
		__method(CreateAdapter) {

		_out() += TLog_Acc::e_new_line;

		if (false == this->m_factory.Is_valid()) {
			_out() += this->m_factory.Error().Print(TError::e_print::e_req);
			_out()();
			return;
		}

		TAdapter adapter;
		this->m_factory.Get(adapter);

		if (this->m_factory.Error())
			_out() += this->m_factory.Error().Print(TError::e_print::e_req);
		else {
			_out() += adapter.Print();
		}
		_out()();
	}

	__method(CreateSwapChain) {
		_out() += TLog_Acc::e_new_line;
		// (1) checks the factory object first;
		if (false == this->m_factory.Is_valid()) {
			_out() += this->m_factory.Error().Print(TError::e_print::e_req);
			_out()();
			return;
		}
#if (0)
		// doesn't work and leads to the error: 'E_NOINTERFACE No such interface supported.';
		// (2) creates warp-adapter object;
		TWarp_enum warp_enum;

		warp_enum.Set(); // tries to enumerate all available warp adapters;
		if (warp_enum.Error()) {
			_out() += warp_enum.Error().Print(TError::e_print::e_req);
			_out()();
			return;
		}
		TAda_Warp ada_warp = warp_enum.Get();
		if (false == ada_warp.Is()) {
			_out() += _T("#error: Cannot create warp-adapter;");
			_out()();
			return;
		}

		// (3) creates warp-device from warp-adapter;
		TDev_Warp device;
		device.Create(ada_warp);
		if (device.Error()) {
			_out() += device.Error().Print(TError::e_print::e_req);
			_out()();
			return;
		}
#else
		// (2) creates a default device object;
		TDevice_HW device;
		device.Create();

		if (device.Error()) {
			_out() += device.Error().Print(TError::e_print::e_req);
			_out()();
			return;
		}
#endif
		// (3) creates a command queue;
		TCmdQueue  cmd_que;
		device.Get(cmd_que);
		if (device.Error()) {
			_out() += device.Error().Print(TError::e_print::e_req);
			_out()();
			return;
		}

		this->m_factory << device;

		TSwapChain sw_chain;

		this->m_factory.Get(sw_chain);
		if (this->m_factory.Error()) {
			_out() += this->m_factory.Error().Print(TError::e_print::e_req);
			_out()();
			return;
		}
	};
#endif
}}}}