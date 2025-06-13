#ifndef _SFXTABSFMT_H_INCLUDED
#define _SFXTABSFMT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jul-2020 at 11:53:29p, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack Sfx tab control format interface declaration file.
*/
#include "sfx.tabs.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { class CControl;

	using namespace ex_ui::controls::sfx;
	using TBase = ex_ui::controls::format::CBase;

namespace format {
}
	class CFormat : public TBase {
	friend class  CControl;
	private:
		 CFormat (CControl&); CFormat (void) = delete; CFormat (const CFormat&); CFormat (CFormat&&) = delete;
		~CFormat (void);

	public:
		void Default (void);
	
	private:
		CFormat& operator = (const CFormat&) = delete;
		CFormat& operator = (CFormat&&) = delete;

	private:
		CControl&  m_ctrl;
	};

}}}}
#if (0)
#include "shared.uix.ctrl.base.fmt.h"
namespace ST_Ctrls { namespace format {

	using ex_ui::controls::CBorder ;
	using ex_ui::controls::CBorders;
	using ex_ui::draw::shape::CCorner;
	using ex_ui::draw::shape::CCorners;

	using ex_ui::controls::format::CBase;

	class CTab_Base : public TFmtBase { typedef TFmtBase TFormat;
	protected:
		CBorders    m_borders;
		CCorners    m_corners;

	protected:
		 CTab_Base (void);
		 CTab_Base (const CTab_Base&);
		~CTab_Base (void);

	public:
		const
		CBorders&   Borders (void) const;
		CBorders&   Borders (void)      ;

	public:
		CTab_Base&  operator = (const CTab_Base&);
		CTab_Base&  operator <<(const CBorders& );
	};

	class CTab : public CTab_Base { typedef CTab_Base TTab;
	public:
		 CTab (void) ;
		 CTab (const CTab&);
		~CTab (void) ;

	public:
		CTab& operator = (const CTab&);
	};

	class CTabs {
	private:
		CTab  m_active  ;
		CTab  m_disabled;
		CTab  m_normal  ;

	public:
		 CTabs (void) ;
		 CTabs (const CTabs&);
		~CTabs (void) ;

	public:
		const
		CTab&   Active (void) const;
		CTab&   Active (void)      ;
		const
		CTab&   Disabled (void) const;
		CTab&   Disabled (void)      ;
		const
		CTab&   Normal (void) const;
		CTab&   Normal (void)      ;

	public:
		CTabs&  operator = (const CTabs&);
	};

	class CTabFormat : public TFmtBase { typedef TFmtBase TFormat;
	protected:
		CTabs      m_tabs;
		CBorders   m_borders;

	public:
		 CTabFormat (void);
		 CTabFormat (const CTabFormat&);
		~CTabFormat (void);

	public:
		const
		CBorders&  Borders (void) const;
		CBorders&  Borders (void)      ;
		const
		CTabs&     Tabs (void) const;
		CTabs&     Tabs (void)      ;

	public:
		CTabFormat& operator = (const CTabFormat&);
		CTabFormat& operator <<(const CBorders&);
		CTabFormat& operator <<(const CTabs&);
	};

	class CSymantec_NA_Tab : public CTabFormat {
	                        typedef CTabFormat TBase;
	public:
		 CSymantec_NA_Tab (void);
		~CSymantec_NA_Tab (void);
	};

	class CWhitespread_Tab : public CTabFormat {
	                        typedef CTabFormat TBase;
	public:
		 CWhitespread_Tab (void);
		~CWhitespread_Tab (void);
	};
}}

typedef ex_ui::controls::CBorders    TTabBorders;
typedef ST_Ctrls::format::CTab       TTabFormat ;
typedef ST_Ctrls::format::CTabFormat TTabbedFmt ;
#endif
#endif/*_SFXTABSFMT_H_D9B720FB_42AC_434C_B055_2F7BC83DECE9_INCLUDED*/