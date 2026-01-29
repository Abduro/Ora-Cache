/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 12:58:26.506, UTC+4, Batumi, Ssturday;
	This is Ebo Pack OpenGL vertex buffer object wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.buffer.h"
#include "test_case_$d$.shape.2d.h"
#include "test_case_$d$.vert.arr.dat.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::CVertBufData{}

CVertBufData::CVertBufData (const e_object _target) : TPipe(_target) {
	this->m_error >>__CLASS__<<__METHOD__<< (e_object::e_none == _target ? __e_not_inited : __s_ok);

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

TError& CVertBufData::Error (void) const { return this->m_error; }

err_code CVertBufData::Get (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	// (1-3) steps: creating the triangle shape and drawing it;
	C3angle tria;
	if (__failed(tria.Draw())) return this->m_error = tria.Error(); // this draw operation creates its own copy of the triangle shape;
	// (4,5) steps: keeping the triangle, getting the buffer identifier and querying its data;
	// (4.a) gets the buffer identifier;
	CVertArray& vert_arr = __vert_arr_accessor (tria());
	const uint32_t u_buf_id = vert_arr.Buffer().GetId();
	// (4.b) queries the data;
	/* *important*: setting buf_data << tria() does not produce any compilation error:
	    the input data is cast to e_bnd_tgts enum element and this leads to invalid target type the buffer is bound to; */
	CData buf_data; buf_data << u_buf_id << vert_arr.Buffer().Target(); // sets required attribute values;
	if (__failed(buf_data.Query())) return this->m_error = buf_data.Error();
	else {
		const TRawData& raw_data = buf_data.Get();
		_out() += TString().Format(_T("[impt] Data is queried: {size = 0x%04x};"), raw_data.GetSize());
		_out() += CVertBufData::To_str(raw_data);
	}
	return this->Error();
}

CString  CVertBufData::To_str (const TRawData& _data, const uint32_t _u_elements, _pc_sz _p_pfx, _pc_sz _p_sfx) {
	_data; _u_elements; _p_pfx; _p_sfx;
	CString cs_out;
	
	if (_data.GetSize() == 0) return (cs_out = TString().Format(_T("%s#empty"), _p_pfx));
	if (_data.GetSize() % sizeof(float)) return (cs_out = TString().Format(_T("%s#not_aligned"), _p_pfx));

	static const uint32_t u_cols = 8, u_sec = 4; u_cols; u_sec;

	const uint32_t u_count = _data.GetSize() / sizeof(float);
	const float* const p_data = reinterpret_cast<const float*>(_data.GetData());
	if (nullptr == p_data)
		return (cs_out = TString().Format(_T("%s#not_float"), _p_pfx));

	static _pc_sz pc_fmt_p = _T("  %.8f"); // positive value preserves the space for minus sign in purposes of alignment;
	static _pc_sz pc_fmt_n = _T(" %.8f");

	uint32_t u_col = 0;

	cs_out += _T("\t");
	for (uint32_t i_ = 0; i_ < u_count; i_++) { u_col += 1;
		if (p_data[i_] < 0.0f)
		     cs_out += TString().Format(pc_fmt_n, p_data[i_]);
		else cs_out += TString().Format(pc_fmt_p, p_data[i_]);
		if (u_col == u_cols) 
			if (i_ > 0) {
				cs_out += _p_sfx;
				cs_out += _p_pfx; u_col = 0;
			}
	}
	cs_out += _p_sfx;

	return  cs_out;
}

#pragma endregion

#pragma region cls::CVertBuffer{}

CVertBuffer::CVertBuffer (const e_object _target) : TPipe(_target) {
	this->m_error >>__CLASS__<<__METHOD__<< (e_object::e_none == _target ? __e_not_inited : __s_ok);

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

TError& CVertBuffer::Error (void) const { return this->m_error; }

uint32_t CVertBuffer::Size (void) const {
	this->m_error <<__METHOD__<<__s_ok; return CVertBuffer::Size((*this)().Target(), this->m_error);
}
uint32_t CVertBuffer::Size (const e_bind_targets _target, CError& _err) {
	_target; _err;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s() <static>:"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto(false); { _out()(false); ctx_auto.Create(); _out()(true); }

	const uint32_t u_size = CBuffer::Get_size(_target, _err);
	if (false == _err) {
		_out() += TString().Format(_T("[impt] The vertex buffer size is: %u (bytes);"), u_size);
	}
	_out()(false); // no output from context destructor;

	return u_size;
}

const
CBuffer& CVertBuffer::operator ()(void) const { return this->m_buffer; }
CBuffer& CVertBuffer::operator ()(void)       { return this->m_buffer; }

#pragma endregion