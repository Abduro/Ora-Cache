#ifndef _UIX_GDI_DEFS_H_INCLUDED
#define _UIX_GDI_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jan-2010 at 11:26:44pm, GMT+3, Rostov-on-Don, Saturday;
	This is Sfx Pack drawing service provider class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 11-Aug-2018 at 4:14:00p, UTC+7, Novosibirsk, Saturday;
*/
#include <atlbase.h>
namespace ATL { // this namespace is required for distinguishing ATL primitive shapes from others;
#include <atltypes.h>       // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/crect-class  ;
}                           // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/classes-shared-by-mfc-and-atl ;
#include <atlimage.h>       // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cimage-class ;

#include "atlapp.h"         // wtl::App is required for working CDC;
#include "atlgdi.h"         // wtl::CDC;

#include <map>
#include "color.alpha.h"
#include "color.rgb.h"

#include "2d.base.h"
#include "2d.base.line.h"
#include "2d.shape.h"
#include "2d.shape.rect.h"

#include "shared.types.h"
#include "sys.error.h"

#if defined(_DEBUG)
#include "shared.preproc.h"
#include "shared.string.h"
#endif

namespace ex_ui { namespace draw { namespace defs {

	using namespace shared::types;
	using CError = shared::sys_core::CError;
	using TError = const CError;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/compiler-options-macros ;
	#define _ATL_NO_AUTOMATIC_NAMESPACE

	interface IExclusion {
		virtual   err_code   Add  (const t_rect&)        { return __e_not_impl; }
		virtual   err_code   Apply(const HDC  ) const    { return __e_not_impl; }
		virtual   err_code   Clear(void)                 { return __e_not_impl; }
		virtual   uint32_t   Count(void)        const    { return 0; }
		virtual   t_rect&    Get  (const uint32_t _ndx)  { _ndx; static t_rect rc_empty = {0}; return rc_empty; }
	};
	interface IRenderer_Base {
		virtual   IExclusion& Excluded(void);
	};
	/*
		This interface is used as a pointer to parent window draw functionality;
		Safity of assignment must be protected by critical section inside a receiver implementation;
		But that is not enough taking into account that interface pointer being assigned may possibly point to destroyed object later;
		the only protection here is an assignment of an interface that is implemented ***exactly*** by parent window;
	*/
	interface IRenderer : public IRenderer_Base
	{
		/*
			This function maybe useful for direct call from child control to owner/parent function of filling the background;
			maybe parent object implementation can identify a calling window by extracting window handle from DC provided for calculating required shifts;
			but at the same time, it is much easier (at least it seems to be so) to provide a rectangle being calculated by child control;
			child control knows who its parent, and to use appropriate shift(s) while calculating a rectangle; but it is not truth always;
		*/
		virtual   err_code  DrawBackground(const HDC hSurface, const t_rect& rcDrawArea) {hSurface; rcDrawArea; return __e_not_impl;}
		virtual   err_code  DrawParentBackground(const HWND hChild, const HDC hSurface, t_rect& rcUpdated) PURE;
	};
}}}

#endif/*_UIXDRAWCOMMONDEFINITIONS_H_INCLUDED*/