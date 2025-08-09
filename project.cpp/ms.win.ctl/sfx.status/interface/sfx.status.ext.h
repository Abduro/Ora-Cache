#ifndef _SFXSTATUSEXT_H_INCLUDED
#define _SFXSTATUSEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2020 at 6:37:00a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack shared status bar control pane interface declaration file.
*/
#include "sfx.status.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace status { class CControl;

	using namespace ex_ui::controls::sfx;

	// https://ux.stackexchange.com/questions/124588/whats-the-difference-between-a-panel-and-pane ;
	// https://en.wikipedia.org/wiki/Paned_window_(computing) ;
namespace pane {

	using CLay_Style = ex_ui::controls::sfx::status::layout::CStyle;

	class CLayout : public ex_ui::controls::pane::CLayout { typedef ex_ui::controls::pane::CLayout TBase;
	public:
		 CLayout (void); CLayout (const CLayout&); CLayout (CLayout&&);
		~CLayout (void) = default;
	public:
		uint32_t Fixed (void) const;     // gets a width value of the pane;
		bool     Fixed (const uint32_t); // sets a fixed size value; returns 'true' in case of value change;
		const
		CLay_Style&  Style (void) const;
		CLay_Style&  Style (void) ;

	public:
		CLayout& operator = (const CLayout&); CLayout& operator = (CLayout&&) = delete;
		CLayout& operator <<(const uint32_t _n_fixed);

	private:
		uint32_t   m_fixed;  // it is used in case if the layout style is set in appropriate value;
		CLay_Style m_style;
	};
}
	typedef pane::CLayout TPn_Lay;

	interface IPaneEvents {
		virtual void  OnTextChanged(const uint32_t _pane_id, _pc_sz _p_text = nullptr) const { _pane_id; _p_text; }
	};

	class CPane : public ex_ui::controls::CPane { typedef ex_ui::controls::CPane TBase;
	public:
		 CPane (void); CPane (const CPane&); CPane (CPane&&); // this 'move' constructor is just for copying data; 'move' operator is not defined;
		~CPane (void);

	public:
		const
		ex_ui::controls::pane::CFormat& Format (void) const;
		ex_ui::controls::pane::CFormat& Format (void) ;

		const
		TPn_Lay& Layout (void) const;
		TPn_Lay& Layout (void) ;
		
		bool    SetSink (const IPaneEvents*); // for events' notifications; it is assumed all notifications are in the main thread of the GUI, thus it is not thread safe;

		_pc_sz  Text (void) const; // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-redrawwindow ; it should work on text change;
		bool    Text (_pc_sz)    ; // what should be taken if the text has been just changed? how to call refreshing of the pane?

		bool    Update (void) ;    // applies layout to the pane components;

	public:
		CPane&  operator = (const CPane&); CPane& operator = (CPane&&) = delete;
		CPane&  operator <<(_pc_sz _p_text);
		CPane&  operator <<(const ex_ui::controls::pane::CFormat&);
		CPane&  operator <<(const TPn_Lay&);

	protected:
		const
		IPaneEvents* GetSink (void) const;
		CPane&  operator <<(const IPaneEvents*);

	protected:
		ex_ui::controls::pane::CFormat m_format;
		const IPaneEvents*  m_evt_sink;
		TPn_Lay  m_layout;
		CString  m_text;
	};

	typedef ::std::vector<CPane> TRawPanes;

	class CGlyph : public CPane { typedef CPane TBase;
	public:
		 CGlyph (void); CGlyph (const CGlyph&) = delete; CGlyph (CGlyph&&) = delete; // this class is not put into container so there is no 'copy' and 'move' constructors nor operators;
		~CGlyph (void);

	private:
		CGlyph& operator = (const CGlyph&) = delete; CGlyph& operator = (CGlyph&&) = delete;
	};

	class CPanes : public IPaneEvents {
	public:
		 CPanes (CControl&); CPanes (void) = delete; CPanes (const CPanes&) = delete; CPanes (CPanes&&) = delete;
		~CPanes (void);

	public:
		err_code   Add (_pc_sz _p_text = nullptr);
		err_code   Add (const CPane&) ; // no check for the added panel; if such a panel is already added, it is present twice;

		uint16_t   Count(void) const ;

		TError&    Error(void) const ;
		const
		CGlyph&    Glyph(void) const;
		CGlyph&    Glyph(void) ;
		const
		CPane&     Pane (const uint16_t _ndx) const; // returns the reference to the pane by index; if out of range the reference to the fake pane is returned; (ro)
		CPane&     Pane (const uint16_t _ndx) ;      // returns the reference to the pane by index; if out of range the reference to the fake pane is returned; (rw)
		const
		TRawPanes& Raw (void) const;
		TRawPanes& Raw (void) ;        // no remove is assumed, otherwise pane indices must be reset;

	public:
		CPanes&  operator = (const CPanes&) = delete; CPanes& operator = (CPanes&&) = delete;

	private:
		void  OnTextChanged (const uint32_t _pane_id, _pc_sz _p_text) const;

	private:
		mutable
		CError    m_error;
		CControl& m_ctrl ;
		TRawPanes m_panes;
		CGlyph    m_glyph;
	};

}}}}

#endif/*_SFXSTATUSEXT_H_INCLUDED*/