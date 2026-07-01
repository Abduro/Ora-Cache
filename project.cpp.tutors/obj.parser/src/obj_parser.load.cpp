/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jul-2026 at 20:17:59.904, UTC+4, Batumi, Wednesday;
	This is 3D module object file loader interface implementation file;
*/
#include "obj_parser.load.h"

using namespace ::shared::parsers::obj;


#pragma region cls::CLoader{}

CLoader::CLoader (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_false = _T("No object file is loaded yet"); }

TError&  CLoader::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CLocator{}

CLocator::CLocator (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_false = _T("No object file is loaded yet"); }

TError&  CLocator::Error (void) const { return this->m_error; }

#pragma endregion