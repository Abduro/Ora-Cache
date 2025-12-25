/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface implementation file; 
*/
#include "ebo_test_$m$.matrix.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace _impl {

	class CPrint {
	public:
		CPrint (const CString& _cls_name, const bool _use_sign = false) : m_cls_name(_cls_name), m_use_sign(_use_sign) {}
	public:
		CString To_str (const t_mat3x3& _mat3x3, const bool _b_out) {
			_mat3x3; _b_out;
			CString  cs_out;
			static _pc_sz pc_sz_fmt_0 = _T("%9.7f");
			static _pc_sz pc_sz_fmt_1 = _T("%+9.7f");

			for (uint32_t row_ = 0; row_ < t_mat3x3::u_rows; row_++) {
				CString cs_row;
				for (uint32_t col_ = 0; col_ < t_mat3x3::u_cols; col_++) {
				#if (0)
					cs_row += TString().Float(_mat3x3(col_, row_), t_fmt_spec::e_decimal, this->m_use_sign ? pc_sz_fmt_1 : pc_sz_fmt_0);
				#else
					if (false) {}
					else if (this->m_use_sign && _mat3x3(col_, row_) < 0.0f) {} // the '-' sign will be added by sprintf();
					else if (this->m_use_sign)
					cs_row += _T(" ");
					cs_row += TString().Float(_mat3x3(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt_0);
				#endif
					if (col_ < t_mat3x3::u_cols - 1)
						cs_row += _T(" ");
				}
				cs_out += TString().Format(_T("%s%s%s"), predefs::_p_pfx, (_pc_sz) cs_row, predefs::_p_sfx);
			}
			if (_b_out) {
				if (this->m_cls_name.IsEmpty())
					this->m_cls_name = __CLASS__;
				_out() += TString().Format(_T("cls::[%s].%s() >> [%s%s%s]"), (_pc_sz)this->m_cls_name, (_pc_sz)__METHOD__, predefs::_p_sfx, (_pc_sz) cs_out, predefs::_p_pfx);
			}

			return  cs_out;
		}

		CString To_str (const t_mat4x4& _mat4x4, const bool _b_out) {
			_mat4x4; _b_out;
			CString  cs_out;
			static _pc_sz pc_sz_fmt_0 = _T("%9.7f");

			for (uint32_t row_ = 0; row_ < t_mat4x4::u_rows; row_++) {
				CString cs_row;
				for (uint32_t col_ = 0; col_ < t_mat4x4::u_cols; col_++) {
					if (false) {}
					else if (this->m_use_sign && _mat4x4(col_, row_) < 0.0f) {} // the '-' sign will be added by sprintf();
					else if (this->m_use_sign)
					cs_row += _T(" ");
					cs_row += TString().Float(_mat4x4(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt_0);
					if (col_ < t_mat4x4::u_cols - 1)
						cs_row += _T(" ");
				}
				cs_out += TString().Format(_T("%s%s%s"), predefs::_p_pfx, (_pc_sz) cs_row, predefs::_p_sfx);
			}
			if (_b_out) {
				if (this->m_cls_name.IsEmpty())
					this->m_cls_name = __CLASS__;
				_out() += TString().Format(_T("cls::[%s].%s() >> [%s%s%s]"), (_pc_sz)this->m_cls_name, (_pc_sz)__METHOD__,  predefs::_p_sfx, (_pc_sz) cs_out, predefs::_p_pfx);
			}
			return  cs_out;
		}
	
	private:
		bool m_use_sign;    // if is set to 'true': each entry/element of the matrix will have the sign '-/+', otherwise the '-' if value is negative;
		CString m_cls_name; // the source class name;
	}; 

}}}}}

#pragma region cls::c_mat3x3{}

c_mat3x3::c_mat3x3 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_mat3x3::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_b_verb = true;
	this->To_str();
}

void c_mat3x3::Set (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *initial* values:");

	this->To_str();

	c_vec3 col_0(false), col_1(false), col_2(false); // output flags to set to 'false';
	col_0.ref().Set(0.0f, 1.0f, 2.0f);
	col_1.ref().Set(3.0f, 4.0f, 5.0f);
	col_2.ref().Set(6.0f, 7.0f, 8.0f);

	_out() += _T("*input* values:");
	_out() += TString().Format(_T("col_#0: %s"), (_pc_sz) col_0.To_str());
	_out() += TString().Format(_T("col_#1: %s"), (_pc_sz) col_1.To_str());
	_out() += TString().Format(_T("col_#2: %s"), (_pc_sz) col_2.To_str());

	this->ref().Cols().Set(0, col_0.ref());
	this->ref().Cols().Set(1, col_1.ref());
	this->ref().Cols().Set(2, col_2.ref());

	_out() += _T("the matrix *result* values:");
	this->To_str();
	_out()();
}

const
t_mat3x3& c_mat3x3::ref (void) const { return this->m_mat3x3; }
t_mat3x3& c_mat3x3::ref (void)       { return this->m_mat3x3; }

CString   c_mat3x3::To_str (_pc_sz _p_prf, _pc_sz _p_sep, _pc_sz _p_sfx) const {
	_p_prf; _p_sep; _p_sfx;

	return _impl::CPrint(__CLASS__).To_str(this->ref(), this->m_b_verb);
}

