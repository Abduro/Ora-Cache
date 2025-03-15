/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Apr-2024 09:24:03.5067986, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack shared preprocessor parser interface implementation file;
*/
#include "shared.preproc.h"

using namespace shared::common;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace common { namespace _impl {

	class CSpecParser {
	public:
		CSpecParser (_pc_sz const _p_spec) {
			this->PutApart(_p_spec);
		}
	public:
		bool PutApart (_pc_sz const _p_spec) {

			bool b_result = (nullptr != _p_spec);
			if (!b_result)
				return b_result;
			static
			_pc_sz s_colons = _T("::");

			TParts  elements_ = TStringEx(_p_spec).Split(s_colons, false);
			switch (elements_.size()) {
				case 0: { m_name_sp = s_ns_global; } break;
				case 1: { m_name_sp = s_ns_global; m_method = elements_[0]; } break;
			case 2: {
				m_name_sp = s_ns_global;
				m_class  = elements_[0];
				m_method = elements_[1];

				set_method(m_class, m_method);
			} break; // it may be very specific; possible assumptions: (1) 1st-namespace, 2nd-function; (2) 1st - class in global, 2nd - method;
			default:
				for (size_t i_ = 0; i_ < elements_.size() - 2; i_++) {
					m_name_sp += elements_[i_];
					bool the_last = (i_ == elements_.size() - 3);
					if (!the_last)
						m_name_sp += s_colons;
				}
				m_class  = elements_[elements_.size() - 2];
				m_method = elements_[elements_.size() - 1];

				set_method(m_class, m_method);
			}

			return b_result;
		}
	public:
		const CString& Class  (void) const { return this->m_class; }
		const CString& Method (void) const { return this->m_method; }
		const CString& NameSp (void) const { return this->m_name_sp; }
		static
		const CString& Normalize (CString& _s_ref) {

			if (_s_ref.IsEmpty())
				return _s_ref;
			INT n_remove = 0;
			for (INT i_ = _s_ref.GetLength() - 1; 0 < i_; --i_) {
				if (_T('\n') == _s_ref.GetAt(i_) || _T('\r') == _s_ref.GetAt(i_))
					n_remove += 1;
			if (0 < n_remove) {
				INT n_ndx = _s_ref.GetLength(); 
				_s_ref.SetAt(n_ndx - n_remove - 0,  _T('\0'));
			}}
			return _s_ref;
		}

	private:
		// error C7525: inline variables require at least '/std:c++17' ;
		// must be: Cfg Props >> C/C++ >> Language >> C++ Language Standard = /std:c++latest ;
		static inline _pc_sz const s_ctor = _T("#{ctor}");
		static inline _pc_sz const s_dtor = _T("#{dtor}");
		static inline _pc_sz const s_ns_global = _T("#global");

		static void set_method(CString& _class, CString& _method) {

			if (_method == _class)
				_method = s_ctor;
			else if (0 == _method.Find(_T("~")))
				_method = s_dtor;
		}
		
	private:
		CString m_name_sp;
		CString m_class;
		CString m_method;
	};

}}}
using namespace shared::common::_impl;
/////////////////////////////////////////////////////////////////////////////
// this code uses mvcc for compilation, thus Microsoft compiler specific macros are used;
// for gcc other approach can be used like this: https://stackoverflow.com/questions/1666802/is-there-a-class-macro-in-c ;

CString CPreprocessor::Class  (_pc_sz const _p_spec) { return CSpecParser(_p_spec).Class (); }
CString CPreprocessor::Method (_pc_sz const _p_spec) {
	return CSpecParser(_p_spec).Method();
}
CString CPreprocessor::NameSp (_pc_sz const _p_spec) { return CSpecParser(_p_spec).NameSp(); }

/////////////////////////////////////////////////////////////////////////////