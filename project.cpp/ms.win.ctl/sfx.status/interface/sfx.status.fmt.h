#ifndef _SFX_STATUS_FMT_H_INCLUDED
#define _SFX_STATUS_FMT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Aug-2020 at 12:52:41p, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack Sfx status bar control format interface declaration file.
*/
#include "sfx.status.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace status { class CControl;

	using namespace ex_ui::controls::sfx;
	using TBase = ex_ui::controls::format::CBase;

namespace format {
	class CBorders : public ex_ui::controls::format::CBorders { typedef ex_ui::controls::format::CBorders TBase;
	public:
		CBorders (void); CBorders (const CBorders&) = delete; CBorders (CBorders&&) = delete; ~CBorders (void) = default;

		err_code  Set (void); // sets color quads' values from currently selected theme;

	private:
		CBorders& operator = (const CBorders&) = delete; CBorders& operator = (CBorders&&) = delete;
	};
}
	class CFormat : public TBase {
	friend class  CControl;
	private:
		 CFormat (CControl&); CFormat (void) = delete; CFormat (const CFormat&); CFormat (CFormat&&) = delete;
		~CFormat (void);

	public:
		const
		format::CBorders&  Borders (void) const;
		format::CBorders&  Borders (void) ;

		void Default (void);
	
	private:
		CFormat& operator = (const CFormat&) = delete;
		CFormat& operator = (CFormat&&) = delete;

	private:
		CControl&  m_ctrl;
		format::CBorders  m_borders; // the color of the pane borders; it looks like the name needs to be changed;
	};

}}}}

#if (0)
#include "shared.uix.ctrl.base.fmt.h"
namespace ST_Ctrls { namespace format {

	using ex_ui::controls::format::CBase;

	class CPanes {
	protected:
		CPane      m_normal;

	public:
		 CPanes (void);
		 CPanes (const CPanes&);
		~CPanes (void);

	public:
		const
		CPane&   Normal (void) const;
		CPane&   Normal (void)      ;

	public:
		CPanes& operator = (const CPanes&);
	};

	class CStatus : public TFmtBase { typedef TFmtBase TFormat;
	protected:
		CPanes   m_panes;
		DWORD    m_img_res;

	public:
		 CStatus (void);
		 CStatus (const CStatus&);
		~CStatus (void);

	public:
		DWORD     Images  (void) const;
		DWORD&    Images  (void)      ;
		const
		CPanes&   Panes (void) const;
		CPanes&   Panes (void)      ;

	public:
		CStatus&  operator = (const CStatus& );
		CStatus&  operator <<(const CPanes&  );
		CStatus&  operator <<(const DWORD _img_res);
	};

	class CSymantec_NA_Sta : public CStatus {
	                        typedef CStatus TBase;
	public:
		 CSymantec_NA_Sta (void);
		~CSymantec_NA_Sta (void);
	};

	class CWhitespread_Sta : public CStatus {
	                        typedef CStatus TBase;
	public:
		 CWhitespread_Sta (void);
		~CWhitespread_Sta (void);
	};
}}

typedef ST_Ctrls::format::CStatus  TStatusFmt;
#endif
#endif/*_SFX_STATUS_FMT_H_INCLUDED*/