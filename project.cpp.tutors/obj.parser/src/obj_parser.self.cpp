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
#pragma region cls::CPrefx{}

CPrefx::CPrefx (void) : m_type(e_pfx_type::e_undef) {}
CPrefx::CPrefx (const CPrefx& _src) : CPrefx() { *this = _src; }
CPrefx::CPrefx (const e_pfx_type _type, _pc_sz _p_spec) : m_type(_type), m_spec(_p_spec) {}

const
CStringA&  CPrefx::Spec (void) const { return this->m_spec; }
CStringA&  CPrefx::Spec (void)       { return this->m_spec; }

e_pfx_type CPrefx::Type (void) const { return this->m_type; }
err_code   CPrefx::Type (const e_pfx_type _type) {
	_type;
	this->m_type = _type; return e_pfx_type::e_undef == _type ? __e_inv_arg : __s_ok;
}

CPrefx& CPrefx::operator = (const CPrefx& _src) { *this << _src.Type() << _src.Spec(); return *this; }
CPrefx& CPrefx::operator <<(const char* _p_spec) { this->Spec() = _p_spec; return *this; }
CPrefx& CPrefx::operator <<(const e_pfx_type _type) { this->Type(_type); return *this; }

#pragma endregion
#pragma region cls::CPrefx_enum{}

CPrefx_enum::CPrefx_enum (void) { this->Init(); }

static CPrefx pfx_inv;

const
CPrefx&  CPrefx_enum::Get (FILE* const _p_pos) {
	_p_pos;
	if (nullptr == _p_pos)
		return pfx_inv;

	const int ch = ::fgetc(_p_pos); // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fgetc-fgetwc ;
	// for some values of the first symbol/letter there is no sense to know the next symbol;
	switch (ch) {
	case '#': return this->m_prefxs.at(size_t(e_pfx_type::e_comm));
	case 'f': return this->m_prefxs.at(size_t(e_pfx_type::e_face));
	case 'g': return this->m_prefxs.at(size_t(e_pfx_type::e_group));
	case 'm': return this->m_prefxs.at(size_t(e_pfx_type::e_mtl));
	case 'u': return this->m_prefxs.at(size_t(e_pfx_type::e_use_mtl));
	case 'v': { // this letter value requires to get the next symbol(s);
	
	} break;
	}
	return pfx_inv;
}

err_code CPrefx_enum::Init (void) {

	for (uint32_t i_ = 0; i_ < this->m_prefxs.size() && i_ < _countof(p_prfx); i_++) { // it is supposed p_prfx array has appropriate size;
		CPrefx& prfx = this->m_prefxs.at(i_);
		prfx << static_cast<e_pfx_type>(i_) << p_prfx[i_]; // https://stackoverflow.com/questions/11452920/how-to-cast-int-to-enum-in-c ;
	}
	return __s_ok; // no error catching yet;
}

#pragma endregion

TPrefxs& ::Get_prefxs (void) {
	static TPrefxs prefxs;
	return  prefxs;
}