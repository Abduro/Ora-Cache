#ifndef _DIRECT_X_ADAPTER_H_INCLUDED
#define _DIRECT_X_ADAPTER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2022 at 13:34:44.9689141, UTC+7, Novosibirsk, Thursday;
	This is Yandex Wanderer project graphic adapter wrapper interface declaration file;
	-----------------------------------------------------------------------------
	https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter  ;
	https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter1 ;
*/
#include "direct_x._iface.h"
#include "direct_x.output.h"

namespace ex_ui { namespace draw { namespace direct_x {
	// generic properties of an adapter of either direct_x 11 or 12;
	class CProps {
	public:
		 CProps (void);
		 CProps (const CProps&);
		 CProps (CProps&&) = delete;
		~CProps (void) = default;

	public:
		bool  Dx_12   (void) const;
		bool  Dx_12   (const bool);
		bool  Hi_Perf (void) const;
		bool  Hi_Perf (const bool);
		bool  Lo_Power(void) const;
		bool  Lo_Power(const bool);
#if defined(_DEBUG)
		CString  Print(const e_print = e_print::e_all) const;
#endif
	public:
		CProps&  operator = (const CProps&);
		CProps&  operator = (CProps&&) = delete;

	private:
		bool  m_hi_perf ;  // high performance;
		bool  m_lo_power;  // low power consumption;
		bool  m_12_vers ;  // support direct_x 12;
	};

}}}

#endif/*_DIRECT_X_ADAPTER_H_INCLUDED*/