#ifndef _SFXSTATUSEXT_H_INCLUDED
#define _SFXSTATUSEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2020 at 6:37:00a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack shared status bar control panel interface declaration file.
*/
#include "sfx.status.inc.h"

namespace ex_ui { namespace controls { namespace sfx {

	using CPane_Base = ex_ui::controls::CPane;

	class CPane : public CPane_Base { typedef CPane_Base TBase;
	};

}}}

#if (0)
#include "sfx.status.lay.h"

namespace ST_Ctrls { class CStatus;

	using ex_ui::controls::CAlign ;
	using ex_ui::controls::CStyle ;
	using ex_ui::controls::format::CBorders_Ex;

	class CPanel_Child {
	private:
		HWND   m_child;  // handle is not controlled by panel;
		TAlign m_align;
		CStyle m_style;  // window position style, for example, SWP_NOSIZE|SWP_NOACTIVATE is set by default;

	public:
		 CPanel_Child (void);
		 CPanel_Child (const CPanel_Child&);
		~CPanel_Child (void);

	public:
		const
		TAlign&  Align(void) const;
		TAlign&  Align(void)      ;
		HWND   Handle (void) const;
		HWND&  Handle (void)      ;  // NULL is also applicable and makes this child is not valid for processing by layout update procedure;
		bool     Is   (void) const;  // returns true if child window handle is valid and successfully checked by ::IsWindow() procedure;
		const
		CStyle&  Style(void) const;
		CStyle&  Style(void)      ;

	public:
		CPanel_Child& operator = (const CPanel_Child&);
		CPanel_Child& operator <<(const CAlign&);
		CPanel_Child& operator <<(const CStyle&);
		CPanel_Child& operator <<(const HWND)   ;
	};

	class CPanel { friend class ST_Ctrls::layout::CStatus_Layout;
	protected:
		DWORD         m_id     ;
		TPanelLay     m_layout ;
		INT           m_img_ndx;   // by default is -1 that means no image is used inside this panel;
		CBorders_Ex   m_borders;   // actually, they are exposed through format namespace, but are based on control's borders;
		CPanel_Child  m_child  ;

	public:
		 CPanel (void);
		 CPanel (const CPanel&);
		 CPanel (const DWORD _id, LPCWSTR _lp_sz_text);
		~CPanel (void);

	public:
		const
		CBorders_Ex& Borders (void) const;
		CBorders_Ex& Borders (void)      ;
		const
		CPanel_Child& Child(void) const;
		CPanel_Child& Child(void)      ;
		DWORD        ID    (void) const;
		DWORD&       ID    (void)      ;
		INT          Image_Ndx (void) const;  // gets image index in image list component;
		INT&         Image_Ndx (void)      ;  // sets image index in image list component;
		const
		TPanelLay&   Layout(void) const;
		TPanelLay&   Layout(void)      ;
		LPCWSTR      Text  (void) const;  // actually this is indirect access to layout text part;
		CStringW&    Text  (void)      ;  // actually this is indirect access to layout text part;

	public:
		CPanel&    operator = (const CPanel&);
		CPanel&    operator <<(const CBorders_Ex&);
		CPanel&    operator <<(const CPanel_Child&);
		CPanel&    operator <<(const CStringW& _cs_text);
		CPanel&    operator <<(const DWORD _panel_id);
		CPanel&    operator <<(LPCWSTR _lp_sz_text);
	};

	typedef ::std::vector<CPanel> TPanels;

	class CPanels { friend class ST_Ctrls::layout::CStatus_Layout;
	public:
		enum _na : INT { e_na = -1 };
	private:
		TPanels   m_panels;
		CError    m_error ;

	public:
		 CPanels (void);
		 CPanels (const CPanels&);
		~CPanels (void);

	public:
		HRESULT   Add   (const CPanel&) ;
		HRESULT   Add   (const DWORD _id, LPCWSTR _lp_sz_text);
		UINT      Count (void) const;
		INT       Has   (const DWORD _id) const;
		TErrorRef Error (void) const;
		const
		CPanel&   Panel (const DWORD _ndx) const;
		CPanel&   Panel (const DWORD _ndx)      ;
		const
		TPanels&  Raw   (void) const;
		TPanels&  Raw   (void)      ;
		HRESULT   Remove(const CPanel&)  ;      // might be dangerous in case if provided panel belongs to internal data vector;
		HRESULT   Remove(const DWORD _id);

	public:
		CPanels&  operator = (const CPanels&) ;
		CPanels&  operator+= (const CPanel& ) ;
		CPanels&  operator-= (const CPanel& ) ; // might be dangerous in case if provided panel belongs to internal data vector;
		CPanels&  operator-= (const DWORD _id);
		bool      operator== (const DWORD _id);

	public:
		INT operator << (const DWORD _id) const; // returns an index of panel in internal data vector;
	};
}

typedef ST_Ctrls::CPanel_Child  TPanelChild;
#endif
#endif/*_SFXSTATUSEXT_H_INCLUDED*/