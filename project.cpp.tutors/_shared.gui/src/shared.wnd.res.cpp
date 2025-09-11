/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Jul-2012 at 8:37:23pm, GMT+3, Rostov-on-Don, Friday;
	This is Pulsepay Shared Application Icon Holder class implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 10-Jun-2016 at 3:40:16p, GMT+7, Phuket, Rawai, Friday;
*/
#include "shared.wnd.res.h"
#include "shared.preproc.h"

using namespace ex_ui::resource;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace resource { namespace _impl {

	class CIcon_Att {
	public:
		 CIcon_Att (void) {} CIcon_Att (const CIcon_Att&) = delete; CIcon_Att (CIcon_Att&&) = delete;
		~CIcon_Att (void) {}
	public:
		SIZE  Size (const bool bTreatAsLargeIcon) const
		{
			const SIZE szIcon = {
				::GetSystemMetrics(bTreatAsLargeIcon ? SM_CXICON : SM_CXSMICON), 
				::GetSystemMetrics(bTreatAsLargeIcon ? SM_CYICON : SM_CYSMICON)
			};
			return szIcon;
		}

	private:
		CIcon_Att& operator = (const CIcon_Att&) = delete;
		CIcon_Att& operator = (CIcon_Att&&) = delete;
	};


}}}
using namespace shared::resource::_impl;
/////////////////////////////////////////////////////////////////////////////

CIcon:: CIcon (void) { m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CIcon::~CIcon (void) { /*there's no resource for being destroyed;*/ }

/////////////////////////////////////////////////////////////////////////////

TError& CIcon::Error (void) const { return this->m_error; }

HICON   CIcon::Load  (const uint16_t nIconResId, const bool bTreatAsLargeIcon) const
{	// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlew ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadimagew ;
	this->m_error << __METHOD__ << __s_ok;

	const SIZE szIcon = CIcon_Att().Size(bTreatAsLargeIcon);
	const HINSTANCE hInstance = static_cast<HINSTANCE>(::GetModuleHandle(nullptr));
	const HICON hIcon = (HICON)::LoadImage(
		hInstance, MAKEINTRESOURCE(nIconResId), IMAGE_ICON, szIcon.cx, szIcon.cy, LR_DEFAULTCOLOR
	);
	if (nullptr == hIcon)
		m_error.Last();
	return hIcon;
}