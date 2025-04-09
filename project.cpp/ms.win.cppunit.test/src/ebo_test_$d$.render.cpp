/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2025 at 04:41:06.363, UTC+4, Batumi, Wednesday;
	This is Ebo Pack 2D/3D draw renderer lib unit test interface implementation file; 
*/
#include "ebo_test_$d$.render.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace shared::types;

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	namespace draw {

		namespace _11 {
			using TAda_Warp = ex_ui::draw::direct_x::_11::CAda_Warp;
			using TWarp_enum = ex_ui::draw::direct_x::_11::CEnum_Warp;
			using TParent_Fac = ex_ui::draw::direct_x::_11::CAda_Warp::CParent;
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
		}
	}

#if (0)
			using TCmdQueue = ex_ui::draw::direct_x::_12::CCmdQueue;
			using TDevice_HW = ex_ui::draw::direct_x::_11::CDevice_HW;
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
	}
			};
		}
	}
#endif

#if (0)
	namespace draw {

		using e_print = ex_ui::draw::direct_x::e_print;
		using TAlphaMode = ex_ui::draw::direct_x::CAlphaMode;


		class CDesc_Wrap {
		public:
			 CDesc_Wrap (void) : m_desc{ 0 } {} CDesc_Wrap (const CDesc_Wrap&) = delete; CDesc_Wrap (CDesc_Wrap&&) = delete;
			~CDesc_Wrap (void) {}

		public:
			const
			TSwapDesc&  ref (void) const { return this->m_desc; }
			TSwapDesc&  ref (void)       { return this->m_desc; }

		private:
			TSwapDesc m_desc;
		private:
			CDesc_Wrap& operator = (const CDesc_Wrap&) = delete;
			CDesc_Wrap& operator = (CDesc_Wrap&&) = delete;
		};

		__class(CAlhaMode) {

			uint32_t n_sync = 0;

			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TAlphaMode().Print(e_print::e_all);
				_out()();
			}

			__method(Set) {

				TAlphaMode a_mode;
				a_mode.Sync(&n_sync);

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("alpha value sync before: %d"), n_sync);

				a_mode.Set(TAlphaMode::e_mode::e_premulti);

				_out() += a_mode.Print(e_print::e_all);
				_out() += TStringEx().Format(_T("alpha value sync after: %d"), n_sync);
				_out()();

			}
		};

		using TBuffer  = ex_ui::draw::direct_x::CBuffer;
		using TUsage   = ex_ui::draw::direct_x::CBuff_Usage::e_usage;
		using TWrapper = ex_ui::draw::direct_x::_12::CDesc_Wrap;
		using TWrapPtr = ex_ui::draw::direct_x::_12::TDescWrapPtr;

		__class(CBuffer) {

			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TBuffer().Print(e_print::e_all);
				_out()();
			}

			__method(Set) {
				TBuffer buffer;

				TWrapPtr p_sync(new TWrapper());

				buffer.Sync() = p_sync;

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("swap desc value sync before: count=%d;usage=%d"),
					buffer.Sync()->ref().BufferCount, buffer.Sync()->ref().BufferUsage
				);

				buffer.Set(3, TUsage::e_read);

				_out() += buffer.Print(e_print::e_all);
				_out() += TStringEx().Format(_T("swap desc value sync after: count=%d;usage=%d"),
					buffer.Sync()->ref().BufferCount, buffer.Sync()->ref().BufferUsage
				);
				_out()();

			//	m_sync.reset();
			}
		};

		using TEffect = ex_ui::draw::direct_x::CEffect;
		__class(CEffect) {

			uint32_t n_sync = 0;

			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TEffect().Print(e_print::e_all);
				_out()();
			}

			__method(Set) {

				TEffect effect(&n_sync);

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("effect value sync before: %d"), n_sync);

				effect.Set(TEffect::e_value::e_flp_seq);

				_out() += effect.Print(e_print::e_all);
				_out() += TStringEx().Format(_T("effect value sync after: %d"), n_sync);
				_out()();
			}
		};

		using TDevice = ex_ui::draw::direct_x::_11::CDevice;
		using TDev_Warp = ex_ui::draw::direct_x::_12::CDevice_Warp;

		using TFeature = ex_ui::draw::direct_x::_11::CFeature;
		using TFeature_Thread = ex_ui::draw::direct_x::_11::CFeature_Thread;
		using TFeature_Format = ex_ui::draw::direct_x::_11::CFeature_Format;

		__class(CDevice) {
		private:
			TDevice_HW m_device;

		public:
			// *attention*: the constructor may be called twice;
			CDevice (void) {
				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

				if (false == this->m_device.Is_valid()) {
					m_device.Create();
					if (false == this->m_device.Is_valid()) {
						_out() += this->m_device.Error().Print(TError::e_print::e_req);
					}
					else
						_out() += _T("The device has been created successfully;");
				}
				_out()();
			}

			~CDevice (void) {
				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
				_out()();
			}
			// at least one test method must be defined, otherwise this test class does not appeat in the test explorer;
			// test class constuctor and destructor do not lead to show this class;

			// this is from ::_12::CDevice class
			__method (WarpAdapter) {
				if (false == this->m_device.Is_valid()) {
					_out() += this->m_device.Error().Print(TError::e_print::e_req);
					_out()();
					return;
				}
				TAda_Warp ada_warp;
				this->m_device.Get(ada_warp);
				if (this->m_device.Error()) {
					_out() += this->m_device.Error().Print(TError::e_print::e_req);
					_out()();
				}
				_out() += _T("The retrieving adapter is succeeded;");

				TParent_Fac fac_parent;
				err_code n_result = ada_warp.Get(fac_parent);

				if (__succeeded(n_result))
					_out() += _T("Parent factory is received;");
				else {
					CError error; error << n_result;
					_out() += error.Print(TError::e_print::e_req);
					_out()();
				}

				_out()();
			}
			__method (Features) {
				if (false == this->m_device.Is_valid()) {
					_out() += this->m_device.Error().Print(TError::e_print::e_req);
					_out()();
					return;
				}

				TFeature_Thread feature_0;
				this->m_device.Get(feature_0);

				if (this->m_device.Error())
					_out() += this->m_device.Error().Print(TError::e_print::e_req);
				else
					_out() += feature_0.Print();

				TFeature_Format feature_1;
				this->m_device.Get(feature_1);

				if (this->m_device.Error())
					_out() += this->m_device.Error().Print(TError::e_print::e_req);
				else
					_out() += feature_1.Print();

				_out()();
			}
		};
		
		using TSwapChain = ex_ui::draw::direct_x::CSwapChain;

		using TClrBits  = ex_ui::draw::direct_x::TClrBits ;
		using TPxFormat = ex_ui::draw::direct_x::CPxFormat;

		__class(CPxFormat) {

			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TPxFormat().Print(e_print::e_all);
				_out()();
			}

			__method(Set) {
				TPxFormat px_fmt;

				TWrapPtr p_sync(new TWrapper());

			//	px_fmt.Sync() = p_sync;
				px_fmt << p_sync;

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("swap desc value sync before: alpha=%d;format=%d"),
					px_fmt.Sync()->ref().AlphaMode, px_fmt.Sync()->ref().Format
				);

				px_fmt.Alpha() << TAlphaMode::e_mode::e_straith;
				px_fmt << TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM ;

				_out() += px_fmt.Print(e_print::e_all);
				_out() += TStringEx().Format(_T("swap desc value sync after: alpha=%d;format=%d"),
					px_fmt.Sync()->ref().AlphaMode, px_fmt.Sync()->ref().Format
				);
				_out()();
			}
		};

		using TSample = ex_ui::draw::direct_x::CSample;

		__class(CSample) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TSample().Print(e_print::e_all);
				_out()();
			}

			__method(Set) {
				TSample sample;

				TWrapPtr p_sync(new TWrapper());

				sample << p_sync;

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("swap desc value sync before: sample_count=%d;sample_quality=%d"),
					sample.Sync()->ref().SampleDesc.Count, sample.Sync()->ref().SampleDesc.Quality
				);

				sample.Set(1, 2);

				_out() += sample.Print(e_print::e_all);
				_out() += TStringEx().Format(_T("swap desc value sync after: sample_count=%d;sample_quality=%d"),
					sample.Sync()->ref().SampleDesc.Count, sample.Sync()->ref().SampleDesc.Quality
				);
				_out()();
			}
		};

		using TSize = ex_ui::draw::direct_x::CSize;

		__class(CSize) {
			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TSize().Print(e_print::e_all);
				_out()();
			}

			__method(Set) {
				TSize size;

				TWrapPtr p_sync(new TWrapper());

				size << p_sync;

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("swap desc value sync before: height=%d;width=%d"),
					size.Sync()->ref().Height, size.Sync()->ref().Width
				);

				size.Set(800, 600);

				_out() += size.Print(e_print::e_all);
				_out() += TStringEx().Format(_T("swap desc value sync after: height=%d;width=%d"),
					size.Sync()->ref().Height, size.Sync()->ref().Width
				);
				_out()();
			}
		};

		using TSwapDesc = ex_ui::draw::direct_x::CSwapDesc;
		using TScale = ex_ui::draw::direct_x::TScale;
		using TSwapFlag = ex_ui::draw::direct_x::TSwapFlag;

		__class(CSwapDesc) {

			__ctor(_ctor) {
				_out() += TLog_Acc::e_new_line;
				_out() += TSwapDesc().Print(e_print::e_all);
				_out()();
			}

			__method(Set) {
				TSwapDesc sw_desc; // alpha mode must receive pointer to sync value;

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
					sw_desc.Alpha().Get(),
					(_pc_sz) sw_desc.Buffer().Print(e_print::e_req),
					(_pc_sz) sw_desc.Effect().Print(e_print::e_req), TStringEx().Dword(sw_desc.Flags()), 
					(_pc_sz) sw_desc.Pixels().Print(e_print::e_req),
					(_pc_sz) sw_desc.Sample().Print(e_print::e_req),
					(_pc_sz) sw_desc.Size().Print(e_print::e_req)  , sw_desc.Scale(),
					(_pc_sz) TStringEx().Bool(sw_desc.Stereo())
				);

				sw_desc.Alpha() << TAlphaMode::e_mode::e_ignore;
				sw_desc.Buffer().Set(3, TUsage::e_shader);

				sw_desc.Effect().Set(TEffect::e_value::e_discard);
				sw_desc.Flags(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE|TSwapFlag::DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY);

				sw_desc.Pixels().Alpha() << TAlphaMode::e_unspec;
				sw_desc.Pixels() << TClrBits::DXGI_FORMAT_UNKNOWN;

				sw_desc.Sample().Set(1, 1);
				sw_desc.Size().Set(555, 333);
				sw_desc.Stereo(true);
				sw_desc.Scale(TScale::DXGI_SCALING_ASPECT_RATIO_STRETCH);

				_out() += sw_desc.Print(e_print::e_all);
				_out() += TStringEx().Format(pc_sz_pat, _T("after"),
					sw_desc.Alpha().Get(),
					(_pc_sz) sw_desc.Buffer().Print(e_print::e_req),
					(_pc_sz) sw_desc.Effect().Print(e_print::e_req), TStringEx().Dword(sw_desc.Flags()),
					(_pc_sz) sw_desc.Pixels().Print(e_print::e_req),
					(_pc_sz) sw_desc.Sample().Print(e_print::e_req),
					(_pc_sz) sw_desc.Size().Print(e_print::e_req)  , sw_desc.Scale(),
					(_pc_sz)TStringEx().Bool(sw_desc.Stereo())
				);
				_out()();
			}
		};

		__class(CWarp_enum) {

			__method(Do) {
				TWarp_enum warp_enum;
				warp_enum.Set();
				warp_enum.Get();
			}
		};

		using TWarpDev = ex_ui::draw::direct_x::_12::CDevice_Warp;

		__class(CDev_warp) {

			__method(ref) {

				TWarp_enum warp_enum;
				TWarpDev   wrap_dev ;
				if (warp_enum.Set()) {
					wrap_dev.Create(warp_enum.Get());
				}
			}

		};
	}
#endif
}}}