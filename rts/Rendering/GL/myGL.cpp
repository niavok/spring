/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#include "StdAfx.h"
#include <string>
#include <SDL.h>

#if defined(WIN32) && !defined(HEADLESS) && !defined(_MSC_VER)
// for APIENTRY
#include <windef.h>
#endif

#include "mmgr.h"
#include "myGL.h"
#include "VertexArray.h"
#include "VertexArrayRange.h"
#include "Rendering/GlobalRendering.h"
#include "System/LogOutput.h"
#include "System/Exceptions.h"
#include "System/TimeProfiler.h"
#include "System/FileSystem/FileHandler.h"



static CVertexArray* vertexArray1 = NULL;
static CVertexArray* vertexArray2 = NULL;

#ifdef USE_GML
static CVertexArray vertexArrays1[GML_MAX_NUM_THREADS];
static CVertexArray vertexArrays2[GML_MAX_NUM_THREADS];
static CVertexArray* currentVertexArrays[GML_MAX_NUM_THREADS];
#else
static CVertexArray* currentVertexArray = NULL;
#endif
//BOOL gmlVertexArrayEnable=0;
/******************************************************************************/
/******************************************************************************/

CVertexArray* GetVertexArray()
{
#ifdef USE_GML // each thread gets its own array to avoid conflicts
	int thread=gmlThreadNumber;
	if(currentVertexArrays[thread]==&vertexArrays1[thread]){
		currentVertexArrays[thread]=&vertexArrays2[thread];
	} else {
		currentVertexArrays[thread]=&vertexArrays1[thread];
	}
	return currentVertexArrays[thread];
#else
	if(currentVertexArray==vertexArray1){
		currentVertexArray=vertexArray2;
	} else {
		currentVertexArray=vertexArray1;
	}
	return currentVertexArray;
#endif
}


/******************************************************************************/

void PrintAvailableResolutions()
{
	// Get available fullscreen/hardware modes
	SDL_Rect **modes=SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
	if (modes == (SDL_Rect **)0) {
		logOutput.Print("Supported Video modes: No modes available!\n");
	}else if (modes == (SDL_Rect **)-1) {
		logOutput.Print("Supported Video modes: All modes available.\n");
	}else{
		char buffer[1024];
		unsigned char n = 0;
		for(int i=0;modes[i];++i) {
			n += SNPRINTF(&buffer[n], 1024-n, "%dx%d, ", modes[i]->w, modes[i]->h);
		}
		// remove last comma
		if (n>=2) {
			buffer[n-2] = '\0';
		}
		logOutput.Print("Supported Video modes: %s\n",buffer);
	}
}

#ifdef GL_ARB_debug_output
#if defined(WIN32) && !defined(HEADLESS)
	#define _APIENTRY APIENTRY
#else
	#define _APIENTRY
#endif
void _APIENTRY OpenGLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
	std::string sourceStr;
	std::string typeStr;
	std::string severityStr;
	std::string messageStr(message, length);

	switch (source) {
		case GL_DEBUG_SOURCE_API_ARB:
			sourceStr = "API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
			sourceStr = "WindowSystem";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
			sourceStr = "Shader";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
			sourceStr = "3rd Party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION_ARB:
			sourceStr = "Application";
			break;
		case GL_DEBUG_SOURCE_OTHER_ARB:
			sourceStr = "other";
			break;
		default:
			sourceStr = "unknown";
	}

	switch (type) {
		case GL_DEBUG_TYPE_ERROR_ARB:
			typeStr = "error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
			typeStr = "deprecated";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
			typeStr = "undefined";
			break;
		case GL_DEBUG_TYPE_PORTABILITY_ARB:
			typeStr = "portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE_ARB:
			typeStr = "peformance";
			break;
		case GL_DEBUG_TYPE_OTHER_ARB:
			typeStr = "other";
			break;
		default:
			typeStr = "unknown";
	}

	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH_ARB:
			severityStr = "high";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM_ARB:
			severityStr = "medium";
			break;
		case GL_DEBUG_SEVERITY_LOW_ARB:
			severityStr = "low";
			break;
		default:
			severityStr = "unknown";
	}

	logOutput.Print("OpenGL Error: source<%s> type<%s> id<%u> severity<%s>:\n%s", sourceStr.c_str(), typeStr.c_str(), id, severityStr.c_str(), messageStr.c_str());
}
#endif // GL_ARB_debug_output

