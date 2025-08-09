#ifndef _CTL_BASE_PANE_H_INCLUDED
#define _CTL_BASE_PANE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-May-2025 at 11:36:46.866, UTC+4, Batumi, Tuesday;
	This is Ebo Pack user control base pane interface declaration file;
*/
#include "ctl.base.defs.h"
#include "ctl.base.format.h"
#include "ctl.base.border.h"
#include "ctl.base.layout.h"

namespace ex_ui { namespace controls {

	using CFmtBase  = ex_ui::controls::format::CBase;
	using CPosition = geometry::_2D::base::CPosition;
	using CPos = CPosition;

	using namespace ex_ui::controls::format;

	using CBorders = ex_ui::controls::borders::CBorders_for_rect;
	using CPadding = ex_ui::controls::layout::CPadding_of_rect;

namespace pane {

	class CFormat : public CFmtBase {
	public:
		class CImage {
		public: static const int32_t not_set = -1;
		public:
			 CImage (void); CImage (const CImage&); CImage (CImage&&) = delete;
			~CImage (void) = default;
		public:
			int32_t Index (void) const;    // returns image index; if not set -1 or other negative value; uint32_t would be better possibly, but image list uses int;
			bool    Index (const int32_t); // sets image index value; returns 'true' in case of change; setting negative value means 'not set';
			bool    Is_set(void) const;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		public:
			CImage& operator = (const CImage&); CImage& operator = (CImage&&) = delete;
			CImage& operator <<(const int32_t _n_ndx);

			operator const int32_t (void) const; // returns image index;
		private:
			int32_t m_index;
		};
	public:
		 CFormat (void); CFormat (const CFormat&); CFormat (CFormat&&) = delete; // is not required yet;
		~CFormat (void) = default;

	public:
		const
		CFormat::CImage& Image (void) const;
		CFormat::CImage& Image (void) ;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CFormat& operator = (const CFormat&); CFormat& operator = (CFormat&&) = delete;
		CFormat& operator <<(const CFormat::CImage&);
		const
		CFmtBase& operator ()(void) const;
		CFmtBase& operator ()(void) ;

	private:
		CFormat::CImage m_image;
	};

	using CImage = ex_ui::controls::layout::CImage;
	/*
		*Note*:
		TThe image margins are the surrounding area of the image;
		Pane padding is the space between the pane context and its borders;
	*/
	class CLayout { // ToDo: how does this layout know of the format that is applied to the pane which it belongs to? 
	public:
		 CLayout (void); CLayout (const CLayout&); CLayout (CLayout&&) = delete; // is not required yet;
		~CLayout (void) = default;    // there's nothig to free;

		const
		CAlign&  Align (void) const;  // the font spec has already the alignment, but for the text only; this alignment is for entire pane;
		CAlign&  Align (void) ;

		const
		CImage&  Image (void) const;  // if the pane does not have an image the image layout indicates 'false';
		CImage&  Image (void) ;	      // if the pane does not have an image the image layout indicates 'false';

		const
		CPadding& Padding (void) const;
		CPadding& Padding (void) ;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const; // ToDo: not updated yet;
#endif
		const
		t_rect&  Rect  (void) const;
		t_rect&  Rect  (void) ;           // direct access to pane rectangle;
		bool     Rect  (const t_rect&);

	public:
		CLayout& operator = (const CLayout&); CLayout& operator = (CLayout&&) = delete; // is not required yet;
		CLayout& operator <<(const CAlign& );     // sets the alignment of the pane;
		CLayout& operator <<(const CImage& );     // makes a copy of the input image layout;
		CLayout& operator <<(const t_rect& );     // calls Update(rect);
		CLayout& operator <<(const CPadding&);

	private:
		CAlign   m_align; // this is a pane elements' alignment;
		CImage   m_image; // an image layout if any image is assigned to the pane;
		t_rect   m_rect ; // this is entire area of the pane;
		CPadding m_padding;
	};
}
	// https://en.wikipedia.org/wiki/Paned_window_(computing) ;
	// http://ptitben2000.chez.com/info/lookandfeel/higk.htm ;
	// https://ux.stackexchange.com/questions/124588/whats-the-difference-between-a-panel-and-pane ;

	class CPane {
	using CBorders = ex_ui::controls::borders::CBorders_for_rect;
	public:
		 CPane (void); CPane (const CPane&); CPane (CPane&&);
		~CPane (void);

	public:
		const
		ex_ui::controls::borders::CBorders_for_rect& Borders (void) const;
		ex_ui::controls::borders::CBorders_for_rect& Borders (void) ;

		uint32_t Id (void) const;     // returns this pane identifier;
		bool     Id (const uint32_t); // sets pane identifier, returns 'true' if text is changed in comparison with previous one;

	public:
		CPane& operator = (const CPane&);
		CPane& operator = (CPane&&);      // just copying fields' data, neither move() nor swap() operation is applied;

		CPane& operator <<(const ex_ui::controls::borders::CBorders_for_rect&);
		CPane& operator <<(const uint32_t _id);

	protected:
		ex_ui::controls::borders::CBorders_for_rect  m_borders;
		uint32_t m_pane_id;
	};

#if (0)
	using CFormat = ex_ui::controls::pane::CFormat;
	using CLayout = ex_ui::controls::pane::CLayout;

	class CPane { // ToDo: this class must be the parent one for pane of the status bar and tabbed controls at least, otherwise it is useless;
	public:
		 CPane (void); CPane (const CPane&); CPane (CPane&&);
		~CPane (void);

	public:
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

		CPane& operator <<(const CFormat&);
		CPane& operator <<(const CLayout&);

	protected:
		CFormat   m_format;
		CLayout   m_layout;
	};
#endif
}}


#endif/*_CTL_BASE_PANE_H_INCLUDED*/