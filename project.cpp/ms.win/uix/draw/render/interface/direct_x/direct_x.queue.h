#ifndef _DIRECT_X_QUEUE_H_INCLUDED
#define _DIRECT_X_QUEUE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr-2025 at  , UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX command queue wrapper interface declaration file;
*/
#include "direct_x._iface.h"

namespace ex_ui { namespace draw { namespace direct_x {

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12commandqueue ;
	typedef ::ATL::CComPtr<ID3D12CommandQueue> TCmdQuePtr;
	typedef D3D12_COMMAND_LIST_TYPE   TCmdLstType ;
	typedef D3D12_COMMAND_QUEUE_DESC  TCmdQueDesc ;
	typedef D3D12_COMMAND_QUEUE_FLAGS TCmdQueFlags;

	class CCmdQueue {
	public:
		 CCmdQueue (void);
		 CCmdQueue (const CCmdQueue&);
		 CCmdQueue (CCmdQueue&&) = delete; // not required yet;
		~CCmdQueue (void) = default;

	public:
		const
		TCmdQueDesc& Desc (void) const;
		TCmdQueDesc& Desc (void) ;

		TError&   Error (void) const;
		bool   Is_valid (void) const;

		const
		TCmdQuePtr&  Ptr (void) const;
		TCmdQuePtr&  Ptr (void) ;

	public:
		CCmdQueue& operator = (const CCmdQueue&);
		CCmdQueue& operator = (CCmdQueue&&) = delete; // not required yet;

		CCmdQueue& operator <<(const TCmdQueDesc&);
		CCmdQueue& operator <<(const TCmdQuePtr&);

	private:
		CError m_error;
		TCmdQuePtr  m_p_queue;
		TCmdQueDesc m_desc;
	};

}}}

#endif/*_DIRECT_X_QUEUE_H_INCLUDED*/