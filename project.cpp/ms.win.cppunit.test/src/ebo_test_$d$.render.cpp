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

		using e_print = ex_ui::draw::direct_x::e_print;

		using TClrBits = ex_ui::draw::direct_x::TClrBits;

		using IBufferSink = ex_ui::draw::direct_x::IBuffer_Sync;
		using TBuffer = ex_ui::draw::direct_x::CBuffer;
		using TUsage = ex_ui::draw::direct_x::CBuff_Usage::e_usage;

		class CBuff_Sync : public IBufferSink {
		public:
			 CBuff_Sync (void) {} CBuff_Sync (const CBuff_Sync&) = delete; CBuff_Sync (CBuff_Sync&&) = delete;
			~CBuff_Sync (void) = default;

		private:
			virtual bool IBuffer_OnCount (const uint32_t _n_value) override final {
				_n_value;
				_out() += TStringEx().Format(
					_T("cls::[%s::%s].%s(count=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _n_value
				);
				return true;
			}
			virtual bool IBuffer_OnUsage (const uint32_t _n_value) override final {
				_n_value;
				_out() += TStringEx().Format(
					_T("cls::[%s::%s].%s(usage=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _n_value
				);
				return true;
			}

		private:
			CBuff_Sync& operator = (const CBuff_Sync&) = delete;
			CBuff_Sync& operator = (CBuff_Sync&&) = delete;
		};

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

		class CSample_Sync : public ISample_Sync {
		public:
			 CSample_Sync (void) {} CSample_Sync (const CSample_Sync&) = delete; CSample_Sync (CSample_Sync&&) = delete;
			~CSample_Sync (void) = default;

		private:
			virtual bool ISample_OnCount (const uint32_t _n_value) override final {
				_n_value;
				_out() += TStringEx().Format(
					_T("cls::[%s::%s].%s(count=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _n_value
				);
				return true;
			}
			virtual bool ISample_OnQuality (const uint32_t _n_value) override final {
				_n_value;
				_out() += TStringEx().Format(
					_T("cls::[%s::%s].%s(quality=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _n_value
				);
				return true;
			}

		private:
			CSample_Sync& operator = (const CSample_Sync&) = delete;
			CSample_Sync& operator = (CSample_Sync&&) = delete;
		};

		using TSwapFlag = ex_ui::draw::direct_x::TSwapFlag;

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

		namespace _11 {
			using TAda_Warp = ex_ui::draw::direct_x::_11::CAda_Warp;
			using TWarp_enum = ex_ui::draw::direct_x::_11::CEnum_Warp;
			using TParent_Fac = ex_ui::draw::direct_x::_11::CAda_Warp::CParent;

			__class(CAda_Warp) {
			};

			using TContext = ex_ui::draw::direct_x::_11::CContext;
			using TDevice = ex_ui::draw::direct_x::_11::CDevice;
			using TDevice_HW = ex_ui::draw::direct_x::_11::CDevice_HW;

			using TFeature = ex_ui::draw::direct_x::_11::CFeature;
			using TFeature_Thread = ex_ui::draw::direct_x::_11::CFeature_Thread;
			using TFeature_Format = ex_ui::draw::direct_x::_11::CFeature_Format;

			// step #1: creating a device and its context:
			// https://learn.microsoft.com/en-us/windows/win32/direct3dgetstarted/work-with-dxgi ;

			__class(CDevice) {
			private:
				TDevice_HW  m_device;

			public:
				// *attention*: the constructor may be called twice;
				 CDevice (void) {
					_out() += TLog_Acc::e_new_line;
					_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

					if (false == this->m_device.Is_valid()) {
						this->m_device.Create();
						if (false == this->m_device.Is_valid()) {
							_out() += this->m_device.Error().Print(TError::e_print::e_req);
						}
						else
							_out() += this->m_device.Print(e_print::e_all);
					}
					_out()();
				}

				~CDevice (void) {
					_out() += TLog_Acc::e_new_line;
					_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
					_out()();
				}

				__method (GetAdapter) {
					if (false == this->m_device.Is_valid()) {
						_out() += this->m_device.Error().Print(TError::e_print::e_req);
						_out()();
						return;
					}
					TAda_Warp adapter;
					this->m_device.Get(adapter);
					if (this->m_device.Error()) {
						_out() += this->m_device.Error().Print(TError::e_print::e_req);
					}
					else if (__failed(adapter.UpdateInfo())) {
						_out() += adapter.Error().Print(TError::e_print::e_req);
					}
					else {
						_out() += adapter.Print(e_print::e_all);
					}
					_out()();
				}

				__method (Context) {
					if (false == this->m_device.Is_valid()) {
						_out() += this->m_device.Error().Print(TError::e_print::e_req);
						_out()();
						return;
					}

					TContext ctx;
					this->m_device.Get(ctx);
					if (this->m_device.Error())
						_out() += this->m_device.Error().Print(TError::e_print::e_req);
					else if (false == ctx.Is_valid())
						_out() += ctx.Error().Print(TError::e_print::e_req);
					else
						_out() += ctx.Print();
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

					TFeature_Format feature_1; feature_1.Ref().InFormat = TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM;
					this->m_device.Get(feature_1);

					if (this->m_device.Error())
						_out() += this->m_device.Error().Print(TError::e_print::e_req);
					else
						_out() += feature_1.Print();

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
	}
			};
		}
	}
#endif

#if (0)
	namespace draw {
		
		using TDev_Warp = ex_ui::draw::direct_x::_12::CDevice_Warp;

		
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
			
		};
		
		using TSwapChain = ex_ui::draw::direct_x::CSwapChain;

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