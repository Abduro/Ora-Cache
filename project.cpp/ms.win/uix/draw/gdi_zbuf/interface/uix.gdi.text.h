#ifndef _UIX_GDI_TEXT_H_INCLUDED
#define _UIX_GDI_TEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 01:44:14.173, UTC+4, Batumi;
	This is Ebo Pack GDI genetric output text block interface declaration file;
*/
#include "uix.gdi.defs.h"

namespace ex_ui { namespace draw { namespace text {

	using namespace ex_ui::draw::defs;

	using CProperty = shared::common::CProperty;

	class CProp_Err : public CProperty { typedef CProperty TBase;
	public:
		 CProp_Err (const uint32_t _n_value, _pc_sz _p_name);
		 CProp_Err (const CProp_Err& );
		 CProp_Err (CProp_Err&&) = delete; // not required yet;
		~CProp_Err (void);

	public:
		const
		CProperty& Base (void) const;
		CProperty& Base (void) ;

		TError&    Error(void) const;

	public:
		bool operator = (const uint32_t _n_value);

	private:
		CProp_Err&  operator = (const CProp_Err&) = delete;
		CProp_Err&  operator = (CProp_Err&&) = delete;

	protected:
		CError  m_error;
	};

	class CProp_Trim : public CProperty { typedef CProperty TBase;
	public:
		 CProp_Trim (const uint32_t _n_value, _pc_sz _p_name); CProp_Trim (const CProp_Trim&) = delete; CProp_Trim (CProp_Trim&&) = delete;
		~CProp_Trim (void);
	public:
		bool operator = (const uint32_t _n_value);
	public:
		CProp_Trim& operator = (const CProp_Trim&);
		CProp_Trim& operator = (CProp_Trim&&) = delete;
	};

namespace format {
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtext ; format flags are taken from this function;
	class CAlign_Horz : public CProp_Trim { typedef CProp_Trim TBase;
	public:
		enum e_value : uint32_t {
		     e_center = DT_CENTER , // Centers text horizontally in the rectangle ;
		     e_left   = DT_LEFT   , // Aligns text to the left ; the *default* flag;
		     e_right  = DT_RIGHT  , // Aligns text to the right;
		};
	public:
		 CAlign_Horz (const uint32_t = e_value::e_left);
		~CAlign_Horz (void);

	public:
#if defined(_DEBUG)
		CString Print(const e_print = e_print::e_all) const;
#endif
		bool Set (const uint32_t _u_flags); // updates/sets the value of this class object; the one flag is acceptable only;
	};

	class CAlign_Vert : public CProp_Trim { typedef CProp_Trim TBase;
	public:
		enum e_value : uint32_t {
		     e_bottom = DT_BOTTOM , // Justifies the text to the bottom of the rectangle ; for DT_SINGLELINE option only;
		     e_middle = DT_VCENTER, // Centers text vertically ; for DT_SINGLELINE option only;
		     e_top    = DT_TOP    , // Justifies the text to the top of the rectangle; the *default* flag;
		};
	public:
		 CAlign_Vert (const uint32_t = e_value::e_top);
		~CAlign_Vert (void);

	public:
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		bool Set (const uint32_t _u_flags); // updates/sets the value of this class object; the one flag is acceptable only;
	};

	class CAlign : public CProp_Trim { typedef CProp_Trim TBase;
	public:
		 CAlign (void);
		~CAlign (void);

	const
		CAlign_Horz& Horz (void) const;
		CAlign_Horz& Horz (void) ;
#if defined(_DEBUG)
		CString      Print(const e_print = e_print::e_all) const;
#endif
		uint32_t Get (void) const;
		bool Set (const uint32_t _u_flags); // updates/sets the horizontal and vertical alignments of of this class object; the two flags may be accepted;
		const
		CAlign_Vert& Vert (void) const;
		CAlign_Vert& Vert (void) ;

	private:
		CAlign_Horz  m_horz;
		CAlign_Vert  m_vert;
	};
	
	// ToDo: a couple of flags are not presented here due to they are not used in this version of the software implementation;

	class CCutter : public CProp_Trim { typedef CProp_Trim TBase;
	public:
		enum e_value : uint32_t {
		     e__na  = 0x0,
		     e_end  = DT_END_ELLIPSIS  , // replaces the end of a string with ellipses; DT_MODIFYSTRING option is on;
		     e_path = DT_PATH_ELLIPSIS , // replaces characters in the middle of the string with ellipses; DT_MODIFYSTRING option is on;
		     e_word = DT_WORD_ELLIPSIS , // truncates any word that does not fit in the rectangle and adds ellipses;
		};
	public:
		 CCutter (void);
		~CCutter (void) = default;

