/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Oct-2025 at 23:43:04.685, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' draw renderer interface implementation file;
*/
#include "gl_renderer.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;

CRenderer:: CRenderer (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CRenderer::~CRenderer (void) {}

TError&     CRenderer::Error (void) const { return this->m_error; }
const
CScene&     CRenderer::Scene (void) const { return this->m_scene; }
CScene&     CRenderer::Scene (void)       { return this->m_scene; }