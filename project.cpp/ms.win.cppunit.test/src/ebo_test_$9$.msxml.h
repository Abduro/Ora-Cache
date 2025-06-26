#ifndef _EBO_TEST_$9$_MSXML_H_INCLUDED
#define _EBO_TEST_$9$_MSXML_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jun-2025 at 03:46:48.903, UTC+4, Batumi, Wednesday;
	This is Ebo Pack MSXML wrapper lib unit test interface declaration file; 
*/
#include "_log.h"

#include "msxml.base.h"
#include "msxml.doc.h"
#include "msxml.error.h"
#include "msxml.ntfs.h"

namespace ebo { namespace boo { namespace test { namespace xml {

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	using TErr_Desc  = shared::xml::ms::CErr_Desc;
	using TErr_Pos   = shared::xml::ms::CErr_Pos ;
	using TPrs_Error = shared::xml::ms::CParseError;

	__class (CErr_Desc) {
	public:
		 CErr_Desc (const bool _b_verb = false);
		~CErr_Desc (void) = default;

	public:
		__ctor (_ctor);
		__method (Set); // this is direct setting values to the error details object; no raw parse error interface is applied;

	private:
		bool    m_b_verb;
		TErr_Desc m_err_desc;
	};

	__class (CErr_Pos) {
	public:
		 CErr_Pos (const bool _b_verb = false);
		~CErr_Pos (void) = default;

	public:
		__ctor (_ctor);
		__method (Set); // this is direct setting values to the error position object; no raw parse error interface is applied;

	private:
		bool    m_b_verb;
		TErr_Pos m_err_pos;
	};

	__class (CParseError) {
	public:
		 CParseError (const bool _b_verb = false);
		~CParseError (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool    m_b_verb;
		TPrs_Error m_prs_err;
	};

	using TServiceId = shared::xml::ms::CServiceId;

	__class (CServiceId) {
	public:
		 CServiceId (const bool _b_verb = false);
		~CServiceId (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool    m_b_verb;
		TServiceId m_svc_id;
	};

	using TSvc_Ids = shared::xml::ms::CSvc_Ids;

	__class(CSvc_Ids) {
	public:
		 CSvc_Ids (const bool _b_verb = false);
		~CSvc_Ids (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool     m_b_verb ;
		TSvc_Ids m_svc_ids;
	};

}}}}

#pragma comment(lib, "sys.err.core_v15.lib")  // for using error object;
#pragma comment(lib, "ebo_test_$$$.lib")      // shared unit test library for common definition(s);
#pragma comment(lib, "ms.xml.6_v15.lib")      // this one must be tested by this unit test project;

#endif/*_EBO_TEST_$9$_MSXML_H_INCLUDED*/