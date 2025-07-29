#ifndef _SFXSTATUSEXT_H_INCLUDED
#define _SFXSTATUSEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2020 at 6:37:00a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack shared status bar control pane interface declaration file.
*/
#include "sfx.status.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace status {

	using namespace ex_ui::controls::sfx;

	// https://ux.stackexchange.com/questions/124588/whats-the-difference-between-a-panel-and-pane ;
	// https://en.wikipedia.org/wiki/Paned_window_(computing) ;

	class CPane /*: public ex_ui::controls::CPane*/ { /*typedef ex_ui::controls::CPane TBase;*/
	public:
		 CPane (void); CPane (const CPane&); CPane (CPane&&); // this 'move' constructor is just for copying data; 'move' operator is not defined;
		~CPane (void);

	public:
		const
		ex_ui::controls::pane::CFormat& Format (void) const;
		ex_ui::controls::pane::CFormat& Format (void) ;
		const
		ex_ui::controls::pane::CLayout& Layout (void) const;
		ex_ui::controls::pane::CLayout& Layout (void) ;

		_pc_sz  Text (void) const;
		bool    Text (_pc_sz)    ;

	public:
		CPane&  operator = (const CPane&); CPane& operator = (CPane&&) = delete;
		CPane&  operator <<(_pc_sz _p_text);
		CPane&  operator <<(const ex_ui::controls::pane::CFormat&);
		CPane&  operator <<(const ex_ui::controls::pane::CLayout&);

	private:
		CString m_text  ;
		ex_ui::controls::pane::CFormat m_format;
		ex_ui::controls::pane::CLayout m_layout;
	};

	typedef ::std::vector<CPane> TRawPanes;

	class CPanes {
	public:
		 CPanes (void); CPanes (const CPanes&) = delete; CPanes (CPanes&&) = delete;
		~CPanes (void);

	public:
		err_code   Add (_pc_sz _p_text = nullptr);
		err_code   Add (const CPane&) ; // no check for the added panel; if such a panel is already added, it is present twice;

		uint16_t   Count (void) const ;

		TError&    Error (void) const ;
		const
		CPane&     Pane (const uint16_t _ndx) const; // returns the reference to the pane by index; if out of range the reference to the fake pane is returned; (ro)
		CPane&     Pane (const uint16_t _ndx) ;      // returns the reference to the pane by index; if out of range the reference to the fake pane is returned; (rw)
		const
		TRawPanes& Raw (void) const;
		TRawPanes& Raw (void) ;

	public:
		CPanes&  operator = (const CPanes&) = delete; CPanes& operator = (CPanes&&) = delete;

	private:
		mutable
		CError    m_error;
		TRawPanes m_panes;
	};

}}}}

#endif/*_SFXSTATUSEXT_H_INCLUDED*/