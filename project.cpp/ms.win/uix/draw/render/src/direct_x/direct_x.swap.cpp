/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr_2025 at 21:19:33.068, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX swap chain component wrapper interface implementation file;
*/
#include "direct_x.swap.h"

using namespace ex_ui::draw::direct_x;

using CBuffer = CSwapDesc::CBuffer;
/////////////////////////////////////////////////////////////////////////////

CBuffer:: CBuffer (TSwapDesc& _desc) : m_desc(_desc) { m_desc.BufferCount = 0; m_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; }
CBuffer:: CBuffer (const CBuffer& _src) : CBuffer(_src.m_desc) { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

uint32_t  CBuffer::Count (void) const { return this->m_desc.BufferCount; }
bool      CBuffer::Count (const uint32_t _n_count) {
	const bool b_changed = (this->Count() != _n_count); if (b_changed) this->m_desc.BufferCount = _n_count; return b_changed;
}

uint32_t  CBuffer::Usage (void) const { return this->m_desc.BufferUsage; }
bool      CBuffer::Usage (const uint32_t _n_usage) {
	const bool b_changed = (this->Usage() != _n_usage); if (b_changed) this->m_desc.BufferUsage = _n_usage; return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CBuffer&  CBuffer::operator = (const CBuffer& _src) { *this << _src.Count() >> _src.Usage(); return *this; }
CBuffer&  CBuffer::operator <<(const uint32_t _n_count) { this->Count(_n_count); return *this; }
CBuffer&  CBuffer::operator >>(const uint32_t _n_usage) { this->Usage(_n_usage); return *this; }

/////////////////////////////////////////////////////////////////////////////

using CSample = CSwapDesc::CSample;

CSample::CSample (TSwapDesc& _desc) : m_desc(_desc) { this->m_desc.SampleDesc.Count = 1; this->m_desc.SampleDesc.Quality = 0; }
CSample::CSample (const CSample& _src) : CSample(_src.m_desc) { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

uint32_t  CSample::Count (void) const { return this->m_desc.SampleDesc.Count; }
bool      CSample::Count (const uint32_t _n_value) {
	const bool b_changed = (this->Count() != _n_value); if (b_changed) this->m_desc.SampleDesc.Count = _n_value; return b_changed;
}
uint32_t  CSample::Quality (void) const { return this->m_desc.SampleDesc.Quality; }
bool      CSample::Quality (const uint32_t _n_value) {
	const bool b_changed = (this->Quality() != _n_value); if (b_changed) this->m_desc.SampleDesc.Quality = _n_value; return b_changed;
}

bool CSample::Set (const uint32_t _n_count, const uint32_t _n_quality) {
	bool b_changed = false;

	if (this->Count(_n_count)) b_changed = true;
	if (this->Quality(_n_quality)) b_changed = true;

	return b_changed;
}

const
TSampleDesc& CSample::Raw (void) const { return this->m_desc.SampleDesc; }
TSampleDesc& CSample::Raw (void) { return this->m_desc.SampleDesc; }

/////////////////////////////////////////////////////////////////////////////

using CSize = CSwapDesc::CSize;

CSize:: CSize (TSwapDesc& _desc) : m_desc(_desc) { this->m_desc.Height = this->m_desc.Width = 0; }
CSize:: CSize (const CSize& _src) : CSize(_src.m_desc) { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

uint32_t CSize::Height (void) const { return this->H(); }
bool     CSize::Height (const uint32_t _n_value) { return this->H(_n_value); }

uint32_t CSize::H (void) const { return this->m_desc.Height; }
bool     CSize::H (const uint32_t _n_value) {
	const bool b_changed = (this->H() != _n_value); if (b_changed) this->m_desc.Height = _n_value; return b_changed;
}

uint32_t CSize::Width (void) const { return this->W(); }
bool     CSize::Width (const uint32_t _n_value) { return this->W(_n_value); }

uint32_t CSize::W (void) const { return this->m_desc.Width; }
bool     CSize::W (const uint32_t _n_value) {
	const bool b_changed = (this->W() != _n_value); if (b_changed) this->m_desc.Width = _n_value; return b_changed;
}

bool     CSize::Set (const uint32_t _n_width, const uint32_t _n_height) {
	bool b_changed = false;
	if (this->H(_n_height)) b_changed = true;
	if (this->W(_n_width)) b_changed = true;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CSize&  CSize::operator = (const CSize& _src) { *this << _src.W() >> _src.H(); return *this; }
CSize&  CSize::operator <<(const uint32_t _n_width) { this->W(_n_width); return *this; }
CSize&  CSize::operator >>(const uint32_t _n_height) { this->H(_n_height); return *this; }

/////////////////////////////////////////////////////////////////////////////

CSwapDesc:: CSwapDesc (void) : m_desc{0}, m_buffer(m_desc), m_size(m_desc), m_sample(m_desc) {}
CSwapDesc:: CSwapDesc (const CSwapDesc& _src) : CSwapDesc() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////
const
CBuffer&    CSwapDesc::Buffer (void) const { return this->m_buffer; }
CBuffer&    CSwapDesc::Buffer (void)       { return this->m_buffer; }
const
TSwapDesc&  CSwapDesc::Raw (void) const { return this->m_desc; }
TSwapDesc&  CSwapDesc::Raw (void)       { return this->m_desc; }
const
CSample&    CSwapDesc::Sample (void) const { return this->m_sample; }
CSample&    CSwapDesc::Sample (void)       { return this->m_sample; }
const
CSize&  CSwapDesc::Size (void) const { return this->m_size; }
CSize&  CSwapDesc::Size (void)       { return this->m_size; }

/////////////////////////////////////////////////////////////////////////////

CSwapDesc&  CSwapDesc::operator = (const CSwapDesc& _src) { *this <<_src.Raw(); return *this; }
CSwapDesc&  CSwapDesc::operator <<(const TSwapDesc& _raw) {  this->Raw() = _raw; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSwapChain:: CSwapChain (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CSwapChain:: CSwapChain (const CSwapChain& _src) : CSwapChain() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

TError&  CSwapChain::Error (void) const { return this->m_error; }
bool     CSwapChain::Is_valid (void) const { return (nullptr != this->Ptr()); }
const
TSwapPtr&    CSwapChain::Ptr (void) const { return this->m_p_swap; }
TSwapPtr&    CSwapChain::Ptr (void)       { return this->m_p_swap; }

/////////////////////////////////////////////////////////////////////////////

CSwapChain&  CSwapChain::operator = (const CSwapChain& _src) { *this << _src.Ptr(); return *this; }
CSwapChain&  CSwapChain::operator <<(const TSwapPtr& _p_swap) { this->Ptr() = _p_swap; return *this; }