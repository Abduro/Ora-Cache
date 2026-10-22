/*
	Createed by Tech_dog (ebontrop@gmail.com) on 07-Oct-2026 at 20:25:22.297, UTC+4, Batumi, Wednesday;
	This is IE JavaScript execution engine wrapper interface implementation file.
*/
#include "web.ie.script.h"
#include "web.ie.accessor.h"
#include "web.ie.host.wnd.h"

using namespace ::ex_ui::web::IE;
using namespace ::ex_ui::web::IE::core;

namespace ex_ui { namespace web { namespace IE { namespace _impl {

	class CScript_helper {
	public:
		 CScript_helper (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
		 CScript_helper (const TBrwWndPtr& _brw_wrap) : CScript_helper() { this->m_control = _brw_wrap; this->Get_doc_2(this->m_document); }
		 CScript_helper (const CScript_helper&) = delete; CScript_helper (CScript_helper&&) = delete;
		~CScript_helper (void) = default;

		TError&  Error (void) const { return this->m_error; }
		TDoc0Ptr Document0 (void) {
			this->m_error <<__METHOD__<<__s_ok;

			if (this->m_document == nullptr) {
				this->m_error <<__e_not_inited;
				return TDoc0Ptr();
			}
			TDoc0Ptr p_doc_0;
			this->m_error << this->m_document.QueryInterface(&p_doc_0);

			return p_doc_0;
		}
		TDoc2Ptr Document2 (void) const { return this->m_document; }

		bool Is_accepted (_pc_sz _p_code) {
			_p_code;
			this->m_error << __METHOD__ << __s_ok;
			this->m_code = _p_code;
			this->m_code.Trim();
			if (this->m_code.IsEmpty())
				this->m_error <<__e_inv_arg;

			return false == this->Error();
		}

		err_code Get_doc_2 (TDocument2Ptr& _doc_2) {
			this->m_error << __METHOD__ << __s_ok;

			if (nullptr == this->m_control)
				return this->m_error <<__e_not_inited;

			CAccessor acc(*this->m_control);
			this->m_error << acc.Document2(_doc_2);
			return this->Error();
		}

		bool operator <<(_pc_sz _p_code) { return this->Is_accepted(_p_code); }

		CScript_helper& operator <<(const TBrwWndPtr& _brw_wrap) {
			this->m_control = _brw_wrap; this->Get_doc_2(this->m_document); return *this;
		}
		operator const TDocument2Ptr& (void) const { return this->m_document; }
		operator const CString& (void) const { return this->m_code; }
		operator const _pc_sz (void) const { return (_pc_sz) this->m_code; }

	private:
		CScript_helper& operator = (const CScript_helper&) = delete; CScript_helper& operator = (CScript_helper&&) = delete;
		mutable
		CError  m_error;
		TBrwWndPtr m_control;
		TDoc2Ptr m_document;
		CString m_code;
	};

}}}} using namespace _impl;

#pragma region cls::CScript{}

CScript:: CScript (TBrwWndPtr& _p_wrapper) : m_control(_p_wrapper) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CScript::~CScript (void) {}

TError&   CScript::Error (void) const { return this->m_error; }

err_code  CScript::Evaluate (_pc_sz _p_code, CComVariant& _result) const {
	_result;
	this->m_error << __METHOD__ << __s_ok;

	CScript_helper script_helper;
	if (false == script_helper.Is_accepted(_p_code))
		return this->m_error = script_helper.Error();

	TDocument2Ptr p_document = (script_helper << this->m_control);

	if (script_helper.Error())
		return this->m_error = script_helper.Error();

	CComPtr<IHTMLWindow2> pWindow;
    this->m_error << p_document->get_parentWindow(&pWindow);
	if (this->Error())
		return this->Error();

	CComQIPtr<IDispatch> pAdapter(pWindow);
	if (false == pAdapter)
		return this->m_error <<__e_no_iface;

	DISPID dispidEval = 0;
	static wchar_t* p_fun_name = const_cast<wchar_t*>(_T("eval"));
	this->m_error << pAdapter->GetIDsOfNames(IID_NULL, &p_fun_name, 1, LOCALE_USER_DEFAULT, &dispidEval);
	if (this->Error())
		return this->Error();

	CComVariant varScript(script_helper);
	DISPPARAMS dispParams = { 0 };
	dispParams.rgvarg = &varScript;
	dispParams.cArgs = 1;

	EXCEPINFO excepInfo = { 0 };
	UINT uArgErr = 0;

	this->m_error << pAdapter->Invoke(dispidEval, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispParams, &_result, &excepInfo, &uArgErr);

	return this->Error();
}

err_code  CScript::Execute (_pc_sz _p_code) {
	this->m_error << __METHOD__ << __s_ok;

	CScript_helper script_helper;
	if (false == script_helper.Is_accepted(_p_code))
		return this->m_error = script_helper.Error();

	TDocument2Ptr p_document = (script_helper << this->m_control);

	if (script_helper.Error())
		return this->m_error = script_helper.Error();

	CComPtr<IHTMLWindow2> window;
	this->m_error << p_document->get_parentWindow(&window);
	if (this->m_error)
		return this->Error();

	_variant_t var_;
	try { // https://learn.microsoft.com/en-us/previous-versions//hh869591(v=vs.85) ;
		m_error = window->execScript(_bstr_t((_pc_sz)script_helper), _bstr_t(_T("JavaScript")), &var_);
	}
	catch(_com_error& err_ref) { m_error = err_ref; }
	return this->Error();
}

err_code  CScript::Get_Object (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->m_script) // the script object is already retrieved;
		return this->Error();

