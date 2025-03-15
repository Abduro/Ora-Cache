/*
	Created by Tech_dog (ebontrop@gmail.com) on 2-Apr-2024 at 09:38:48.4917163, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX libs unit test common defenitions' implementation file;
*/
#include "_defs.h"

using namespace ebo::boo::test;

/////////////////////////////////////////////////////////////////////////////

void _apr_02_2024_t_09_38_48_a(void) {}

namespace ebo { namespace boo { namespace test {

#if defined WIN64
	uint64_t __address_of (const void* const _p_fun_ptr) {
		_p_fun_ptr;
		const
		uint64_t* p_address = reinterpret_cast<const uint64_t*>(_p_fun_ptr);
		uint64_t  n_address = (!!p_address ? *p_address : 0);
		return n_address;
	}
#else
	uint32_t __address_of (const void* const _p_fun_ptr) {
		_p_fun_ptr;
		const
		uint32_t* p_address = reinterpret_cast<const uint32_t*>(_p_fun_ptr);
		uint32_t  n_address = (!!p_address ? *p_address : 0);
		return n_address;
	}
#endif

}}}