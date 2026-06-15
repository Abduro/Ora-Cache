/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jun-2026 at 13:22:45.309, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL viewport cache wrapper interface implementation file;
*/
#include "mouse.cache.h"
#include "sys.sync_obj.h"

using namespace ::win_api::mouse;
using CSyncObject = shared::sys_core::CSyncObject;

CSyncObject& MsgMouseRef(void) { static CSyncObject crt_sect; return crt_sect; }

#define Mouse_Safe_Lock() Safe_Lock(MsgMouseRef());

#pragma region cls::CCache{}

CCache::CCache (void) : m_cursor{0} {}

t_point CCache::CurPos (void) const {
	Mouse_Safe_Lock();
	return this->m_cursor;
}
void    CCache::CurPos (const int32_t _x, const uint32_t _y) {
	Mouse_Safe_Lock();
	this->m_cursor.x = _x;
	this->m_cursor.y = _y;
}

CCache& CCache::operator <<(const t_point& _cur_pos) {
	this->CurPos(_cur_pos.x, _cur_pos.y); return *this;
}

#pragma endregion

TMouseCache& ::Get_cursor (void) {
	static TMouseCache cache;
	return cache;
}