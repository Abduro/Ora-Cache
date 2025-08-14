/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Aug-2025 at 11:57:56.930, (UTC+4), Batumi, Thursday;
	This is Ebo Pack Sfx status bar user control wrapper interface implementation file;
*/
#include "ctl.status.h"

using namespace ebo::boo::gui::ctl;

#include "ebo.sha.gui.theme.h"
#include "win.gui_view.h"

#define pane_borders_thick 1

namespace ebo { namespace boo { namespace gui { namespace _impl {

	CString Get_entry_point (void) {
	
		static bool b_1st_time = false;
		static shared::sys_core::CSystemTime time;

		if (b_1st_time == false) {
			b_1st_time = true;

			time.Offset().Get()._hours = -12;
			time.Offset().Get()._mins  =  34;

			time.Offset().Alias(_T("The Moon"));
		}
		time.Current();
		CString cs_out = time.To_string(shared::sys_core::CDateTimeFmt::iso_8601::e_time_complete);
		cs_out += TStringEx().Format (_T(" (%s)"), time.Offset().Alias());

		return cs_out;
	}

}}}}

using namespace ebo::boo::gui::_impl;
/////////////////////////////////////////////////////////////////////////////

CStatus:: CStatus (void) : m_timer(*this) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CStatus::~CStatus (void) { if (m_timer.IsValid()) m_timer.Destroy(); }

err_code  CStatus::At_1st(void) {
	this->m_error <<__METHOD__<<__s_ok;

	CSta_bar& sta_bar = this->Get();

	if (sta_bar.Panes().Count())
		return this->m_error << (err_code) TErrCodes::eObject::eInited;

	// (1) gets path to the folder of the test images;

	using CPaths = ebo::sha::theme::paths::CStatus;
	CPaths paths;

	if (__failed(paths.Set())) {
		return this->m_error = paths.Error();
	}

	using namespace ex_ui::controls::sfx::status;

	// (2) loads images and appends them to the status bar image list;
	CImages& images = sta_bar.Images();

	if (__failed(images.List().Append((_pc_sz) paths.Get(0), TImgFmt::e_png))) return this->m_error = images.List().Error();
	if (__failed(images.List().Append((_pc_sz) paths.Get(1), TImgFmt::e_png))) return this->m_error = images.List().Error();

	// (3) adds panes to status bar:
	if (__failed(sta_bar.Panes().Add())) return this->m_error = (*this)().Panes().Error(); // (3.1) the status icon pane, no text is intended for it;
	if (__failed(sta_bar.Panes().Add())) return this->m_error = (*this)().Panes().Error(); // (3.2) text message pane;
	if (__failed(sta_bar.Panes().Add())) return this->m_error = (*this)().Panes().Error(); // (3.3) graphical clock representation control pane;

	// (4) sets properties of the panes; actually accessing directly the reference to the vector of the raw panes would make a sense;
	CPane&  pane_0 = (*this)().Panes().Pane(0); if ((*this)().Panes().Error()) return this->m_error = (*this)().Panes().Error();
	CPane&  pane_1 = (*this)().Panes().Pane(1); if ((*this)().Panes().Error()) return this->m_error = (*this)().Panes().Error();
	CPane&  pane_2 = (*this)().Panes().Pane(2); if ((*this)().Panes().Error()) return this->m_error = (*this)().Panes().Error();

	using CLay_Style = ex_ui::controls::sfx::status::layout::CStyle;

#pragma region pane_no_0
{
	pane_0.Format().Image().Index(0);    // it is supposed to be an image 'ready' status by default;

	ex_ui::controls::pane::CFormat& fmt_ = pane_0.Format(); fmt_;
	ex_ui::controls::sfx::status::TPn_Lay& out_ = pane_0.Layout(); out_;

	out_.Style().Width() << CLay_Style::CWidth::e_fixed;
	out_.Image().Margins().Set(0x2);   // sets 2px for margins of all sides in order to have some gap between the pane image and pane boundaries;
	out_.Image().Margins().Left(0x9);  // just for testing of the left side indentation ; the value is in accordance with the image being used;

	out_.Fixed(sta_bar.Layout().Height());
}
#pragma endregion

#pragma region pane_no_1
{
	ex_ui::controls::pane::CFormat& fmt_ = pane_1.Format(); fmt_;
	ex_ui::controls::sfx::status::TPn_Lay& out_ = pane_1.Layout(); out_;

	out_.Style().Width() << CLay_Style::CWidth::e_auto;
	out_.Padding().Left(0x5);

	pane_1.Text(_T("Ready"));
}
#pragma endregion

#pragma region pane_no_2
{
	ex_ui::controls::pane::CFormat& fmt_ = pane_2.Format(); fmt_;
	ex_ui::controls::sfx::status::TPn_Lay& out_ = pane_2.Layout(); out_;

	out_.Style().Stick() << CLay_Style::CStick::e_right;
	out_.Style().Width() << CLay_Style::CWidth::e_fixed;
	out_.Fixed(215); // ToDo: needs to have some calculation of the width from expected string pattern length;

	out_.Padding().Left(0x3);

	pane_2.Text(_T("00:00:00:000"));
#if defined(pane_borders_thick) && (pane_borders_thick != 0)
//	pane_2.Borders().Left()  << pane_borders_thick; the border class operator '<<' sets its ID and not the thickness of its base class 'line';
//	pane_2.Borders().Right() << pane_borders_thick; the same as above;
	pane_2.Borders().Left().Thickness(pane_borders_thick);
	pane_2.Borders().Right().Thickness(pane_borders_thick);
#if defined(_DEBUG)
	for (ex_ui::controls::borders::TRawBorders::const_iterator it_ = pane_2.Borders().Raw().begin(); it_ != pane_2.Borders().Raw().end(); ++it_) {
		const CBorder& border = it_->second;
		if (border.Is_valid() && !!border.Thickness()) {
			bool b_is_valid = false; b_is_valid = !b_is_valid;
		}
	}
#endif
#endif
}
#pragma endregion

	CGlyph& glyph = this->Get().Panes().Glyph();

	glyph.Format().Image().Index(1);
	glyph.Layout().Style().Width() << CLay_Style::CWidth::e_fixed;
	glyph.Layout().Fixed(sta_bar.Layout().Height());

	return this->Error();
}

