/*
	Createed by Tech_dog (ebontrop@gmail.com) on 02-Oct-2026 at 09:54:54.568, UTC+4, Batumi, Friday;
	This is installed IE version wrapper interface implementation file.
*/
#include "web.ie.emulate.h"
#include "sys.registry.h"

using namespace ::ex_ui::web::IE;

namespace ex_ui { namespace web { namespace IE { namespace _impl {

	class CReg_helper {
	public:
		 CReg_helper (void) {
		 }
		 CReg_helper (const CReg_helper&) = delete; CReg_helper (CReg_helper&&) = delete;
		~CReg_helper (void) {
		}

	private:
		CReg_helper& operator = (const CReg_helper&) = delete; CReg_helper& operator = (CReg_helper&&) = delete;
	};

}}}} using namespace ::ex_ui::web::IE::_impl;

#pragma region cls::CEmulate{} : 

CEmulate::CEmulate (_pc_sz _p_host) : m_host_name(_p_host) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

#pragma endregion