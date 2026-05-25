/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jan-2026 at 01:26:39.207, UTC+4, Batumi, Wednesday;
	This is OpenGL draw context of regular device and of renderer wrapper uint test adapter interface implementation file;
*/
#include "test_adap_$d$.ctx.h"
#include <crtdbg.h>

using namespace test::open_gl::context;

#pragma region cls::c_ctx{}

c_ctx:: c_ctx (void) {}
c_ctx::~c_ctx (void) {
//	__debugbreak(); it very looks like running *each* test case method creates its own *new* copy of this class;
//	_out()();       thus other event handlers' macros should be used those are executed *before* and *after* running the test case;
}

void c_ctx::Device (void) {

	CTstDevice dev_ctx;

	dev_ctx.Create();
	dev_ctx.Delete();

	_out()();
}

void c_ctx::Graphics (void) {
	
	ver_1_1::CTstGraph graph;

	graph.Create();
	graph.Delete();

	_out()();
}

void c_ctx::OnClean (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

void c_ctx::OnInit (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

#pragma endregion
#pragma region cls::c_px_format{}

void c_px_format::Find_ndx (void) {
	CTstFormat().Find({32, 24, 8});
	_out()();
}

#pragma endregion