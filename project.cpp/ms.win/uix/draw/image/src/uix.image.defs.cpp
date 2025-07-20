/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jul-2025 at 20:34:10.387, UTC+4, Batumi, Wednesday;
	This is Ebo Pack image wrapper project common declarations' implementation file;
*/
#include "uix.image.defs.h"

using namespace ex_ui::draw::images;

namespace ex_ui { namespace draw { namespace images { namespace _impl { void __warning_lnk_4221 (void) {}}}}}

CImageType:: CImageType (void) {} CImageType::CImageType (const e_format _e_fmt) : CImageType() { *this << _e_fmt; }
CImageType::~CImageType (void) {}

_pc_sz CImageType::Ext (const e_format _e_fmt) {
	return (_pc_sz)(this->m_ext = CImageType::ToExt(_e_fmt));
}

CImageType& CImageType::operator <<(const e_format _e_fmt) { this->Ext(_e_fmt); return *this; }

CString  CImageType::ToExt (const CImageType::e_format _e_format) {

	CString cs_ext;

	switch (_e_format) {
	case e_format::e_bmp : cs_ext = _T("bmp" ); break;
	case e_format::e_jpg : cs_ext = _T("jpg" ); break;
	case e_format::e_jpeg: cs_ext = _T("jpeg"); break;
	case e_format::e_png : cs_ext = _T("png" ); break;
	default:
		cs_ext = _T("*");
	}

	return  cs_ext;
}

/////////////////////////////////////////////////////////////////////////////

CListId:: CListId (void) {}
CListId::~CListId (void) {}

dword  CListId::ToDword (const t_size& _size) {
	return (static_cast<dword>(_size.cx) << 16) | static_cast<dword>(_size.cy);
}

t_size CListId::ToSize  (const dword _n_id) {
	return { _n_id >> 16, _n_id & 0xff };
}