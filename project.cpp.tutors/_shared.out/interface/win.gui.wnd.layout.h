#ifndef _WIN_GUI_WND_LAYOUT_H_INCLUDED
#define _WIN_GUI_WND_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Sep-2025 at 05:28:25.438, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shared GUI window layout interface declaration file;
*/
#include "shared.defs.h"
namespace shared { namespace out {

	using namespace shared::defs;
	using namespace shared::types;

	using CWindow = ::ATL::CWindow;

namespace docking {

	class CSide {
	public:
		enum e_sides : uint32_t {
		e_left  = 0x0,
		e_top   = 0x1,
		e_right = 0x2,
		e_btm   = 0x3,
		};
	public:
		CSide (void); CSide (const CSide&) = delete; CSide (CSide&&) = delete; ~CSide (void) = default;

		e_sides Side (void) const;
		bool    Side (const e_sides); // returns 'true' if side value is changed;

		CSide&  operator <<(const e_sides);

	private:
		CSide& operator = (const CSide&) = delete; CSide& operator = (CSide&&) = delete;
		e_sides  m_side;
	};

	class CValue {
	public:
		enum e_ctrl : uint32_t {
		e_auto  = 0x1,   // this means the value is dependable of outer property, e.g. is assigned to the width of the window on re/size message handling;
		e_fixed = 0x0,   // this means the value is not changable, in other words 'const'; this is the *default* value control type;
		};
		CValue (const long = 0, const e_ctrl = e_ctrl::e_fixed); CValue (const CValue&) = delete; CValue (CValue&&) = delete; ~CValue (void) = default;

		e_ctrl  Ctrl (void) const;
		bool    Ctrl (const e_ctrl);            // returns 'true' on change of the value control type;

		bool    Is_auto (void) const;
		bool    Is_auto (const bool b_state);   // returns 'true' on change of the value control type; works like a trigger: if 'false' -' e_fixed' is assigned and vice versa;

		bool    Is_fixed (void) const;
		bool    Is_fixed (const bool b_state);  // returns 'true' on change of the value control type;

		long    Get (void) const;  // gets the value;
		bool    Set (const long);  // sets the value; returns 'true' on value change;

		bool    Set (const long _l_value, const e_ctrl _ctrl);

		CValue& operator <<(const e_ctrl);  // sets the value control type;
		CValue& operator <<(const long);    // sets the value;

	private:
		CValue& operator = (const CValue&) = delete; CValue& operator = (CValue&&) = delete;
		e_ctrl  m_ctrl ;
		long    m_value;
	};

	class CSize {
	public:
		CSize (const long _l_cx = 0, const long _l_cy = 0); // the value control type is set to 'fixed' for both fields;
		CSize (const CValue& _cx, const CValue& _cy);  CSize (const CSize&) = delete; CSize (CSize&&) = delete; ~CSize (void) = default;

		const
		CValue& Height (void) const;
		CValue& Height (void) ;
		bool    Height (const long _l_value, const CValue::e_ctrl); // returns 'true' in case if the value or control type is changed;

		const
		CValue& Width  (void) const;
		CValue& Width  (void) ;
		bool    Width  (const long _l_value, const CValue::e_ctrl); // returns 'true' in case if the value or control type is changed;

		CSize& operator >>(const CValue& _v_height);
		CSize& operator <<(const CValue& _v_width);

	private:
		CSize& operator = (const CSize&) = delete; CSize& operator = (CSize&&) = delete;
		CValue m_height;
		CValue m_width;
	};

	class CPane {
	public:
		CPane (void); CPane (const CPane&) = delete; CPane (CPane&&) = delete; ~CPane (void) = default;

		const
		CSide& Side (void) const;
		CSide& Side (void) ;
		const
		CSize& Size (void) const;
		CSize& Size (void) ;

	private:
		CPane& operator = (const CPane&) = delete;
		CPane& operator = (CPane&&) = delete;

		CSide  m_side;
		CSize  m_size;
	};

}

	// this version of the layout implementation supports two components only:
	// (a) a window in the top part of the client area, this is the child window of graphics output: DirectX and OpenGL tutorials;
	// (b) a window in the bottom part of the client area, this is the debug output console; (text mode);
	class CLayout {
	public:
		 CLayout (void); CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;

		 const
		 CWindow& Main (void) const; // returns the reference to the target window which client area is adjusted by this layout; (ro);
		 CWindow& Main (void) ;      // returns the reference to the target window which client area is adjusted by this layout; (rw);
		 
		 // https://thecontentauthority.com/blog/below-vs-bottom ;
		 // https://www.abbreviations.com/abbreviation/bottom ;
		 const
		 CWindow& Bottom (void) const;
		 CWindow& Bottom (void) ;

		 // https://forum.wordreference.com/threads/bottom-lower-and-top-upper.2453408/ ; << good explaining;
		 // Google AI: 'Top' can be considered more *absolute*, referring to a singular point, whereas 'upper' is relative..."

		 const
		 CWindow& Top (void) const;
		 CWindow& Top (void) ;

	private:
		 CLayout& operator = (const CLayout&) = delete;
		 CLayout& operator = (CLayout&&) = delete;

		 CWindow  m_low;
		 CWindow  m_top;

		 CWindow  m_target;   // actually, it is the main window of the tutorial app;
	};

}}

#endif/*_WIN_GUI_WND_LAYOUT_H_INCLUDED*/