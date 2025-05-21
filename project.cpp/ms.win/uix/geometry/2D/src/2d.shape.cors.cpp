/*
	Creted by Tech_Dog (ebontrop@gmail.com) on 18-May-2025 at 22:05:34.461,(UTC+4), Batumi, Sunday;
	This is Ebo Pack 2D space geometry curve corners interface implementation file;
*/
#include "2d.shape.cors.h"

using namespace geometry::base::_2D;

/////////////////////////////////////////////////////////////////////////////

CCorner:: CCorner (const CMarker& _marker, const int8_t _radius) : m_marker(_marker), m_radius(_radius) {}
CCorner:: CCorner (const CCorner& _ref) : CCorner() { *this = _ref; }
CCorner::~CCorner (void) {}

/////////////////////////////////////////////////////////////////////////////
const
uint32_t  CCorner::Id (void) const { return this->m_marker.Id(); }
uint32_t& CCorner::Id (void)       { return this->m_marker.Id_ref(); }

bool CCorner::Is_concave (void) const { return this->Radius() < 0; }
bool CCorner::Is_convex (void) const { return this->Radius() > 0; }

bool CCorner::Is_valid (void) const { return !!this->Id(); }

int8_t    CCorner::Radius (void) const { return this->m_radius; }
int8_t&   CCorner::Radius (void)       { return this->m_radius; }

/////////////////////////////////////////////////////////////////////////////

CCorner&  CCorner::operator = (const CCorner& _ref ) { *this << _ref.Radius() << _ref.Id(); return *this; }
CCorner&  CCorner::operator <<(const int8_t  _radius) {  this->Radius() = _radius; return *this; }
CCorner&  CCorner::operator <<(const uint32_t  _marker) {  this->Id() = _marker; return *this; }
/////////////////////////////////////////////////////////////////////////////

CCorners:: CCorners (void) {}
CCorners:: CCorners (const CCorners& _ref) : CCorners() { *this = _ref; }
CCorners::~CCorners (void) { if (this->Is()) m_corners.clear(); }

/////////////////////////////////////////////////////////////////////////////

err_code   CCorners::Add (const uint32_t _marker, const CCorner& _corner) {
err_code n_result = __s_ok;
	try {
		this->m_corners[_marker] = _corner;
	}
	catch (const ::std::bad_alloc&) { n_result = __e_no_memory; }
	return n_result;
}
const
CCorner&   CCorners::Get (const uint32_t _marker) const {
	TRawCorners::const_iterator it_ = this->Raw().find(_marker);
	if (it_ == this->Raw().end()) {
		static CCorner na_; return na_;
	} else
		return it_->second;
}
CCorner&   CCorners::Get (const uint32_t _marker)      {
	TRawCorners::iterator it_ = this->Raw().find(_marker);
	if (it_ == this->Raw().end()) {
		static CCorner na_; return na_;
	} else
		return it_->second;
}
const bool CCorners::Has (const uint32_t _marker) const {
	TRawCorners::const_iterator it_ = this->Raw().find(_marker); return (it_ != this->Raw().end());
}
const bool CCorners::Is  (void) const { return (this->Raw().empty() == false);}
const
TRawCors&  CCorners::Raw (void) const { return m_corners; }
TRawCors&  CCorners::Raw (void)       { return m_corners; }

err_code   CCorners::Rem (const uint32_t _marker) {
	_marker;
	err_code n_result = __s_ok;
	TRawCors::iterator it_ = this->Raw().find(_marker);
	if (it_ == this->Raw().end())
		return n_result = (err_code)TErrCodes::eData::eNotFound;
	try {
		this->Raw().erase(it_);
	} catch (...) { n_result = __e_no_memory; }
	return n_result;
}

err_code   CCorners::Set (const uint32_t _marker, const int8_t _radius) {
err_code n_result = __s_ok;
	if (this->Has(_marker)) {
		this->Get(_marker) << _radius;
	}
	else if (!!_marker) {
		n_result = this->Add(_marker, CCorner(CMarker(_marker, _T("#no_matter"), false), _radius));
	}
	else
		n_result = __e_inv_arg;

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

CCorners&  CCorners::operator += (const CCorner& _corner) { this->Add(_corner.Id(), _corner); return *this; }
CCorners&  CCorners::operator -= (const CCorner& _corner) { this->Rem(_corner.Id()); return *this; }

CCorners&  CCorners::operator  = (const CCorners& _src) {
	_src;
	err_code n_result = __s_ok;
	if (this->Raw().empty() == false)
		this->Raw().clear();

	for (TRawCorners::const_iterator it_ = _src.Raw().begin(); it_ != _src.Raw().end(); ++it_) {
		n_result = this->Add(it_->first, it_->second);
		if (__failed(n_result))
			break;
	}
	return *this;
}