TError&   CStatus::Error (void) const { return this->m_error; }

const
CSta_bar& CStatus::Get (void) const { return this->m_status; }
CSta_bar& CStatus::Get (void)       { return this->m_status; }

err_code  CStatus::OnCreate (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if ((*this)().Is_valid())
		return this->m_error = (err_code) TErrCodes::eObject::eExists;

	if (!shared::Get_View().Parent())
		return this->m_error = __e_hwnd;

	CSta_bar& sta_bar = this->Get();
	// (1) creates status bar user control;
	if (__failed(sta_bar.Create(shared::Get_View().Parent(), 0xA)))
		return this->m_error = this->Get().Error();

	this->m_error << this->m_timer.Create(100);
	return this->Error();
}
err_code  CStatus::OnDestroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	CSta_bar& sta_bar = this->Get();

	if (__failed(sta_bar.Destroy()))
		this->m_error = sta_bar.Error();

	return this->Error();
}

void  CStatus::SetText(_pc_sz _p_text, const uint16_t _pane_ndx/* = 1*/) {
	_p_text; _pane_ndx;
	this->Get().Panes().Pane(_pane_ndx).Text(_p_text);
}

void  CStatus::IWaitable_OnComplete (void) {
	this->Get().Panes().Pane(2).Text((_pc_sz) Get_entry_point());
}

const
CSta_bar& CStatus::operator ()(void) const { return this->Get(); }
CSta_bar& CStatus::operator ()(void)       { return this->Get(); }
