#ifndef _EBOSHAGUITHEME_H_INCLUDED
#define _EBOSHAGUITHEME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Dec-2020 at 7:50:01.682 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Sha Optima Tool GUI generic format color theme interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack UM test project on 14-Jan-2021 at 12:03:27.717 pm, UTC+7, Novosibirsk, Thursday;
	Adopted to Ebo Pack render project desktop GUI app on 26-Apr-2025 at 22:49:56.695, UTC+4, Batumi, Saturday; 
*/
#include "win.gui.inc.h"
#include "uix.theme.named.h"
#include "uix.theme.reg.h"

using namespace ex_ui::theme;
using namespace ex_ui::theme::storage;

#include "uix.image.prov.h"

using namespace ex_ui::draw::images;

namespace ebo { namespace sha { namespace theme { namespace colors {
	// this namespace and references to other ones are not required and are kept for backward compatibility only;
	using namespace ex_ui::color::rgb;
	using namespace ex_ui::theme::colors;

}}}}

namespace ebo { namespace sha { namespace theme {
	// this namespace and references to other ones are not required and are kept for backward compatibility only;
	using namespace ex_ui::color::rgb;
	using namespace ex_ui::theme;

namespace paths {

	class CNot_Copyable {
	protected:
		 CNot_Copyable (void) = default; CNot_Copyable (const CNot_Copyable&) = delete; CNot_Copyable (CNot_Copyable&&) = delete;
		~CNot_Copyable (void) = default;
	public:
		 TError& Error (void) const;
		 bool Is_valid (void) const; // returns 'true' in case if the path to the root folder of the theme test cases is already set, i.e. not empty;

		 _pc_sz    Get (void) const; // gets the path to one of the folders of the theme test cases;

	protected:
		mutable
		CError   m_error;
		CString  m_path ;

	private:
		CNot_Copyable& operator = (const CNot_Copyable&) = delete; CNot_Copyable& operator = (CNot_Copyable&&) = delete;
	};
	/*
		this is the test cases root path of the registry key:
		the registry key path: HKEY_CURRENT_USER\SOFTWARE\ebo::boo::renderer\Themes\{currnet palette}\Theme#{ndx}\test.cases ;
		the key 'path' value: it contains the full path to the folder of the test cases' images;
	*/
	class CRoot : public CNot_Copyable { typedef CNot_Copyable No_Copy;
	public:
		 CRoot (void);
		~CRoot (void);

	public:
		err_code Set (void);  // reads the path to the currently selected theme test cases from the registry;
		operator _pc_sz (void);
	};
	/*
		this class gets absolute path to particular image file that will be used whithin a pane of the status bar control;
		the registry key path is: {test.cases::control_0}
		the named value for particular image file is: 'image_{#of the index}', e.g. 'image_0';
			the path to the folder of the test images + '\sta-bar' + file name of the named value described above;
		for example:
			hkey_cur_usr\software\ebo::boo::renderer\Themes\{currnet palette}\Theme#{ndx}\test.cases\control_0@image_{ndx};
	*/
	class CStatus : public CNot_Copyable { typedef CNot_Copyable No_Copy;
	public:
		 CStatus (void); CStatus (const CStatus&) = delete; CStatus (CStatus&&) = delete;
		~CStatus (void);

		CString  Get (const uint32_t _img_ndx); // gets the path to image file by specifying value name index, i.e. 'image_0'...'image_n';

		err_code Set (void);  // reads the path to the status bar control test cases from the registry;

	};
}

namespace images {
}

}}}

namespace ebo { namespace sha { namespace theme { namespace direct_x {
	// this namespace and references to other ones are not required and are kept for backward compatibility only;
	using CFloat = ex_ui::color::rgb::CFloat;
	using namespace ex_ui::theme::direct_x;

}}}}

#endif/*_EBOSHAGUITHEME_H_INCLUDED*/