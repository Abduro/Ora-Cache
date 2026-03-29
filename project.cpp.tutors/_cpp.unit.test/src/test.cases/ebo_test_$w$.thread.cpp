/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:58:43.965, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool unit test adapter interface implementation file; 
*/
#include "ebo_test_$w$.thread.h"

using namespace ebo::boo::test::thread;

#pragma region cls::c_event{}

void c_event::Create (void) { CTstEvent().Create(); _out()(); }

void c_event::Destroy (void) {

	CTstEvent event;

	event.Create();
	event.Destroy(); _out()();
}

#pragma endregion