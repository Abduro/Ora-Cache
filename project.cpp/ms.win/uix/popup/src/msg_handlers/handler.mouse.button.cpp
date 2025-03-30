/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Oct-2024 at 18:19:25.738, UTC+4, Batumi, Monday;
	This is Ebo Pack shared mouse buttons' window message handler interface implementation file;
*/
#include "handler.mouse.button.h"

using namespace ex_ui::message::handlers;
using namespace ex_ui::message::handlers::mouse::buttons;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace message { namespace handlers { namespace mouse { namespace buttons { namespace _impl {

	class CActionType {
		using e_type = CAction::e_type;
	public:
		 CActionType (void) {} CActionType (const CActionType&) = delete; CActionType (CActionType&&) = delete;
		~CActionType (void) {}

	public:
		static _pc_sz To_string (const uint32_t _type) {
			_type;
			static CString cs_type;

			cs_type.Empty();

			if (e_type::e_double   == _type) { cs_type = _T("#double_click;"); } 
			if (e_type::e_pressed  == _type) { cs_type = _T("#pressed;"); }
			if (e_type::e_released == _type) { cs_type = _T("#released;"); }
			if (e_type::e__undef   == _type) { cs_type = _T("#undefined;"); }

			if (cs_type.IsEmpty())
				cs_type = _T("#unsupp;");

			return cs_type.GetString();
		}

	private:
		CActionType& operator = (const CActionType&) = delete;
		CActionType& operator = (CActionType&&) = delete;
	};

	class CPlaceWhere {
		using e_where = CPlace::e_where;
	public:
		 CPlaceWhere (void) {} CPlaceWhere (const CPlaceWhere&) = delete; CPlaceWhere (CPlaceWhere&&) = delete;
		~CPlaceWhere (void) {}

	public:
		static _pc_sz To_string (const uint32_t _place) {
			_place;
			static CString cs_place;

			cs_place.Empty();

			if (e_where::e_Left   == _place) { cs_place = _T("#left_side;"); } 
			if (e_where::e_Middle == _place) { cs_place = _T("#middle;"); }
			if (e_where::e_Right  == _place) { cs_place = _T("#right_side;"); }
			if (e_where::e_X_1    == _place) { cs_place = _T("#x_1_place;"); }
			if (e_where::e_X_2    == _place) { cs_place = _T("#x_2_place;"); }
			if (e_where::e__Undef == _place) { cs_place = _T("#undefined;"); }

			if (cs_place.IsEmpty())
				cs_place = _T("#unsupp;");

			return cs_place.GetString();
		}

	private:
		CPlaceWhere& operator = (const CPlaceWhere&) = delete;
		CPlaceWhere& operator = (CPlaceWhere&&) = delete;
	};

}}}}}}
using namespace ex_ui::message::handlers::mouse::buttons::_impl;
/////////////////////////////////////////////////////////////////////////////

CAction:: CAction (const e_type _type) : m_type(_type) {}
CAction:: CAction (const CAction& _src) : CAction() { *this = _src; }
CAction:: CAction (CAction&& _victim) : CAction() { *this = _victim; }
CAction::~CAction (void) {}

/////////////////////////////////////////////////////////////////////////////

using e_type = CAction::e_type;

bool      CAction::Is_valid (void) const { return !!this->Type(); }

e_type    CAction::Type (void) const { return this->m_type; }
bool      CAction::Type (const e_type _type) { const bool b_changed = (this->Type() != _type); if (b_changed) this->m_type = _type; return b_changed; }

#if defined (_DEBUG)
CString   CAction::Print(const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{type=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{type=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{type=%s;valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());
	CString cs_out;

	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, CActionType::To_string(this->Type()), (_pc_sz)cs_valid); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, CActionType::To_string(this->Type()), (_pc_sz)cs_valid); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, CActionType::To_string(this->Type()), (_pc_sz)cs_valid); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CAction&  CAction::operator = (const CAction& _src) { *this << _src.Type(); return *this; }
CAction&  CAction::operator = (CAction&& _victim)  { *this = _victim; _victim.Type(e_type::e__undef); return *this; }
CAction&  CAction::operator <<(const e_type _type)  { this->Type(_type);  return *this; }

/////////////////////////////////////////////////////////////////////////////

CButton:: CButton (void) {}
CButton:: CButton (const CButton& _src) : CButton() { *this = _src; }
CButton::~CButton (void) {}

/////////////////////////////////////////////////////////////////////////////

