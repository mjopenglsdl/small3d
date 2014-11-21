#include "Renderer.h"
#include "Exception.h"
#include <fstream>
#include <unordered_map>
#include "MathFunctions.h"
#include <dimitrikourk/glm/glm/gtc/type_ptr.hpp>
#include <miguel/sdl2/include/SDL.h>
#include <cstring>

using namespace std;

namespace small3d
{
	string openglErrorToString(GLenum error);

	string Renderer::loadShaderFromFile(const string &fileLocation)
	{
		initLogger();
		string shaderSource = "";
		ifstream file((SDL_GetBasePath() + fileLocation).c_str());
		string line;
		if (file.is_open())
		{
			while (getline(file, line))
			{
				shaderSource += line + "\n";
			}
		}
		return shaderSource;
	}

	GLuint Renderer::compileShader(const string &shaderSourceFile, const GLenum shaderType)
	{

		GLuint shader = glCreateShader(shaderType);

		string shaderSource = this->loadShaderFromFile(shaderSourceFile);

		const char *shaderSourceChars = shaderSource.c_str();
		glShaderSource(shader, 1, &shaderSourceChars, NULL);

		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{

			throw Exception(
				"Failed to compile shader:\n" + shaderSource + "\nInfo: "
				+ this->getProgramInfoLog(perspectiveProgram));
		}
		else
		{
			LOGINFO("Shader " + shaderSourceFile + " compiled successfully.");
		}

		return shader;
	}

	Renderer::Renderer()
	{
		isOpenGL33Supported = false;
		sdlWindow = 0;
		perspectiveProgram = 0;
		orthographicProgram = 0;
		textures = new unordered_map<string, GLuint>();
		font = NULL;
		noShaders = false;
		lightDirection = glm::vec3(0.0f, 0.9f, 0.2f);
		zNear = 1.0f;
		zFar = 25.0f;
		cameraPosition = glm::vec3(0, 0, 0);
		cameraRotation = glm::vec3(0, 0, 0);

	}

	Renderer::~Renderer()
	{

		LOGINFO("Renderer destructor running");
		for (unordered_map<string, GLuint>::iterator it = textures->begin();
			it != textures->end(); ++it)
		{
			LOGINFO("Deleting texture for " + it->first);
			glDeleteTextures(1, &it->second);
		}
		delete textures;

		if (!noShaders)
		{
			glUseProgram(0);
		}

		if(orthographicProgram != 0)
		{
			glDeleteProgram(orthographicProgram);
		}

		if(perspectiveProgram != 0)
		{
			glDeleteProgram(perspectiveProgram);
		}

		TTF_CloseFont(font);
		TTF_Quit();

		if (sdlWindow != 0)
		{
			SDL_DestroyWindow(sdlWindow);
		}
		SDL_Quit();
	}

	void Renderer::initSDL(int width, int height, bool fullScreen)
	{
		sdlWindow = 0;

		// initialize SDL video
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			LOGERROR(SDL_GetError());
			throw Exception(string("Unable to initialise SDL"));
		}
#ifdef __APPLE__
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
#endif
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		Uint32 flags = fullScreen ? SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP :
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		sdlWindow = SDL_CreateWindow("Avoid the Bug 3D", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height,
			flags);

		if (SDL_GL_CreateContext( sdlWindow ) == NULL)
		{
			LOGERROR(SDL_GetError());
			throw Exception(string("Unable to create GL context"));
		}

		if (!sdlWindow)
		{
			LOGERROR(SDL_GetError());
			throw Exception("Unable to set video");
		}

		if(TTF_Init()==-1)
		{
			LOGERROR(TTF_GetError());
			throw Exception("Unable to initialise font system");
		}

		string fontPath = SDL_GetBasePath() + ttfFontPath;
		LOGINFO("Loading font from " + fontPath);

		font = TTF_OpenFont(fontPath.c_str(), 48);

