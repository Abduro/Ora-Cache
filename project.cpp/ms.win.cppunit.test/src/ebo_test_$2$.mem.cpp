/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Aug-2024 at 11:30:16.7885457, UTC+4, Batumi, Wednesday;
	This is Ebo Pack shared lib memory management base interface implementation file; 
*/
#include "ebo_test_$2$.mem.h"

using namespace ebo::boo::test::memory;

/////////////////////////////////////////////////////////////////////////////

CBuffer:: CBuffer (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CBuffer::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("ctor: %s"), (_pc_sz) this->m_buffer.Print(e_print::e_all));
	_out()();
}

void CBuffer::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) this->m_buffer.Print(e_print::e_all));

	const uint32_t u_req_size = 1024;

	_out() += TStringEx().Format(_T("Required size: %u (bytes)"), u_req_size);

	if (__failed(this->m_buffer.Create(u_req_size))) // the using HeapValidate() throws the system error, that looks like the debug breakpoint;
		_out() += this->m_buffer.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*after *: %s"), (_pc_sz) this->m_buffer.Print(e_print::e_all));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace memory { namespace _impl {

	static _pc_sz pc_sz_pat_crt = _T("Creating the memory block: %s;");
	static _pc_sz pc_sz_pat_end = _T("Destroying the memory block: %s;");

	class CAlloc {
	public:
		 CAlloc (TPsuedo& _alloc) : m_alloc(_alloc) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
		 CAlloc (void) = delete; CAlloc(const CAlloc&) = delete; CAlloc (CAlloc&&) = delete;
		~CAlloc (void) {}

	public:
		err_code Create (void) {
			_out() += TLog_Acc::e_emp_line; // stupid approach; must be fixed;
			_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			this->m_error <<__METHOD__<<__s_ok;

			err_code n_result = this->m_alloc.Builder().Create();
			if (__failed(n_result)) {
				_out() += TString().Format(pc_sz_pat_crt, (_pc_sz) this->m_alloc.Builder().Error().Print(TError::e_req));
			}
			else {
				_out() += TString().Format(pc_sz_pat_crt, TString().Format(_T("success >> the size is %u (bytes)"), this->m_alloc.Size()));
				_out() += _T(""); 
				_out() += TString().Format(_T("%s"), (_pc_sz) this->m_alloc.Print());
			}
			return this->Error();
		}

		err_code Destroy (void) {
			_out() += _T("");
			_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			this->m_error <<__METHOD__<<__s_ok;

			err_code n_result = this->m_alloc.Builder().Destroy();
			if (__failed(n_result)) {
				_out() += TString().Format(pc_sz_pat_end, (_pc_sz) this->m_alloc.Builder().Error().Print(TError::e_req));
			}
			else
				_out() += TString().Format(pc_sz_pat_end, _T("success"));

			return this->Error();
		}

		TError&  Error (void) const { return this->m_error; }

		err_code Init (_pc_sz _p_text) {

			_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			this->m_error <<__METHOD__<<__s_ok;

			if (nullptr == _p_text || 0 == ::_tcslen(_p_text)) {

				this->m_error << __e_inv_arg = _T("Input text data is invalid");
				_out() += this->Error().Print(TError::e_req);
			}
			else {
				_out() += _T("Init params:");

				shared::memory::shared_flags flags; _out().Cached() += flags.Print();
				shared::memory::shared_data  data ;

				data.p_data = (void*) _p_text; 
				data.n_size = TString(_p_text).Bytes(); // terminate zero must be included;

				_out() += data.Print();
				this->m_alloc << data << flags;
			}
			return this->Error();
		}

	private: CAlloc& operator = (const CAlloc&) = delete; CAlloc& operator = (CAlloc&&) = delete;
	private:
		TPsuedo& m_alloc;
		CError   m_error;
	};

	class CLog {
	public:
		 CLog (void) { this->m_error >> __CLASS__ << __METHOD__ << TErrCodes::no_error; }
		 CLog (const CLog&) {}
		 CLog (CLog&&) = delete;
		~CLog (void) {}

	public:
		err_code Create (THandle& _h_file) { // creates a handle of a temporary file; it is just for testing the handle, but not the file;
			_h_file;
			this->m_error << __METHOD__ << TErrCodes::no_error;

			if (_h_file.Is())
				return this->m_error << (err_code)TErrCodes::eObject::eExists;
#pragma region __refs_7
			// giving the name to the temporary file: https://en.cppreference.com/w/cpp/language/string_literal ;
			// and using solution directory macro: https://stackoverflow.com/questions/19969868/how-to-access-solutiondir-macro-from-c-code ;

			// https://stackoverflow.com/questions/631664/accessing-environment-variables-in-c :: has the very good answer;
			// https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros :: just for knowing that kind of macros;

			// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfile2 ; is very interesting and requires an example of its usage;
			// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea ;
#pragma endregion
			handle h_file = ::CreateFile(
				this->Get_path(), /*FILE_ALL_ACCESS*/GENERIC_READ | GENERIC_WRITE , 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
			);
			if (__inv_handle_val == h_file) {
				return this->m_error.Last();
			}

			_out() += TStringEx().Format (_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
			_out() += TStringEx().Format (_T("Target file %s%s is created;"), _p_new_line, (_pc_sz) this->Get_path()) ;

			if (__failed(_h_file.Attach( h_file, true )))
				return this->m_error = _h_file.Error();
			
			return this->Error();
		}

		TError&  Error (void) const { return this->m_error; }

		_pc_sz   Get_path (void) {
			// https://stackoverflow.com/questions/14888402/accessing-visual-studio-macros-from-source-code :: looks like what is needed and this works;
#if defined(_Output) // must be defined anyway through preprocessor defs of this project settings;
			this->m_path = _Output; this->m_path += _ProjId; this->m_path += _T(".test.log");
#else
			this->m_path = _T("#n/a");
#endif
			return this->m_path.GetString();
		}

	private:
		CLog& operator = (const CLog&){}  // looks like very funny joke: no returning a value >> no compile and no linkage errors;
		CLog& operator = (CLog&&) = delete;
	private:
		CError  m_error;
		CString m_path ;   // this is the path to temporary file that is going to be created;
	};
}}}}}

