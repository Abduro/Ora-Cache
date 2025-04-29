#ifndef _HANDLER_MOUSE_BUTTON_H_INCLUDED
#define _HANDLER_MOUSE_BUTTON_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Oct-2024 at 18:16:30.518, UTC+4, Batumi, Monday;
	This is Ebo Pack shared mouse buttons' window message handler interface declaration file;
*/
#include "handler.base.h"
#include "2D.base.h"

namespace ex_ui { namespace message { namespace handlers { namespace mouse { namespace buttons {

	using CPoint = geometry::base::_2D::CPoint;

	using CError = shared::sys_core::CError;
	using TError = const CError;

	class CAction {
	public:
		enum e_type : uint32_t {
		     e__undef   = 0x0, // the type of action is undefined; this is default value;
		     e_double   = 0x1, // this is double click by the mouse button;
		     e_pressed  = 0x2, // a particular mouse button is being pressed;
		     e_released = 0x3, // a particular mouse button is released;
		};

	public:
		 CAction (const e_type = e_type::e__undef);
		 CAction (const CAction&);
		 CAction (CAction&&);
		~CAction (void);

	public:
		bool  Is_valid (void) const;   // returns true in case when e_type is not assigned to e__undef value;
		e_type    Type (void) const;
		bool      Type (const e_type); // returns true in case of changing value;

#if defined (_DEBUG)
		CString   Print(const e_print = e_print::e_all) const;
#endif
	public:
		CAction&  operator = (const CAction&);
		CAction&  operator = (CAction&&);
		CAction&  operator <<(const e_type);

	private:
		e_type    m_type;
	};

	class CPlace { // place is declared before button class due to the latter uses this class object, not pointer to it, so compiler makes the rule;
	public:
		enum e_where : uint32_t {
		     e__Undef = 0, e_Left = MK_LBUTTON , e_Middle = MK_MBUTTON , e_Right = MK_RBUTTON , e_X_1 = MK_XBUTTON1, e_X_2 = MK_XBUTTON2,
		};
	public:
		 CPlace (const e_where = e_where::e__Undef);
		 CPlace (const CPlace&);
		 CPlace (CPlace&&);
		~CPlace (void);

	public:
		bool Is_valid (void) const;     // returns true if place is defined;
		e_where Where (void) const;
		bool    Where (const e_where);  // returns true if placement is changed;

#if defined (_DEBUG)
		CString   Print(const e_print = e_print::e_all) const;
#endif
	public:
		CPlace& operator = (const CPlace&);
		CPlace& operator = (CPlace&&);
		CPlace& operator <<(const e_where);

	private:
		e_where m_place;
	};

	class CButton {
	public:
		 CButton (void);
		 CButton (const CButton&);
		 CButton (CButton&&) = delete;
		~CButton (void);

	public:
		bool  Is_valid (void) const;
		const
		CPlace&  Place (void) const;
		CPlace&  Place (void) ;

#if defined (_DEBUG)
		CString   Print(const e_print = e_print::e_all) const;
#endif

	public:
		CButton& operator = (const CButton&);
		CButton& operator = (CButton&&) = delete;
		CButton& operator <<(const CPlace&);

	private:
		CPlace  m_place;
	};

	class CVirtualKeys {
	public:
		enum e_keys : uint32_t {
		     e_alt   = FALT    ,  // alt-key is not defined in mouse message virtual keys, but the definition for keyboard accelerators is fine;        
		     e_ctrl  = FCONTROL,  // the same as MK_CONTROL [0x0008] ;
		     e_shift = FSHIFT   , // the same as MK_SHIFT   [0x0004] ;
		};
	public:
		 CVirtualKeys (const uint32_t _raw_keys = 0);
		 CVirtualKeys (const CVirtualKeys&);
		 CVirtualKeys (CVirtualKeys&&);  // it doesn't seem to be necessary, but following the habit;
		~CVirtualKeys (void);

	public:
		uint32_t  Get (void) const;
		bool      Set (const uint32_t, const bool _b_alt); // returns true if keys' value is changed; important: alt-key must be checked if necessary;

		bool Has (const e_keys _key) const;
#if defined (_DEBUG) // copy & paste works here :D
		CString   Print(const e_print = e_print::e_all) const;
#endif

	public:
		CVirtualKeys&  operator = (const CVirtualKeys&);      // this operator copies virtual key value without checking alt-key is being pressed or not;
		CVirtualKeys&  operator = (CVirtualKeys&&);
		CVirtualKeys&  operator <<(const uint32_t _raw_keys); // this operator checks pressing alt-key during set operation;

	private:
		uint32_t  m_keys;
	};

	typedef CVirtualKeys t_vkeys;

	class CEvent {
	public:
		 CEvent (void);
		 CEvent (const CEvent&);
		 CEvent (const CAction::e_type, const CPlace::e_where, const int32_t _cursor_x, const int32_t _cursor_y);
		 CEvent (CEvent&&) = delete;
		~CEvent (void);

	public:
		const
		CAction& Action (void) const;
		CAction& Action (void) ;
		const
		CButton& Button (void) const;
		CButton& Button (void) ;
		const
		CPoint&  Point  (void) const;
		CPoint&  Point  (void) ;

		bool  Is_valid  (void) const; // returns true in case when action and button attributes are valid both, otherwise there is no sense in this event;

#if defined (_DEBUG)
		CString   Print(const e_print = e_print::e_all) const;
#endif
		const
		t_vkeys&  VKeys(void) const;
		t_vkeys&  VKeys(void) ;

	public:
		CEvent& operator = (const CEvent&);
		CEvent& operator = (CEvent&&) = delete;

		CEvent& operator <<(const CAction&);
		CEvent& operator <<(const CButton&);
		CEvent& operator <<(const CPoint& );           // for setting cursor location in client area coordinate system; ToDo: what is about non-client area?
		CEvent& operator <<(const t_vkeys&);
		// operators for assigning primitive values ;
		CEvent& operator <<(const CAction::e_type);    // for convenient assignment an action type via redirection;
		CEvent& operator <<(const CPlace::e_where);    // for convenient assignment a button place via redirection;

		CEvent& operator <<(const int32_t _cursor_x);
		CEvent& operator >>(const int32_t _cursor_y);

		CEvent& operator <<(const uint32_t _v_keys) ;  // sets virtual keys from window message, alt+key check is turned on;

	private:
		CAction m_action;
		CButton m_button;
		CPoint  m_point ;
		t_vkeys m_vkeys ;
	};

	/*
		Window messages for all mouse buttons have the same input arguments or message segnature;
		Thus a mouse button message handler may have only one method for capturing messages like this:
		OnMessage(button={left|middle|right|x1|x2}, action={pressed|released|double click}, point={x|y});
	*/

	interface IBtnEventSink {
		virtual err_code IEvtButton_OnReceive(const CEvent&);
	};

	class CHandler : public CBase { typedef CBase TBase;
	public:
		// there is no care about better data container yet;
		typedef ::std::set<IBtnEventSink*> TListeners;                      // a set of listeners' plain pointers; using smart pointers would be better;
		typedef ::std::map<const CAction::e_type, TListeners>  TActions;    // associating a set of listeners with particular action;
		typedef ::std::map<const CPlace::e_where, TActions> TTargets;       // associating action types with particular mouse button;

	public:
		 CHandler (void);
		 CHandler (const CHandler&) = delete;
		 CHandler (CHandler&&) = delete;
		~CHandler (void);

	public:
		BEGIN_MSG_MAP(CHandler)
			MESSAGE_HANDLER (WM_LBUTTONDBLCLK, OnMessage ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttondblclk ;
			MESSAGE_HANDLER (WM_LBUTTONDOWN  , OnMessage ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttondown   ;
			MESSAGE_HANDLER (WM_LBUTTONUP    , OnMessage ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttonup     ;
			MESSAGE_HANDLER (WM_MBUTTONDBLCLK, OnMessage ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mbuttondblclk ;
			MESSAGE_HANDLER (WM_MBUTTONDOWN  , OnMessage ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mbuttondown   ;
			MESSAGE_HANDLER (WM_MBUTTONUP    , OnMessage ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mbuttonup     ;
			MESSAGE_HANDLER (WM_RBUTTONDBLCLK, OnMessage ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttondblclk ;
			MESSAGE_HANDLER (WM_RBUTTONDOWN  , OnMessage ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttondown   ;
			MESSAGE_HANDLER (WM_RBUTTONUP    , OnMessage ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttonup     ;
		END_MSG_MAP()

	protected:
		l_result OnMessage(uint32_t, w_param, l_param, int32_t&); // this function creates appropriate event object and notifies subscriber(s);

	public:
		err_code  Subscribe (const CPlace::e_where _button, const CAction::e_type _action, IBtnEventSink*);
		err_code  Unsubscribe (const CPlace::e_where _button, const CAction::e_type _action, IBtnEventSink*);

	public:
		err_code  Notify (const CEvent&) const; // notifies susbsciber(s) by event object;

	private:
		CHandler& operator = (const CHandler&) = delete;
		CHandler& operator = (CHandler&&) = delete;

	private:
		TTargets  m_targets;
	};

}}}}}

#endif/*_HANDLER_MOUSE_BUTTON_H_INCLUDED*/