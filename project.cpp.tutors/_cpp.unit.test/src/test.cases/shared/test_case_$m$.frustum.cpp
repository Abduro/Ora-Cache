/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-May-2026 at 19:11:29.586, UTC+4, Batumi, Tuesday;
	This is OpenGL virtual camera frustum wrapper interface implementation file for using in test cases' adapters;
*/
#include "test_case_$m$.frustum.h"

using namespace test::open_gl::frustum;

#pragma region cls::CTstAspect{}

CTstAspect::CTstAspect (const bool _b_verbose) : m_verbose(_b_verbose) {}

err_code CTstAspect::Set (const uint32_t _height, const uint32_t _width) {
	_height; _width;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Input args: _height=%u;_width=%u;"), _height, _width);

	if (__failed((*this)().Set(_height, _width))) { _out() += (*this)().Error();}
	else { _out() += TString().Format(_T("[impt] Result: aspects' ratio = %.7f;"), (*this)().Ratio()); }

	return (*this)().Error();
}

const
CAspect&    CTstAspect::operator ()(void) const { return this->m_aspect; }
CAspect&    CTstAspect::operator ()(void)       { return this->m_aspect; }

#pragma endregion
#pragma region cls::CTstCfg{}

CTstCfg::CTstCfg (const bool _b_verbose) : m_verbose(_b_verbose) {}

err_code CTstCfg::Set_defaults (void) {

	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Default())) { _out() += (*this)().Error(); }
	else {
		static _pc_sz p_cs_pat = _T("default values: FoV vert = %.2f deg (%.7f rad); dist: near = %.2f; far = %.2f;");

		const float f_deg = (*this)().FoV().Vert().Get().Degrees();
		const float f_rad = (*this)().FoV().Vert().Get().Radians();

		const float f_far  = (*this)().Planes().Far();
		const float f_near = (*this)().Planes().Near();

		_out() += TString().Format(p_cs_pat, f_deg, f_rad, f_near, f_far);
	}

	return (*this)().Error();
}

const
CCfg&  CTstCfg::operator ()(void) const { return this->m_cfg; }
CCfg&  CTstCfg::operator ()(void)       { return this->m_cfg; }

#pragma endregion
#pragma region cls::CTstFoV{}

CTstFoV::CTstFoV (const bool _b_verbose) : m_verbose(_b_verbose) {}

const
CFoV& CTstFoV::operator ()(void) const { return this->m_fov; }
CFoV& CTstFoV::operator ()(void)       { return this->m_fov; }

#pragma endregion
#pragma region cls::CTstFrustum{}

CTstFrustum::CTstFrustum (const bool _b_verbose) : m_verbose(_b_verbose) {}

err_code  CTstFrustum::Update (void) {

	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const uint32_t u_height = 683, u_width = 683;

	CAspect& aspect = (*this)().Aspect();
	CCfg& cfg = (*this)().Cfg();

	if (__failed(aspect.Set(u_height, u_width))) { _out() += aspect.Error(); return aspect.Error(); }
	if (__failed(cfg.Default())) { _out() += cfg.Error(); return cfg.Error(); }

	if (__failed((*this)().Update())) _out() += (*this)().Error();
	else {
		const c_mat4x4& mat_proj = (*this)().Project();
		_out() += _T("[impt] perspective matrix:");
		_out() += c_mtx_4x4::To_str(mat_proj, false);
	}

	return (*this)().Error();
}

const
CFrustum& CTstFrustum::operator ()(void) const { return this->m_frust; }
CFrustum& CTstFrustum::operator ()(void)       { return this->m_frust; }

#pragma endregion