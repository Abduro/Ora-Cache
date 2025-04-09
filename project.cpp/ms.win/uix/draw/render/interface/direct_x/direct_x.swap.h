#ifndef _DIRECT_X_SWAP_H_INCLUDED
#define _DIRECT_X_SWAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr_2025 at 21:17:32.647, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX swap chain component wrapper interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.format.h"
#include "direct_x.queue.h"

namespace ex_ui { namespace draw { namespace direct_x {
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-usage ;
	class CBuff_Usage {
	public:
		enum e_usage : uint32_t {
		     e__unspec = 0,                               // this is not acceptable value for the back buffer usage;
		     e_back    = DXGI_USAGE_BACK_BUFFER         , // the surface or resource is used as a back buffer;
		     e_discard = DXGI_USAGE_DISCARD_ON_PRESENT  , // this flag is for internal use only;
		     e_read    = DXGI_USAGE_READ_ONLY           , // read only access to a surface or resource;
		     e_shader  = DXGI_USAGE_SHADER_INPUT        , // a surface or resource as an input to a shader;
		     e_shared  = DXGI_USAGE_SHARED              , // a surface or resource is shared;
		     e_target  = DXGI_USAGE_RENDER_TARGET_OUTPUT, // a surface or resource is used as an output render target;
		     e_unorder = DXGI_USAGE_UNORDERED_ACCESS    , // a surface or resource has unordered access;
		};
	private:
		CBuff_Usage (void) = delete; CBuff_Usage (const CBuff_Usage&) = delete; CBuff_Usage (CBuff_Usage&&) = delete; ~CBuff_Usage (void) = delete;
	private:
		CBuff_Usage& operator = (const CBuff_Usage&) = delete;
		CBuff_Usage& operator = (CBuff_Usage&&) = delete;
	};
	// the fields of this class are used in both structures: DXGI_SWAP_CHAIN_DESC and DXGI_SWAP_CHAIN_DESC1;
	interface IBuffer_Sync {
		virtual bool IBuffer_OnCount (const uint32_t _n_value) = 0;
		virtual bool IBuffer_OnUsage (const uint32_t _n_value) = 0;
	};

	class CBuffer {
	public:
		 CBuffer (const uint32_t _n_count = 1, const uint32_t _n_usage = CBuff_Usage::e_target); // it would be better to use double buffering;
		 CBuffer (IBuffer_Sync* const);
		 CBuffer (const CBuffer&);
		 CBuffer (CBuffer&&) = delete;
		~CBuffer (void);

	public:
		uint32_t  Count (void) const;      // gets buffer count value; must be at least 1 (one) buffer count, i.e. front buffer;
		bool      Count (const uint32_t);  // sets buffer count value; returns true on change;
		uint32_t  Usage (void) const;      // gets buffer usage value; by default is set to DXGI_USAGE_RENDER_TARGET_OUTPUT;
		bool      Usage (const uint32_t);  // sets buffer usage value; returns true on change;

		bool Is_valid   (void) const;      // returns true in case when buffer count and usage values are not equal to zero both;
		bool Set (const uint32_t _n_count, const uint32_t _n_usage);
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		err_code  Sync (IBuffer_Sync* const); // the assignment is thread-safe, but input pointer life cycle is under control of its owner;

	public:
		CBuffer&  operator = (const CBuffer&);
		CBuffer&  operator = (CBuffer&&) = delete;
		CBuffer&  operator <<(const uint32_t _n_count);
		CBuffer&  operator >>(const uint32_t _n_usage);

		CBuffer&  operator <<(IBuffer_Sync* const);

	private:
		uint32_t  m_count;
		uint32_t  m_usage;
		IBuffer_Sync* m_p_sync;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_swap_effect ;
	typedef DXGI_SWAP_EFFECT TEffect;
	// this class enumeration is used in both structures: DXGI_SWAP_CHAIN_DESC and DXGI_SWAP_CHAIN_DESC1;
	class CEffect {
	public:
		enum e_value : uint32_t {
		     e_discard  = TEffect::DXGI_SWAP_EFFECT_DISCARD        , // not supported in dx12;
		     e_sequent  = TEffect::DXGI_SWAP_EFFECT_SEQUENTIAL     , // not supported in dx12;
		     e_flp_disc = TEffect::DXGI_SWAP_EFFECT_FLIP_DISCARD   , // supported in dx12; is set by default in this class;
		     e_flp_seq  = TEffect::DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL, // supported in dx12;
		};
	public:
		 CEffect (uint32_t* const _p_sync = nullptr) ;
		 CEffect (const CEffect&) ;
		 CEffect (CEffect&&) = delete;
		~CEffect (void) = default;

