/* Copyright (C) 2015 Dr. Michael Robb

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General License
   as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   The program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Public License for more details.

   You should have received a copy of the GNU Public License 
   along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include "fractals.h"

// --------------------------------------------------------------------------
// Helper function to compile shader units
// --------------------------------------------------------------------------

#define BUFFER_SIZE 4096

GLuint CShaderUtils::compile_shaderunit(GLuint type, const char **src, const std::string &strname)
{
GLint compiled = GL_FALSE;

GLuint shaderidx = glCreateShader(type);
ASSERT(glGetError() == GL_NO_ERROR);
ASSERT(shaderidx > 0);

glShaderSource(shaderidx, 1, src, NULL);
ASSERT(glGetError() == GL_NO_ERROR);

glCompileShader(shaderidx);
ASSERT(glGetError() == GL_NO_ERROR);

glGetShaderiv(shaderidx, GL_COMPILE_STATUS, &compiled);
ASSERT(glGetError() == GL_NO_ERROR);

if (GL_FALSE == compiled)
        {
        char *buffer = new char [BUFFER_SIZE];

        if (NULL == buffer)
        {
        std::cout << "Unable to allocate text buffer for shader info log" << std::endl;

        return -1;
        }

        glGetShaderInfoLog(shaderidx, BUFFER_SIZE-1, NULL, buffer);
        std::cout << "test_create_program: Unable to compile " << strname << " shader -reason: " << std::endl << buffer << std::endl;
        std::cout << "|" << *src << "|" << std::endl;
        delete [] buffer;
        return -1;
        }

return shaderidx;
}

// ==========================================================================
// COMPUTE SHADER
// ==========================================================================

void CWindowCompute::setparameters_computeshader(GLuint progid, CFractalParameters &parameters)
{
assert(progid != 0);

glUniform1f(glGetUniformLocation(progid, "fescaperadius"), parameters.m_escaperadius);
ASSERTGL();
glUniform1f(glGetUniformLocation(progid, "fescaperadiusp2"), parameters.m_escaperadius*parameters.m_escaperadius);
ASSERTGL();

glUniform1f(glGetUniformLocation(progid, "fracxcen"), parameters.m_xcen);
ASSERTGL();
glUniform1f(glGetUniformLocation(progid, "fracycen"), parameters.m_ycen);
ASSERTGL();

glUniform1f(glGetUniformLocation(progid, "fracxwidth"), parameters.m_xwidth);
ASSERTGL();
glUniform1f(glGetUniformLocation(progid, "fracywidth"),  parameters.m_ywidth);
ASSERTGL();
glUniform1i(glGetUniformLocation(progid, "maxiter"),  parameters.m_maxiter);
ASSERTGL();
glUniform1f(glGetUniformLocation(progid, "fangle"),  parameters.m_angle);
ASSERTGL();
glUniform1f(glGetUniformLocation(progid, "fpower"),  parameters.m_power);
ASSERTGL();
glUniform1f(glGetUniformLocation(progid, "fbanding"),  parameters.m_banding);
ASSERTGL();
glUniform1f(glGetUniformLocation(progid, "fminclamp"),  parameters.m_minclamp);
ASSERTGL();

glUniform1i(glGetUniformLocation(progid, "modesmooth"), parameters.m_modesmooth);
ASSERTGL();

glUniform1i(glGetUniformLocation(progid, "modepower"), parameters.m_modepower);
ASSERTGL();

glUniform1i(glGetUniformLocation(progid, "cycleoffset"), parameters.m_cycleoffset);
ASSERTGL();

glUniform1i(glGetUniformLocation(progid, "modeinvert"), parameters.m_modeinvert);
ASSERTGL();
}

void CWindowCompute::compute_gpu(void)
{
// Function parameters are as follows:
//
// unit - texture unit
// texture - name of the texture to bind to the image unit
// level   - texture level
// layered - whether a layered texture binding is to be used
// layer   - Which layer, otherwise ignored
// access  - type of access
// format  - format for imagestore function calls

// ----- Set up the source texture - unit 0 --------------------------------

GLuint idx = m_parameters.m_texpalette;

if (idx >= m_textable.size() )
	{
	idx = m_textable[0];
	}

glBindImageTexture(1, m_textable[idx], 0, GL_FALSE, 0, GL_READ_ONLY, TEX_INTERNALFORMAT);
ASSERTGL();

// ----- Set up the destination texture - unit 1 ---------------------------
glBindImageTexture(0, m_texdst, 0, GL_FALSE, 0, GL_WRITE_ONLY, TEX_INTERNALFORMAT);
ASSERTGL();

glUseProgram(m_computeshader);
ASSERTGL();

setparameters_computeshader(m_computeshader, m_parameters);

glDispatchCompute(m_parameters.m_texwidth/16, m_parameters.m_texheight/16, 1); // width x height threads in blocks of 16^2
ASSERTGL();
}

// --------------------------------------------------------------------------
// In order to write to a texture, we have to introduce it as image2D.
// local_size_x/y/z layout variables define the work group size.
// gl_GlobalInvocationID is a uvec3 variable giving the global ID of the thread,
// gl_LocalInvocationID is the local index within the work group, and
// gl_WorkGroupID is the work group's index
// --------------------------------------------------------------------------

const char *str_fractcompute[] =
{
"#version 430\n"
"layout ("
TEX_COMPUTEFORMAT
") uniform writeonly image2D dstTex;\n"
"layout ("
TEX_COMPUTEFORMAT
") uniform readonly image1D transferTex;\n"
"\n"
"layout (local_size_x = 16, local_size_y = 16) in;\n"
"\n"

"#define MANDELBROT_PN 1\n"
"#define MANDELBROT_P2 2\n"
"#define MANDELBROT_P3 4\n"

"uniform float fescaperadius;\n"
"uniform float fescaperadiusp2;\n"
"uniform float fracxcen;\n"
"uniform float fracycen;\n"
"uniform float fracxwidth;\n"
"uniform float fracywidth;\n"
"uniform float fangle;\n"
"uniform float fpower;\n"
"uniform float fbanding;\n"
"uniform float fminclamp;\n"
"uniform int   maxiter;\n"
"uniform bool  modesmooth;\n"
"uniform int   modepower;\n"
"uniform int   cycleoffset;\n"
"uniform bool  modeinvert;\n"
"\n"
"vec4 transfercolor(float fval)\n"
"{\n"
"if (modeinvert)\n"
"	{\n"
"	fval = 1.0 -fval;\n"
"	}\n"
"\n"
"int xsize = imageSize(transferTex).x;\n"
"float fpos = (xsize-2) * fval;\n"
"int ibase = int(fpos);\n"
"float frac = fract(fpos);\n"
"\n"
"ibase = (ibase + cycleoffset) % (xsize-2);\n"
"vec4 v1 = imageLoad(transferTex, ibase+1);\n"
"vec4 v2 = imageLoad(transferTex, ibase+2);\n"
"return mix(v1,v2,frac);\n"
"}\n"

"struct SComplex \n"
"{\n"
"float real;\n"
"float imag;\n"
"};\n"
"\n"

"struct SPolar\n"
"{\n"
"float radius;\n"
"float angle;\n"
"};\n"
"\n"

"SPolar topolar( in SComplex value )\n"
"{\n"
"SPolar polar;\n"
"float fr = value.real;\n"
"float fi = value.imag;\n"
"polar.radius = sqrt( fr * fr + fi * fi );\n"
"\n"
"if (abs(polar.radius) > 0.005)\n"
"\t{\n"
"\tfr /= polar.radius;\n"
"\tfi /= polar.radius;\n"
"\t}\n"
"polar.angle = atan( fi, fr);\n"
"\n"
"return polar;\n"
"}\n"

"SComplex frompolar( in SPolar polar )\n"
"{\n"
"return SComplex( cos( polar.angle ) * polar.radius,\n"
"	          sin( polar.angle ) * polar.radius );\n"
"}\n"
"\n"

"SComplex power( in SComplex value, in float fpower)\n"
"{\n"
"SPolar polar = topolar( value );\n"
"return frompolar( SPolar( pow(polar.radius, fpower), fpower * polar.angle ) );\n"
"}\n"
"\n"

"float magnitude(in SComplex val)\n"
"{\n"
"return val.real * val.real + val.imag * val.imag;\n"
"}\n"

"\n"
"void mandelbrot_p2(in SComplex cval, inout SComplex pos, out float r2)\n"
"{\n"
"float tr = pos.real; // Take temporary copies here so that\n"
"float ti = pos.imag; // original values are not overwritten\n"
"float tr2 = tr * tr; // while we still need them.\n"
"float ti2 = ti * ti;\n"
"pos.real = tr2 - ti2 + cval.real;\n"
"pos.imag = 2.0 * tr * ti + cval.imag;\n"
"r2 = magnitude(pos);\n"
"}\n"

"void mandelbrot_p3(in SComplex cval, inout SComplex pos, out float r2)\n"
"{\n"
"float tr = pos.real; // Take temporary copies here so that\n"
"float ti = pos.imag; // original values are not overwritten\n"
"float tr2 = tr * tr; // while we still need them.\n"
"float ti2 = ti * ti;\n"
"float tr3 = tr2 * tr;\n"
"float ti3 = ti2 * ti;\n"
"\n"
"pos.real = tr3 - 3.0 * tr * ti2 + cval.real;\n"
"pos.imag = 3.0 * tr2 * ti - ti3 + cval.imag;\n"
"r2 = magnitude(pos);\n"
"}\n"

"// Notes: This implementation makes use of De Moivre's theoerem\n"
"//\n"
"// [r (cos theta + i sin theta)]^n = r^n ( cos n theta + i sin n theta)\n"
"// (Creal,Cimag) = constant term\n"
"// (real,imag) = current coordinate\n"
"// r2 = magnitude of new coordinate\n"
"void mandelbrot_power(in SComplex cval, inout SComplex pos, out float r2, float fpower)\n"
"{\n"
"SComplex result = power(pos, fpower);\n"
"pos.real = result.real + cval.real;\n"
"pos.imag = result.imag + cval.imag;\n"
"r2 = magnitude(pos);\n"
"}\n"
"\n"

"// param are parametric coordinates in X and Y (basic texture coordinates)\n"
"// Creal and Cimag are the resulting complex coordinates for this texel\n"
"void transform(in vec2 param, out float Creal, out float Cimag)\n"
"{\n"
"float crot = cos(fangle);\n"
"float srot = sin(fangle);\n"
"vec2 vhalf = vec2(0.5, 0.5 );\n"
"mat2 mrot = mat2( crot, srot, -srot, crot );\n"
"param = mrot *((param - vhalf) * vec2(fracxwidth, fracywidth));\n"
"Creal = fracxcen + param.x;\n"
"Cimag = fracycen + param.y;\n"
"}\n"
"\n"

"vec4 mandelbrot(vec2 param)\n"
"{\n"
"float Creal, Cimag;\n"
"transform(param, Creal, Cimag);\n"
"float logpow;\n"
"int iter;\n"
"float r2 = 0.0;\n"
"SComplex cval = SComplex(Creal, Cimag);\n"
"SComplex pos = SComplex(Creal, Cimag);\n"
"\n"
"if (modepower == MANDELBROT_PN)\n"
"	{\n"
"	for (iter = 0; (iter < maxiter) && (r2 < fescaperadius); ++iter)\n"
"      		{\n"
"		mandelbrot_power( cval, pos, r2, fpower );\n"
"      		}\n"
"\n"
"	mandelbrot_power( cval, pos, r2, fpower );\n"
"	mandelbrot_power( cval, pos, r2, fpower );\n"
"	logpow = fpower;\n"
"	}\n"
"else if (modepower == MANDELBROT_P2)\n"
"	{\n"
"	for (iter = 0; (iter < maxiter) && (r2 < fescaperadius); ++iter)\n"
"      		{\n"
"		mandelbrot_p2( cval, pos, r2 );\n"
"      		}\n"
"\n"
"	mandelbrot_p2( cval, pos, r2 );\n"
"	mandelbrot_p2( cval, pos, r2 );\n"
"	logpow = 2.0;\n"
"	}\n"
"else if (modepower == MANDELBROT_P3)\n"
"	{\n"
"	for (iter = 0; (iter < maxiter) && (r2 < fescaperadius); ++iter)\n"
"       	{\n"
"		mandelbrot_p3( cval, pos, r2 );\n"
"       	}\n"
"\n"
"	mandelbrot_p3( cval, pos, r2 );\n"
"	mandelbrot_p3( cval, pos, r2 );\n"
"	logpow = 3.0;\n"
"	}\n"
"\n"
"vec4 colfinal;\n"
"\n"
"// ----- Apply the transfer texture -----\n"
"\n"
"if (r2 < fescaperadius)\n"
"	{\n"
"	colfinal = imageLoad( transferTex, 0);\n"
"	}\n"
"else\n"
"	{\n"
"	float mu;\n"
"	if(modesmooth)\n"
"		{\n"
"		mu = (iter - (log (log(sqrt(r2)))) / log(logpow) )/fescaperadiusp2;\n"
"		mu = max(fminclamp, mu); // keep outer perimeter dark\n"
"		}\n"
"	else\n"
"		{\n"
"		mu = (float(iter) / float(maxiter)) * fbanding;\n"
"		}\n"
"\n"
"	colfinal = transfercolor( fract(mu) );\n"
"	}\n"
"\n"
"return colfinal;\n"
"}\n"

"void main()\n"
"{\n"
"vec2 vpos = vec2(gl_GlobalInvocationID.xy);\n"
"ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);\n"
"vec2 vscale = imageSize(dstTex);\n"
"vec2 param = vpos/vscale;\n"
"vec4 finalcol = mandelbrot(param);\n"
"imageStore(dstTex, storePos, finalcol);\n"
"}\n"
};

GLuint CWindowCompute::init_computeshader(void)
{
static std::string str_compute = "compute";

// Creating the compute shader, and the program object containing the shader
GLuint cs = compile_shaderunit(GL_COMPUTE_SHADER, str_fractcompute, str_compute);
ASSERTGL();
assert(cs > 0);

GLuint progid = glCreateProgram();
ASSERTGL();
assert(progid > 0);

glAttachShader(progid, cs);
ASSERTGL();

glLinkProgram(progid);
ASSERTGL();

GLint rvalue;
glGetProgramiv(progid, GL_LINK_STATUS, &rvalue);
ASSERTGL();

if (!rvalue) 
	{
        cerr << "Error in linking compute shader program" << endl;
        GLchar log[10240];
        GLsizei length;
        glGetProgramInfoLog(progid, 10239, &length, log);
      	cerr << "Linker log:\n" << log << "\n";
        exit(41);
    	}  	 

glUseProgram(progid);
ASSERTGL();

// Set up the assigned texture units
glUniform1i(glGetUniformLocation(progid, "dstTex"), 0);	// Texture unit 0
ASSERTGL();

glUniform1i(glGetUniformLocation(progid, "transferTex"), 1);	// Texture unit 1
ASSERTGL();

setparameters_computeshader(progid, m_parameters);

return progid;
}
