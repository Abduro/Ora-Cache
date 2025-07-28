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

	using CImage = ex_ui::controls::layout::CImage;

namespace pane {

	class CFormat : public CFmtBase {
	public:
		 CFormat (void); CFormat (const CFormat&); CFormat (CFormat&&) = delete; // is not required yet;
		~CFormat (void) = default;

	public:
		int32_t  Image_Ndx (void) const;     // returns image index; if not set -1 or other negative value; uint32_t would be better possibly, but image list uses int;
		bool     Image_Ndx (const int32_t);  // sets image index value; returns 'true' in case of change; setting negative value means 'not set';
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CFormat& operator = (const CFormat&); CFormat& operator = (CFormat&&) = delete;
		CFormat& operator <<(const int32_t _img_ndx);
		const
		CFmtBase& operator ()(void) const;
		CFmtBase& operator ()(void) ;

		operator const int32_t (void) const; // returns image index;

	private:
		int32_t  m_img_ndx;
	};

	class CLayout {
	public:
		 CLayout (void); CLayout (const CLayout&); CLayout (CLayout&&) = delete; // is not required yet;
		~CLayout (void) = default;    // there's nothig to free;

		const
		CAlign&  Align (void) const;  // the font spec has already the alignment, but for the text only; this alignment is for entire pane;
		CAlign&  Align (void) ;
		const
		CImage&  Image (void) const;  // if the pane does not have an image the image layout indicates 'false';
		CImage&  Image (void) ;	      // if the pane does not have an image the image layout indicates 'false';
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		const
		t_rect&  Rect  (void) const;
		t_rect&  Rect  (void);

		bool  Update (void);          // updates the sizes and points of components of the pane; a position of the pane is calculated;
		bool  Update (const t_rect&); // updates the sizes and points of components of the pane; a position is set by input rect;

	public:
		CLayout& operator = (const CLayout&); CLayout& operator = (CLayout&&) = delete; // is not required yet;
		CLayout& operator <<(const CAlign& ); // sets the alignment of the pane;
		CLayout& operator <<(const CImage& ); // makes a copy of the input image layout;
		CLayout& operator <<(const t_rect& ); // calls Update(rect);

	private:
		CAlign   m_align; // this is a pane elements' alignment;
		CImage   m_image; // an image layout if any image is assigned to the pane;
		t_rect   m_rect ; // this is entire area of the pane;
	};
}
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
			CPane&  Pane (void) const;   // it is just for copy constructor of this class;
			CPane&  Pane (void) ;	     // it is just for copy constructor of this class;

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
			CAlign& Align (void) const;  // the font spec has already the alignment, but for the text only; this alignment is for entire pane;
			CAlign& Align (void) ;
			const
			CImage& Image (void) const;  // if this pane does not have an image the image layout indicates 'false';
			CImage& Image (void) ;	     // if this pane does not have an image the image layout indicates 'false';
			const
			CPane&  Pane  (void) const;  // it is just for copy constructor of this class;
			CPane&  Pane  (void) ;	     // it is just for copy constructor of this class;
#if (0)
			const
			CPos& Pos (void) const;      // the shortcut for Position(); (ro)
			CPos& Pos (void) ;           // the shortcut for Position(); (rw)
			const
			CPos& Position (void) const; // gets a reference to current position of the pane; (ro)
			CPos& Position (void) ;      // gets a reference to current position of the pane; (rw)
#endif
#if defined(_DEBUG)
			CString Print(const e_print = e_print::e_all) const;
#endif
			const
		    t_rect& Rect (void) const;
		    t_rect& Rect (void);
			bool  Update (void);                         // updates the sizes and points of components of the pane; a placement of the pane is calculated;
			bool  Update (const t_rect& _rect_of_place); // updates the sizes and points of components of the pane; a placement is set by input rect;

		public:
			CLayout& operator = (const CLayout&);
			CLayout& operator = (CLayout&&) = delete;

			CLayout& operator <<(const CAlign&);
		//	CLayout& operator <<(const CPosition&);

		private:
			CAlign    m_align; // this pane elements' alignment;
			CImage    m_image; // an image layout if any image is assigned to this panel;
			CPane&    m_pane ;
#if (0)
			CPosition m_position;
#endif
			t_rect    m_rect ; // this is entire area of this pane;
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