	public:
		uint32_t Get (void) const;      // ToDo: perhaps TEffect type value must be returned;
		bool     Set (const uint32_t);
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		TEffect  Raw (void) const;
		void     Sync (uint32_t* const);

	private:
		CEffect&  operator = (const CEffect&);
		CEffect&  operator = (CEffect&&) = delete;

		CEffect&  operator <<(const uint32_t _n_effect);
		CEffect&  operator <<(uint32_t* const _p_sync);

	private:
		e_value   m_value;
		uint32_t* m_p_sync;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgicommon/ns-dxgicommon-dxgi_sample_desc ;
	typedef DXGI_SAMPLE_DESC TSampleDesc;

	interface ISample_Sync {
		virtual bool ISample_OnCount (const uint32_t _n_value) = 0;
		virtual bool ISample_OnQuality (const uint32_t _n_value) = 0;
	};

	class CSample {
	public:
		 CSample (const uint32_t _n_count = 1, const uint32_t _n_quality = 0); // at least 1(one) sample must be set;
		 CSample (ISample_Sync* const);
		 CSample (const CSample&);
		 CSample (CSample&&) = delete;
		~CSample (void) = default;

	public:
		uint32_t Count (void) const;
		bool     Count (const uint32_t);
		uint32_t Quality (void) const;
		bool     Quality (const uint32_t);

		bool  Is_valid (void) const; // returns 'true' in case when sample count does not equal to zero;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		bool Set (const uint32_t _n_count, const uint32_t _n_quality);

		const
		TSampleDesc& Raw (void) const;
		TSampleDesc& Raw (void) ;

		err_code Sync (ISample_Sync* const);

	public:
		CSample&  operator = (const CSample&);
		CSample&  operator = (CSample&&) = delete;

		CSample&  operator <<(const uint32_t _n_count);
		CSample&  operator >>(const uint32_t _n_quality);

		CSample&  operator <<(ISample_Sync* const);

		operator const TSampleDesc& (void) const;

	public:
#if (0)
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11device-checkmultisamplequalitylevels ;
		static err_code Get_quality(const TResFormat, const uint32_t _n_smp_count, uint32_t& _levels);
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_feature_data_multisample_quality_levels ; for DX12;
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-id3d12device-checkfeaturesupport ;
#endif
	private:
		TSampleDesc  m_desc;
		ISample_Sync* m_p_sync;
	};
	
	class CUInt32_Wrap {
	public:
		 CUInt32_Wrap (void) : m_value(0) {} CUInt32_Wrap (const CUInt32_Wrap& _src) { this->m_value = _src; }
		~CUInt32_Wrap (void) = default;

	public:
		const
		uint32_t& ref (void) const { return this->m_value; }
		uint32_t& ref (void)       { return this->m_value; }

		operator const uint32_t& (void) const { return this->ref(); }
		operator       uint32_t& (void)       { return this->ref(); }

	private:
		uint32_t m_value;
	};

	typedef ::std::shared_ptr<CUInt32_Wrap> TUint32Ptr;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_swap_chain_flag ;
	typedef DXGI_SWAP_CHAIN_FLAG TSwapFlag;

	class CSwapFlags {
	public:
		 CSwapFlags (void) = default; CSwapFlags (const CSwapFlags&) = delete; CSwapFlags (CSwapFlags&&) = delete;
		~CSwapFlags (void) = default;
#if defined(_DEBUG)
	public:
		CString  Print (const uint32_t _n_flags) const;
#endif
	private:
		CSwapFlags& operator = (const CSwapFlags&) = delete;
		CSwapFlags& operator = (CSwapFlags&&) = delete;
	};
}}}

#endif/*_DIRECT_X_SWAP_H_INCLUDED*/