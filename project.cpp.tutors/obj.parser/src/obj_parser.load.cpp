/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jul-2026 at 20:17:59.904, UTC+4, Batumi, Wednesday;
	This is 3D module object file loader interface implementation file;
*/
#include "obj_parser.load.h"
#include "console.format.h"

using namespace ::shared::parsers::obj;

namespace shared { namespace parsers { namespace _impl {
#if (0)

struct HandleDeleter { // defines a custom deleter for unique_ptr compatibility;
	void operator()(HANDLE h) const noexcept {
		if (nullptr == h && __e_handle != h) {
			::CloseHandle(h);
		}
	}
};

using ScopedHandle = std::unique_ptr<void, HandleDeleter>; // creates a friendly alias for an RAII managed handle;
void Do_raii(void) {
	// wraps a standard file handle directly into a smart pointer;
	ScopedHandle h_file(::CreateFile(_T("log.txt"), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0));
	/*
	reading from/writing to the open file;
	h_file automatically goes out of scope here and triggers CloseHandle safely;
	*/
}
#endif
	class CHandle {
	public:
		 CHandle (void) : m_handle(0) {} CHandle (const CHandle&) = delete; CHandle (CHandle&&) = delete;
		 CHandle (HANDLE _handle) : m_handle(_handle) {}
		~CHandle (void) {
			/* Common Pitfalls to Avoid
			Double Closing: Never call CloseHandle twice on the same handle. This can result in unintended silent errors or closing a recycled handle belonging to a completely different thread.
			Wrong Disposer Functions: Do not use CloseHandle on structures or handles returned by UI/GDI layers or specific subsystem APIs.
			*/
			if (true == (*this)) {
				if (0 == ::CloseHandle(this->m_handle)) {
					::__trace_err_ex_2(CError(__CLASS__, __METHOD__, __LastErrToHresult()));
				}
				else { this->m_handle = 0; }
			}
		}

		operator HANDLE (void) const { return this->m_handle; }
		operator bool (void) const { return this->m_handle != nullptr && this->m_handle != __e_handle; }

	private:
		CHandle& operator = (const CHandle&) = delete; CHandle& operator = (CHandle&&) = delete;
		HANDLE m_handle;
	};

static _pc_sz p_err_inv_handle = _T("The input path is invalid");

	class CFile {
	public:
		 CFile (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_false = _T("No file path is checked yet"); }
		 CFile (const CFile&) = delete; CFile (CFile&&) = delete;
		~CFile (void) = default;

		TError& Error (void) const { return this->m_error; }

