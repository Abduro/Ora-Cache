/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr_2025 at 21:19:33.068, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX swap chain component wrapper interface implementation file;
*/
#include "direct_x.swap.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

CAlphaMode:: CAlphaMode (void) : m_mode(e_mode::e_unspec) {}
CAlphaMode:: CAlphaMode (const TSwapDescPtr& _p_desc) : m_desc(_p_desc), m_mode(e_mode::e_unspec) {}
CAlphaMode:: CAlphaMode (const CAlphaMode& _src) : CAlphaMode() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

uint32_t  CAlphaMode::Get (void) const { return this->m_mode; }
bool      CAlphaMode::Set (const uint32_t _n_value) {
	const bool b_changed = (this->Get() != _n_value);
	if (b_changed) {
		this->m_mode = _n_value;
		if (this->Sync())
			this->Sync()->AlphaMode = static_cast<TAlphaMode>(_n_value);
	}
	return b_changed;
}

const
TSwapDescPtr& CAlphaMode::Sync (void) const { return this->m_desc; }
TSwapDescPtr& CAlphaMode::Sync (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////

CAlphaMode&  CAlphaMode::operator = (const CAlphaMode& _src) { *this << _src.Sync(); return *this; }
CAlphaMode&  CAlphaMode::operator <<(uint32_t _n_mode) { this->Set(_n_mode); return *this; }
CAlphaMode&  CAlphaMode::operator <<(const TSwapDescPtr& _p_sync) { this->Sync() = _p_sync; return *this; }

/////////////////////////////////////////////////////////////////////////////

CBuffer:: CBuffer (const uint32_t _n_count, const uint32_t _n_usage) : m_count(_n_count), m_usage(_n_usage) {}
CBuffer:: CBuffer (const CBuffer& _src) : CBuffer() { *this = _src; }
CBuffer:: CBuffer (const TSwapDescPtr& _p_desc) : CBuffer() { *this << _p_desc;}

/////////////////////////////////////////////////////////////////////////////

uint32_t  CBuffer::Count (void) const { return this->m_count; }
bool      CBuffer::Count (const uint32_t _n_value) {
	const bool b_changed = (this->Count() != _n_value);
	if (b_changed) {
		this->m_count = _n_value;
		if (this->Sync())
			this->Sync()->BufferCount = _n_value;
	}
	return b_changed;
}

uint32_t  CBuffer::Usage (void) const { return this->m_usage; }
bool      CBuffer::Usage (const uint32_t _n_value) {
	const bool b_changed = (this->Usage() != _n_value);
	if (b_changed) {
		this->m_usage = _n_value;
		if (this->Sync())
			this->Sync()->BufferUsage = _n_value;
	}
	return b_changed;
}

bool CBuffer::Is_valid (void) const { return (!!this->Count() && !!this->Usage()); }

bool CBuffer::Set (const uint32_t _n_count, const uint32_t _n_usage) {
	bool b_changed = false;

	if (this->Count(_n_count)) b_changed = true;
	if (this->Usage(_n_usage)) b_changed = true;

	return b_changed;
}

const
TSwapDescPtr& CBuffer::Sync (void) const { return this->m_desc; }
TSwapDescPtr& CBuffer::Sync (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////

CBuffer&  CBuffer::operator = (const CBuffer& _src) { *this << _src.Count() >> _src.Usage(); return *this; }
CBuffer&  CBuffer::operator <<(const uint32_t _n_count) { this->Count(_n_count); return *this; }
CBuffer&  CBuffer::operator >>(const uint32_t _n_usage) { this->Usage(_n_usage); return *this; }

CBuffer&  CBuffer::operator <<(const TSwapDescPtr& _p_desc) { this->Sync() = _p_desc; return *this; }

/////////////////////////////////////////////////////////////////////////////

CEffect:: CEffect (void) : m_value(e_value::e_flp_seq) {}
CEffect:: CEffect (const CEffect& _src) : CEffect() { *this = _src; }
CEffect:: CEffect (const TSwapDescPtr& _p_desc) : CEffect() { *this << _p_desc; }

/////////////////////////////////////////////////////////////////////////////

uint32_t CEffect::Get (void) const { return this->m_value; }
bool     CEffect::Set (const uint32_t _n_value) {
	const bool b_changed = (this->Get() != _n_value);
	if (b_changed) {
		this->m_value = static_cast<e_value>(_n_value);
		if (this->Sync())
			this->Sync()->SwapEffect = static_cast<TEffect>(_n_value);
	}
	return b_changed;
}
const
TSwapDescPtr& CEffect::Sync (void) const { return this->m_desc; }
TSwapDescPtr& CEffect::Sync (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////

CEffect&  CEffect::operator = (const CEffect& _src) { *this << _src.Get() << _src.Sync(); return *this; }

CEffect&  CEffect::operator <<(const TSwapDescPtr& _p_desc) { this->Sync() = _p_desc; return *this; }
CEffect&  CEffect::operator <<(const uint32_t _n_effect) { this->Set(_n_effect); return *this; }

/////////////////////////////////////////////////////////////////////////////

CPxFormat:: CPxFormat (void) {}
CPxFormat:: CPxFormat (const CPxFormat& _src) : CPxFormat() { *this = _src; }
CPxFormat:: CPxFormat (const TSwapDescPtr& _p_desc) : CPxFormat() { *this << _p_desc; }

/////////////////////////////////////////////////////////////////////////////
const
CAlphaMode& CPxFormat::Alpha (void) const { return this->m_alpha; }
CAlphaMode& CPxFormat::Alpha (void)       { return this->m_alpha; }

uint32_t    CPxFormat::Format (void) const { return this->m_format; }
bool        CPxFormat::Format (const TResFormat _n_value) {
	const bool b_changed = (this->Format() != static_cast<uint32_t>(_n_value));
	if (b_changed) {
		this->m_format = _n_value;
		if (this->Sync())
			this->Sync()->Format = _n_value;
	}
	return b_changed;
}

TPxFormat   CPxFormat::Raw (void) const {

	TPxFormat raw_ = { (TResFormat) this->Format(), (TAlphaMode_2) this->Alpha().Get() };
	return raw_;
}

const
TSwapDescPtr& CPxFormat::Sync (void) const { return this->m_desc; }
TSwapDescPtr& CPxFormat::Sync (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////

CPxFormat&  CPxFormat::operator = (const CPxFormat& _src) { *this << _src.Alpha() << (TResFormat)_src.Format() << _src.Sync(); return *this; }
CPxFormat&  CPxFormat::operator <<(const CAlphaMode& _alpha) { this->Alpha() = _alpha; return *this; }
CPxFormat&  CPxFormat::operator <<(const TResFormat _value) { this->Format(_value); return *this; }
CPxFormat&  CPxFormat::operator <<(const TSwapDescPtr& _p_desc) { this->Sync() = _p_desc; this->Alpha().Sync() = _p_desc; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSample:: CSample (void) : m_desc{0} {}
CSample:: CSample (const CSample& _src) : CSample() { *this = _src; }
CSample:: CSample (const TSwapDescPtr& _p_desc) : CSample() { *this << _p_desc; }

/////////////////////////////////////////////////////////////////////////////

uint32_t  CSample::Count (void) const { return this->Raw().Count; }
bool      CSample::Count (const uint32_t _n_value) {
	const bool b_changed = (this->Count() != _n_value);
	if (b_changed) {
		this->Raw().Count = _n_value;
		if (this->Sync())
			this->Sync()->SampleDesc.Count = _n_value;
	}
	return b_changed;
}
uint32_t  CSample::Quality (void) const { return this->Raw().Quality; }
bool      CSample::Quality (const uint32_t _n_value) {
	const bool b_changed = (this->Quality() != _n_value);
	if (b_changed) {
		this->Raw().Quality = _n_value;
		if (this->Sync())
			this->Sync()->SampleDesc.Quality = _n_value;
	}
	return b_changed;
}

bool CSample::Set (const uint32_t _n_count, const uint32_t _n_quality) {
	bool b_changed = false;

	if (this->Count(_n_count)) b_changed = true;
	if (this->Quality(_n_quality)) b_changed = true;

	return b_changed;
}

const
TSampleDesc& CSample::Raw (void) const { return this->m_desc; }
TSampleDesc& CSample::Raw (void)       { return this->m_desc; }

const
TSwapDescPtr& CSample::Sync (void) const { return this->m_p_sync; }
TSwapDescPtr& CSample::Sync (void)       { return this->m_p_sync; }

/////////////////////////////////////////////////////////////////////////////

CSample&  CSample::operator = (const CSample& _src) { *this << _src.Count() >> _src.Quality() << _src.Sync(); return *this; } // instead of assigning Count() and Quality() it is just enough to set Raw();
CSample&  CSample::operator <<(const uint32_t _n_count) { this->Count(_n_count); return *this; }
CSample&  CSample::operator >>(const uint32_t _n_quality) { this->Quality(_n_quality); return *this; }

CSample&  CSample::operator <<(const TSwapDescPtr& _p_sync) { this->Sync() = _p_sync; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSize:: CSize (void) : m_size{0} {}
CSize:: CSize (const CSize& _src) : CSize() { *this = _src; }
CSize:: CSize (const TSwapDescPtr& _p_sync) : CSize() { *this << _p_sync; }

/////////////////////////////////////////////////////////////////////////////

uint32_t CSize::Height (void) const { return this->H(); }
bool     CSize::Height (const uint32_t _n_value) { return this->H(_n_value); }

uint32_t CSize::H (void) const { return this->Raw().height; }
bool     CSize::H (const uint32_t _n_value) {
	const bool b_changed = (this->H() != _n_value);
	if (b_changed) {
		this->Raw().height = _n_value;
		if (this->Sync())
			this->Sync()->Height = _n_value;
	}
	return b_changed;
}

uint32_t CSize::Width (void) const { return this->W(); }
bool     CSize::Width (const uint32_t _n_value) { return this->W(_n_value); }

uint32_t CSize::W (void) const { return this->Raw().width; }
bool     CSize::W (const uint32_t _n_value) {
	const bool b_changed = (this->W() != _n_value);
	if (b_changed) {
		this->Raw().width = _n_value;
		if (this->Sync())
			this->Sync()->Width = _n_value;
	}
	return b_changed;
}

bool     CSize::Set (const uint32_t _n_width, const uint32_t _n_height) {
	bool b_changed = false;
	if (this->H(_n_height)) b_changed = true;
	if (this->W(_n_width)) b_changed = true;
	return b_changed;
}

const
TSize_U& CSize::Raw (void) const { return this->m_size; }
TSize_U& CSize::Raw (void)       { return this->m_size; }

const
TSwapDescPtr& CSize::Sync (void) const { return this->m_p_sync; }
TSwapDescPtr& CSize::Sync (void)       { return this->m_p_sync; }

/////////////////////////////////////////////////////////////////////////////

CSize&  CSize::operator = (const CSize& _src) { *this << _src.Raw() << _src.Sync(); return *this; }
CSize&  CSize::operator <<(const uint32_t _n_width) { this->W(_n_width); return *this; }
CSize&  CSize::operator >>(const uint32_t _n_height) { this->H(_n_height); return *this; }

CSize&  CSize::operator <<(const TSize_U& _size) { this->Raw() = _size; return *this; }
CSize&  CSize::operator <<(const TSwapDescPtr& _p_sync) { this->Sync() = _p_sync; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSwapDesc:: CSwapDesc (void) :  m_desc{0}, m_sync(&m_desc), m_alpha(m_sync), m_buffer(m_sync), m_effect(m_sync), m_format(m_sync), m_sample(m_sync), m_size(m_sync){}
CSwapDesc:: CSwapDesc (const CSwapDesc& _src) : CSwapDesc() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////
const
CAlphaMode& CSwapDesc::Alpha (void) const { return this->m_alpha; }
CAlphaMode& CSwapDesc::Alpha (void)       { return this->m_alpha; }
const
CBuffer&    CSwapDesc::Buffer (void) const { return this->m_buffer; }
CBuffer&    CSwapDesc::Buffer (void)       { return this->m_buffer; }
const
CEffect&    CSwapDesc::Effect (void) const { return this->m_effect; }
CEffect&    CSwapDesc::Effect (void)       { return this->m_effect; }
const
CPxFormat&  CSwapDesc::Format (void) const { return this->m_format; }
CPxFormat&  CSwapDesc::Format (void)       { return this->m_format; }
const
TSwapDesc&  CSwapDesc::Raw (void) const { return this->m_desc; }
TSwapDesc&  CSwapDesc::Raw (void)       { return this->m_desc; }
const
CSample&    CSwapDesc::Sample (void) const { return this->m_sample; }
CSample&    CSwapDesc::Sample (void)       { return this->m_sample; }
const
CSize&  CSwapDesc::Size (void) const { return this->m_size; }
CSize&  CSwapDesc::Size (void)       { return this->m_size; }

bool  CSwapDesc::Stereo (void) const { return this->m_desc.Stereo; }
bool  CSwapDesc::Stereo (const bool _b_value) {
	const bool b_changed = (this->Stereo() != _b_value);
	if (b_changed)
		this->m_desc.Stereo = _b_value;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CSwapDesc&  CSwapDesc::operator = (const CSwapDesc& _src) { *this <<_src.Raw(); return *this; }
CSwapDesc&  CSwapDesc::operator <<(const TSwapDesc& _raw) {  this->Raw() = _raw; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSwapChain:: CSwapChain (void) : m_target(nullptr) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CSwapChain:: CSwapChain (const CSwapChain& _src) : CSwapChain() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

TError&  CSwapChain::Error (void) const { return this->m_error; }
bool     CSwapChain::Is_valid (void) const { return (nullptr != this->Ptr()); }
const
TChainPtr& CSwapChain::Ptr (void) const { return this->m_p_chain; }
TChainPtr& CSwapChain::Ptr (void)       { return this->m_p_chain; }

const
CCmdQueue& CSwapChain::Queue (void) const { return this->m_queue; }
CCmdQueue& CSwapChain::Queue (void)       { return this->m_queue; }

HWND CSwapChain::Target (void) const { return this->m_target; }
bool CSwapChain::Target (const HWND _h_target) {
	if (nullptr == _h_target || !::IsWindow(_h_target))
		return false;
	this->m_target = _h_target;
	return true;
}

/////////////////////////////////////////////////////////////////////////////

CSwapChain&  CSwapChain::operator = (const CSwapChain& _src) { *this << _src.Ptr(); return *this; }
CSwapChain&  CSwapChain::operator <<(const TChainPtr& _p_chain) { this->Ptr() = _p_chain; return *this; }