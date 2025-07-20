#ifndef _UIX_IMAGE_DEFS_H_INCLUDED
#define _UIX_IMAGE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jul-2025 at 20:29:18.730, UTC+4, Batumi, Wednesday;
	This is Ebo Pack image wrappers' project included references and common declaration file;
*/
#include <atlbase.h>
#include <atlcomcli.h>
#include <atlfile.h>

#include <commctrl.h>
#include <coml2api.h>

#pragma comment (lib, "Comctl32.lib")

#include "shared.props.h"
#include "shared.types.h"
#include "shared.preproc.h"
#include "shared.string.h"

#include "sys.error.h"
#include "sys.mem.global.h"

namespace ex_ui { namespace draw { namespace images {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx;

	using namespace shared::memory;

	// https://developer.mozilla.org/en-US/docs/Web/Media/Guides/Formats/Image_types ;
	// https://learn.microsoft.com/en-us/dotnet/desktop/winforms/advanced/types-of-bitmaps ;

	class CImageType {
	public:
		enum e_format : uint32_t {
		     e__undef = 0x0, // this enumeration can be extended for new acceptable formats of the image, but this one is enough for the time being;
		     e_bmp    = 0x1, // https://en.wikipedia.org/wiki/BMP_file_format ;
		     e_jpg    = 0x2, // https://en.wikipedia.org/wiki/JPEG ; two different items just mean two different file extensions;
			 e_jpeg   = 0x3, // https://www.adobe.com/creativecloud/file-types/image/raster/jpeg-file.html ;
		     e_png    = 0x4, // https://en.wikipedia.org/wiki/PNG ;
		};
	public:
		 CImageType (void);  CImageType (const CImageType&) = delete; CImageType (CImageType&&) = delete;
		 CImageType (const e_format);
		~CImageType (void);

		_pc_sz Ext (const e_format);

	public:
		static CString ToExt (const e_format);

		CImageType& operator <<(const e_format);
	private:
		CImageType& operator = (const CImageType&) = delete; CImageType& operator = (CImageType&&) = delete;
		CString m_ext;
	};

	using TImgType = CImageType;
	using TImgFmt  = CImageType::e_format;

	// https://learn.microsoft.com/en-us/windows/win32/controls/ilc-constants ;
	using HImgList = HIMAGELIST;
	using HBitmap  = HBITMAP;

	class CListId {
	public:
		 CListId (void);
		 CListId (const t_size&); CListId (const dword _id); CListId (const CListId&) = delete; CListId (CListId&&) = delete;
		~CListId (void);

	public:
		static dword  ToDword (const t_size&);  // converts input image size to list identifier;
		static t_size ToSize  (const dword);    // converts the input list identifier to image size;

	private:
		CListId& operator = (const CListId&) = delete; CListId& operator = (CListId&&) = delete;
	};

}}}

#endif/*_UIX_IMAGE_DEFS_H_INCLUDED*/