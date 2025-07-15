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

	class CStream {
	public:
		 CStream (void); CStream (const CStream&) = delete; CStream (CStream&&) = delete;
		~CStream (void);
	public:
		err_code  Create (_pc_sz _p_file_path);

		TError&   Error  (void) const;

	private: CStream& operator = (const CStream&) = delete; CStream& operator = (CStream&&) = delete;
	private:
		CError  m_error;
	};
}}}

#endif/*_UIX_IMAGE_STREAM_H_INCLUDED*/