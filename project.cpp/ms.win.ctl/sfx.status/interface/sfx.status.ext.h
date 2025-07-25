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

	class CPane : public ex_ui::controls::CPane { typedef ex_ui::controls::CPane TBase;
	public:
		 CPane (void); CPane (const CPane&); CPane (CPane&&); // this 'move' constructor is just for copying data; 'move' operator is not defined;
		~CPane (void);

	public:
		CPane&  operator = (const CPane&); CPane& operator = (CPane&&) = delete;
	};

	typedef ::std::vector<CPane> TRawPanes;

	class CPanes {
	public:
		 CPanes (void); CPanes (const CPanes&) = delete; CPanes (CPanes&&) = delete;
		~CPanes (void);

	public:
		err_code   Add (const CPane&) ; // no check for the added panel; if such a panel is already added, it is present twice;

		TError&    Error (void) const ;
		const
		TRawPanes& Raw (void) const;
		TRawPanes& Raw (void) ;

	public:
		CPanes&  operator = (const CPanes&) = delete; CPanes& operator = (CPanes&&) = delete;

	private:
		CError    m_error;
		TRawPanes m_panes;
	};

}}}}

#endif/*_SFXSTATUSEXT_H_INCLUDED*/