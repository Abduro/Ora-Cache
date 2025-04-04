/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Aug-2024 at 11:30:16.7885457, UTC+4, Batumi, Wednesday;
	This is Ebo Pack shared lib memory management base interface implementation file; 
*/
#include "ebo_test_$2$.mem.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	namespace memory {

		__class(CBuffer) {
			__ctor(_ctor) {

				const uint32_t u_req_size = 1024;

				TRawData buffered(u_req_size);

				Assert::IsTrue (buffered.IsValid()); // the using HeapValidate() throws the system error, that looks like the debug breakpoint;
				Assert::IsFalse(buffered.Error());

				_out() += TLog_Acc::e_new_line;
				_out().Cached() += buffered.Print();
				_out().Cached()();
			}
		};

		__class(CHandle) {

			class CBuilder {
			public:
				 CBuilder (void) { this->m_error >> __CLASS__ << __METHOD__ << TErrCodes::no_error; }
				 CBuilder (const CBuilder&) {}
				 CBuilder (CBuilder&&) = delete;
				~CBuilder (void) {}

			public:
				err_code Create (THandle& _h_file) { // creates a handle of a temporary file; it is just for testing the handle, but not the file;
					_h_file;
					this->m_error << __METHOD__ << TErrCodes::no_error;

					if (_h_file.Is())
						return this->m_error << (err_code)TErrCodes::eObject::eExists;

					// giving the name to the temporary file: https://en.cppreference.com/w/cpp/language/string_literal ;
					// and using solution directory macro: https://stackoverflow.com/questions/19969868/how-to-access-solutiondir-macro-from-c-code ;

					// https://stackoverflow.com/questions/631664/accessing-environment-variables-in-c :: has the very good answer;
					// https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros :: just for knowing that kind of macros;

					// https://stackoverflow.com/questions/14888402/accessing-visual-studio-macros-from-source-code :: looks like what is needed and this works;

#if defined(_Output) // must be defined anyway through preprocessor defs of this project settings;
					CString cs_path = _Output; cs_path += _ProjId; cs_path += _T(".test.log");
#else
					CString cs_path = _T("#n/a");
#endif
					// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfile2 ; is very interesting and requires an example of its usage;
					// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea ;
					_h_file.Attach(
						::CreateFile((_pc_sz)cs_path, FILE_ALL_ACCESS, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0), true
					);
					if (__inv_handle_val == _h_file)
						this->m_error.Last();

					return this->Error();
				}

				TError&  Error (void) const { return this->m_error; }
			private:
				CBuilder& operator = (const CBuilder&){}  // looks like very funny joke: no returning a value >> no compile and no linkage errors;
				CBuilder& operator = (CBuilder&&) = delete;

			private:
				CError m_error;
			};

			__ctor(_ctor){
				THandle handle;
				_out() += TLog_Acc::e_new_line;
				_out().Cached() += handle.Print();
				_out().Cached()();
			}

			__method(Copy_in_better_words_Clone) {

				THandle source;
				THandle target;

				CBuilder().Create(source);

				_out() += TLog_Acc::e_new_line;
				_out().Cached() += _T("source handle:");
				_out().Cached() += source.Print();

				if (source.Is()) {
					target.Clone(source);
				}
				_out() += TLog_Acc::e_new_line;
				_out().Cached() += _T("target handle:");
				_out().Cached() += target.Print();

				_out()();
			}
		};

		using THeap = shared::memory::CHeap;

		__class(CHeap) {

			class C_local {
			public:
				C_local (void) { m_data = 0; } C_local(const C_local&) = delete; C_local(C_local&&) = delete; ~C_local (void) {}

			public:
				uint32_t Data (void) const { return this->m_data; }
				bool     Data (const uint32_t _value) {
					const bool b_changed = (this->Data() != _value);
					if (b_changed)
						this->m_data = _value;
					return b_changed;
				}

			CString  Print (void) const {

				static _pc_sz pc_sz_pat = _T("cls::[%s].%s()>>{data=%u}");

				CString cs_out; cs_out.Format(pc_sz_pat, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, this->Data());
				return  cs_out;
			}

			private:
				uint32_t m_data;
			};

			__method(Is_alloca) {

				C_local cls_loc; cls_loc.Data(5);

				bool b_is_alloca = THeap::Is_alloca(this);
				bool b_on_stack  = THeap::Is_stack (this);

				static _pc_sz pc_sz_pat_a = _T("cls::[%s].%s()>>{is_alloca=%s;on_stack=%s};");
				static _pc_sz pc_sz_pat_l = _T("%s>>{is_alloca=%s;on_stack=%s};");
				
				_out().Opts() += TLog_Acc::e_new_line;
				_out() += TString().Format(pc_sz_pat_a, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, TString().Bool(b_is_alloca), TString().Bool(b_on_stack));

				b_is_alloca = THeap::Is_alloca(&cls_loc);
				b_on_stack  = THeap::Is_stack (&cls_loc);

				_out() += TString().Format(pc_sz_pat_l, (_pc_sz) cls_loc.Print(), TString().Bool(b_is_alloca), TString().Bool(b_on_stack));
				_out()();

			}

			__method(In_stack) {

				C_local cls_loc; cls_loc.Data(3);

				bool b_is_on = THeap::Is_stack(this);

				static _pc_sz pc_sz_pat = _T("cls::[%s].%s()>>{on_stack=%s};");
				
				_out().Opts() += TLog_Acc::e_new_line;
				_out() += TString().Format(pc_sz_pat, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, TString().Bool(b_is_on));

				b_is_on = THeap::Is_stack(&cls_loc);

				_out() += TString().Format(_T("%s>>{on_stack=%s}"), (_pc_sz) cls_loc.Print(), TString().Bool(b_is_on));
				_out()();
			}
		};

		__class(CPsuedo) {
			__method(Life_Cycle){
				shared::memory::shared_flags flags; _out().Cached() += flags.Print();
				shared::memory::shared_data data;

				_pc_sz p_text = _T("text data;");
				data.p_data = (PVOID)p_text; 
				data.n_size = TString(p_text).Bytes(); // terminate zero must be included;

				_out() += TLog_Acc::e_new_line;
				_out().Cached() += data.Print();
				_out().Cached() += _T(" ");
				
				TPsuedo psuedo;
				psuedo << data << flags;
				_out().Cached() += psuedo.Print(TPsuedo::e_att);

				if (__succeeded(psuedo.Builder().Create())) {
					_out().Cached() += psuedo.Builder().Print();
					_out().Cached() += TString().Format(_T("Memory block size: %u (bytes)"), psuedo.Size());
					_out().Cached() += _T(" ");

					_pc_sz p_exceed = _T("0|1|2|3|4|5|6|7|8|9|a|b|c|d|f");

					psuedo.Content().Write(p_exceed);
					_out().Cached() += TString().Format(
						_T("Writing text '%s' to memory block; result: %s"), p_exceed, psuedo.Content().Error().Print(TError::e_req).GetString()
					);
					if (!psuedo.Content().Error()) {
						CString cs_get = psuedo.Content().Read();
						_out().Cached() += TString().Format(
							_T("Reading a text to memory block; result: %s;text='%s'"), psuedo.Content().Error().Print(TError::e_req).GetString(), (LPCTSTR)cs_get 
						);
						_out().Cached() += _T(" ");
					}
					_out().Cached() += psuedo.Content().Error().Print(TError::e_req);
				}
				
				psuedo.Builder().Destroy(); _out().Cached() += psuedo.Builder().Print();

				_out().Cached()();
			}

			__method(Realloc) {

				_pc_sz p_text = _T("Text data");

				shared::memory::shared_flags flags;
				shared::memory::shared_data  data ;

				data.p_data = (PVOID)p_text; 
				data.n_size = (DWORD)(::_tcslen(p_text) + 1) * sizeof(t_char); // terminated zero must be included;

				TPsuedo psuedo;
				psuedo << data << flags;

				_out() += TLog_Acc::e_new_line;
				_out().Cached() += psuedo.Print(TPsuedo::e_att);

				CString cs_cnt;

				psuedo.Builder().Create();
				_out().Cached() += psuedo.Builder().Print();
				_out().Cached() += TString().Format(_T("Memory block size: %u (bytes)"), psuedo.Size());

				cs_cnt = psuedo.Content().Read();
				_out().Cached() += TString().Format(_T("Memory block content: '%s'"), (_pc_sz)cs_cnt);

				_pc_sz p_text_ex = _T("New text data plus a couple of chars");
#if (0) // this test case is not passed! the access violation occurs! [fixed: when this flag is set, no data change is accepted;]
				flags += t_mem_flags::e_modify;
				psuedo << flags;
#elif (1)
				_out().Cached() += _T("The modify flag is not set;");
#else
				_out().Cached() += _T(" ");
				_out().Cached() += _T("[#error]: modifying buffer size and its content does not pass the test!");
				_out().Cached() += _T(" ");
#endif
				data.p_data  = (void*)p_text_ex; 
				data.n_size  = static_cast<DWORD>(::_tcslen(p_text_ex)) * sizeof(t_char); // if specified size is less than required, a truncation occurs;

				psuedo.Builder().Update(data);
				_out().Cached() += psuedo.Builder().Print();
				_out().Cached() += TString().Format(_T("Memory block size: %u (bytes)"), psuedo.Size());

				cs_cnt = psuedo.Content().Read();
				_out().Cached() += TString().Format(_T("Memory block content: '%s'"), (_pc_sz)cs_cnt);

				psuedo.Builder().Destroy(); _out().Cached() += psuedo.Builder().Print();

				_out().Cached()();
			}
		};

		__class(CNamed) {
			__ctor(_ctor) {

				TSection section;
				TPage& page = section.Page();

				_out().Cached() += section.Print();
				_out().Cached() += page.Print();
				_out().Cached()();
			}
		};

		__class(CPage) {
			__method(Life_Cycle) {

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
				section.Data(data);

				// the section must be initialized first by its name and data, otherwise the page object won't be created;
				section.Name(_T("section#1"));

				page.Create();  _out() += page.Print();
				view.Open();    _out() += view.Print();
				
				_out() += _T("");
				_out() += TString().Format(_T("Writing cached data: %s;"), p_text);

				view.Write();

				_out() += TString().Format(_T("Read data: %s"), (_pc_sz)view.Read());
				_out() += view.Error().Print();
				_out() += _T("");

				_pc_sz p_trunc = _T("This is the text that will be truncated: the error object will show that;");

				_out() += _T("Writing input data:");
				_out() += p_trunc;
				_out() += _T("");

				view.Write(p_trunc);

				_out() += TString().Format(_T("Read data: %s"), (_pc_sz)view.Read());
				_out() += view.Error().Print();
				_out() += _T("");

				view.Close();   _out() += view.Print();
				page.Destroy(); _out() += page.Print();

				_out()();
			}
		};

	}
}}}