#ifndef _EBO_TEST_$D$_RENDER_H_INCLUDED
#define _EBO_TEST_$D$_RENDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2025 at 04:40:50.58, UTC+4, Batumi, Wednesday;
	This is Ebo Pack 2D/3D draw renderer lib unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "_log.h"

#include "sys.error.h"
#include "direct_x._iface.h"
#include "direct_x.adapter.h"
#include "direct_x.device.h"
#include "direct_x.factory.h"
#include "direct_x.queue.h"

#include "direct_x.swap.h"
#include "direct_x.swap.1.h"
#include "direct_x.swap.2.h"

#include "render.base.h"

namespace ebo { namespace boo { namespace test {

	using CWindow = ::ATL::CWindow;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

	class CFake_Wnd : public ::ATL::CWindowImpl<CFake_Wnd> { typedef ::ATL::CWindowImpl<CFake_Wnd> TBase;
	public:
		CFake_Wnd (void) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;
			TBase::Create(HWND_MESSAGE);

			if (false == TBase::IsWindow())
				this->m_error.Last();
			else
				this->m_error << __s_ok;
			if (this->Error())
				_out() += this->Error().Print(TError::e_print::e_req);
			_out()();
		}
		~CFake_Wnd (void) {
			_out() += TLog_Acc::e_new_line;
			_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
			if (TBase::IsWindow())
			    TBase::DestroyWindow();
			_out()();
		}
	public:
		TError&  Error (void) const { return this->m_error; }
		DECLARE_EMPTY_MSG_MAP();

	private:
		CFake_Wnd (const CFake_Wnd&) = delete;
		CFake_Wnd (CFake_Wnd&&) = delete;
		CFake_Wnd& operator = (const CFake_Wnd&) = delete;
		CFake_Wnd& operator = (CFake_Wnd&&) = delete;

	private:
		CError  m_error;
	};

}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;
#pragma comment(lib, "render_v15.lib")       // this one must be tested by this unit test project;

#endif/*_EBO_TEST_$D$_RENDER_H_INCLUDED*/