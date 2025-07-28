#ifndef _CTL_BASE_IMAGE_H_INCLUDED
#define _CTL_BASE_IMAGE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Jul-2025 at 20:50:50.000, UTC+4, Batumi, Wednesday;
	This is Ebo Pack user base control image interface declaration file;
*/
#include "ctl.base.defs.h"
#include "ctl.base.layout.h"

#include "uix.image.cache.h"
#include "uix.image.prov.h"

namespace ex_ui { namespace controls {

	using CMargins = ex_ui::controls::layout::CMargins_of_rect;
	using HImgList = HIMAGELIST;
	using CImgList = ex_ui::draw::images::CList;

	class CImages {
	public:
		 CImages (void); CImages (const CImages&); CImages (CImages&&) = delete;
		~CImages (void);

	public:
		const
		CImgList& List (void) const;
		CImgList& List (void) ;

	public:
		CImages&  operator = (const CImages&) = delete; CImages& operator = (CImages&&) = delete;
	private:
		CImgList  m_list;
	};

}}
#endif/*_CTL_BASE_IMAGE_H_INCLUDED*/