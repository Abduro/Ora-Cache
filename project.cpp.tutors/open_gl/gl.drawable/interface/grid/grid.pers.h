#ifndef _GRID_PERS_H_INCLUDED
#define _GRID_PERS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-May-2026 at 00:13:21.809, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' view grid persistent interface declaration file; 
*/
#include "drawable.defs.h"

namespace open_gl { namespace views { namespace grid { using namespace shared::defs;

	using CColor = ex_ui::color::rgb::CFloat;

	class CPersistent { // this class is for loading/saving grid settings from/in the registry;
	public:
		class CCell {
		public:
			CCell (void); CCell (const CCell&) = delete; CCell (CCell&&) = delete; ~CCell (void) = default;
			const
			t_size& Get (void) const;
			t_size& Get (void) ;
			static
			bool Is_valid (const t_size&, CError&); // validates the input size for emptiness;
			bool Is_valid (void) const;             // returns 'true' if the height and the width of the cell does not equal to zero (0);

			void Load (void); // reads grid cell size from the system registry;
			void Save (void); // saves grid cell size to the system registry;

		private:
			CCell& operator = (const CCell&) = delete; CCell& operator = (CCell&&) = delete;
			t_size m_size;
		};

		class CGrid {
		public:
			CGrid (void); CGrid (const CGrid&) = delete; CGrid (CGrid&&) = delete; ~CGrid (void) = default;

			uint32_t Cols (void) const;
			err_code Cols (const uint32_t);

			void Load (void);
			void Save (void);

			uint32_t Rows (void) const;
			err_code Rows (const uint32_t);

		private:
			CGrid& operator = (const CGrid&) = delete; CGrid& operator = (CGrid&&) = delete;
			uint32_t m_cols, m_rows;
		};

		class CLine {
		public:
			CLine (void); CLine (const CLine&) = delete; CLine (CLine&&) = delete; ~CLine (void) = default;
			const
			CColor& Clr (void) const;
			CColor& Clr (void) ;

			void     Load  (void); // reads grid line props from the system registry;
			uint32_t Thick (void) const;
			bool     Thick (const uint32_t);

		private:
			CLine& operator = (const CLine&) = delete; CLine& operator = (CLine&&) = delete;
			CColor   m_color; // grid line color;
			uint32_t m_thick; // https://www.allacronyms.com/thk/thickness ;
		};

		CPersistent (void); CPersistent (const CPersistent&) = delete; CPersistent (CPersistent&&) = delete; ~CPersistent (void) = default;
		const
		CCell&   Cell (void) const;
		CCell&   Cell (void) ;
		TError&  Error(void) const;
		const
		CGrid&   Grid (void) const;
		CGrid&   Grid (void) ;
		const
		CLine&   Line (void) const;
		CLine&   Line (void) ;

		err_code Load (void); // loads settings from system registry for given grid;
		err_code Save (void); // saves settings of given grid to system registry;

	private:
		CPersistent& operator = (const CPersistent&) = delete; CPersistent& operator = (CPersistent&&) = delete;
		mutable
		CError m_error;
		CCell  m_cell ;
		CGrid  m_grid ;
		CLine  m_line ;
	};

}}}

#endif/*_GRID_PERS_H_INCLUDED*/