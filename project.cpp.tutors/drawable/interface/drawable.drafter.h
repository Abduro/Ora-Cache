#ifndef _DRAWABLE_DRAFTER_H_INCLUDEDE
#define _DRAWABLE_DRAFTER_H_INCLUDEDE
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 17:02:41.310, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object/drafter interface declaration file;
*/
#include "drawable.defs.h"
#include "runner.tpl.h"

namespace shared { namespace drawable {

	using CTplRunner = shared::runnable::threads::pool::CTplRunner;

	class CDrafter : public CTplRunner { typedef CTplRunner TBase;
	public:
		CDrafter (void); CDrafter (const CDrafter&); CDrafter (CDrafter&&) = delete; ~CDrafter (void);

		virtual err_code Prepare (void);

	public:
		CDrafter& operator = (const CDrafter&); CDrafter& operator = (CDrafter&&) = delete;
	};
}}

#endif/*_DRAWABLE_DRAFTER_H_INCLUDEDE*/