void LoadExtensions()
{
	glewInit();

	const char* glVersion = (const char*) glGetString(GL_VERSION);
	const char* glVendor = (const char*) glGetString(GL_VENDOR);
	const char* glRenderer = (const char*) glGetString(GL_RENDERER);
	const char* glslVersion = (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION);
	const char* glewVersion = (const char*) glewGetString(GLEW_VERSION);
	const char* glExtensions = (const char*) glGetString(GL_EXTENSIONS);

	// log some useful version info
	logOutput.Print("SDL:  %d.%d.%d\n",
		SDL_Linked_Version()->major,
		SDL_Linked_Version()->minor,
		SDL_Linked_Version()->patch);
	logOutput.Print("GL version:   %s\n", glVersion);
	logOutput.Print("GL vendor:    %s\n", glVendor);
	logOutput.Print("GL renderer:  %s\n", glRenderer);
	logOutput.Print("GLSL version: %s\n", glslVersion); // only non-NULL as of OpenGL 2.0
	logOutput.Print("GLEW version: %s\n", glewVersion);

#if       !defined DEBUG
	{
		// Print out warnings for really crappy graphic cards/drivers
		const std::string gfxCardVendor = (glVendor != NULL)? glVendor: "UNKNOWN";
		const std::string gfxCardModel  = (glRenderer != NULL)? glRenderer: "UNKNOWN";
		bool gfxCardIsCrap = false;

		if (gfxCardVendor == "SiS") {
			gfxCardIsCrap = true;
		} else if (gfxCardModel.find("Intel") != std::string::npos) {
			// the vendor does not have to be Intel
			if (gfxCardModel.find(" 945G") != std::string::npos) {
				gfxCardIsCrap = true;
			} else if (gfxCardModel.find(" 915G") != std::string::npos) {
				gfxCardIsCrap = true;
			}
		}

		if (gfxCardIsCrap) {
			logOutput.Print("WW     WWW     WW    AAA     RRRRR   NNN  NN  II  NNN  NN   GGGGG  \n");
			logOutput.Print(" WW   WW WW   WW    AA AA    RR  RR  NNNN NN  II  NNNN NN  GG      \n");
			logOutput.Print("  WW WW   WW WW    AAAAAAA   RRRRR   NN NNNN  II  NN NNNN  GG   GG \n");
			logOutput.Print("   WWW     WWW    AA     AA  RR  RR  NN  NNN  II  NN  NNN   GGGGG  \n");
			logOutput.Print("(warning)\n");
			logOutput.Print("Your graphic card is ...\n");
			logOutput.Print("well, you know ...\n");
			logOutput.Print("insufficient\n");
			logOutput.Print("(in case you are not using a horribly wrong driver).\n");
			logOutput.Print("If the game crashes, looks ugly or runs slow, buy a better card!\n");
			logOutput.Print(".\n");
		}
	}
#endif // !defined DEBUG

	std::string s = (glExtensions != NULL)? glExtensions: "";
	for (unsigned int i = 0; i < s.length(); i++)
		if (s[i] == ' ') s[i] = '\n';

	std::string missingExts = "";
	if (!GLEW_ARB_multitexture) {
		missingExts += " GL_ARB_multitexture";
	}
	if (!GLEW_ARB_texture_env_combine) {
		missingExts += " GL_ARB_texture_env_combine";
	}
	if (!GLEW_ARB_texture_compression) {
		missingExts += " GL_ARB_texture_compression";
	}

	if (!missingExts.empty()) {
		static const unsigned int errorMsg_maxSize = 2048;
		char errorMsg[errorMsg_maxSize];
		SNPRINTF(errorMsg, errorMsg_maxSize,
				"Needed OpenGL extension(s) not found:\n"
				"%s\n"
				"Update your graphic-card driver!\n"
				"graphic card:   %s\n"
				"OpenGL version: %s\n",
				missingExts.c_str(),
				glRenderer,
				glVersion);
		handleerror(0, errorMsg, "Update graphic drivers", 0);
	}

#if defined(GL_ARB_debug_output) && !defined(HEADLESS) //! it's not defined in older GLEW versions
	if (GLEW_ARB_debug_output) {
		logOutput.Print("Installing OpenGL-DebugMessageHandler");
		glDebugMessageCallbackARB(&OpenGLDebugMessageCallback, NULL);
	}
#endif

	vertexArray1 = new CVertexArray;
	vertexArray2 = new CVertexArray;
}


void UnloadExtensions()
{
	delete vertexArray1;
	delete vertexArray2;
	vertexArray1 = vertexArray2 = NULL;
}


/******************************************************************************/

void glBuildMipmaps(const GLenum target,GLint internalFormat,const GLsizei width,const GLsizei height,const GLenum format,const GLenum type,const void *data)
{
	ScopedTimer timer("Textures::glBuildMipmaps");

	if (globalRendering->compressTextures) {
		switch ( internalFormat ) {
			case 4:
			case GL_RGBA8 :
			case GL_RGBA :  internalFormat = GL_COMPRESSED_RGBA_ARB; break;

			case 3:
			case GL_RGB8 :
			case GL_RGB :   internalFormat = GL_COMPRESSED_RGB_ARB; break;

			case GL_LUMINANCE: internalFormat = GL_COMPRESSED_LUMINANCE_ARB; break;
		}
	}

	// create mipmapped texture

	if (IS_GL_FUNCTION_AVAILABLE(glGenerateMipmapEXT) && !globalRendering->atiHacks) {
		// newest method
		glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
		if (globalRendering->atiHacks) {
			glEnable(target);
			glGenerateMipmapEXT(target);
			glDisable(target);
		} else {
			glGenerateMipmapEXT(target);
		}
	} else if (GLEW_VERSION_1_4) {
		// This required GL-1.4
		// instead of using glu, we rely on glTexImage2D to create the Mipmaps.
		glTexParameteri(target, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
	} else {
		gluBuild2DMipmaps(target, internalFormat, width, height, format, type, data);
	}
}


/******************************************************************************/

void ClearScreen()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity();            // Reset The Projection Matrix
	gluOrtho2D(0,1,0,1);
	glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix

	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1,1,1);
}