bool      CButton::Is_valid (void) const { return (this->Place().Is_valid()); }

const
CPlace&   CButton::Place (void) const { return this->m_place; }
CPlace&   CButton::Place (void)       { return this->m_place; }

#if defined (_DEBUG)
CString   CButton::Print(const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{place=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{place=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{place=%s;valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());
	CString cs_out;

	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_pat_a, 
		(_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)this->Place().Print(CPlace::e_no_ns), (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n,
		(_pc_sz)__CLASS__  , (_pc_sz) this->Place().Print(CPlace::e_no_ns), (_pc_sz)cs_valid);
	}
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)this->Place().Print(CPlace::e_req) , (_pc_sz)cs_valid); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CButton& CButton::operator = (const CButton& _src) { *this << _src.Place(); return *this; }
CButton& CButton::operator <<(const CPlace& _place) { this->Place() = _place; return *this; }

/////////////////////////////////////////////////////////////////////////////

CEvent:: CEvent (void) {}
CEvent:: CEvent (const CEvent& _src) : CEvent() { *this = _src; }
CEvent:: CEvent (const CAction::e_type _action, const CPlace::e_where _button, const int32_t _cursor_x, const int32_t _cursor_y) {
	*this << _action << _button << _cursor_x >> _cursor_y;
}
CEvent::~CEvent (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CAction& CEvent::Action (void) const { return this->m_action; }
CAction& CEvent::Action (void)       { return this->m_action; }
const
CButton& CEvent::Button (void) const { return this->m_button; }
CButton& CEvent::Button (void)       { return this->m_button; }
const
CPoint&  CEvent::Point  (void) const { return this->m_point ; }
CPoint&  CEvent::Point  (void)       { return this->m_point ; }

bool  CEvent::Is_valid  (void) const { return this->Action().Is_valid() && this->Button().Is_valid(); }

#if defined (_DEBUG)
CString  CEvent::Print  (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{action=%s;button=%s;point=%s;keys=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{action=%s;button=%s;point=%s;keys=%s}");
	static _pc_sz pc_sz_pat_r = _T("{action=%s;button=%s;point=%s;keys=%s}");

	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			(_pc_sz) this->Action().Print(CAction::e_no_ns),
			(_pc_sz) this->Button().Print(CButton::e_no_ns),
			(_pc_sz) this->Point ().Print(CPoint ::e_no_ns),
			(_pc_sz) this->VKeys ().Print(t_vkeys::e_no_ns)
		);
	}
	if (e_print::e_no_ns == e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
			(_pc_sz) this->Action().Print(CAction::e_no_ns),
			(_pc_sz) this->Button().Print(CButton::e_no_ns),
			(_pc_sz) this->Point ().Print(CPoint ::e_no_ns),
			(_pc_sz) this->VKeys ().Print(t_vkeys::e_no_ns)
		);
	}
	if (e_print::e_req   == e_opt) {
		cs_out.Format(pc_sz_pat_r,
			(_pc_sz) this->Action().Print(CAction::e_req),
			(_pc_sz) this->Button().Print(CButton::e_req),
			(_pc_sz) this->Point ().Print(CPoint ::e_req),
			(_pc_sz) this->VKeys ().Print(t_vkeys::e_req)
		);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

const
t_vkeys&  CEvent::VKeys(void) const { return this->m_vkeys; }
t_vkeys&  CEvent::VKeys(void)       { return this->m_vkeys; }

/////////////////////////////////////////////////////////////////////////////

CEvent&  CEvent::operator = (const CEvent& _src) { *this << _src.Action() << _src.Button() << _src.Point(); return *this; }

CEvent&  CEvent::operator <<(const CAction& _action) { this->Action() = _action; return *this; }
CEvent&  CEvent::operator <<(const CButton& _button) { this->Button() = _button; return *this; }
CEvent&  CEvent::operator <<(const CPoint&  _point ) { this->Point () = _point ; return *this; }

CEvent&  CEvent::operator <<(const CAction::e_type _action) { this->Action() << _action; return *this; }
CEvent&  CEvent::operator <<(const CPlace::e_where _button) { this->Button() << _button; return *this; }

CEvent&  CEvent::operator <<(const int32_t _cursor_x) { this->Point() << _cursor_x; return *this; }
CEvent&  CEvent::operator >>(const int32_t _cursor_y) { this->Point() >> _cursor_y; return *this; }

CEvent&  CEvent::operator <<(const uint32_t _v_keys)  { this->VKeys().Set(_v_keys, true); return *this; }

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace message { namespace handlers { namespace mouse { namespace buttons { namespace _impl {

	class CData {
		using e_button = CPlace::e_where;
		using e_action = CAction::e_type;

		using TListeners = CHandler::TListeners;
		using TTargets   = CHandler::TTargets;
		using TActions   = CHandler::TActions;

	public:
		 CData (void) { m_error >> __CLASS__ << __METHOD__ << __s_ok; } CData (const CData&) = delete; CData (CData&&) = delete;
		~CData (void) {}
	
	public:
		const TListeners& Find (const CEvent& _evt, const TTargets& _targets) const {
			_evt;
			m_error << __METHOD__ << __s_ok;
			if (_evt.Is_valid()) {
				TTargets::const_iterator it_button = _targets.find(_evt.Button().Place().Where());
				if (it_button != _targets.end()) {
					TActions::const_iterator it_action = it_button->second.find(_evt.Action().Type());
					if (it_action != it_button->second.end()) {
						return it_action->second;
					}
					else
						m_error << (err_code)TErrCodes::eData::eNotFound = _T("required action is not found;");
				}
				else
					m_error << (err_code)TErrCodes::eData::eNotFound = _T("mouse button is not found;");
			}
			else
				m_error << __e_invalid_arg = _T("event object is invalid;");

			static const TListeners lst_empty;
			return lst_empty;
		}

		TError&  Error (void) const { return this->m_error; }

		bool  Is_valid (const CPlace::e_where _button, const CAction::e_type _action, IBtnEventSink* _p_sink) {
			_button; _action; _p_sink;
			m_error << __METHOD__ << __s_ok;

			if (nullptr == _p_sink) {
				m_error << __e_pointer;
				return false;
			}

			if (e_button::e__Undef == _button) {
				(m_error << (err_code)TErrCodes::eData::eInvalid) = _T("the button is not defined;");
				return false;
			}

			if (e_action::e__undef == _action) {
				(m_error << (err_code)TErrCodes::eData::eInvalid) = _T("the action is not assigned;");
				return false;
			}

			return true;
		}

	private:
		CData& operator = (const CData&) = delete;
		CData& operator = (CData&&) = delete;

	private:
		mutable CError m_error; // a mutability is made for 'find' method especially;
	};

	class CDecoder {
	public:
		 CDecoder (void) : m_action(CAction::e_type::e__undef), m_button(CPlace::e_where::e__Undef) {}
		 CDecoder (const CDecoder&) = delete; CDecoder (CDecoder&&) = delete;
		~CDecoder (void) {}

	public:
		CAction::e_type Action (void) const { return this->m_action; }
		CPlace::e_where Button (void) const { return this->m_button; }

		void Do (const uint32_t _u_msg) {
		
			switch (_u_msg) {
			case WM_LBUTTONDBLCLK: { m_action = CAction::e_type::e_double  ; m_button = CPlace::e_where::e_Left  ; } break;
			case WM_MBUTTONDBLCLK: { m_action = CAction::e_type::e_double  ; m_button = CPlace::e_where::e_Middle; } break;
			case WM_RBUTTONDBLCLK: { m_action = CAction::e_type::e_double  ; m_button = CPlace::e_where::e_Right ; } break;
			case WM_LBUTTONDOWN  : { m_action = CAction::e_type::e_pressed ; m_button = CPlace::e_where::e_Left  ; } break;
			case WM_MBUTTONDOWN  : { m_action = CAction::e_type::e_pressed ; m_button = CPlace::e_where::e_Middle; } break;
			case WM_RBUTTONDOWN  : { m_action = CAction::e_type::e_pressed ; m_button = CPlace::e_where::e_Right ; } break;
			case WM_LBUTTONUP    : { m_action = CAction::e_type::e_released; m_button = CPlace::e_where::e_Left  ; } break;
			case WM_MBUTTONUP    : { m_action = CAction::e_type::e_released; m_button = CPlace::e_where::e_Middle; } break;
			case WM_RBUTTONUP    : { m_action = CAction::e_type::e_released; m_button = CPlace::e_where::e_Right ; } break;
			default:;
				m_action = CAction::e_type::e__undef;
				m_button = CPlace::e_where::e__Undef;
			}
		}

	private:
		CDecoder& operator = (const CDecoder&) = delete;
		CDecoder& operator = (CDecoder&&) = delete;

	private:
		CAction::e_type  m_action;
		CPlace::e_where  m_button;
	};

	CString _virt_key_to_str (const uint32_t _keys) {
		_keys;
		using e_keys = CVirtualKeys::e_keys;

		CString cs_keys;

		if (e_keys::e_alt   & _keys) { if (false == cs_keys.IsEmpty()) cs_keys += _T(";"); cs_keys += _T("alt" ); }
		if (e_keys::e_ctrl  & _keys) { if (false == cs_keys.IsEmpty()) cs_keys += _T(";"); cs_keys += _T("ctrl"); }
		if (e_keys::e_shift & _keys) { if (false == cs_keys.IsEmpty()) cs_keys += _T(";"); cs_keys += _T("shft"); }

		if (cs_keys.IsEmpty()) cs_keys = _T("#none");

		return  cs_keys;
	}

}}}}}}
using namespace ex_ui::message::handlers::mouse::buttons::_impl;
/////////////////////////////////////////////////////////////////////////////