		err_code Is_Text (_pc_sz _p_path) {
			_p_path;
			this->m_error <<__METHOD__<<__s_ok;

			if (nullptr == _p_path || _MAX_DRIVE >= ::_tcslen(_p_path)) {
				return this->m_error <<__e_inv_arg  = p_err_inv_handle;
			}

			CHandle h_file = ::CreateFile(_p_path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			if (false == h_file) {
				return this->m_error.Last();
			}

			// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfilesizeex ;
			// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfilesize ;
			// actually, getting the file size is not required because ::ReadFile() can take care it through param 'lpNumberOfBytesRead';

			dword u_high = 0;
			const dword u_size = ::GetFileSize(h_file, &u_high); // u_high is not taken into account in context of this function;
			if (0 > (int32_t)u_size) {
				return this->m_error.Last();
			}
			static
			const uint32_t n_req_sz = 100;
			const uint32_t n_buf_sz = u_size > n_req_sz ? n_req_sz : u_size;

			::std::vector<char> v_buf(n_buf_sz, 0); 
			// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile ;
			if (0 == ::ReadFile(h_file, v_buf.data(), n_buf_sz, 0, 0))
				return this->m_error.Last();

			for (uint32_t i_ = 0; i_ < n_buf_sz; i_++) {
				const char bt_ = v_buf.at(i_);
				if ((bt_ < 9) || (bt_ > 13 && bt_ < 32) || (bt_ == 127) || (bt_ == 256)) { // checks for ASCII & UTF-8
					this->m_error <<__s_false = _T("This is not text printable file");
					break;
				}
			}

			return this->Error();
		}
		err_code Is_valid (_pc_sz _p_path) const {
			_p_path;
			this->m_error <<__METHOD__<<__s_ok;

			if (nullptr == _p_path || _MAX_DRIVE >= ::_tcslen(_p_path)) {
				return this->m_error <<__e_inv_arg  = p_err_inv_handle;
			}
			/* https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesa ;
			   https://learn.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants ;
			   Starting with Windows 10, Version 1607, you can opt-in to remove the MAX_PATH limitation without prepending "\\?\".
			*/
			const dword attrs = ::GetFileAttributes(_p_path);
			if (INVALID_FILE_ATTRIBUTES == attrs)
				return this->m_error.Last();
			if (FILE_ATTRIBUTE_DIRECTORY & attrs)
				return this->m_error <<__e_inv_arg = _T("Input path specifies the directory");

			return this->Error();
		}

	private:
		CFile& operator = (const CFile&) = delete; CFile& operator = (CFile&&) = delete;
		mutable
		CError m_error;
	};

}}} using namespace ::shared::parsers::_impl;

#pragma region cls::CBase{}

using CBase = ::shared::parsers::obj::CBase;

CBase::CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CBase::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CLoader{}

// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s ;
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s ;
#if defined (_UNICODE)
#define fdopen _wfdopen
#define fopen_s _wfopen_s
#define strerror_s _wcserror_s
#else
#define fdopen _fdopen
#define strerror_s strerror_s
#define fopen_s fopen_s
#endif

CLoader:: CLoader (void) : TBase(), m_p_file(0) { TBase::m_error >>__CLASS__<<__s_false = _T("No object file is loaded yet"); }
CLoader::~CLoader (void) {
	if (this->Is_opened()) this->Close();
}

err_code CLoader::Close (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == this->Is_opened()) {
		__trace_warn_2(_T("No file been opened"));
		return TBase::Error();
	}
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fclose-fcloseall ;
	const errno_t n_result = ::fclose(this->m_p_file);
	if (!!n_result) {
		TBase::m_error << (err_code) TErrCodes::eAccess::eDenied = _T("File close failed");
	}
	else
		this->m_p_file = 0;
	return TBase::Error();
}

bool CLoader::Is_opened (void) const { return nullptr != this->m_p_file; }
bool CLoader::Is_Text (_pc_sz _path, CError& _error) {
	_path; _error;
	bool b_text = false;
	CFile file;
	if (__failed(file.Is_Text(_path))) {
		_error = file.Error();
		return b_text;
	} else if (__s_ok == file.Error().Result()) b_text = true;
	else {/*__s_false == file.Error().Result()*/}
	
	return b_text;
}

err_code CLoader::Open (_pc_sz _path) {
	_path;
	TBase::m_error <<__METHOD__<<__s_ok;

	CFile file;
	if (__failed(file.Is_valid(_path)))
		return TBase::m_error = file.Error();

	if (nullptr != this->m_p_file) {
		return TBase::m_error << (err_code) TErrCodes::eObject::eInited = _T("The file is already open");
	}
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/errno-doserrno-sys-errlist-and-sys-nerr ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/errno-constants ;
	const errno_t n_result = fopen_s(&this->m_p_file, _path, _T("r"));
	if (!!n_result) {
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s ;
		static const size_t req_len = 256u;
		t_char buffer[req_len] = {0};
		if (!!strerror_s(buffer, req_len, n_result)) {}

		return (TBase::m_error = static_cast<dword>(n_result)) = TString().Format(_T("File open failed: errno = %d"), n_result); 
	}
	CString cs_path(_path);
	if (cs_path.GetLength() > 40) {
		cs_path = TString().Format(_T("%s...%s"), (_pc_sz) cs_path.Left(20), (_pc_sz) cs_path.Right(20));
	}

	__trace_info_2(_T("The file '%s' is opened;\n"), (_pc_sz) cs_path);

	return TBase::Error();
}

