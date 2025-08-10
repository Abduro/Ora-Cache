#ifndef _SFX_CTRL_CACHE_H_INCLUDED
#define _SFX_CTRL_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Aug-2025 at 16:22:40.790, (UTC+4), Batumi, Sunday;
	This is Ebo Pack status bar user control pointer cache interface definition file;
*/
#include "sfx.tabs.ctrl.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { namespace _impl {

#include "sys.sync_obj.h"

shared::sys_core::CSyncObject sync_ob;

#define Safe_Guard Safe_Lock(sync_ob)

	typedef ex_ui::controls::sfx::tabbed::CControl*  TCtrlPtr;
	typedef 

	class CCache_Ptr { // not used;
	public:
		 CCache_Ptr (void) = default; CCache_Ptr (const CCache_Ptr&) = delete; CCache_Ptr (CCache_Ptr&&) = delete;
		~CCache_Ptr (void) = default;

	public:
		const TCtrlPtr Get (void) const { return nullptr; }
	
	private:
		 CCache_Ptr& operator = (const CCache_Ptr&) = delete; CCache_Ptr& operator = (CCache_Ptr&&) = delete;
	};

}}}}}

#endif/*_SFX_CTRL_CACHE_H_INCLUDED*/