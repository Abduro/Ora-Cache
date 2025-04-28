/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2025 at 23:18:09.022, UTC+4, Batumi, Saturday;
	This is Ebo Pack DirectX shape vertex wrapper interface implementation file; 
*/
#include "direct_x.vertex.h"
#include "direct_x.swap.h"     // for printing buffer usage;
#include "direct_x.texture.h"  // for printing texture binding;

namespace ex_ui { namespace draw { namespace direct_x {
/////////////////////////////////////////////////////////////////////////////
namespace _11 { using namespace ex_ui::draw::direct_x;

CVtxDesc::CVtxDesc (void) : m_desc{0}{}
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString   CVtxDesc::Print (const TVtxDesc& _desc, const e_print _e_opt) {
	_desc; _e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{usage=%s;bind=%s;cpu=%s;misc=%s;stride=%u}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{usage=%s;bind=%s;cpu=%s;misc=%s;stride=%u}");
	static _pc_sz pc_sz_pat_r = _T("{usage=%s;bind=%s;cpu=%s;misc=%s;stride=%u}");

	CString cs_bind = CBind::Print(_desc.BindFlags);
	CString cs_cpu  = CCpu_Access::Print(_desc.CPUAccessFlags);
	CString cs_misc = CMiscFlags::Print(_desc.MiscFlags);
	CString cs_use  = CBuff_Usage::Print(_desc.Usage);

	CString cs_out;

	const uint32_t n_stride = _desc.StructureByteStride;

	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a,
			(_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_use, (_pc_sz)cs_bind, (_pc_sz)cs_cpu, (_pc_sz)cs_misc, n_stride
		);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n,
			(_pc_sz)__CLASS__, (_pc_sz)cs_use, (_pc_sz)cs_bind, (_pc_sz)cs_cpu, (_pc_sz)cs_misc, n_stride
		);
	}
	if (e_print::e_req   == _e_opt) {
		cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_use, (_pc_sz)cs_bind, (_pc_sz)cs_cpu, (_pc_sz)cs_misc, n_stride);
	}

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
CString   CVtxDesc::Print (const e_print _e_opt) const {
   return CVtxDesc::Print (this->Raw() , _e_opt);
}
#endif
const
TVtxDesc& CVtxDesc::Raw (void) const { return this->m_desc; }
TVtxDesc& CVtxDesc::Raw (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////

CVertex:: CVertex (void) { this->m_error << __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////
const
CVtxDesc& CVertex::Desc  (void) const { return this->m_desc;  }
CVtxDesc& CVertex::Desc  (void)       { return this->m_desc;  }

TError&   CVertex::Error (void) const { return this->m_error; }

bool      CVertex::Is_valid (void) const { return nullptr != this->Ptr(); }
#if defined(_DEBUG)
CString   CVertex::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());
	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_valid); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
const
TBufferPtr& CVertex::Ptr (void) const { return this->m_p_buf; }
err_code    CVertex::Ptr (const TBufferPtr& _p_buf) {
	_p_buf;
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_buf)
		return this->m_error << __e_pointer;

	if (this->Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	this->m_p_buf = _p_buf;
	this->m_p_buf->GetDesc(&this->Desc().Raw());

	return this->Error();
}
	
}
/////////////////////////////////////////////////////////////////////////////
namespace _12 { using namespace ex_ui::draw::direct_x;
}

}}}