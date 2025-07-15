#ifndef _UIX_IMAGE_STREAM_H_INCLUDED
#define _UIX_IMAGE_STREAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2022 at 18:16:52.246 [the time stamp is not accurate], UTC+7, Novosibirsk, Thursday;
	This is image stream interface declaration file; [this declaration is made within 'Smart Diagram' project of ARQA Technologies]
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack image wrappers' project on 11-Jul-2025 at 22:01:56.684, UTC+4, Batumi, Friday;
*/
#include "uix.image.defs.h"

namespace ex_ui { namespace draw { namespace images {

	using CAlloc = shared::memory::CAllocator;

	typedef ::ATL::CComPtr<IStream> TStreamPtr;
	// https://learn.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-istream ;
	/*
		https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-createstreamonhglobal ;
		the excerpt from above article:
		CreateStreamOnHGlobal will accept a memory handle allocated with GMEM_FIXED, but this usage is not recommended.
		the above statement is taken into account and CAllocator prohibits of using fixed size memory block;
	*/
	class CStream {
	public:
		 CStream (void); CStream (const CStream&) = delete; CStream (CStream&&) = delete;
		~CStream (void);
	public:
		err_code  Create (const CAlloc&);        // creates a stream from the input global memory block;
		err_code  Create (_pc_sz _p_file_path);  // this method requires to save global memory block till this stream object will be unused;
		err_code  Destroy(void) ;
		TError&   Error  (void) const;

		bool    Is_valid (void) const;

#if defined(_DEBUG)
		CString   Print  (const e_print = e_print::e_all) const;
#endif
		const
		TStreamPtr&  Ptr (void) const;
		TStreamPtr&  Ptr (void) ;

	private: CStream& operator = (const CStream&) = delete; CStream& operator = (CStream&&) = delete;
	private:
		CAlloc m_alloc;  // used for temporarily implementation;
		CError m_error;
		TStreamPtr m_p_stream;
	};
}}}

#endif/*_UIX_IMAGE_STREAM_H_INCLUDED*/