/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-May-2026 at 00:11:05.865, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' view grid persistent interface implementation file; 
*/
#include "grid.pers.h"
#include "sys.registry.h"

using namespace ::open_gl::views::grid;
using CHex = ::ex_ui::color::rgb::CHex;

#pragma region cls::CCell{}

using CCell = CPersistent::CCell;

CCell::CCell (void) : m_size{0} {}

const
t_size& CCell::Get (void) const { return this->m_size; }
t_size& CCell::Get (void)       { return this->m_size; }

bool CCell::Is_valid (void) const { return 0 < this->Get().cx && 0 < this->Get().cy; }
bool CCell::Is_valid (const t_size& _u_size, CError& _err) {
	_u_size; _err;
	if (1 > _u_size.cx || 1 > _u_size.cy) {
		_err <<__e_not_inited = TString().Format(_T("#__e_not_init: cell size {w=%d;h=%d} is invalid"), _u_size.cx, _u_size.cy);
	}
	return false == _err;
}

void CCell::Load (void) {
	using CRegCell = shared::sys_core::storage::CGrid::CCell;
	CRegCell& reg_cell = ::Get_reg_router().Viewport().Grid().Cell();

	TRegKeyEx reg_key;
	this->m_size.cx = reg_key.Value().GetDword(reg_cell.Root(), (_pc_sz) reg_cell.Name(CRegCell::e_width));
	if (reg_key.Error()) {
		__trace_err_ex_2(reg_key.Error());
	}
	this->m_size.cy = reg_key.Value().GetDword(reg_cell.Root(), (_pc_sz) reg_cell.Name(CRegCell::e_height));
	if (reg_key.Error()) {
		__trace_err_ex_2(reg_key.Error());
	}

	static const uint32_t u_min = 25u;
	if (u_min > this->m_size.cx) this->m_size.cx = u_min;
	if (u_min > this->m_size.cy) this->m_size.cy = u_min;
}

void CCell::Save (void) {
	using CRegCell = shared::sys_core::storage::CGrid::CCell;
	using e_values = CRegCell::e_values;

	CRegCell& reg_cell = ::Get_reg_router().Viewport().Grid().Cell();
	TRegKeyEx reg_key;

	reg_key.Value()() << reg_cell.Root();
	reg_key.Value()() >> reg_cell.Name(e_values::e_height); if (__failed(reg_key.Value().Set(this->Get().cy))) __trace_err_ex_2(reg_key.Error());
	reg_key.Value()() >> reg_cell.Name(e_values::e_width ); if (__failed(reg_key.Value().Set(this->Get().cx))) __trace_err_ex_2(reg_key.Error());
}

#pragma endregion
#pragma region cls::CGrid{}

using CGrid = CPersistent::CGrid;

CGrid::CGrid (void) : m_cols(1), m_rows(1) {}

uint32_t CGrid::Cols (void) const { return this->m_cols; }
err_code CGrid::Cols (const uint32_t _u_cols) {
	_u_cols;
	err_code n_result = __s_ok;
	if (1 > _u_cols) {
		__trace_warn_2(_T("grid column number is 0;\n")); n_result = __s_false;
	}
	this->m_cols = _u_cols;
	return n_result;
}

void CGrid::Load (void) {
	using CRegGrid = shared::sys_core::storage::route::CGrid;
	CRegGrid& reg_grid = ::Get_reg_router().Viewport().Grid();

	TRegKeyEx reg_key;

	this->Cols(reg_key.Value().GetDword(reg_grid.Root(), reg_grid.Cols())); if (reg_key.Error()) __trace_err_ex_2(reg_key.Error());
	this->Rows(reg_key.Value().GetDword(reg_grid.Root(), reg_grid.Rows())); if (reg_key.Error()) __trace_err_ex_2(reg_key.Error());

	if (0 == this->Cols()) this->Cols(1);
	if (0 == this->Rows()) this->Rows(1);
}
void CGrid::Save (void) {
	using CRegGrid = shared::sys_core::storage::route::CGrid;
	CRegGrid& reg_grid = ::Get_reg_router().Viewport().Grid();

	TRegKeyEx reg_key;

	reg_key.Value().Set(reg_grid.Root(), reg_grid.Cols(), this->Cols()); if (reg_key.Error()) __trace_err_ex_2(reg_key.Error());
	reg_key.Value().Set(reg_grid.Root(), reg_grid.Rows(), this->Rows()); if (reg_key.Error()) __trace_err_ex_2(reg_key.Error());
}

uint32_t CGrid::Rows (void) const { return this->m_rows; }
err_code CGrid::Rows (const uint32_t _u_rows) {
	_u_rows;
	err_code n_result = __s_ok;
	if (1 > _u_rows) {
		__trace_warn_2(_T("grid row number is 0;\n")); n_result = __s_false;
	}
	this->m_rows = _u_rows;
	return n_result;
}

#pragma endregion
#pragma region cls::CLine{}
using CLine = CPersistent::CLine;

CLine::CLine (void) : m_thick(1u) {}
const
CColor&  CLine::Clr (void) const { return this->m_color; }
CColor&  CLine::Clr (void)       { return this->m_color; }

void CLine::Load (void) {
	using CRegGrid = shared::sys_core::storage::route::CGrid;
	CRegGrid& reg_grid = ::Get_reg_router().Viewport().Grid();

	TRegKeyEx reg_key;
	// gets grid line color;
	CString cs_clr = reg_key.Value().GetString(reg_grid.Root(), reg_grid.Clr_name());
	if (reg_key.Error()) {
		__trace_err_ex_2(reg_key.Error());
	}
	this->Clr().Set((rgb_color)CHex((_pc_sz)cs_clr));
}

uint32_t CLine::Thick (void) const { return this->m_thick; }
bool     CLine::Thick (const uint32_t _u_value) {
	const bool b_changed = this->Thick() != _u_value; if (b_changed) this->m_thick = _u_value; return b_changed;
}

#pragma endregion
#pragma region cls::CPersistent{}

CPersistent::CPersistent (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

const
CCell&   CPersistent::Cell (void) const { return this->m_cell; }
CCell&   CPersistent::Cell (void)       { return this->m_cell; }

TError&  CPersistent::Error(void) const { return this->m_error;}
const
CGrid&   CPersistent::Grid (void) const { return this->m_grid; }
CGrid&   CPersistent::Grid (void)       { return this->m_grid; }
const
CLine&   CPersistent::Line (void) const { return this->m_line; }
CLine&   CPersistent::Line (void)       { return this->m_line; }

err_code CPersistent::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;
	this->Cell().Load();
	this->Grid().Load();
	this->Line().Load();

	return this->Error();
}

err_code CPersistent::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;
	this->Cell().Save();
//	this->Grid().Save();

	return this->Error();
}

#pragma endregion