using e_button = CPlace::e_where;
using e_action = CAction::e_type;

CHandler:: CHandler (void) { TBase::m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CHandler::~CHandler (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code   CHandler::Subscribe (const CPlace::e_where _button, const CAction::e_type _action, IBtnEventSink* _p_sink) {
	_button; _action; _p_sink;
	TBase::m_error << __METHOD__ << __s_ok;

	CData data;
	if (false == data.Is_valid(_button, _action, _p_sink)) {
		return (TBase::m_error << data.Error().Result()) = data.Error().Desc();
	}

	SAFE_LOCK(TBase::m_guard);

	TTargets::iterator it_target = this->m_targets.find(_button);
	if (it_target == this->m_targets.end()) {
		TListeners listeners;
		listeners.insert(_p_sink);

		TActions actions;
		actions.insert(::std::make_pair(_action, listeners));

		m_targets.insert(::std::make_pair(_button, actions));
	}
	else {
		TActions::iterator it_action = it_target->second.find(_action);
		if (it_action == it_target->second.end()) {

			TListeners listeners;
			listeners.insert(_p_sink);
		
			it_target->second.insert(::std::make_pair(_action, listeners));
		}
		else {
			TListeners::iterator it_listener = it_action->second.find(_p_sink);
			if (it_listener != it_action->second.end())
				m_error << (err_code)TErrCodes::eObject::eExists;
			else
				it_action->second.insert(_p_sink);
		}
	}

	return TBase::Error();
}

err_code   CHandler::Unsubscribe (const CPlace::e_where _button, const CAction::e_type _action, IBtnEventSink* _p_sink) {
	_button; _action; _p_sink;
	TBase::m_error << __METHOD__ << __s_ok;

	CData data;
	if (false == data.Is_valid(_button, _action, _p_sink)) {
		return (TBase::m_error << data.Error().Result()) = data.Error().Desc();
	}

	SAFE_LOCK(TBase::m_guard);

	bool b_found = false;

	TTargets::iterator it_target = this->m_targets.find(_button);
	if (it_target != this->m_targets.end()) {
		TActions::iterator it_action = it_target->second.find(_action);
		if (it_action != it_target->second.end()) {
			TListeners::iterator it_listener = it_action->second.find(_p_sink);
			if (it_listener != it_action->second.end()) {
				it_action->second.erase(it_listener);
				b_found = true;
			}
		}
	}

	if (false == b_found)
		TBase::m_error << (err_code)TErrCodes::eObject::eNotFound;

	return TBase::Error();
}

/////////////////////////////////////////////////////////////////////////////

l_result   CHandler::OnMessage(uint32_t _u_msg, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_u_msg; _w_param; _l_param; _b_handled = false;
	l_result n_result = 0;

	CDecoder decoder; decoder.Do(_u_msg);
	CEvent evt;
	evt << decoder.Action() << decoder.Button() << (int32_t)GET_X_LPARAM(_l_param) >> (int32_t)GET_Y_LPARAM(_l_param) << (uint32_t)_w_param;

	n_result = this->Notify(evt); // expected: __s_ok - handled; __s_false or err_code - not handled;

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code   CHandler::Notify (const CEvent& _evt) const {
	_evt;
	TBase::m_error << __METHOD__ << __s_false; // the input event is not handled yet;

	if (false == _evt.Is_valid())
		return (TBase::m_error << __e_inv_arg) = _T("event object is not valid;");

	SAFE_LOCK(TBase::m_guard);

	CData data;
	const TListeners& listeners = data.Find(_evt, this->m_targets);

	if (true == data.Error())
		return (TBase::m_error = data.Error());

	if (listeners.empty())
		return (TBase::m_error << (err_code)TErrCodes::eData::eEmpty = _T("no subscibers;"));

	for (TListeners::const_iterator it_ = listeners.begin(); it_ != listeners.end(); ++it_) {
		
		IBtnEventSink* const p_sink = *it_;
		if (nullptr == p_sink) // looks like not possible, but nevertheless;
			continue;

		err_code n_result = p_sink->IEvtButton_OnReceive(_evt);
		if (__s_ok == n_result) { // the event is handled by the subscriber, so it just breaks the iteration;
			TBase::m_error << n_result; break;
		}
		if (__failed (n_result)) {
			m_error << n_result;
			break;
		}
	}

	return TBase::Error(); // if the event is not handled or an error occurs, __s_false is returned that indicates source window message is not handled;
}

/////////////////////////////////////////////////////////////////////////////

using e_where = CPlace::e_where;

CPlace:: CPlace (const e_where _place) : m_place (_place) {}
CPlace:: CPlace (const CPlace& _src) : CPlace() { *this = _src; }
CPlace:: CPlace (CPlace&& _victim) : CPlace() { *this = _victim; }
CPlace::~CPlace (void) {}

/////////////////////////////////////////////////////////////////////////////

bool     CPlace::Is_valid (void) const { return !!this->Where(); }
e_where  CPlace::Where (void) const { return this->m_place; }
bool     CPlace::Where (const e_where _place) { const bool b_changed = (this->Where() != _place); if (b_changed) this->m_place = _place; return b_changed; }

#if defined (_DEBUG)
CString  CPlace::Print(const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{where=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{where=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{where=%s;valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid()); CString cs_where = CPlaceWhere::To_string(this->Where());
	CString cs_out;

	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_where, (_pc_sz)cs_valid); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_where, (_pc_sz)cs_valid); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_where , (_pc_sz)cs_valid); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CPlace& CPlace::operator = (const CPlace& _src) { *this << _src.Where(); return *this; }
CPlace& CPlace::operator = (CPlace&& _victim)   { *this = _victim; _victim.Where(e_where::e__Undef); return *this; }
CPlace& CPlace::operator <<(const e_where _place){ this->Where(_place); return *this; }

/////////////////////////////////////////////////////////////////////////////

CVirtualKeys:: CVirtualKeys (const uint32_t _raw_keys) : m_keys(_raw_keys) {}
CVirtualKeys:: CVirtualKeys (const CVirtualKeys& _src) : CVirtualKeys() { *this = _src; }
CVirtualKeys:: CVirtualKeys (CVirtualKeys&& _victim  ) : CVirtualKeys() { *this= _victim; }
CVirtualKeys::~CVirtualKeys (void) {}

////////////////////////////////////////////////////////////////////////////

uint32_t CVirtualKeys::Get (void) const { return this->m_keys; }
bool     CVirtualKeys::Set (const uint32_t _keys, const bool _b_alt) {
	_keys; _b_alt;
	uint32_t raw_keys = _keys;
	// https://stackoverflow.com/questions/1811206/on-win32-how-to-detect-whether-a-left-shift-or-right-alt-is-pressed-using-perl ;
	if (_b_alt) { // alt key must be checked;
		const bool b_alt = ::GetKeyState(VK_MENU) < 0; // this is stated in ms document for left button mouse down, for instance  ;
		if ( b_alt) raw_keys |= e_keys::e_alt;
		if (!b_alt) raw_keys &=~e_keys::e_alt;
	}
	
	const bool b_changed = (this->Get() != raw_keys); if (b_changed) this->m_keys = raw_keys; return b_changed;
}

bool     CVirtualKeys::Has (const e_keys _key) const { return (this->Get() & _key); }

#if defined (_DEBUG)
CString  CVirtualKeys::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{keys=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{keys=%s}");
	static _pc_sz pc_sz_pat_r = _T("{keys=%s}");

	CString cs_keys = _virt_key_to_str(this->Get());
	CString cs_out;

	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_keys); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_keys); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_keys); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CVirtualKeys&  CVirtualKeys::operator = (const CVirtualKeys& _src) { this->Set(_src.Get(), false); return *this; }
CVirtualKeys&  CVirtualKeys::operator = (CVirtualKeys&& _victim) { *this = _victim; _victim.Set(0, false); return *this; }

CVirtualKeys&  CVirtualKeys::operator <<(const uint32_t _keys) { this->Set(_keys, true); return *this; }