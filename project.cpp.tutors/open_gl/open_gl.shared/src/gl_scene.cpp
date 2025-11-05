/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Oct-2025 at 23:56:35.016, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL generic scene wrapper interface implementation file;
*/
#include "gl_scene.h"
#include "program\gl_prog_linker.h"
#include "program\gl_prog_status.h"
#include "shader\gl_compiler.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;

using CDevice = context::CDevice;

CScene::CContext::CContext (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CScene::CContext::Clear (void) {
	this->m_error <<__METHOD__<<__s_ok;

	context::CBase*  ctx_bases[] = { &this->Draw(), &this->Device() };

	for (uint32_t i_ = 0; i_ < _countof(ctx_bases); i_++) {
		if (__failed(ctx_bases[i_]->Destroy()))
			this->m_error = ctx_bases[i_]->Error(); // keeps going to the next context; base class outputs error to the trace itself;
	}

	return this->Error();
}

const
CScene::CDevCtx& CScene::CContext::Device (void) const { return this->m_dev_ctx; }
CScene::CDevCtx& CScene::CContext::Device (void)       { return this->m_dev_ctx; }
const
CScene::CDrwCtx& CScene::CContext::Draw (void) const { return this->m_drw_ctx; }
CScene::CDrwCtx& CScene::CContext::Draw (void)       { return this->m_drw_ctx; }

TError& CScene::CContext::Error (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////

CScene:: CScene (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CScene::~CScene (void) {}

const
vertex::CArrObject&  CScene::Array (void) const { return this->m_array; }
vertex::CArrObject&  CScene::Array (void)       { return this->m_array; }
const
CScene::CContext& CScene::Ctx (void) const { return this->m_ctx; }
CScene::CContext& CScene::Ctx (void)       { return this->m_ctx; }

TError&  CScene::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Array().Is_bound()) {
		if (__failed(this->Array().Unbind()))
			return this->m_error = this->Array().Error();
		if (__failed(this->Array().Delete()))
			return this->m_error = this->Array().Error();
	}

	// it is not necessary to check a binding of the buffer, it makes itself, just unbind it;
	if (this->Prog().Buffer().Is_bound()) {
		if (__failed(this->Prog().Buffer().Unbind()))
			return this->m_error = this->Prog().Buffer().Error();

		if (__failed(this->Prog().Buffer().Destroy()))
			return this->m_error = this->Prog().Buffer().Error();
	}
#if (0) // shaders must be deleted right after linking the program;
	if (__failed(this->Prog().Shaders().Detach()))
		return this->m_error = this->Prog().Shaders().Error();

	if (__failed(this->Prog().Shaders().Delete()))
		return this->m_error = this->Prog().Shaders().Error();
#endif
	if (__failed(this->Prog().Delete()))
		return this->m_error = this->Prog().Error();

	return this->Error();
}

TError&  CScene::Error (void) const { return this->m_error; }

err_code CScene::Prepare (void) {
	this->m_error <<__METHOD__<<__s_ok;

	shader::CCompiler cmpl;
	if (false == cmpl.Is_supported()) {
		 __trace_err_2(_T("%s\n"), (_pc_sz) cmpl.Error().Print(TError::e_print::e_req));
		return this->m_error = cmpl.Error();
	}
	else
		__trace_warn_2(_T("%s\n"), _T("Shader compiler is supported;"));

	if (__failed(this->Array().Create()))
		return this->m_error = this->Array().Error();
	if (__failed(this->Array().Bind()))
		return this->m_error = this->Array().Error();

	if (__failed(this->Prog().Create()))
		return this->m_error = this->Prog().Error();
	// activates or binds vertex array attributes;
	this->Array().Attrs() << this->Prog().Id();

	if (__failed(this->Prog().Shaders().Create()))
	    return this->m_error = this->Prog().Shaders().Error();

	if (__failed(this->Prog().Shaders().Load()))
		return this->m_error = this->Prog().Shaders().Error();

	if (__failed(this->Prog().Shaders().Compile()))
		return this->m_error = this->Prog().Shaders().Error();

	if (__failed(this->Prog().Shaders().Attach()))
		return this->m_error = this->Prog().Shaders().Error();

	static _pc_sz attr_names[] = {_T("colorIn"), _T("positionIn")};

	// these attributes' names must be coincident with vertex shader source code, possibly a parsing of the code should give an ability to get them;
	if (__failed(this->Array().Attrs().Clr().Name(attr_names[0]))) /*return*/ this->m_error = this->Array().Attrs().Clr().Error();
	if (__failed(this->Array().Attrs().Pos().Name(attr_names[1]))) /*return*/ this->m_error = this->Array().Attrs().Pos().Error();
	// the error may be set by procedure of assigning the name to attribute, just output the error to trace log;
	if (this->Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	/*important:
	  the attributes' indices are set through source code of vertex shader, the same is for vertex color, it can be set in fragment shader;
	  but these indices can be applied after program linking only; they can be received by querying the program object;
	  for this tutorial another way of vertex attribute location is selected:
	  the indices are set before linking the program, it is assumed the indices are the same as in shaders' source code;
	  after linking the program the indices are checked for test purpose that they are sill have the same values;
	*/

	// sets attributes' indecise (aka location) before linking the program,
	// an index of the particular attribute must be the same as in actual vertex: 0 - position; 1 - color;
	// also, it is very important: the shader source code can change the location of the attributes and after the program linking those locations will be applied;
	if (__failed(this->Array().Attrs().Clr().Index().Set(1))) /*return*/ this->m_error = this->Array().Attrs().Clr().Error();
	if (__failed(this->Array().Attrs().Pos().Index().Set(0))) /*return*/ this->m_error = this->Array().Attrs().Pos().Error();
	// the same as above, the error may be set by procedure of setting the index to attribute, just output the error to trace log;
	if (this->Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}

	if (__failed(this->Prog().Link()))
		return this->m_error = this->Prog().Error();

	// https://stackoverflow.com/questions/9113154/proper-way-to-delete-glsl-shader ;
	if (false) {}
	else if (__failed(this->Prog().Shaders().Detach())) this->m_error = this->Prog().Shaders().Error(); // the error is output to trace by the shaders' cache;
	else if (__failed(this->Prog().Shaders().Delete())) this->m_error = this->Prog().Shaders().Error(); // the error is output to trace by the shaders' cache;

	// checks vertex attributes' indices after linking the program and deleting the shaders;
	// the indices must be the same as them were set before the linking;

	const int32_t n_clr_ndx = this->Array().Attrs().Clr().Index().Get();
	const int32_t n_pos_ndx = this->Array().Attrs().Pos().Index().Get();

	if (this->Array().Attrs().Clr().Index().Error()) this->m_error = this->Array().Attrs().Clr().Index().Error(); else {__trace_info_2(_T("The attr '%s' has the index = %d;\n"), attr_names[0], n_clr_ndx); }
	if (this->Array().Attrs().Pos().Index().Error()) this->m_error = this->Array().Attrs().Pos().Index().Error(); else {__trace_info_2(_T("The attr '%s' has the index = %d;\n"), attr_names[1], n_pos_ndx); }
	// the error may be set by any attribute and the error of the first attribute may be overritten by the error of the last attriboute,
	// but it is not important for this time yet;
	if (this->Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
#if (0) // the arreay is already bound by above;
	// before enabling the attributes the vertex array must be activated, i.e. to be bound;
	if (__failed(this->Array().Bind())) {
		return this->m_error = this->Array().Error(); // The array is still inactive, so its attributes will not be enabled successfully;
	}
#endif
	if (__failed(this->Array().Enable(true)))
		this->m_error = this->Array().Error(); // in case of error to make attributes be enabled it is very possible the setting data to buffer will fail;

	if (__failed(this->Prog().Buffer().Create()))
		return this->m_error = this->Prog().Buffer().Error();

	using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;
#if (0)
	if (__failed(this->Prog().Buffer().BindTo(e_bind_targets::e_array)))
		return this->m_error = this->Prog().Buffer().Error();
#else
	if (__failed(this->Prog().Buffer().Bind()))
		return this->m_error = this->Prog().Buffer().Error();
#endif
	if (__succeeded(this->Prog().Validate())) {
		__trace_info_2(_T("The draw scene is prepared;\n"));
	}

	return this->Error();
}

const
CProgram& CScene::Prog (void) const { return this->m_prog; }
CProgram& CScene::Prog (void)       { return this->m_prog; }