/******************************************************************************/

static unsigned int LoadProgram(GLenum, const char*, const char*);

/**
 * True if the program in DATADIR/shaders/filename is
 * loadable and can run inside our graphics server.
 *
 * @param target glProgramStringARB target: GL_FRAGMENT_PROGRAM_ARB GL_VERTEX_PROGRAM_ARB
 * @param filename Name of the file under shaders with the program in it.
 */

bool ProgramStringIsNative(GLenum target, const char* filename)
{
	// clear any current GL errors so that the following check is valid
	glClearErrors();

	GLuint tempProg = LoadProgram(target, filename, (target == GL_VERTEX_PROGRAM_ARB? "vertex": "fragment"));

	if (tempProg == 0) {
		return false;
	}

	glSafeDeleteProgram(tempProg);
	return true;
}


/**
 * Presumes the last GL operation was to load a vertex or
 * fragment program.
 *
 * If it was invalid, display an error message about
 * what and where the problem in the program source is.
 *
 * @param filename Only substituted in the message.
 * @param program The program text (used to enhance the message)
 */
static bool CheckParseErrors(GLenum target, const char* filename, const char* program)
{
	if (glGetError() != GL_INVALID_OPERATION)
		return false;

	// Find the error position
	GLint errorPos = -1;
	GLint isNative =  0;

	glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &errorPos);
	glGetProgramivARB(target, GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB, &isNative);

	// Print implementation-dependent program
	// errors and warnings string.
	const GLubyte* errString = glGetString(GL_PROGRAM_ERROR_STRING_ARB);

	logOutput.Print(
		"[myGL::CheckParseErrors] Shader compilation error at index "
		"%d (near \"%.30s\") when loading %s-program file %s:\n%s",
		errorPos, program + errorPos,
		(target == GL_VERTEX_PROGRAM_ARB? "vertex": "fragment"),
		filename, errString ? (const char*) errString : "(null)"
	);

	return true;
}


static unsigned int LoadProgram(GLenum target, const char* filename, const char* program_type)
{
	GLuint ret = 0;

	if (!GLEW_ARB_vertex_program) {
		return ret;
	}
	if (target == GL_FRAGMENT_PROGRAM_ARB && !GLEW_ARB_fragment_program) {
		return ret;
	}

	CFileHandler file(std::string("shaders/") + filename);
	if (!file.FileExists ()) {
		char c[512];
		SNPRINTF(c, 512, "[myGL::LoadProgram] Cannot find %s-program file '%s'", program_type, filename);
		throw content_error(c);
	}

	int fSize = file.FileSize();
	char* fbuf = new char[fSize + 1];
	file.Read(fbuf, fSize);
	fbuf[fSize] = '\0';

	glGenProgramsARB(1, &ret);
	glBindProgramARB(target, ret);
	glProgramStringARB(target, GL_PROGRAM_FORMAT_ASCII_ARB, fSize, fbuf);

	if (CheckParseErrors(target, filename, fbuf)) {
		ret = 0;
	}

	delete[] fbuf;
	return ret;
}

unsigned int LoadVertexProgram(const char* filename)
{
	return LoadProgram(GL_VERTEX_PROGRAM_ARB, filename, "vertex");
}

unsigned int LoadFragmentProgram(const char* filename)
{

	return LoadProgram(GL_FRAGMENT_PROGRAM_ARB, filename, "fragment");
}


void glSafeDeleteProgram(GLuint program)
{
	if (!GLEW_ARB_vertex_program || (program == 0)) {
		return;
	}
	glDeleteProgramsARB(1, &program);
}


/******************************************************************************/

void glClearErrors()
{
	int safety = 0;
	while ((glGetError() != GL_NO_ERROR) && (safety < 1000)) {
		safety++;
	}
}


/******************************************************************************/

void SetTexGen(const float& scaleX, const float& scaleZ, const float& offsetX, const float& offsetZ)
{
	const GLfloat planeX[] = {scaleX, 0.0f,   0.0f,  offsetX};
	const GLfloat planeZ[] = {  0.0f, 0.0f, scaleZ,  offsetZ};

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, planeX);
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, planeZ);
	glEnable(GL_TEXTURE_GEN_T);
}

/******************************************************************************/