	CScript_helper script_helper(this->m_control);
	if (script_helper.Error())
		return this->m_error = script_helper.Error();

	this->m_error << script_helper.Document0()->get_Script(&this->m_script);

	return this->Error();
}

err_code  CScript::Get_Names (void) {

	if (__failed(this->Get_Object()))
		return this->Error();

	this->m_error <<__METHOD__<<__s_ok;

	CComPtr<IDispatchEx> pScript_ex;
	this->m_error << this->m_script->QueryInterface(&pScript_ex);
	if (this->Error())
		return this->Error();

	func_names_t fn_names;

	DISPID dispId = 0;
	this->m_error << pScript_ex->GetNextDispID(fdexEnumAll, DISPID_STARTENUM, &dispId);

	while (false == this->Error()) {
		dword_t grfdexProps = 0;
		if (__succeeded(pScript_ex->GetMemberProperties(dispId, fdexPropCanCall, &grfdexProps))) {
			if (grfdexProps & fdexPropCanCall) {
				bstr_t bs_name;
				if (__succeeded(pScript_ex->GetMemberName(dispId, bs_name.GetAddress()))) {
					fn_names.push_back(CString((_pc_sz)bs_name));
				}
			}
		}
		this->m_error << pScript_ex->GetNextDispID(fdexEnumAll, dispId, &dispId);
	}

	return this->Error();
}

bool CScript::Is_func (_pc_sz _fn_name) const {
	_fn_name;
	static _pc_sz p_script_pat = _T("typeof window.%s");

	CComVariant v_result; // ::VariantInit() is called in the constructor of this class;

	if (__failed(this->Evaluate(TString().Format(p_script_pat, _fn_name), v_result)))
		return false;
	else
		return v_result.vt == VT_BSTR && ::wcscmp(v_result.bstrVal, _T("function")) == 0;
}

#pragma endregion
#pragma region cls::CScript_Coll{}

CScript_Coll:: CScript_Collection (TBrwWndPtr& _p_wrapper) : m_control(_p_wrapper) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CScript_Coll::~CScript_Collection (void) {}

TError&  CScript_Coll::Error (void) const { return this->m_error; }

err_code CScript_Coll::Get (void) {
	this->m_error <<__METHOD__<<__s_ok;

	CScript_helper script_helper(this->m_control);
	if (script_helper.Error())
		return this->m_error = script_helper.Error();

	this->m_error << script_helper.Document2()->get_scripts(&this->m_scripts);

	return this->Error();
}

err_code CScript_Coll::Get_Items (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->m_scripts)
		return this->m_error <<__e_not_inited;

	long n_count = 0;
	this->m_error << this->m_scripts->get_length(&n_count);
	if (this->Error())
		return this->Error();

	for (long i_ = 0; i_ <n_count; i_++) {
		_variant_t v_index((long)i_);
		_variant_t v_empty;

		TDispPtr p_item = 0;
		this->m_error << this->m_scripts->item(v_empty, v_index, &p_item);
		if (this->m_error)
			break;

		TScriptElPtr p_element;
		this->m_error << p_item->QueryInterface(&p_element);
		if (this->m_error)
			break;
	}

	return this->Error();
}

#pragma endregion