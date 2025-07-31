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

	class CPane {
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

		_pc_sz  Text (void) const;
		bool    Text (_pc_sz)    ;

	public:
		CPane&  operator = (const CPane&); CPane& operator = (CPane&&) = delete;
		CPane&  operator <<(_pc_sz _p_text);
		CPane&  operator <<(const ex_ui::controls::pane::CFormat&);
		CPane&  operator <<(const TPn_Lay&);

	protected:
		CString m_text  ;
		ex_ui::controls::pane::CFormat m_format;
		TPn_Lay m_layout;
	};

	typedef ::std::vector<CPane> TRawPanes;

	class CGlyph : public CPane { typedef CPane TBase;
	public:
		 CGlyph (void); CGlyph (const CGlyph&) = delete; CGlyph (CGlyph&&) = delete; // this class is not put into container so there is no 'copy' and 'move' constructors nor operators;
		~CGlyph (void);

	private:
		CGlyph& operator = (const CGlyph&) = delete; CGlyph& operator = (CGlyph&&) = delete;
	};

	class CPanes {
	public:
		 CPanes (void); CPanes (const CPanes&) = delete; CPanes (CPanes&&) = delete;
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
		TRawPanes& Raw (void) ;

	public:
		CPanes&  operator = (const CPanes&) = delete; CPanes& operator = (CPanes&&) = delete;

	private:
		mutable
		CError    m_error;
		TRawPanes m_panes;
		CGlyph    m_glyph;
	};

}}}}

#endif/*_SFXSTATUSEXT_H_INCLUDED*/