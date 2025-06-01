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
	
	bool b_changed = false;

	return b_changed;
}

bool CLayout::Update (const t_rect& _rect_of_place) {
	this->Position() << _rect_of_place;
	// pane borders require theit coords update;
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

