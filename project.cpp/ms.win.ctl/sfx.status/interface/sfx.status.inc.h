#ifndef _SFX_STATUS_INC_H_INCLUDED
#define _SFX_STATUS_INC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Jun-2025 at 22:55:15.232, UTC+4, Batumi, Wednesday;
	This is Ebo Pack status bar user control include header(s) declaration file;
*/
#pragma region __atl_&_stl__
#include <atlbase.h>
#include <atlwin.h>
#include <map>
#include <cstdint>             // for data type definitions, for example, uint32_t;
#pragma endregion

#pragma region __shared_&_sys_core__
#include "sys.error.h"
#include "shared.preproc.h"
#include "shared.string.h"
#include "shared.types.h"
#include "sys.sync_obj.h"
#pragma endregion

#pragma region __ctl_base__
#include "ctl.base.border.h"
#include "ctl.base.format.h"
#include "ctl.base.layout.h"
#include "ctl.base.pane.h"
#include "ctl.base.props.h"
#pragma endregion

namespace ex_ui { namespace controls { namespace sfx {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

	using CMargin = ex_ui::controls::layout::CMargin;
	using CBorders= ex_ui::controls::borders::CBorders_for_rect;
	using CBorder = ex_ui::controls::borders::CBorder;
	using CPoint  = geometry::_2D::base::CPoint;

	using CWindow = ::ATL::CWindow;

namespace status { namespace layout {
#pragma region __refs_b
	// https://stackoverflow.com/questions/43230907/per-monitor-dpi-aware-windows-system-image-list ;
	// https://www.themathdoctors.org/what-are-length-and-width/ ;
	// https://www.quora.com/Whats-the-difference-between-length-width-height-and-depth ; so 'width' is still be used;
#pragma endregion
	class CStyle {
	public:
		class CStick {
		public:
			enum e_side : uint32_t {
			     e_left = 0,  // this is *default* side of stick of a pane;
			     e_right      // this is a case when a pane is sticked to the right side of window and changes its position when window is resized;
			};
			static const bool Is_left (const uint32_t _side) { return (e_side::e_left  == _side); }
			static const bool Is_right(const uint32_t _side) { return (e_side::e_right == _side); }

			CStick (const e_side = e_side::e_left); CStick (const CStick&); ~CStick (void)/* = default*/;

			e_side  Get (void) const;
			bool    Set (const e_side); // returns 'true' in case of side value change;

			const bool Is_left (void) const { return CStick::Is_left (this->Get()); }
			const bool Is_right(void) const { return CStick::Is_right(this->Get()); }

		public:
			CStick& operator = (const CStick&); CStick& operator = (CStick&&) = delete;
			CStick& operator <<(const e_side );

		private:
			e_side  m_side;
		};
		class CWidth {
		public:
			enum e_mode : uint32_t {
			     e_auto  = 1, // when this type of pane width is set, the pane will automatically fill all available space of the control;
			     e_fixed = 0, // this is *default* type of a pane width, it is defined by given value of the width and is not changed by layout;
			};
			static const bool Is_auto (const uint32_t _side) { return (e_mode::e_auto  == _side); }
			static const bool Is_fixed(const uint32_t _side) { return (e_mode::e_fixed == _side); }

			CWidth (const e_mode = e_mode::e_fixed); CWidth (const CWidth&); ~CWidth (void)/* = default*/;

			e_mode  Get (void) const;
			bool    Set (const e_mode); // returns 'true' in case of width mode change;

			const bool Is_auto (void) const { return CWidth::Is_auto (this->Get()); }
			const bool Is_fixed(void) const { return CWidth::Is_fixed(this->Get()); }

		public:
			CWidth& operator = (const CWidth&); CWidth& operator = (CWidth&&) = delete;
			CWidth& operator <<(const e_mode );

		private:
			e_mode  m_mode;
		};

	public:
		 CStyle (void);
		 CStyle (const CStyle&); CStyle (CStyle&&) = delete;
		~CStyle (void);

	public:
		const
		CStick& Stick (void) const;
		CStick& Stick (void) ;
		const
		CWidth& Width (void) const;
		CWidth& Width (void) ;

		bool Set (const CStick::e_side, const CWidth::e_mode); // returns 'true' if side or width mode is changed;

	public:
		CStyle& operator = (const CStyle&);
		CStyle& operator <<(const CStick&);
		CStyle& operator <<(const CWidth&);

	private:
		CStick  m_stick;
		CWidth  m_width;
	};

}}

}}}

#endif/*_SFX_STATUS_INC_H_INCLUDED*/