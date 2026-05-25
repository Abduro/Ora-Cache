/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jan-2026 at 22:02:46.843, UTC+4, Batumi, Friday;
	This is OpenGL tutorials' program wrapper unit test interface implementation file.
*/
#include "test_adap_$d$.prog.h"

using namespace test::open_gl::prog;

#pragma region cls::c_prog{}

void c_prog::Grid (void) {

	CTstGraph graph;
	if (__failed(graph.Create())) { _out()(); return; }

	CProg prog(e_object::e_grid); prog.Opts() << CProg::COpts::e_opts::e_link << CProg::COpts::e_opts::e_use_$;

	prog.Create();
	prog.Delete();

	graph.Delete();

	_out()();
}

void c_prog::Tria (void) {

	CTstGraph graph;
	if (__failed(graph.Create())) { _out()(); return; }

	CProg prog(e_object::e_tria); prog.Opts() << CProg::COpts::e_opts::e_link << CProg::COpts::e_opts::e_use_$;

	prog.Create();
	prog.Delete();

	graph.Delete();

	_out()();
}
#pragma endregion