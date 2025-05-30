#ifndef _COLOR_GRADIENT_H_INCLUDED
#define _COLOR_GRADIENT_H_INCLUDED
/*
	Created by Tech_doc (ebontrop@gmail.com) on 12-Oct-2021 at 1:16:28.2479704 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack color project gradient interface declaration file;
*/
#include "color._defs.h"
#include "color.compl.h"

namespace ex_ui { namespace color { namespace rgb {

	using CSet = ex_ui::color::complementary::CSet;
	using CTriplet = CSet;

	// https://en.wikipedia.org/wiki/List_of_mathematical_abbreviations#G ;
	// https://en.wikipedia.org/wiki/Gradient ;
	// https://en.wikipedia.org/wiki/Color_gradient ;
	// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gradientfill ;
	// https://www.dictionary.com/browse/gradient ;
	// https://developer.mozilla.org/en-US/docs/Web/CSS/gradient/linear-gradient ;
	// https://developer.mozilla.org/en-US/docs/Web/CSS/gradient ;

	class CGradient { // ToDo: (1) an angle of gradient direction in degrees; (2) a type of gradient: (a) linear; (b) radial; (c) conic;
	public:
		 CGradient (void);
		 CGradient (const CColor& _from, const CColor& _to);
		 CGradient (const rgb_color _from, const rgb_color _to); CGradient (CGradient&&);
		 CGradient (const CGradient&);
		~CGradient (void);

	public: // ToDo: if both colors are the same or fully transparent, is this case true?
		const bool  Is    (void) const; // returns true if one of the gradient colors is true;
		const bool  IsVert(void) const;
		      bool& IsVert(void)      ;
		const
		CColor& c0(void) const;     // gets first color (ro);
		CColor& c0(void)      ;     // gets first color (rw);
		const
		CColor& c1(void) const;     // gets second color (ro);
		CColor& c1(void)      ;     // gets second color (rw);

		const
		CColor& From (void) const;  // gets a reference to color of gradient start; it is the same as this::c0(); (ro);
		CColor& From (void)      ;  // gets a reference to color of gradient start; it is the same as this::c0(); (rw);
		const
		CColor& To (void) const;    // gets a reference to color of gradient stop; it is the same as this::c1(); (ro);
		CColor& To (void)      ;    // gets a reference to color of gradient stop; it is the same as this::c1(); (rw);

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		err_code Set (const CSet&); // takes into account the dark (start/from) and light (stop/to) colors only;
		err_code Set (const CColor& _from, const CColor& _to);
		err_code Set (const rgb_color _from, const rgb_color _to);

	public:
		CGradient& operator = (const CGradient&);
		CGradient& operator = (CGradient&&);           // there is no move/swap operation is used actually, becase it is not required;
		CGradient& operator <<(const bool _b_vert);
		CGradient& operator <<(const CSet& );
		CGradient& operator <<(const CColor& _from);
		CGradient& operator >>(const CColor& _to);

	protected:
		CColor   m_clr_0 ;          // the first color or the color which the gradient starts from;
		CColor   m_clr_1 ;          // the second color or the color which the gradient ends up;
		bool     m_b_vert;          // a direction of a gradient either vertical (default) or horizontal;
	};
}}}

typedef ::std::vector<ex_ui::color::rgb::CGradient> TRawGrads;

namespace ex_ui { namespace color { namespace rgb {

	using namespace ex_ui::color;

	// https://stackoverflow.com/questions/31427117/difference-between-element-item-and-entry-when-it-comes-to-programming
	class CGradient_Strip {
	public:
		 CGradient_Strip (void);
		 CGradient_Strip (const CGradient_Strip&); CGradient_Strip (CGradient_Strip&&) = delete;
		~CGradient_Strip (void);

	public:
		err_code    Add   (const CGradient&);
		err_code    Clear (void) ;
		uint32_t    Count (void) const;
		TError&     Error (void) const;
		const bool  Is    (void) const; // returns true if this strip is not empty and all gradient tiles are valid;
		const bool  IsVert(void) const; // returns true if *each* gradient element is vertical;
		      void  IsVert(const bool); // sets an orientation to all elements of this strip;
#if defined(_DEBUG)
		CString     Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		TRawGrads&  Raw  (void) const;
		err_code  Remove (const uint32_t _ndx);   // removes the gradient tile/element by the input index;
		const
		CGradient&  Tile (const uint32_t _ndx) const;
		CGradient&  Tile (const uint32_t _ndx);

	public:
		CGradient_Strip& operator = (const CGradient_Strip&);
		CGradient_Strip& operator = (CGradient_Strip&&) = delete;

		CGradient_Strip& operator <<(const TRawGrads&);

		CGradient_Strip& operator+= (const CGradient&);
		CGradient_Strip& operator-= (const uint32_t _ndx);

	protected:
		mutable
		CError    m_error;
		TRawGrads m_strip;
	};
}}}

typedef ex_ui::color::rgb::CGradient        TGradient;       using TGrad = TGradient;
typedef ex_ui::color::rgb::CGradient_Strip  TGradientStrip;  using TGradStrip = TGradientStrip;

#endif/*_COLOR_GRADIENT_H_INCLUDED*/