#pragma endregion
#pragma region cls::c_mat4x4{}

c_mat4x4::c_mat4x4 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_mat4x4::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_b_verb = true;
	this->To_str();
}

void c_mat4x4::Identity (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->ref().Identity();

	this->m_b_verb = true;
	this->To_str();
}

void c_mat4x4::Translate (void) {

	c_vec3 vec3;
	vec3.Set();

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* translate:");

	this->ref().Rows().Set(t_mat4x4::u_rows - 1, 1.0f); // sets the last row of the matrix to some value that is not zero, otherwise there's no translation;

	this->m_b_verb = true;
	this->To_str();

	this->ref().Translate(vec3.ref());

	_out() += _T("the matrix *after* translate:");
	this->To_str();
}

const
t_mat4x4& c_mat4x4::ref (void) const { return this->m_mat4x4; }
t_mat4x4& c_mat4x4::ref (void)       { return this->m_mat4x4; }

CString c_mat4x4::To_str (_pc_sz _p_prf, _pc_sz _p_sep, _pc_sz _p_sfx) const {
	_p_prf; _p_sep; _p_sfx;

	static _pc_sz pc_sz_fmt = _T("%9.7f");

	CString cs_out;

	for (uint32_t row_ = 0; row_ < t_mat4x4::u_rows; row_++) {
		CString cs_row;
		for (uint32_t col_ = 0; col_ < t_mat4x4::u_cols; col_++) {
			cs_row += TString().Float(this->ref().Cell(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt);
			if (col_ < t_mat4x4::u_cols - 1)
				cs_row += _p_sep;
		}
		cs_out += TString().Format(_T("%s%s%s"), _p_prf, (_pc_sz) cs_row, _p_sfx);
	}
	if (this->m_b_verb) {
		_out() += TString().Format(_T("cls::[%s].%s() >> [%s%s%s]"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_sfx, (_pc_sz) cs_out, _p_prf);
		_out()();
	}
	return cs_out;
}

#pragma endregion
#pragma region cls::c_rot_3x3{}

c_rot_3x3::c_rot_3x3 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_rot_3x3::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	this->To_str();
}

const
t_rot3x3& c_rot_3x3::ref (void) const { return this->m_rot3x3; }
t_rot3x3& c_rot_3x3::ref (void)       { return this->m_rot3x3; }

void      c_rot_3x3::Rotate_x (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	_impl::CPrint(__CLASS__).To_str(this->ref(), true);
	c_vec3 x_axis(false); x_axis.ref().Set(1.0f, 0.0f, 0.0f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; %s-axis = %s;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], _T("x"), (_pc_sz) x_axis.To_str());

		this->ref().Do(f_angels[i_], x_axis.ref());

		_out() += _T("the matrix *after* rotate:");
		_impl::CPrint(__CLASS__, true).To_str(this->ref(), true);
	}
	_out()();
}

void      c_rot_3x3::Rotate_y (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	_impl::CPrint(__CLASS__).To_str(this->ref(), true);
	c_vec3 y_axis(false); y_axis.ref().Set(0.0f, 1.0f, 0.0f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; %s-axis = %s;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], _T("y"), (_pc_sz) y_axis.To_str());

		this->ref().Do(f_angels[i_], y_axis.ref());

		_out() += _T("the matrix *after* rotate:");
		_impl::CPrint(__CLASS__, true).To_str(this->ref(), true);
	}
	_out()();
}

void      c_rot_3x3::Rotate_z (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	_impl::CPrint(__CLASS__).To_str(this->ref(), true);
	c_vec3 z_axis(false); z_axis.ref().Set(0.0f, 0.0f, 1.0f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; %s-axis = %s;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], _T("z"), (_pc_sz) z_axis.To_str());

		this->ref().Do(f_angels[i_], z_axis.ref());

		_out() += _T("the matrix *after* rotate:");
		_impl::CPrint(__CLASS__, true).To_str(this->ref(), true);
	}
	_out()();
}

CString   c_rot_3x3::To_str (void) const {
	CString cs_out = _impl::CPrint(__CLASS__).To_str(this->ref(), this->m_b_verb); if (this->m_b_verb) _out()();
	return  cs_out;
}

#pragma endregion
#pragma region cls::c_rot_4x4{}

c_rot_4x4::c_rot_4x4 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_rot_4x4::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	this->To_str();
}

const
t_rot4x4& c_rot_4x4::ref (void) const { return this->m_rot4x4; }
t_rot4x4& c_rot_4x4::ref (void)       { return this->m_rot4x4; }

void      c_rot_4x4::Rotate_x (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	_impl::CPrint(__CLASS__).To_str(this->ref(), true);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_]);

		this->ref().On_x(f_angels[i_]);

		_out() += _T("the matrix *after* rotate:");
		_impl::CPrint(__CLASS__, true).To_str(this->ref(), true);
	}
	_out()();
}

CString   c_rot_4x4::To_str (void) const {
	CString cs_out = _impl::CPrint(__CLASS__).To_str(this->ref(), this->m_b_verb); if (this->m_b_verb) _out()();
	return  cs_out;
}

#pragma endregion