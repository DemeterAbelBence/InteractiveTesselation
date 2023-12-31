///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Mathematics (glm.g-truc.net)
///
/// Copyright (c) 2005 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// Restrictions:
///		By making use of the Software for military purposes, you choose to make
///		a Bunny unhappy.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file glm/mat4x4.hpp
/// @date 2013-12-24 / 2013-12-24
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "detail/type_mat4x4.hpp"

namespace glm
{
	/// 4 columns of 4 components matrix of low precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef tmat4x4<float, lowp>		lowp_mat4;
	
	/// 4 columns of 4 components matrix of medium precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef tmat4x4<float, mediump>		mediump_mat4;
	
	/// 4 columns of 4 components matrix of high precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef tmat4x4<float, highp>		highp_mat4;
	
	/// 4 columns of 4 components matrix of low precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef tmat4x4<float, lowp>		lowp_mat4x4;
	
	/// 4 columns of 4 components matrix of medium precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef tmat4x4<float, mediump>		mediump_mat4x4;
	
	/// 4 columns of 4 components matrix of high precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef tmat4x4<float, highp>		highp_mat4x4;

	inline mat4 translate(vec3 t) {
		return mat4(vec4(1, 0, 0, t.x),
			vec4(0, 1, 0, t.y),
			vec4(0, 0, 1, t.z),
			vec4(0, 0, 0, 1));
	}

	inline mat4 scale(vec3 s) {
		return mat4(vec4(s.x, 0, 0, 0),
			vec4(0, s.y, 0, 0),
			vec4(0, 0, s.z, 0),
			vec4(0, 0, 0, 1));
	}

	inline mat4 rotation(float angle, vec3 w) {
		float c = cosf(angle), s = sinf(angle);
		return mat4(
			vec4(c * (1 - w.x * w.x) + w.x * w.x, w.x * w.y * (1 - c) - w.z * s, w.x * w.z * (1 - c) + w.y * s, 0),
			vec4(w.x * w.y * (1 - c) + w.z * s, c * (1 - w.y * w.y) + w.y * w.y, w.y * w.z * (1 - c) - w.x * s, 0),
			vec4(w.x * w.z * (1 - c) - w.y * s, w.y * w.z * (1 - c) + w.x * s, c * (1 - w.z * w.z) + w.z * w.z, 0),
			vec4(0, 0, 0, 1)
		);
	}

}//namespace glm
