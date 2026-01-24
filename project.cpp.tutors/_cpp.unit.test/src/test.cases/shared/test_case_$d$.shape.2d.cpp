/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Jan-2026 at 13:39:05.751, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 2D shape wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.shape.2d.h"
#include "test_case_$d$.prog.h"
#include "test_case_$d$.vert.arr.obj.h"

using namespace ebo::boo::test::open_gl::draw;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	CTriangle&  __tria_accessor (void) { return ::Get_Tria_2d(); }

}}}}}

#if (1)
#pragma region cls::CTria{}

C3angle::C3angle (void) : TPipe(e_object::e_tria), m_ctx(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	_out()(false);
	if (__failed(this->m_ctx.Create()))
		this->m_error = this->m_ctx.Error(); _out()(true); // restores verbose mode of the logger;
}

err_code C3angle::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
	// it is supposed the logger verbose is turned on;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CTriangle& tria = __tria_accessor(); // the triangle constructor makes basic configuration and data sizes check;
	if (tria.Error()) { // it an error occurs the triangle {ctor} prints out it to debug trace;
		this->m_error = tria.Error();
		_out() += this->Error().Print(TError::e_print::e_req); return this->Error();
	}
	_out()(false); // it is not of interest to get info from program create routines;

	// the 1st step: creating the program and its shaders, compiling shaders and attaching them to program;
	CProg prog((*this)()); prog << CProg::e_opts::e_link << CProg::e_opts::e_use_$; // the options are required for proper program creation;

	if (__failed(prog.Create())) {
		return this->m_error = prog.Error();
	} // otherwise, the shaders are created and compiled, the program is linked;

	// the 2nd step: creating vertex array object;
	CVertArrObj vao((*this)());
	if (__failed(vao.Create())) {
		return this->m_error = vao.Error();
	}

	_out()(true);
	_out() += TString().Format(_T("[impt] The triangle shape (prog_id = 0x%02x) is created;"), prog.GetId());
	return this->Error();
}

err_code C3angle::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()(false);

	CTriangle& tria = __tria_accessor(); // the triangle should be already created, thus no check error of this constructor that is not called;

	// the 1st step: deleting the associated program;
	CProg prog((*this)()); prog << CProg::e_opts::e_link << CProg::e_opts::e_use_$; // the options are required for proper program deletion;
	const uint32_t u_prog_id = prog.GetId();

	// the deletion of the prgram detaches the shaders and deletes them if any;
	if (__failed(prog.Delete())) {
		return this->m_error = prog.Error();
	}

	// the 2nd step: deleting the associated vertex array object;
	CVertArrObj vao((*this)());
	if (__failed(vao.Delete())) {
		return this->m_error = vao.Error();
	}

	tria; // the shape of the triangle does nothing here and participates in the vertex data set and in the triangle shape drawing;

	_out()(true);
	_out() += TString().Format(_T("[impt] The triangle shape (prog_id = 0x%02x) is deleted;"), u_prog_id);

	return this->Error();
}

err_code C3angle::Draw (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(this->Create())) return this->Error();

	_out()(false);  // turns the log verbose off; there is none of interest in internal messages of triangle draw operation;
	// triangle shape is created, but its vertices are not set to value, it is important, otherwise vertex array is invalid;
	::Get_shapes().Defaults().SetTo((*this)());

	CTriangle& tria = __tria_accessor();
	if (__failed(tria.Draw()))
		this->m_error = tria.Error(); // the error trace is made by 'draw' method; no exit at this point;
	
	_out()(true);
	if (this->Error())
		_out() += this->Error().Print(TError::e_print::e_req);
	else
		_out() += _T("[impt] Triangle draw is completed;");

	return this->Error();
}

TError& C3angle::Error (void) const { return this->m_error; }

const
TPipe& C3angle::operator ()(void) const { return (TPipe&)*this; }
TPipe& C3angle::operator ()(void)       { return (TPipe&)*this; }

#pragma endregion
#endif