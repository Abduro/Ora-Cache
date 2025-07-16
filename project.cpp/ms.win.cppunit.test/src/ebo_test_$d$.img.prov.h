#ifndef _EBO_TEST_$D$_IMG_PROV_H_INCLUDED
#define _EBO_TEST_$D$_IMG_PROV_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Jul-2025 at 01:03:26.469, UTC+4, Batumi, Thursday;
	This is Ebo Pack WinAPI GDI image cache data provider unit test interface declaration file;
*/
#include "ebo_test_$d$.img.defs.h"

namespace ebo { namespace boo { namespace test { namespace cache {

	using namespace ebo::boo::test::images;

	using TResult = ex_ui::draw::images::CResult;
	using TDataProvider = ex_ui::draw::images::CDataProvider;

	__class (CDataProvider) {
	public:
		 CDataProvider (const bool _b_verb = false);
		~CDataProvider (void) = default;

	public:
		__method (LoadFile);

	private:
		bool      m_b_verb;
		TDataProvider  m_prov;
	};

}}}}

#endif/*_EBO_TEST_$D$_IMG_PROV_H_INCLUDED*/