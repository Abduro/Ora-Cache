/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Jul-2026 at 19:15:48.811, UTC+4, Batumi, Wednesday;
	This is 3D module object file parser interface implementation file;
*/
#include "obj_parser.self.h"

using namespace shared::parsers::obj;

#pragma region cls::CParser{}

CParser::CParser (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CParser::Do (const FILE* _p_file) {
	_p_file;
	this->m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_file)
		return this->m_error <<__e_pointer = _T("Invalid file stream pointer");

	FILE* p_pos = const_cast<FILE*>(_p_file);

	int ch = 0;
	while(!::feof(p_pos)) {
		ch = ::fgetc(p_pos); // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fgetc-fgetwc ;
	switch (ch) {
	case 'v' : break;
	case 'f' : break;
	case '\n': break;
	default:;
	}}

	return this->Error();
}

TError&  CParser::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CSpecifier{}

using e_type = CSpecifier::e_type;

e_type CSpecifier::Get (FILE* const _p_pos) const {
	_p_pos;
	if (_p_pos == nullptr)
		return e_type::e_undef;

	int ch = ::fgetc(_p_pos); // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fgetc-fgetwc ;
	ch;
	return e_type::e_undef;
}


#pragma endregion