err_code CLoader::To_handle (HANDLE& _h_out) {
	TBase::m_error <<__METHOD__<<__s_ok;
	return CLoader::To_handle(this->m_p_file, TBase::m_error, _h_out);
}

static _pc_sz p_err_file_handle = _T("File handle is invalid");
static _pc_sz p_err_file_desc = _T("File desc is invalid or is not belong to open file");

err_code CLoader::To_handle (FILE* _p_file, CError& _error, HANDLE& _h_out) {
	_p_file; _error; _h_out;
	if (nullptr == _p_file)
		return _error << __e_pointer = _T("File stream pointer is invalid");
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fileno ;
	const int n_desc = ::_fileno(_p_file);
	if (0 > n_desc)
		return _error << __e_inv_arg = p_err_file_desc;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/get-osfhandle ;
	_h_out = reinterpret_cast<HANDLE>(::_get_osfhandle(n_desc));
	if (__e_handle == _h_out)
		_error << (err_code)TErrCodes::eObject::eHandle = p_err_file_handle;
	return _error;
}

err_code CLoader::To_stream (const HANDLE _h_file, CError& _error, FILE*& _p_stream, const dword _flags) {
	_h_file; _error; _p_stream; _flags;
	if (__e_handle == _h_file)
		_error << (err_code)TErrCodes::eObject::eHandle = p_err_file_handle;

	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/open-osfhandle ;
	const int n_desc = ::_open_osfhandle(reinterpret_cast<intptr_t>(_h_file), static_cast<int>(_flags));
	if (0 > n_desc)
		return _error << (err_code)TErrCodes::eExecute::eParameter = _T("Creating file stream failed");
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fdopen-wfdopen ;
	_p_stream = fdopen(n_desc, _T("r")); // to-do: this is default conversion to mode of opening the file, otherwise the converter must be created;
	if (nullptr == _p_stream) {
		_error << __e_inv_arg = p_err_file_desc;
	}

	return _error;
}

CLoader::operator FILE* (void) const { return this->m_p_file; }

#pragma endregion
#pragma region cls::CLocator{}

static _pc_sz p_obj_path = _T("obj_path");
static _pc_sz p_err_locate = _T("No object file is located yet");

CLocator::CLocator (void) : TBase() { TBase::m_error >>__CLASS__<<__s_false = p_err_locate; }

bool  CLocator::Is_found (void) const {
	bool b_found = false;
	TBase::m_error <<__METHOD__<<__s_false = p_err_locate;

	if (this->m_obj_path.IsEmpty())
		return b_found;

	CFile file;
	if (__failed(file.Is_valid(this->m_obj_path)))
		TBase::m_error = file.Error();
	else
		b_found = true;

	return b_found;
}

err_code CLocator::Locate (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	CFile file;
	// (1) checks command line first;
	using
	CCmdLine = ::shared::input::CCmdLine;
	CCmdLine cmd_ln;
	if (__failed(cmd_ln.Parse()))
		return TBase::m_error = cmd_ln.Error();
	if (cmd_ln.Has(p_obj_path)) {
		this->m_obj_path = cmd_ln.Arg(p_obj_path);

		if (__failed(file.Is_valid(this->m_obj_path)))
			return TBase::m_error = file.Error();
	}

	if (this->m_obj_path.IsEmpty() == false)
		return TBase::Error();
	// (2) checks the registry root key for value named 'p_obj_path';
	TRegKeyEx the_key;
	this->m_obj_path = the_key.Value().GetString(CLocator::Root(), p_obj_path);
	if (the_key.Error()) {
		::__trace_err_ex_2(the_key.Error());
	}

	if (this->m_obj_path.IsEmpty() == false)
		return TBase::Error();

	if (__failed(file.Is_valid(this->m_obj_path)))
		TBase::m_error = file.Error();
	else {
		using CFormat = ::shared::console::CFormat;
		__trace_impt_2(_T("The object file path:\n%s%s;\n"), CFormat::Indent(), this->Path());
	}

	return TBase::Error();
}

