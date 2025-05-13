#ifndef _EBO_TEST_$D$_ZBUF_SHADE_H_INCLUDED
#define _EBO_TEST_$D$_ZBUF_SHADE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-May-2025 at 08:57:25.708, UTC+4, Batumi, Monday;
	This is Ebo Pack WinAPI GDI in-memory draw shade renderer lib unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "ebo_test_$d$.zbuf.h"

namespace ebo { namespace boo { namespace test { namespace draw {

#pragma region __shade

	using TRectMesh = ex_ui::draw::shade::CRectMesh;

	__class(CRectMesh) {
	public:
		 CRectMesh (const bool _b_verb = false);
		~CRectMesh (void) = default;

	public:
		__method (_ctor);
		__method (Set);

	private:
		bool m_b_verb;
		TRectMesh  m_mesh;
	};

	using TTriMesh = ex_ui::draw::shade::CTriMesh;
	using TCorners = ex_ui::draw::shade::CTriMesh::e_corner;

	__class(CTriMesh) {
	public:
		 CTriMesh (const bool _b_verb = false);
		~CTriMesh (void) = default;

	public:
		__method (_ctor);
		__method (Set);

	private:
		bool m_b_verb;
		TTriMesh  m_mesh;
	};

	using TShader = ex_ui::draw::shade::CShader;

	__class(CShader) {
	public:
		 CShader (const bool _b_verb = false);
		~CShader (void) = default;

	public:
		__method (_ctor);

	private:
		bool m_b_verb;
		TShader  m_shader;
	};

	using TRectShader = ex_ui::draw::shade::CRectShader;

	__class(CRectShader) {
	public:
		 CRectShader (const bool _b_verb = false);
		~CRectShader (void) = default;

	public:
		__method (Set);
		__method (Validate);

	private:
		bool m_b_verb;
		TRectShader  m_shader;
	};

	using TTriShader = ex_ui::draw::shade::CTriShader;

	__class(CTriShader) {
	public:
		 CTriShader (const bool _b_verb = false);
		~CTriShader (void) = default;

	public:
		__method (Set);
		__method (Validate);

	private:
		bool m_b_verb;
		TTriShader  m_shader;
	};

	using TVertex = ex_ui::draw::shade::CVertex;

	__class(CVertex) {
	public:
		 CVertex (const bool _b_verb = false);
		~CVertex (void) = default;

	public:
		__method (_ctor);

	private:
		bool m_b_verb;
		TVertex  m_vertex;
	};
#pragma endregion

}}}}

#endif/*_EBO_TEST_$D$_ZBUF_SHADE_H_INCLUDED*/