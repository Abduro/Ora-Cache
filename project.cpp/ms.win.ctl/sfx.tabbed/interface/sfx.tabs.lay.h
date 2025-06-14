#ifndef _SFXTABSLAY_H_INCLUDED
#define _SFXTABSLAY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Aug-2020 at 7:31:11p, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared tabbed control layout interface declaration file;
*/
#include "sfx.tabs.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { class CControl;

	using CSides = ex_ui::controls::layout::CMargins_of_rect::CSides;
	using eSide  = ex_ui::controls::layout::CMargins_of_rect::CSides::_part;

	class CLayout;

namespace layout {

	using namespace ex_ui::controls::sfx::tabbed;
	using CLayout = ex_ui::controls::sfx::tabbed::CLayout;

	class CTabs { friend class ex_ui::controls::sfx::tabbed::CLayout;
	public :
		 CTabs (void); CTabs (const CTabs&) = delete; CTabs (CTabs&&) = delete;
		~CTabs (void);

	public:
		uint32_t  Gap (void) const;
		uint32_t& Gap (void)      ;
		bool      Gap (const uint32_t _u_value);

		uint32_t  Height(void) const;
		uint32_t& Height(void)      ;     // sets a height of all tabs;
		bool      Height(const uint32_t); // sets a height of all tabs; returns 'true' in case if the height value is changed;

		uint32_t  Ledge (void) const;
		uint32_t& Ledge (void)      ;
		bool      Ledge (const uint32_t);

		t_rect    Rect  (void) const;     // gets a rectangle of tabs area;

		eSide     Side  (void) const;     // gets a side where all tabs reside;
		eSide&    Side  (void)      ;     // sets a side where all tabs reside;
		bool      Side  (const TSide);
		// ToDo: t_size must be replaced to geometry::_2D::base::CSize_U;
		const
		t_size&   Size  (void) const;     // gets a size of each tab;
		uint32_t& Width (void)      ;     // sets a width of each tab;
		bool      Width (const uint32_t&);

	private:
		CTabs&  operator = (const CTabs&) = delete;
		CTabs&  operator = (CTabs&&) =  delete;

	private:
		CSides   m_sides  ;   // sides of tab control where tabs can be located; the top side is default;
		t_size   m_size   ;   // a size of each tab;
		t_rect   m_rect   ;   // entire area of tabs, including free space of the background;
		uint32_t m_gap    ;   // a gap between tabs;
		uint32_t m_ledge  ;   // extra part of tabs which resides out of tab area; this part of tabs overlaps parent window area; by default is 3;
	};
}

	class CLayout {
	friend class  CControl;
	private:
		 CLayout (CControl&); CLayout (void) = delete; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void);

	public:
		TError&   Error (void) const;

		err_code  Update (void) ;                    // updates the internal components' layout by using this control window client area;
		err_code  Update (const t_rect& _rc_area);   // updates tabbed control window position into an area provided;

	public:
		CLayout&  operator <<(const t_rect& _rc_area);        // updates tabbed control window position in accordance with area  ;
		t_rect    operator = (const t_rect& _rc_area) const;  // returns calculated rectangle of tabbed control for area provided;

	private:
		CLayout&  operator = (const CLayout&) = delete;
		CLayout&  operator = (CLayout&&) = delete;

	private:
		mutable
		CError    m_error ;
		CControl& m_ctrl  ;
	};

}}}}

#if(0)

namespace ST_Ctrls { class CTabbed; namespace layout {

	using shared::sys_core::CError;

	using ex_ui::controls::CSides;
	using ex_ui::controls::TSide ;
	using ex_ui::controls::CMargins;

	class CTabLayout {
	protected:
		mutable
		CError       m_error  ;
		CTabbed&     m_control;
		CTabs        m_tabs   ;
		CMargins     m_margins;

	public:
		 CTabLayout (CTabbed&);
		~CTabLayout (void);

	public:
		TErrorRef    Error  (void) const;
		const
		CMargins&    Margins(void) const;
		CMargins&    Margins(void)      ;
		RECT         Page   (void) const;           // gets tab page rectangle that is available for page window; for top-aligned tabs is implemented only;
		const
		CTabs&       Tabs   (void) const;
		CTabs&       Tabs   (void)      ;
		HRESULT      Update (void)      ;           // recalculates position/rectangle of all elements;
		HRESULT      Update (const RECT& _rc_area); // updates tab control window position into an area provided;

	public:
		CTabLayout&  operator<<(const RECT& _rc_area);        // updates tab control window position in accordance with area  ;
		const RECT   operator =(const RECT& _rc_area) const;  // returns calculated rectangle of tab control window for area provided;

	private: // non-copyable;
		CTabLayout (const CTabLayout&);
		CTabLayout& operator = (const CTabLayout&);
	};
}}

typedef ST_Ctrls::layout::CTabs       TTabs;
typedef ST_Ctrls::layout::TSide       TTabsSide;
typedef ST_Ctrls::layout::CTabLayout  TTabsLay ;
#endif

#endif/*_SFXTABSLAY_H_ED51B0CD_0B83_4607_923A_CC1046DCD60A_INCLUDED*/