err_code CLocator::Open (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	/* https://docs.microsoft.com/en-us/windows/win32/learnwin32/example--the-open-dialog-box ;
	// https://docs.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ifileopendialog ;
	// https://docs.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ifiledialog ;
	*/
	using namespace ::ATL;

	CComPtr<IFileOpenDialog> p_dialog;
	TBase::m_error = p_dialog.CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL);
	if (TBase::Error())
		return TBase::Error();

	COMDLG_FILTERSPEC flt_spec[] = {
		{ _T("3D Model Object file (*.obj)"), _T("*.obj") }
	};
	err_code
	n_result = p_dialog->SetFileTypes(_countof(flt_spec), flt_spec);
	n_result = p_dialog->SetTitle(_T("Open 3D Model Object File"));
	n_result = p_dialog->Show(TConAccess());

	if (__succeeded(n_result)) {

		CComPtr<IShellItem> p_item;
		n_result = p_dialog->GetResult(&p_item);

		if (__succeeded(n_result)) {
			PWSTR lp_path = nullptr;
			n_result = p_item->GetDisplayName(SIGDN_FILESYSPATH, &lp_path);

			if (__succeeded(n_result)) {
				this->m_obj_path = lp_path;
			}
			if (lp_path) {
				::CoTaskMemFree(lp_path); lp_path = nullptr;
			}
		}
	}
	TBase::m_error = n_result;
	return TBase::Error();
}

_pc_sz CLocator::Path (void) const { return (_pc_sz) this->m_obj_path; }

_pc_sz CLocator::Root (void) {

	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root = TString().Format(_T("%s\\Utils\\ObjParser"), ::Get_reg_router().Root().Path());
	}

	return (_pc_sz) cs_root;
}

#pragma endregion
#pragma region cls::CReader{}

CReader::CReader (void) : TBase() { TBase::m_error >>__CLASS__<<__s_ok; }

const
CLocator& CReader::Loc (void) const { return this->m_lctr; }
CLocator& CReader::Loc (void)       { return this->m_lctr; }

/* the query to Google AI: difference between fgets and fread c++;
The primary difference is that std::fgets is line-oriented and intended for text, while std::fread is block-oriented and designed for binary data.
std::fgets automatically stops reading when it hits a newline character (\n) and appends a null-terminator (\0) to form a valid C-string.
std::fread ignores all newlines, reads exactly the raw chunk size you request, and never modifies the buffer with a null terminator.
*/
// https://learn.microsoft.com/en-us/windows/win32/fileio/testing-for-the-end-of-a-file ;

err_code CReader::Read (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	// (1) checks the locator first;
	if (false == this->Loc().Is_found()) { // the file path is empty or does not exist if the file path is read from command line or the registry;
		if (this->Loc().Error()) { // this error is set by locator.Is_found();
			return TBase::m_error = this->Loc().Error(); // returns the error;
		}

		if (__failed(this->Loc().Locate())) { // it is suppossed to try to locate an object file again;
			return TBase::m_error = this->Loc().Error(); // file path is found, but the file does not exist or is the directory;
		}
	}
	// (2) the locator contains the path to the file that is suppossed to be an model object file; tries to opent the file;
	CLoader loader;
	if (__failed(loader.Open(this->Loc().Path()))) {
		return TBase::m_error = loader.Error();
	}
	if (false == CLoader::Is_Text(this->Loc().Path(), TBase::m_error)) {
		__trace_warn_2(_T("The object file is not text file"));
		return TBase::Error();
	}

	FILE* const p_str = loader;

	::Get_model().Reset();

	// (3) reads file content and makes a call to parser;
	CParser parser;
	s_cache chached;

	/*::fread() is much faster but requires additional programming for catching the end of line;*/
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/ferror ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/feof ;

	while (!(::feof(p_str) || ::ferror(p_str))) {
		::fgets(chached.buffer, chached.buf_len, p_str); // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fgets-fgetws ;
		if (__failed(parser.Do(chached))) {
			return TBase::m_error = parser.Error();
		}
	}
	if (::ferror(p_str)) {
	}

	return TBase::Error();
}

#pragma endregion