	public:
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		bool Set (const uint32_t _u_flags); // updates/sets the value of this class object; the one flag is acceptable only;
	};

	class CModifier : public CProp_Trim { typedef CProp_Trim TBase;
	public:
		enum e_value : uint32_t {
		     e__na  = 0x0,
		     e_do_modify   = DT_MODIFYSTRING, // Modifies the specified string to match the displayed text;
		     e_no_prefix   = DT_NOPREFIX    , // Turns off processing of prefix characters;
		     e_do_prefix   = DT_PREFIXONLY  , // Draws only an underline at the position of the character following the ampersand (&) prefix character;
		     e_hide_prefix = DT_HIDEPREFIX  , // Ignores the ampersand (&) prefix character in the text;
		     e_tabs_ext    = DT_EXPANDTABS  , // Expands tab characters; The default number of characters per tab is 8 (eight);
		};
	public:
		 CModifier (void) ;
		~CModifier (void) = default;

	public:
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		bool Set (const uint32_t _u_flags); // updates/sets the value of this class object; multiple flags are acceptable;
	};

	typedef CModifier CAlterer; // https://www.wordreference.com/synonyms/modifier ;

	typedef CCutter CCut; // just for playing with class names;

	class COptimizer : public CProp_Trim { typedef CProp_Trim TBase;
	public:
		enum e_value : uint32_t {
		     e__na  = 0x0,
		     e_rc_calc = DT_CALCRECT  , // Determines the width and height of the rectangle; no drawing;
		     e_no_clip = DT_NOCLIP    , // DrawTextEx is somewhat faster when DT_NOCLIP is used;
		     e_single  = DT_SINGLELINE, // Displays text on a single line only;
		};
	public:
		 COptimizer (void) ;
		~COptimizer (void) = default;

	public:
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		bool Set (const uint32_t _u_flags); // updates/sets the value of this class object; multiple flags are acceptable;
	};

	typedef COptimizer COptima; // just for playing with class names;

	class CFormat : public CProp_Trim { typedef CProp_Trim TBase;
	public:
		 CFormat (void) ;
		~CFormat (void) = default;
	
	public:
		const
		CAlign& Align (void) const;
		CAlign& Align (void) ;
		const
		CCut&  Cut (void) const;
		CCut&  Cut (void) ;
		const
		CAlterer& Modify (void) const;
		CAlterer& Modify (void) ;
		const
		COptima& Optimize(void) const;
		COptima& Optimize(void) ;

	public:
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		uint32_t  Get (void) const;       // gets flags from all components of this format object;
		bool Set (const uint32_t _flags); // change any format component in accordance with input flags; returns 'true' in case of at least one flag is changed;

	public:
		CFormat& operator << (const CAlign&);
		CFormat& operator << (const CAlterer&);
		CFormat& operator << (const CCutter&);
		CFormat& operator << (const COptima&);

		CFormat& operator += (const uint32_t _flags);
		CFormat& operator -= (const uint32_t _flags);

	private:
		CAlign    m_align ;
		CCutter   m_cutter;
		CAlterer  m_modify;
		COptima   m_optima;
	};
}
	class CText_Base {
	protected:
		 CText_Base (void); CText_Base (const CText_Base&) = delete; CText_Base (CText_Base&&) = delete;
		~CText_Base (void);

	public:
		const
		rgb_color& Fore  (void) const;
		rgb_color& Fore  (void) ;
		const
		t_rect&    Out_to(void) const;
		t_rect&    Out_to(void) ;
		const
		CString&   Text  (void) const;
		CString&   Text  (void) ;

	protected:
		rgb_color  m_clr_fore ;
		t_rect     m_draw_rect;
		CString    m_text ;

	public:
		CText_Base&  operator <<(_pc_sz _p_text);
		CText_Base&  operator <<(const rgb_color& _clr_fore);
		CText_Base&  operator <<(const t_rect&);

