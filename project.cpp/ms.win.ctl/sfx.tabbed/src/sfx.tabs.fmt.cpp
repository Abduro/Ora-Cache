/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Aug-2020 at 5:30:33a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack Sfx tab control format interface implementation file.
*/
#include "sfx.tabs.fmt.h"
#include "sfx.tabs.ctrl.h" // this header is included here due to exclude cyclic dependencies through header files;

using namespace ex_ui::controls::sfx::tabbed;
using namespace ex_ui::controls::sfx::tabbed::format;

/////////////////////////////////////////////////////////////////////////////

CFormat::CBorder_Clrs:: CBorder_Clrs (void) {
	try {
		this->m_colors.insert(::std::make_pair(TStateValue::eNormal, shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_border)));
		this->m_colors.insert(::std::make_pair(TStateValue::eSelected, shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_border, TThemeState::e_selected)));
	} catch (const ::std::bad_alloc&){}
}
CFormat::CBorder_Clrs::~CBorder_Clrs (void) {}

/////////////////////////////////////////////////////////////////////////////

rgb_color CFormat::CBorder_Clrs::Get (const TStateValue _state) const {
	_state;
	TVisualStateAssoc::const_iterator found_ = this->m_colors.find(_state);
	if (found_ == this->m_colors.end()) {
		static rgb_color the_emptiness = 0x0;
		return the_emptiness;
	}
	else
		return found_->second;
}

/////////////////////////////////////////////////////////////////////////////

CFormat:: CFormat (CControl& _ctrl) : m_ctrl(_ctrl) { this->Default(); }
CFormat::~CFormat (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CFormat::CBorder_Clrs& CFormat::Border_Clrs (void) const { return this->m_border; }

void CFormat::Default (void) {

	this->m_ctrl.Borders() << (uint8_t)1;
	this->m_ctrl.Borders().Base() << TRgbQuad(shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_border));

	TBase::Bkgnd().Solid() << shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back);

	static _pc_sz pc_sz_fnt_names[] = {
		_T("Pirulen Rg"), _T("Verdana"), _T("Age Normal"), _T("Trebuchet MS")
		//       0               1               2                 3
	};

	TBase::Font().Family(pc_sz_fnt_names[0]); // the exact name is very important, otherwise the other system font will be created (default for GUI);
	TBase::Font().Fore() = this->Border_Clrs().Get(TStateValue::eSelected);
	TBase::Font().Size() = -12;
	TBase::Font().Options() += TFontOpts::eExactSize;
}