		if (!font)
		{
			LOGERROR(TTF_GetError());
			throw Exception("Failed to load font");
		}
		else
		{
			LOGINFO("TTF font loaded successfully");
		}

	}

	string Renderer::getProgramInfoLog(const GLuint linkedProgram) const
	{

		GLint infoLogLength;
		glGetProgramiv(linkedProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *infoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(linkedProgram, infoLogLength, NULL, infoLog);
		string infoLogStr = infoLog;

		delete[] infoLog;

		return infoLogStr;

	}

	void Renderer::detectOpenGLVersion()
	{
#ifdef __APPLE__
		glewExperimental = GL_TRUE;
#endif
		int initResult = glewInit();

		if (initResult != GLEW_OK)
		{
			throw Exception("Error initialising GLEW");
		}
		else
		{
			string glewVersion = (char*) glewGetString(GLEW_VERSION);
			LOGINFO("Using GLEW version " + glewVersion);
		}

		checkForOpenGLErrors("initialising GLEW", false);

		string glVersion = (char*) glGetString(GL_VERSION);
		glVersion = "OpenGL version supported by machine: " + glVersion;
		LOGINFO(glVersion);

		if (glewIsSupported("GL_VERSION_3_3"))
		{
			LOGINFO("Ready for OpenGL 3.3");
			isOpenGL33Supported = true;
		}
		else if (glewIsSupported("GL_VERSION_2_1"))
		{
			LOGINFO("Ready for OpenGL 2.1");
		}
		else
		{
			noShaders = true;
			throw Exception(
				"None of the supported OpenGL versions (3.3 nor 2.1) are available.");
		}

	}

	void Renderer::checkForOpenGLErrors(string when, bool abort) {
		GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			LOGERROR("OpenGL error while " + when);

			do
			{
				LOGERROR(openglErrorToString(errorCode));
				errorCode = glGetError();
			}
			while(errorCode != GL_NO_ERROR);

			if (abort)
				throw Exception("OpenGL error while " + when);
		}
	}

	void Renderer::init(const int width, const int height, const bool fullScreen, 
		const string ttfFontPath, const string shadersPath)
	{
		this->ttfFontPath = ttfFontPath;

		this->initSDL(width, height, fullScreen);

		this->detectOpenGLVersion();

		string vertexShaderPath;
		string fragmentShaderPath;
		string simpleVertexShaderPath;
		string simpleFragmentShaderPath;

		if (isOpenGL33Supported)
		{
			vertexShaderPath = shadersPath + "OpenGL33/perspectiveMatrixLightedShader.vert";
			fragmentShaderPath = shadersPath + "OpenGL33/textureShader.frag";
			simpleVertexShaderPath =
				shadersPath + "OpenGL33/simpleShader.vert";
			simpleFragmentShaderPath = shadersPath + "OpenGL33/simpleShader.frag";

		}
		else
		{
			vertexShaderPath =
				shadersPath + "OpenGL21/perspectiveMatrixLightedShader.vert";
			fragmentShaderPath = shadersPath + "OpenGL21/textureShader.frag";
			simpleVertexShaderPath =
				shadersPath + "OpenGL21/simpleShader.vert";
			simpleFragmentShaderPath = shadersPath + "OpenGL21/simpleShader.frag";
		}

		glViewport(0, 0, (GLsizei) width, (GLsizei) height);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 10.0f);

		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint vertexShader = compileShader(vertexShaderPath,
			GL_VERTEX_SHADER);
		GLuint fragmentShader = compileShader(fragmentShaderPath,
			GL_FRAGMENT_SHADER);

		perspectiveProgram = glCreateProgram();
		glAttachShader(perspectiveProgram, vertexShader);
		glAttachShader(perspectiveProgram, fragmentShader);

		glLinkProgram(perspectiveProgram);

		GLint status;
		glGetProgramiv(perspectiveProgram, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			throw Exception("Failed to link program:\n" + this->getProgramInfoLog(perspectiveProgram));
		}
		else
		{
			LOGINFO("Linked main rendering program successfully");

			glUseProgram(perspectiveProgram);

			// Perspective

			GLuint perspectiveMatrixUniform = glGetUniformLocation(perspectiveProgram,
				"perspectiveMatrix");

			float perspectiveMatrix[16];
			memset(perspectiveMatrix, 0, sizeof(float) * 16);
			perspectiveMatrix[0] = 1.0f; // frustum scale
			perspectiveMatrix[5] = ROUND_2_DECIMAL(width / height);
			perspectiveMatrix[10] = (zNear + zFar) / (zNear - zFar); 
			perspectiveMatrix[14] = 2.0f * zNear * zFar / (zNear - zFar); // 2 * zNear * zFar / (zNear - zFar);
			perspectiveMatrix[11] = -1.0f; // zCamera

			glUniformMatrix4fv(perspectiveMatrixUniform, 1, GL_FALSE,
				perspectiveMatrix);

			glUseProgram(0);
		}
		glDetachShader(perspectiveProgram, vertexShader);
		glDetachShader(perspectiveProgram, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClearDepth(1.0f);

		// Program (with shaders) for rendering text

		GLuint textVertexShader = compileShader(simpleVertexShaderPath,
			GL_VERTEX_SHADER);
		GLuint textFragmentShader = compileShader(simpleFragmentShaderPath,
			GL_FRAGMENT_SHADER);

		orthographicProgram = glCreateProgram();
		glAttachShader(orthographicProgram, textVertexShader);
		glAttachShader(orthographicProgram, textFragmentShader);

		glLinkProgram(orthographicProgram);

		glGetProgramiv(orthographicProgram, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			throw Exception("Failed to link program:\n" + this->getProgramInfoLog(orthographicProgram));
		}
		else
		{
			LOGINFO("Linked text rendering program successfully");
		}
		glUseProgram(0);
	}

	GLuint Renderer::generateTexture(const string &name, const float *texture, const int width, const int height )
	{

		GLuint textureHandle;
		
		glGenTextures(1, &textureHandle);

		glBindTexture(GL_TEXTURE_2D, textureHandle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

		GLint internalFormat = isOpenGL33Supported ? GL_RGBA32F : GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_RGBA,
			GL_FLOAT, &texture[0]);

		textures->insert(make_pair(name, textureHandle));

		return textureHandle;
	}

	void Renderer::deleteTexture( const string &name )
	{
		unordered_map<string, GLuint>::iterator nameTexturePair = textures->find(name);

		if(nameTexturePair != textures->end())
		{
			glDeleteTextures(1, &(nameTexturePair->second));
			textures->erase(name);
		}
	}

	GLuint Renderer::getTextureHandle(const string &name)
	{
		GLuint handle = 0;

		unordered_map<string, GLuint>::iterator nameTexturePair = textures->find(name);

		if(nameTexturePair != textures->end())
		{
			handle = nameTexturePair->second;
		}

		return handle;
	}

	void Renderer::positionSceneObject( const glm::vec3 &offset, const glm::vec3 &rotation )
	{
		// Rotation

		GLuint xRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
			"xRotationMatrix");
		GLuint yRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
			"yRotationMatrix");
		GLuint zRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
			"zRotationMatrix");

		glUniformMatrix4fv(xRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateX(rotation.x)));
		glUniformMatrix4fv(yRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateY(rotation.y)));
		glUniformMatrix4fv(zRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateZ(rotation.z)));

		GLuint offsetUniform = glGetUniformLocation(perspectiveProgram, "offset");
		glUniform3fv(offsetUniform, 1, glm::value_ptr(offset));
	}


	void Renderer::positionCamera()
	{
		// Camera rotation

		GLuint xCameraRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
			"xCameraRotationMatrix");
		GLuint yCameraRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
			"yCameraRotationMatrix");
		GLuint zCameraRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
			"zCameraRotationMatrix");

		glUniformMatrix4fv(xCameraRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateX(cameraRotation.x)));
		glUniformMatrix4fv(yCameraRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateY(cameraRotation.y)));
		glUniformMatrix4fv(zCameraRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateZ(cameraRotation.z)));

		// Camera position

		GLuint cameraPositionUniform = glGetUniformLocation(perspectiveProgram, "cameraPosition");
		glUniform3fv(cameraPositionUniform, 1, glm::value_ptr(cameraPosition));
	}


	void Renderer::renderImage(const float *vertices, const string &textureName, const bool &perspective)
	{
		
		glUseProgram(perspective? perspectiveProgram : orthographicProgram);

		float triangleVerts[24] =
		{
			vertices[0], vertices[1], vertices[2], 1.0f,
			vertices[4], vertices[5], vertices[6], 1.0f,
			vertices[12], vertices[13], vertices[14], 1.0f,
			vertices[12], vertices[13], vertices[14], 1.0f,
			vertices[4], vertices[5], vertices[6], 1.0f,
			vertices[8], vertices[9], vertices[10], 1.0f
		};

		GLuint vao = 0;
		if (isOpenGL33Supported)
		{
			// Generate VAO
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
		}

		glEnableVertexAttribArray(0);

		GLuint boxBuffer = 0;
		glGenBuffers(1, &boxBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, boxBuffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(float) * 24,
			triangleVerts,
			GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		GLuint textureHandle = getTextureHandle(textureName);

		if (textureHandle == 0)
		{
			throw Exception("Texture " + textureName + "has not been generated");
		}

		glBindTexture(GL_TEXTURE_2D, textureHandle);

		float textureCoords[12] =
		{
			1.0f, 0.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};

		GLuint coordBuffer = 0;

		glGenBuffers(1,&coordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(float) * 12,
			&textureCoords,
			GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		if (perspective)
		{
			// Find the colour uniform
			GLuint colourUniform = glGetUniformLocation(perspectiveProgram, "colour");

			// "Disable" colour since there is a texture
			glUniform4fv(colourUniform, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));

			positionSceneObject(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			positionCamera();
		}

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDeleteBuffers(1, &boxBuffer);
		glDeleteBuffers(1, &coordBuffer);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (isOpenGL33Supported)
		{
			glDeleteVertexArrays(1, &vao);
			glBindVertexArray(0);
		}

		checkForOpenGLErrors("rendering image", true);
	}

	void Renderer::renderSceneObject(shared_ptr<SceneObject> sceneObject)
	{
		// Use the shaders prepared at initialisation
		glUseProgram(perspectiveProgram);

		GLuint vao = 0;
		if (isOpenGL33Supported)
		{
			// Generate VAO
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
		}

		GLuint positionBufferObject = 0;
		GLuint indexBufferObject = 0;
		GLuint normalsBufferObject = 0;
		GLuint sampler = 0;
		GLuint texture = 0;
		GLuint uvBufferObject = 0;

		// Pass the vertex positions to the shaders
		glGenBuffers(1, &positionBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glBufferData(GL_ARRAY_BUFFER,
			sceneObject->getModel().vertexDataSize,
			sceneObject->getModel().vertexData,
			GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		// Pass vertex indexes

		glGenBuffers(1, &indexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sceneObject->getModel().indexDataSize,
			sceneObject->getModel().indexData,
			GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

		// Normals
		glGenBuffers(1, &normalsBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, normalsBufferObject);
		glBufferData(GL_ARRAY_BUFFER,
			sceneObject->getModel().normalsDataSize,
			sceneObject->getModel().normalsData, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Find the colour uniform
		GLuint colourUniform = glGetUniformLocation(perspectiveProgram, "colour");

		// Add texture if that is contained in the model
		shared_ptr<Image> textureObj = sceneObject->getTexture();

		if (textureObj)
		{
			// "Disable" colour since there is a texture
			glUniform4fv(colourUniform, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));

			texture = this->getTextureHandle(sceneObject->getName());

			if (texture == 0)
			{
				texture = generateTexture(sceneObject->getName(), textureObj->getData(), textureObj->getWidth(), textureObj->getHeight());
			}

			glBindTexture(GL_TEXTURE_2D, texture);

			// UV Coordinates

			glGenBuffers(1, &uvBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER, uvBufferObject);
			glBufferData(GL_ARRAY_BUFFER,
				sceneObject->getModel().textureCoordsDataSize,
				sceneObject->getModel().textureCoordsData, GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}
		else
		{
			// If there is no texture, use the colour of the object
			glUniform4fv(colourUniform, 1, glm::value_ptr(*sceneObject->getColour()));
		}

		// Lighting
		GLuint lightDirectionUniform = glGetUniformLocation(perspectiveProgram,
			"lightDirection");
		glUniform3fv(lightDirectionUniform, 1,
			glm::value_ptr(lightDirection));

		positionSceneObject(*sceneObject->getOffset(), *sceneObject->getRotation());

		positionCamera();

		// Throw an exception if there was an error in OpenGL, during
		// any of the above.
		checkForOpenGLErrors("rendering scene", true);

		// Draw
		glDrawElements(GL_TRIANGLES,
			sceneObject->getModel().indexDataIndexCount,
			GL_UNSIGNED_INT, 0);

		// Clear stuff
		if (textureObj)
		{
			glDisableVertexAttribArray(2);
		}

		if (positionBufferObject != 0)
		{
			glDeleteBuffers(1, &positionBufferObject);
		}

		if ( indexBufferObject != 0)
		{
			glDeleteBuffers(1, &indexBufferObject);
		}
		if ( normalsBufferObject != 0)
		{
			glDeleteBuffers(1, &normalsBufferObject);
		}
		if ( sampler != 0)
		{
			glDeleteSamplers(1, &sampler);
		}
		if ( uvBufferObject != 0)
		{
			glDeleteBuffers(1, &uvBufferObject);
		}

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		if (isOpenGL33Supported)
		{
			glDeleteVertexArrays(1, &vao);
			glBindVertexArray(0);
		}

		glUseProgram(0);

	}

	void Renderer::renderText(const string &text, const SDL_Color &colour, 
		const float &topX, const float &topY, const float &bottomX, const float &bottomY)
	{

		GLuint textHandle = getTextureHandle("text_" + text);

		if (textHandle == 0)
		{

			SDL_Surface *textSurface = TTF_RenderText_Blended(font,
				text.c_str(), colour);
			int numPixels = textSurface->h * textSurface->w;

			Uint32 *pix = static_cast<Uint32*>(textSurface->pixels);

			float *texturef = new float[numPixels * 4];

			for (int pidx = 0; pidx < numPixels; ++pidx)
			{
				Uint32 r = pix[pidx] & textSurface->format->Rmask;
				Uint32 g = pix[pidx] & textSurface->format->Gmask;
				Uint32 b = pix[pidx] & textSurface->format->Bmask;
				Uint32 a = pix[pidx] & textSurface->format->Amask;

				r = r >> textSurface->format->Rshift;
				g = g >> textSurface->format->Gshift;
				b = b >> textSurface->format->Bshift;
				a = a >> textSurface->format->Ashift;

				float ttuple[4] = {(float)r, // used to be boost::numeric_cast<float, Uint32>
					(float)g,
					(float)b,
					(float)a
				};

				ttuple[0]= floorf(100.0f * (ttuple[0] / 255.0f) + 0.5f) / 100.0f;
				ttuple[1]= floorf(100.0f * (ttuple[1] / 255.0f) + 0.5f) / 100.0f;
				ttuple[2]= floorf(100.0f * (ttuple[2] / 255.0f) + 0.5f) / 100.0f;
				ttuple[3]= floorf(100.0f * (ttuple[3] / 255.0f) + 0.5f) / 100.0f;

				memcpy(&texturef[pidx * 4], &ttuple, sizeof(ttuple));

			}

			textHandle = generateTexture("text_" + text, texturef, textSurface->w, textSurface->h);

			delete[] texturef;
			texturef = NULL;
			SDL_FreeSurface(textSurface);

		}

		float boxVerts[16] =
		{
			bottomX, topY, -0.5f, 1.0f,
			topX, topY, -0.5f, 1.0f,
			topX, bottomY, -0.5f, 1.0f,
			bottomX, bottomY, -0.5f, 1.0f
		};

		this->renderImage(boxVerts, "text_" + text);
	}

	void Renderer::clearScreen()
	{
		// Clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::swapBuffers()
	{
		SDL_GL_SwapWindow(sdlWindow);
	}

	string openglErrorToString(GLenum error)
	{
		string errorString;

		switch(error) {
		case GL_NO_ERROR:
			errorString="GL_NO_ERROR: No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
			break;
		case  GL_INVALID_ENUM:
			errorString="GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case  GL_INVALID_VALUE:
			errorString="GL_INVALID_VALUE: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case  GL_INVALID_OPERATION:
			errorString="GL_INVALID_OPERATION: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case  GL_INVALID_FRAMEBUFFER_OPERATION:
			errorString="GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case  GL_OUT_OF_MEMORY:
			errorString="GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
			break;
		case  GL_STACK_UNDERFLOW:
			errorString="GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
			break;
		case   GL_STACK_OVERFLOW:
			errorString="GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
			break;
		default:
			errorString="Unknown error";
			break;
		}
		return errorString;
	}

}

