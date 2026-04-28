#ifndef __DRAWABLE_DEFS_H_INCLUDED
#define __DRAWABLE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 12:29:48.128, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object common declaration file;
*/
#include "shared.defs.h"
#include "runner.tpl.h"

namespace shared { namespace drawable { using namespace shared::defs;

	using CDelay = shared::runnable::CDelay;
	using CTplRunner = shared::runnable::threads::pool::CTplRunner;
}}

#endif/*__DRAWABLE_DEFS_H_INCLUDED*/