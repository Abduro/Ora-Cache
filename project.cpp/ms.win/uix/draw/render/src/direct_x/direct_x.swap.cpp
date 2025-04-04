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

CSwapDesc:: CSwapDesc (void) : m_desc{0}, m_buffer(m_desc) {}
CSwapDesc:: CSwapDesc (const CSwapDesc& _src) : CSwapDesc() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////
const
CBuffer&    CSwapDesc::Buffer (void) const { return this->m_buffer; }
CBuffer&    CSwapDesc::Buffer (void)       { return this->m_buffer; }
const
TSwapDesc&  CSwapDesc::Raw (void) const { return this->m_desc; }
TSwapDesc&  CSwapDesc::Raw (void)       { return this->m_desc; }

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