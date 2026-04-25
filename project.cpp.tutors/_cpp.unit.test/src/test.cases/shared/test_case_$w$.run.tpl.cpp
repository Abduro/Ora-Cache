/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Apr-2026 at 10:37:32.520, UTC+4, Batumi, Friday;
	This is Ebo Pack system thread pool wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.run.tpl.h"

using namespace test::win_api;
using namespace test::win_api::threads;

#pragma region cls::CTstTplExt{}

CTstTplExt:: CTstTplExt (void) {}
CTstTplExt::~CTstTplExt (void) {}

CTstTplExt::operator const CTplRunner& (void) const { return (CTplRunner&)*this; }
CTstTplExt::operator       CTplRunner& (void)       { return (CTplRunner&)*this; }

void CTstTplExt::Run_Func (void) {
	_out() += TString().Format(_T("[impt] cls::[%s].%s(): entered;"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const dword u_slice = 100;     // this is the counter/slice of time to increment the elapsed time;
	const dword u_frame = 2000;    // this is time frame to wait for; (msec);

	uint32_t cnt_ = 0; cnt_; // this is the counter of the iterations for log messages;

	CDelay delay_evt(u_slice, u_frame);

	while (/*false == (*p_runner)().Is_stopped() &&*/ true == ((TBase&)(*this))().Is_running()) {
		delay_evt.Wait();          // waits for a particular time slice; (u_slice)
		_out() += TString().Format(_T("cls::[%s].%s(): iter_ = #%u;"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, ++cnt_);

		if (delay_evt.Elapsed()) { // the time frame being waited for is reached; (u_frame)
			delay_evt.Reset();
			break;
		}
	}
	((TBase&)(*this))().Event() << true; // *required*: to set the event to signal state, i.e. the job is done;
}

#pragma endregion
#pragma region cls::CTstTplRunner{}

CTstTplRunner:: CTstTplRunner (void) {}
CTstTplRunner::~CTstTplRunner (void) {
	if ((*this)()().Is_running()) {
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		this->Stop(/*_cls_output*/false);
		_out()();
	}
}

err_code CTstTplRunner::Start (bool _cls_output/* = true*/) {
	_cls_output;
	if (_cls_output)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Start())) { _out() += (*this)().Error(); return (*this)().Error(); }
	else _out() += _T("[impt] result: thread pool work item has started;");

	return (*this)().Error();
}

err_code CTstTplRunner::Stop (bool _cls_output/* = true*/) {
	_cls_output;
	if (_cls_output)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Stop())) { _out() += (*this)().Error(); return (*this)().Error(); }
	else _out() += _T("[impt] result: thread pool work item has stopped;");

	return (*this)().Error();
}
const
CTplRunner& CTstTplRunner::operator ()(void) const { return this->m_run_ext; }
CTplRunner& CTstTplRunner::operator ()(void)       { return this->m_run_ext; }

#pragma endregion