/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-May-2025 at 11:46:26.845, UTC+4, Batumi, Tuesday;
	This is Ebo Pack user control base pane interface implementation file;
*/
#include "ctl.base.pane.h"

using namespace ex_ui::controls;
using CFormat = CPane::CFormat;
using CLayout = CPane::CLayout;
/////////////////////////////////////////////////////////////////////////////

CFormat:: CFormat (CPane& _pane) : m_pane(_pane) {}

const
TRgbQuad& CFormat::Bkgnd (void) const { return this->m_bkgnd; }
TRgbQuad& CFormat::Bkgnd (void)       { return this->m_bkgnd; }

/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (CPane& _pane) : m_pane(_pane) {}

const
CPosition& CLayout::Position (void) const { return this->m_position; }
CPosition& CLayout::Position (void)       { return this->m_position; }

bool CLayout::Update (void) {
	return this->m_pane.Borders().Set(this->Position());
}

bool CLayout::Update (const t_rect& _rect_of_place) {
	this->Position() << _rect_of_place;
	return this->Update();
}

/////////////////////////////////////////////////////////////////////////////

CPane:: CPane (void) : m_format(*this), m_layout(*this)  {}
CPane::~CPane (void) {}

/////////////////////////////////////////////////////////////////////////////

const
CBorders& CPane::Borders (void) const { return this->m_borders; }
CBorders& CPane::Borders (void)       { return this->m_borders; }
const
CFormat&  CPane::Format  (void) const { return this->m_format ; }
CFormat&  CPane::Format  (void)       { return this->m_format ; }
const
CLayout&  CPane::Layout  (void) const { return this->m_layout ; }
CLayout&  CPane::Layout  (void)       { return this->m_layout ; }

err_code  CPane::Draw (const HDC _hdc, const t_rect& _drw_area) const {
	_hdc; _drw_area;
	err_code n_result = __s_ok;

	const t_rect drw_area = this->Layout().Position();

	CZBuffer z_buffer(_hdc, drw_area);

	if (z_buffer.Is_valid() == false)
		return (n_result = z_buffer.Error());

	// (1) draws the background first;
	const TRgbQuad& bkg_ = this->Format().Bkgnd();
	if (bkg_.Is() && bkg_.A() != 0) { // alpha value must be checked too;
		n_result = z_buffer.Draw(drw_area, bkg_);
	}

	using e_sides = ex_ui::controls::layout::CGaps_of_rect::e_sides;
	using CBorder = ex_ui::controls::borders::CBorder;

	for (int16_t i_ = 0; i_ <= e_sides::e_bottom; i_++) { // border set for rectangular area is expected, but nevertheless;

		const CBorder& border = this->Borders().Get(static_cast<e_sides>(i_));

		if (border.IsClear())
			continue;

		n_result = z_buffer.Draw(border);
		if (__failed(n_result))
			break;
	}

	return  n_result;
}