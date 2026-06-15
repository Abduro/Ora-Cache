#ifndef _MOUSE_CACHE_H_INCLUDED
#define _MOUSE_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jun-2026 at 13:19:27.377, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL viewport cache wrapper interface declaration file;
*/
#include "drawable.defs.h"

namespace win_api { namespace mouse { using namespace shared::defs;

	class CCache {
	public:
		CCache (void); CCache (const CCache&) = delete; CCache (CCache&&) = delete; ~CCache (void) = default;

		t_point  CurPos (void) const;
		void     CurPos (const int32_t _x, const uint32_t _y);

		CCache& operator <<(const t_point& _cur_pos);
	private:
		CCache& operator = (const CCache&) = delete; CCache& operator = (CCache&&) = delete;
		t_point m_cursor; // this is the last position of the mouse cursor at the moment of mouse message handling;
	};

}}

typedef win_api::mouse::CCache TMouseCache; TMouseCache& Get_cursor (void);

#endif/*_MOUSE_CACHE_H_INCLUDED*/