using namespace ebo::boo::test::memory::_impl;

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace memory {

CHandle:: CHandle (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CHandle::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("ctor: %s"), (_pc_sz) this->m_handle.Print(e_print::e_all));
	_out()();
}

void CHandle::Clone (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) this->m_handle.Print(e_print::e_all));

	THandle  source;
	CLog builder;

	_out() += _T("Creating a temporary file handle...");

	if (__failed( builder.Create(source) )) {
		_out() += builder.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	_out() +=  TStringEx().Format(_T("The file handle: %s"), (_pc_sz) source.Print(e_print::e_all));
	_out() += _T("Trying to clone the file handle...");

	if (__failed( this->m_handle.Clone(source) )) {
		_out() += this->m_handle.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	_out() += TStringEx().Format(_T("*result*: %s"), (_pc_sz) this->m_handle.Print(e_print::e_all));
	_out()();
}

}}}}

/////////////////////////////////////////////////////////////////////////////

CHeap:: CHeap (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CHeap::GetWhere (void) {

	class CLocal {
	public:
		CLocal (void) { m_data = 0; } CLocal (const CLocal&) = delete; CLocal (CLocal&&) = delete; ~CLocal (void) {}

	public:
		uint32_t Data (void) const { return this->m_data; }
		bool     Data (const uint32_t _value) {
			const bool b_changed = (this->Data() != _value);
			if (b_changed)
				this->m_data = _value;
			return b_changed;
		}
	private: CLocal& operator = (const CLocal&) = delete; CLocal& operator = (CLocal&&) = delete;
	private:
		uint32_t m_data;
	};

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	bool b_is_alloca = THeap::Is_alloca(this);
	bool b_on_stack  = THeap::Is_stack (this);

	_out() += TString().Format(_T("Checks where the 'this' pointer resides: %son_heap=%s;on_stack=%s;"),
		_p_new_line, TString().Bool(b_is_alloca), TString().Bool(b_on_stack));

	CLocal cls_loc;

	b_is_alloca = THeap::Is_alloca(&cls_loc);
	b_on_stack  = THeap::Is_stack (&cls_loc);

	_out() += TString().Format(_T("Checks where the variable of method scope resides: %son_heap=%s;on_stack=%s;"),
		_p_new_line, TString().Bool(b_is_alloca), TString().Bool(b_on_stack));

	CLocal* p_local = new CLocal;

	b_is_alloca = THeap::Is_alloca(p_local);
	b_on_stack  = THeap::Is_stack (p_local);

	_out() += TString().Format(_T("Checks where the dynamically created object resides: %son_heap=%s;on_stack=%s;"),
		_p_new_line, TString().Bool(b_is_alloca), TString().Bool(b_on_stack));

	delete p_local; p_local = nullptr;

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CMemAlloc:: CMemAlloc (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CMemAlloc:: Life_Cycle (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CAlloc alloc(this->m_alloca);

	if (__failed(alloc.Init(_T("text data;")))) { // all prints is made by CAlloc class itself;
		_out()(); return;
	}

	if (__failed(alloc.Create())) { // all prints is made by CAlloc class itself;
		_out()(); return;
	}

	alloc.Destroy();
	_out()();
}

void CMemAlloc:: Locker (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CAlloc alloc(this->m_alloca);

	if (__failed(alloc.Init(_T("text data;")))) { // all prints is made by CAlloc class itself;
		_out()(); return;
	}

	if (__failed(alloc.Create())) { // all prints is made by CAlloc class itself;
		_out()(); return;
	}

	if (__failed(this->m_alloca.Locker().Lock())) {
		_out() += this->m_alloca.Locker().Error().Print(TError::e_req);
	}
	else
		_out() += _T("The memory block has been *locked* successfully;");

	if (__failed(this->m_alloca.Locker().Unlock())) {
		_out() += this->m_alloca.Locker().Error().Print(TError::e_req);
	}
	else
		_out() += _T("The memory block has been *unlocked* successfully;");

	_out() += _T("Intentionally producing the error by unlocking twice:");
	if (__failed(this->m_alloca.Locker().Unlock())) {
		_out() += this->m_alloca.Locker().Error().Print(TError::e_req);
	}
	else
		_out() += _T("The memory block has been *unlocked* successfully;");

	alloc.Destroy();
	_out()();
}

void CMemAlloc:: Realloc (void) {

	_out() += TLog_Acc::e_emp_line;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CAlloc alloc(this->m_alloca);

	if (__failed(alloc.Init(_T("Input text data;")))) { // all prints is made by CAlloc class itself;
		_out()(); return;
	}

	if (__failed(alloc.Create())) { // all prints is made by CAlloc class itself;
		_out()(); return;
	}

	TString cs_data = this->m_alloca.Content().Read();

	if (this->m_alloca.Content().Error().Is())
		_out() += this->m_alloca.Content().Error().Print(TError::e_req);
	else {
		_out() += _T(""); // just for adding the empty line in the output window;
		_out() += TString().Format(_T("Content data: '%s' (%u bytes)"), (_pc_sz) cs_data, /*cs_data.Bytes()*/this->m_alloca.Size());
	}
	_pc_sz p_text_ex = _T("New text data plus a couple of chars");
	uint32_t n_size  = static_cast<uint32_t>((::_tcslen(p_text_ex) + 1) * sizeof(t_char)); // 0-terminator is included;

#if (0) // this test case is not passed! the access violation occurs! [fixed: when this flag is set, no data change is accepted;]
	flags += t_mem_flags::e_modify;
	psuedo << flags;
#elif (1)
	_out().Cached() += _T("")/*_T("The modify flag is not set;")*/;
#else
	_out().Cached() += _T("");
	_out().Cached() += _T("[#error]: modifying buffer size and its content does not pass the test!");
	_out().Cached() += _T("");
#endif

	_out() += _T("Setting new data for a reallocation of the memory:");
	_out() +=  TString().Format (_T("data: %s (%u byte(s))"), p_text_ex, n_size) ;

	shared::memory::shared_data data;

	data.p_data = (void*) p_text_ex;
	data.n_size = n_size;

	if (__failed( this->m_alloca.Builder().Update(data) ))
		_out() += this->m_alloca.Builder().Error().Print(TError::e_req);
	else {
		cs_data << (_pc_sz) this->m_alloca.Content().Read();
		_out() += _T("");
		_out() += TString().Format (_T("*result*: the data in the content: '%s' (%u byte(s))"), (_pc_sz) cs_data, cs_data.Bytes()) ;
	}

	alloc.Destroy();
	_out()();
}

void CMemAlloc:: Truncate (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CAlloc alloc(this->m_alloca);

	if (__failed(alloc.Init(_T("text data;")))) { // all prints is made by CAlloc class itself;
		_out()(); return;
	}

	if (__failed(alloc.Create())) { // all prints is made by CAlloc class itself;
		_out()(); return;
	}

	TString cs_exceed (_T("0|1|2|3|4|5|6|7|8|9|a|b|c|d|f"));
	_out() += TStringEx().Format(_T("Writing the data with exceeded size:%s%s (%d bytes)"), _p_new_line, (_pc_sz) cs_exceed, cs_exceed.Bytes());

	err_code n_result = this->m_alloca.Content().Write((_pc_sz)cs_exceed);
	if (__failed(n_result)) {
		_out() += this->m_alloca.Content().Error().Print(TError::e_req);
	}
	else {
		_out() += _T("Reading truncated data from memory block:");

		TString cs_get = this->m_alloca.Content().Read();

		if (this->m_alloca.Content().Error().Is())
			_out() += this->m_alloca.Content().Error().Print(TError::e_req);
		else
			_out() += TString().Format(_T("%s (%u bytes)"), (_pc_sz) cs_get, cs_get.Bytes() - sizeof(t_char)); // the string got zero terminate byte automatically;
	}
	alloc.Destroy();
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

void CNamed::_ctor (void) {

	TSection section;
	TPage& page = section.Page();

	_out().Cached() += section.Print();
	_out().Cached() += page.Print();
	_out().Cached()();
}

/////////////////////////////////////////////////////////////////////////////

void CPage:: Life_Cycle (void) {
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TSection section;

	TPage& page = section.Page(); _out() += page.Print();
	TView& view = section.View(); _out() += view.Print();

	shared::memory::shared_data data;

	_pc_sz p_text = _T("<root desc=""stupid""/>");
	data.p_data   = (void*) p_text; 
	data.n_size   = TString(p_text).Bytes();

	/* the data of section is used:
		(1) TPage::Create() << data.n_size;
		(2) TView::Open()   << data.n_size;
		(3) TView::Read()   << data.n_size;
		(4) TView::Write()  << data.n_size << data.p_data;
		(5) TView::Write(str);
	*/
	// the section must be initialized first by its name and data, otherwise the page object won't be created;

	section.Data(data);
	if (__failed(section.Name(_T("section#1")))) {
		_out() += section.Error().Print(TError::e_req);
		_out()(); return;
	}

	if (__failed(page.Create())) {
		_out() += page.Error().Print(TError::e_req);
		_out()(); return;
	}
	
	_out() += page.Print();
	view.Open();
	_out() += view.Print();

	_out() += _T("");
	_out() += TString().Format(_T("Writing cached data: %s;"), p_text);

	if (__failed(view.Write())) {
		_out() += view.Error().Print(TError::e_req);
	}
	else {
		_out() += TString().Format(_T("Read data: %s"), (_pc_sz)view.Read());
	}
	_out()();
}