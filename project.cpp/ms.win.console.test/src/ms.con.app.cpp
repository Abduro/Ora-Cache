/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-May-2024 at 19:02:54.1092812, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack cppuinit test console app interface implementation file;
*/
#include "ms.con.app.h"
#include "ms.con.out.h"

using namespace ebo::boo::con;
using namespace ebo::boo::test;

namespace ebo { namespace boo { namespace con { namespace _impl {

	using CError = shared::sys_core::CError;
	using TError = const CError;

	using TString = TStringEx; 

	class CHandler {
	public:
		 CHandler (void) { m_error >> __CLASS__ << __METHOD__; }
		 CHandler (const CHandler&) = delete;
		 CHandler (CHandler&&) = delete;
		~CHandler (void) {}

	public:
		TError&   Error (void) const { return this->m_error; }

	public:
		CHandler& operator = (const CHandler&) = delete;
		CHandler& operator = (CHandler&&) = delete;
	
	private:
		CError m_error;
	};

}}}}

using namespace ebo::boo::con::_impl;

#include <eh.h>
#include <exception>

class SE_Exception : public std::exception
{
private:
	const unsigned int nSE;
public:
	SE_Exception() noexcept : SE_Exception{ 0 } {}
	SE_Exception( unsigned int n ) noexcept : nSE{ n } {}
	unsigned int getSeNumber() const noexcept { return nSE; }
};

class Scoped_SE_Translator
{
private:
	const _se_translator_function old_SE_translator;
public:
	Scoped_SE_Translator( _se_translator_function new_SE_translator ) noexcept
		: old_SE_translator{ _set_se_translator( new_SE_translator ) } {}
	~Scoped_SE_Translator() noexcept { _set_se_translator( old_SE_translator ); }
};

void SEFunc()
{
//	__try
	try
	{
		printf( "In __try, about to force exception\n" );
		int x = 5;
		int y = 0;
		int *p = &y;
		*p = x / *p;
	}
	catch(...)
//	__finally
	{
		printf( "In __finally\n" );
	}
}

void trans_func( unsigned int _ex_code, EXCEPTION_POINTERS* _ptrs) {
	_ex_code; _ptrs;
//	using CError  = shared::sys_core::CError;
//	using CCode   = shared::sys_core::seh::CCode;
//	using TFake   = shared::sys_core::seh::CCode_Fake;
//	using errno_l = shared::sys_core::seh::errno_l;
//	using Accept  = shared::sys_core::seh::CAccepted;

	throw SE_Exception( _ex_code );
#if (0)
	CError err_; err_ >> __CLASS__ << __METHOD__ = (DWORD)__sys_ex_code_2_errno(_ex_code);
#if (0)
	const CCode& code_0 = TFake().Ref().Find((uint32_t)_ex_code);
	_out_t << (_pc_sz)code_0.Print() << ::std::endl;

	const CCode& code_1 = TFake().Ref().Find((errno_l)__sys_ex_code_2_errno(_ex_code));
	_out_t << (_pc_sz)code_1.Print() << ::std::endl;

	const CCode& code_2 = TFake().Ref().Get(_ptrs);
	_out_t << (_pc_sz)code_2.Print() << ::std::endl;
#endif
	using TFlag_Unw = shared::sys_core::seh::CFlag_Unw_Collection;
	using CFlag     = shared::sys_core::seh::CFlag;
	using TRawFlags = shared::sys_core::seh::TRawFlags;
	using CRecord   = shared::sys_core::seh::CRecord;
	
	TFlag_Unw flag_unw; flag_unw << _ptrs;
#if (0)
	_out_t << _T("Getting exception flags:") << ::std::endl;
	TRawFlags raw_flags = flag_unw.Get(); // makes a copy of the flags' vector;
	if (raw_flags.empty()) {
		_out_t << _T("No flag set;") << ::std::endl;
		_out_t << _T("Changing input data:") << ::std::endl;
//		if (Accept()(_ptrs)) {
			uint32_t raw_value = TExcValues::e_no_way | TExcValues::e_collide  | (TExcValues::e_collide * 2) ;
			flag_unw << raw_value;
//		}
	}
	raw_flags  = flag_unw.Get();
	_out() << TFlag_Unw::Print(raw_flags);
	_out() << TFlag_Unw::Print(flag_unw.Get());
#endif
	_out() << (CRecord() >> _ptrs);

//	_out()();

	throw shared::sys_core::CError();
//	throw err_;
#endif
}

#define _TEST_EXC_HANDLER 0

int _tmain (void) {

	int n_result = 0;
#if (_TEST_EXC_HANDLER)
#if (0)
	TCmdLine cmd_line;
	cmd_line.Append(_T("module"), _T("shared::sys_core::seh::CTranslator"));

	_out_t << (_pc_sz)cmd_line.Print() << ::std::endl;
#endif
	using CError = shared::sys_core::CError;
#if (1)
	Scoped_SE_Translator scoped_se_translator( trans_func );
#else
	CTranslator trans_scope(trans_func);
//	CTranslator trans_scope;
#endif
	try
	{
#if (1)
		SEFunc();
#else
		CThrow().Cases()._0();
		CThrow().Cases()._1();
#endif
	}
	catch( const SE_Exception& e ) {
		e;
		printf( "Caught a __try exception, error %8.8x.\n", e.getSeNumber() );
	}
	catch( const shared::sys_core::CError& _ex)
	{
		_ex;
		_out() << (_pc_sz)_ex.Print(CError::e_req);
	}
#endif
	// https://stackoverflow.com/questions/21257544/c-wait-for-user-input ;
	_out().Wait(_T("\n\tPress [Enter] key or click [x] button to exit;"));
//	_out()();
//	::std::cin.get();

	return n_result;
}