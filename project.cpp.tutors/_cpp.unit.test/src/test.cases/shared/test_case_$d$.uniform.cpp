/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Jan-2026 at 14:40:29.234, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL uniform data type wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.uniform.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::CUni_enum{}

CUni_enum::CUni_enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

uint32_t CUni_enum::Count (const uint32_t _prog_id) {
	this->m_error <<__METHOD__<<__s_ok; return CUni_enum::Count(_prog_id, this->m_error);
}
uint32_t CUni_enum::Count (const uint32_t _prog_id, CError& _err) {
	return CUniEnum::Count(_prog_id, _err);
}

TError&  CUni_enum::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CUni_form{}

CUni_form::CUni_form (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CUni_form::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CUni_value{}

CUni_value::CUni_value (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CUni_value::Error (void) const { return this->m_error; }

#pragma endregion