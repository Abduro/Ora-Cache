/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr-2025 at 22:25:25.260, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX command queue wrapper interface implementation file;
*/
#include "direct_x.queue.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

CCmdQueue:: CCmdQueue (void) : m_desc{0} {
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

	this->Desc().Flags = TCmdQueFlags::D3D12_COMMAND_QUEUE_FLAG_NONE;
	this->Desc().Type  = TCmdLstType::D3D12_COMMAND_LIST_TYPE_DIRECT;
}
CCmdQueue:: CCmdQueue (const CCmdQueue& _src) : CCmdQueue() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////
const
TCmdQueDesc& CCmdQueue::Desc (void) const { return this->m_desc; }
TCmdQueDesc& CCmdQueue::Desc (void)       { return this->m_desc; }

TError&   CCmdQueue::Error (void) const { return this->m_error; }
bool      CCmdQueue::Is_valid (void) const { return (nullptr != this->Ptr()); }
const
TCmdQuePtr&  CCmdQueue::Ptr (void) const { return this->m_p_queue; }
TCmdQuePtr&  CCmdQueue::Ptr (void)       { return this->m_p_queue; }

/////////////////////////////////////////////////////////////////////////////

CCmdQueue&  CCmdQueue::operator = (const CCmdQueue& _src) { *this << _src.Ptr() << _src.Desc(); return *this; }

CCmdQueue&  CCmdQueue::operator <<(const TCmdQueDesc& _desc) { this->Desc() = _desc; return *this; }
CCmdQueue&  CCmdQueue::operator <<(const TCmdQuePtr& _p_queue) { this->Ptr() = _p_queue; return *this; }