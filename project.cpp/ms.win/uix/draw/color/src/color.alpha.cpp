/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Oct-2021 at 1:45:38.8392778 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack color alpha value interface implementation file;
*/
#include "color.alpha.h"

using namespace ex_ui::color;
using namespace ex_ui::color::rgb;

/////////////////////////////////////////////////////////////////////////////

rgb_value CAlpha::COpacity::Get (rgb_color _color) {
	_color;
	return (static_cast<rgb_value>(_color >> 24));
}

rgb_value CAlpha::COpacity::Get (const TPercent& _percent) {
	_percent;
	return CAlpha::COpacity::Get((uint8_t)_percent.GetAsInt());
}

rgb_value CAlpha::COpacity::Get (const uint8_t _percent) {
	_percent;
#if (0)
	if (!TPercent::Is(_percents))
		return 0;
#else
	if (TPercent::e_max < _percent)
		return 0;
#endif
	else {
		static const float f_1_pct = float(rgb_val_max) / 100.0f;
		return static_cast<rgb_value>(::std::ceilf(static_cast<float>(_percent) * f_1_pct));
	}
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString CAlpha::Print (const TPercent& _percent) {
	_percent;
	static _pc_sz pc_sz_pat = _T("cls::[%s].(%u%%)>>value=%u;opaque=%u%%;");

	const TPercent pct_opaq(100 - _percent.GetAsInt());

	CString cs_out; cs_out.Format(pc_sz_pat, (_pc_sz)__CLASS__, _percent.GetAsInt(), TOpecity::Get(pct_opaq), pct_opaq.GetAsInt());
	return  cs_out;
}

CString CAlpha::Print (const rgb_value _n_value, const e_print _e_opt) {
	_n_value; _e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {value=%u(%u%%)}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {value=%u(%u%%)}");
	static _pc_sz pc_sz_pat_r = _T("{value=%u(%u%%)}");

	const float f_alpha_prcnt = (float)_n_value/(float)rgb_val_max * 100.0f;
	const int32_t alpha_prcnt = TPercent(f_alpha_prcnt).GetAsInt();

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _n_value, alpha_prcnt);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, _n_value, alpha_prcnt); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, _n_value, alpha_prcnt); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif