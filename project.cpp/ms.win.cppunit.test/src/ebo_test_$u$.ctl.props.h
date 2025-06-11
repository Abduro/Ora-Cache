#ifndef _EBO_TEST_$U$_CTL_PROPS_H_INCLUDED
#define _EBO_TEST_$U$_CTL_PROPS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jun-2025 at 09:51:42.841, UTC+4, Batumi, Wednesday;
	This is Ebo Pack user control base property set unit test interface declaration file; 
*/
#include "ebo_test_$u$.ctl.base.h"

namespace ebo { namespace boo { namespace test { namespace ctl {
namespace props {

	using TAling = ex_ui::controls::properties::CAlign;
	
	__class (CAlign) {
	public:
		 CAlign (const bool _b_verb = false);
		~CAlign (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool    m_b_verb;
		TAling  m_align ;
	};

	using THAling = ex_ui::controls::properties::CAlign_Horz;
	
	__class (CAlign_Horz) {
	public:
		 CAlign_Horz (const bool _b_verb = false);
		~CAlign_Horz (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool    m_b_verb;
		THAling m_horz;
	};

	using TVAling = ex_ui::controls::properties::CAlign_Vert;
	
	__class (CAlign_Vert) {
	public:
		 CAlign_Vert (const bool _b_verb = false);
		~CAlign_Vert (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool    m_b_verb;
		TVAling m_vert;
	};

	using TProperty = ex_ui::controls::properties::CProperty;

	__class (CProperty) {
	public:
		 CProperty (const bool _b_verb = false);
		~CProperty (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool    m_b_verb;
		TProperty  m_prop;
	};
}
}}}}

#endif/*_EBO_TEST_$U$_CTL_PROPS_H_INCLUDED*/