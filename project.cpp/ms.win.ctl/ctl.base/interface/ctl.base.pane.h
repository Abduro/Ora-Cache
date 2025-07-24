#ifndef _CTL_BASE_PANE_H_INCLUDED
#define _CTL_BASE_PANE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-May-2025 at 11:36:46.866, UTC+4, Batumi, Tuesday;
	This is Ebo Pack user control base pane interface declaration file;
*/
#include "ctl.base.defs.h"
#include "ctl.base.format.h"

namespace ex_ui { namespace controls {

	using CFmtBase  = ex_ui::controls::format::CBase;
	using CPosition = geometry::_2D::base::CPosition;
	using CPos = CPosition;

	using namespace ex_ui::controls::format;

	// https://en.wikipedia.org/wiki/Paned_window_(computing) ;
	// http://ptitben2000.chez.com/info/lookandfeel/higk.htm ;
	// https://ux.stackexchange.com/questions/124588/whats-the-difference-between-a-panel-and-pane ;

	class CPane {
	public:
		class CFormat : public CFmtBase {
		private:
			CFormat (void) = delete;
			CFormat (CPane&); CFormat (const CFormat&); CFormat (CFormat&&) = delete; ~CFormat (void) = default;

		const
		CPane&  Pane (void) const;
		CPane&  Pane (void) ;

		public:
			int32_t  Image_Ndx (void) const;     // returns image index; if not set -1;
			bool     Image_Ndx (const int32_t);  // sets image index value; returns 'true' in case of change;
#if defined(_DEBUG)
		CString Print(const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		public:
			CFormat& operator = (const CFormat&);
			CFormat& operator = (CFormat&&) = delete;
		private:
			CPane&    m_pane ;
			int32_t   m_img_ndx;
			friend class CPane;		
		};

		class CLayout {
			friend class CPane;
		private:
			CLayout (void) = delete;
			CLayout (CPane&); CLayout (const CLayout&); CLayout (CLayout&&) = delete; ~CLayout (void) = default;

		public:
			const
			CAlign& Align (void) const;  // the font spec has already the alignment but for the text only; this alignment is for entire pane;
			CAlign& Align (void)      ;
			const
			CPane&  Pane (void) const;
			CPane&  Pane (void) ;
			const
			CPos& Pos (void) const;      // the shortcut for Position(); (ro)
			CPos& Pos (void) ;           // the shortcut for Position(); (rw)
			const
			CPos& Position (void) const; // gets a reference to current position of the pane; (ro)
			CPos& Position (void) ;      // gets a reference to current position of the pane; (rw)
#if defined(_DEBUG)
			CString Print(const e_print = e_print::e_all) const;
#endif
			bool  Update (void);                         // updates the sizes and points of components of the pane; a placement of the pane is calculated;
			bool  Update (const t_rect& _rect_of_place); // updates the sizes and points of components of the pane; a placement is set by input rect;

		public:
			CLayout& operator = (const CLayout&);
			CLayout& operator = (CLayout&&) = delete;

			CLayout& operator <<(const CAlign&);
			CLayout& operator <<(const CPosition&);

		private:
			CAlign    m_align   ;  // this pane elements alignment;
			CPane&    m_pane;
			CPosition m_position;
		};

	public:
		 CPane (void); CPane (const CPane&); CPane (CPane&&);
		~CPane (void);

	public:
#if (0)
		const
		CBorders& Borders (void) const;
		CBorders& Borders (void) ;
#endif
		const
		CFormat&  Format  (void) const;
		CFormat&  Format  (void) ;
		const
		CLayout&  Layout  (void) const;
		CLayout&  Layout  (void) ;

		err_code  Draw (const HDC, const t_rect& _drw_area) const;
#if defined(_DEBUG)
		CString Print(const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CPane& operator = (const CPane&);
		CPane& operator = (CPane&&);      // just copying fields' data, neither move() nor swap() operation is applied;
#if (0)
		CPane& operator <<(const CBorders&);
#endif
		CPane& operator <<(const CFormat&);
		CPane& operator <<(const CLayout&);

	protected:
		CBorders  m_borders;
		CFormat   m_format;
		CLayout   m_layout;
	};
}}


#endif/*_CTL_BASE_PANE_H_INCLUDED*/