	private:
		CText_Base&  operator = (const CText_Base&) = delete;
		CText_Base&  operator = (CText_Base&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtext ;

	class CDrawText : public CText_Base { typedef CText_Base TBase;
	using CFormat = ex_ui::draw::text::format::CFormat;
	public:
		 CDrawText (void);
		~CDrawText (void);

	public:
		const
		CFormat&   Format(void) const;
		CFormat&   Format(void) ;

	private:
		CFormat   m_format;
	};

namespace output {

	class CAlign_Horz : public CProp_Trim { typedef CProp_Trim TBase;
	public:
		enum e_value : uint32_t {
		     e_base   = TA_BASELINE , // The reference point is on the base line of the text ; VTA_BASELINE == TA_BASELINE ;
			 e_center = TA_CENTER   , // The reference point is aligned horizontally with the center of the bounding rectangle;
		     e_left   = TA_LEFT     , // The reference point is on the left edge of the bounding rectangle; 0 value indicates this flag is *default*;
		     e_right  = TA_RIGHT    , // The reference point is on the right edge of the bounding rectangle;
		};
	public:
		 CAlign_Horz (const uint32_t = e_value::e_left);
		~CAlign_Horz (void);

	public:
		bool Set (const uint32_t _u_flags); // updates/sets the flags value of this class object; the only one flag is accepted;

	public:
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
	};

	class CAlign_Vert : public CProp_Trim { typedef CProp_Trim TBase;
	public:
		enum e_value : uint32_t {
		     e_base   = TA_BASELINE, // The reference point is on the base line of the text ; VTA_BASELINE == TA_BASELINE ;
		     e_bottom = TA_BOTTOM  , // The reference point is on the bottom edge of the bounding rectangle ;
		     e_center = TA_CENTER  , // The reference point is aligned vertically with the center of the bounding rectangle ; VTA_CENTER == TA_CENTER ;
		     e_top    = TA_TOP     , // The reference point is on the top edge of the bounding rectangle ; 0 value indicates this flag is *default*;
		};
	public:
		 CAlign_Vert (const uint32_t = e_value::e_top);
		~CAlign_Vert (void);

	public:
		bool Set (const uint32_t _u_flags); // updates/sets the flags value of this class object;

	public:
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gettextalign ;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-settextalign ;

	class CAlign : public CProp_Err { typedef CProp_Err TBase;
	public:
		enum e_value : uint32_t {
		     e_update_cp = TA_UPDATECP  , // The current position is updated after each text output call;
		     e_no_update = TA_NOUPDATECP, // The current position is not updated after each text output call; this the *default* value;
		};
	public:
		 CAlign (void);
		~CAlign (void);

	public: // interacting with the target device context;
		err_code GetFrom (const HDC&);        // gets flags from input device context handle;
		err_code SetTo (const HDC&);          // sets flags to the input device context handle;

	public: // data mutator(s), i.e. setter(s) and getter(s);
		uint32_t Get (void) const;            // gets all flags OR-ed that are set for horizontal and vertical alignments;
		bool     Set (const uint32_t _flags); // sets flags eather for horizontal and vertical alignments; *note* one flag may be accepted by both alignments, for example, e_center;

	public: // thise is just the accessors;
		const
		CAlign_Horz& Horz (void) const;
		CAlign_Horz& Horz (void) ;
#if defined(_DEBUG)
		CString      Print(const e_print = e_print::e_all) const;
#endif
		const
		CAlign_Vert& Vert (void) const;
		CAlign_Vert& Vert (void) ;

	public:
		err_code operator <<(const HDC&); // gets the alignment flags from input device context handle;
		err_code operator >>(const HDC&); // sets the alignment flags to the input device context handle;
		
	private:
		CAlign_Horz m_horz;
		CAlign_Vert m_vert;
	};
}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-textouta ;
	// https://stackoverflow.com/questions/2250437/how-to-draw-vertical-text-in-windows-gui << the question;
	// https://stackoverflow.com/a/2250840/4325555 << the answer;

	class CTextOut : public CText_Base { typedef CText_Base TBase;
	using CAlign = ex_ui::draw::text::output::CAlign;
	public:
		 CTextOut (void);
		~CTextOut (void);

	public:
		const
		CAlign&    Align (void) const;
		CAlign&    Align (void) ;

		const
		t_point&   Anchor(void) const;
		t_point&   Anchor(void) ;

		const
		HDC&       Ctx   (void) const;
		HDC&       Ctx   (void) ;
		
		/* *note*: using the rectangle does not provide correct text placement, especially for vertical output the text;
		   for example, tabs of the tabbed control reside on the left side of the window, in such case rectangle is applicable for drawing the tab borders only,
		   but for text output of the tab caption is not, because the text must be placed to correct point for the TextOut() function,
		   thus, X & Y must be calculated for specific alignment in any case, otherwise the text is drawn at the place that is not expected to be;
		*/
		err_code   Recalc_anchor (void); // it is required for correct alignment of the text, especially for vertical output;

	public:
		CTextOut&  operator <<(const HDC&);
		CTextOut&  operator <<(const t_rect&);

	private:
		CTextOut&  operator = (const CTextOut&) = delete;
		CTextOut&  operator = (CTextOut&&) = delete;

	private:
		CAlign    m_align;
		HDC       m_h_dc ;
		t_point   m_anchor;
	};

}}}

#endif/*_UIX_GDI_TEXT_H_INCLUDED*/