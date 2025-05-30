#ifndef _CTL_BASE_PANE_H_INCLUDED
#define _CTL_BASE_PANE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-May-2025 at 11:36:46.866, UTC+4, Batumi, Tuesday;
	This is Ebo Pack user control base pane interface declaration file;
*/
#include "ctl.base.defs.h"
#include "ctl.base.border.h"

namespace ex_ui { namespace controls {

	using CBorders  = ex_ui::controls::borders::CSet;
	using CPosition = geometry::_2D::base::CPosition;
	using CPos = CPosition;

	class CPane {
	public:
		class CFormat {
		private:
			CFormat (CPane&); CFormat (const CFormat&) = delete; CFormat (CFormat&&) = delete; ~CFormat (void) = default;

		public:
			const
			TRgbQuad& Bkgnd (void) const;
			TRgbQuad& Bkgnd (void) ;

		private:
			CFormat& operator = (const CFormat&) = delete;
			CFormat& operator = (CFormat&&) = delete;
		private:
			CPane&    m_pane ;
			TRgbQuad  m_bkgnd;
			friend class CPane;		
		};
		class CLayout {
		private:
			CLayout (CPane&); CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete; ~CLayout (void) = default;

		public:
			const
			CPosition& Position (void) const;
			CPosition& Position (void) ;

		private:
			CLayout& operator = (const CLayout&) = delete;
			CLayout& operator = (CLayout&&) = delete;
		private:
			CPane&    m_pane;
			CPosition m_position;
			friend class CPane;
		};
	public:
		 CPane (void); CPane (const CPane&) = delete; CPane (CPane&&) = delete;
		~CPane (void);

	public:
		const
		CBorders& Borders (void) const;
		CBorders& Borders (void) ;
		const
		CFormat&  Format  (void) const;
		CFormat&  Format  (void) ;
		const
		CLayout&  Layout  (void) const;
		CLayout&  Layout  (void) ;

	public:
		CPane& operator = (const CPane&) = delete;
		CPane& operator = (CPane&&) = delete;

	protected:
		CBorders  m_borders;
		CFormat   m_format;
		CLayout   m_layout;
	};
}}


#endif/*_CTL_BASE_PANE_H_INCLUDED*/