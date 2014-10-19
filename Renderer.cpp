#include "Renderer.h"
#include "EngineException.h"
#include <fstream>
#include <unordered_map>
#include "EngineMath.h"
#include "Vector3.h"
#include "Vector4.h"

using namespace std;

namespace small3d
{

	string Renderer::loadShaderFromFile(const string &fileLocation)
	{
		string shaderSource = "";
		ifstream file((cfg->getHomeDirectory() + fileLocation).c_str());
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

			throw EngineException(
				"Failed to compile shader:\n" + shaderSource + "\nInfo: "
				+ this->getProgramInfoLog(program));
		}
		else
		{
			LOGINFO("Shader " + shaderSourceFile + " compiled successfully.");
		}

		return shader;
	}

	Renderer::Renderer(const shared_ptr<Configuration> cfg,
		const shared_ptr<EngineLog> log)
	{
		this->cfg = cfg;
		this->log = log;
		isOpenGL33Supported = false;
		sdlWindow = 0;
		program = 0;
		textProgram = 0;
		textures = new unordered_map<string, GLuint>();
		font = NULL;
		noShaders = false;
		
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

		if(textProgram != 0)
		{
			glDeleteProgram(textProgram);
		}

		if(program != 0)
		{
			glDeleteProgram(program);
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
			throw EngineException(string("Unable to initialise SDL"));
		}

		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

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
			throw EngineException(string("Unable to create GL context"));
		}

		if (!sdlWindow)
		{
			LOGERROR(SDL_GetError());
			throw EngineException("Unable to set video");
		}

		if(TTF_Init()==-1)
		{
			LOGERROR(TTF_GetError());
			throw EngineException("Unable to initialise font system");
		}

		string fontPath = cfg->getHomeDirectory() + ttfFontPath;
		LOGINFO("Loading font from " + fontPath);

		font = TTF_OpenFont(fontPath.c_str(), 48);

		if (!font)
		{
			LOGERROR(TTF_GetError());
			throw EngineException("Failed to load font");
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
		int initResult = glewInit();
		
		if (initResult != GLEW_OK)
		{
			char resBuf[5];
			_itoa_s(initResult, resBuf, 5, 10);
			LOGERROR("Glew initialisation returned " + string(resBuf));
			throw EngineException("Error initialising GLEW");
		}
		else
		{
			string glewVersion = (char*) glewGetString(GLEW_VERSION);
			LOGINFO("Using GLEW version " + glewVersion);
		}

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
			throw EngineException(
				"None of the supported OpenGL versions (3.3 nor 2.1) are available.");
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
		string textVertexShaderPath;
		string textFragmentShaderPath;

		if (isOpenGL33Supported)
		{
			vertexShaderPath = shadersPath + "OpenGL33/perspectiveMatrixLightedShader.vert";
			fragmentShaderPath = shadersPath + "OpenGL33/textureShader.frag";
			textVertexShaderPath =
				shadersPath + "OpenGL33/textShader.vert";
			textFragmentShaderPath = shadersPath + "OpenGL33/textShader.frag";

		}
		else
		{
			vertexShaderPath =
				shadersPath + "OpenGL21/perspectiveMatrixLightedShader.vert";
			fragmentShaderPath = shadersPath + "OpenGL21/textureShader.frag";
			textVertexShaderPath =
				shadersPath + "OpenGL21/textShader.vert";
			textFragmentShaderPath = shadersPath + "OpenGL21/textShader.frag";
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

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			throw EngineException("Failed to link program:\n" + this->getProgramInfoLog(program));
		}
		else
		{
			LOGINFO("Linked main rendering program successfully");

			glUseProgram(program);

			// Perspective

			GLuint perspectiveMatrixUniform = glGetUniformLocation(program,
				"perspectiveMatrix");

			float perspectiveMatrix[16];
			memset(perspectiveMatrix, 0, sizeof(float) * 16);
			perspectiveMatrix[0] = 1.0f; // frustum scale
			perspectiveMatrix[5] = 1.8f; // frustum scale
			perspectiveMatrix[10] = (1.0f + 25.0f) / (1.0f - 25.0f); // (zNear + zFar) / (zNear - zFar)
			perspectiveMatrix[14] = 2.0f * 1.0f * 25.0f / (1.0f - 25.0f); // 2 * zNear * zFar / (zNear - zFar);
			perspectiveMatrix[11] = -1.0f; //cameraPos.z? or just the -1 factor...

			glUniformMatrix4fv(perspectiveMatrixUniform, 1, GL_FALSE,
				perspectiveMatrix);

			glUseProgram(0);
		}
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClearDepth(10.0f);

		// Program (with shaders) for rendering text

		GLuint textVertexShader = compileShader(textVertexShaderPath,
			GL_VERTEX_SHADER);
		GLuint textFragmentShader = compileShader(textFragmentShaderPath,
			GL_FRAGMENT_SHADER);

		textProgram = glCreateProgram();
		glAttachShader(textProgram, textVertexShader);
		glAttachShader(textProgram, textFragmentShader);

		glLinkProgram(textProgram);

		glGetProgramiv(textProgram, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			throw EngineException("Failed to link program:\n" + this->getProgramInfoLog(textProgram));
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


	void Renderer::renderTexturedQuad(const float *vertices, const string &textureName)
	{
		GLuint textureHandle = getTextureHandle(textureName);

		if (textureHandle == 0)
		{
			throw EngineException("Texture " + textureName + "has not been generated");
		}
		glBindTexture(GL_TEXTURE_2D, textureHandle);

		glUseProgram(textProgram);

		glEnableVertexAttribArray(0);

		GLuint boxBuffer = 0;
		glGenBuffers(1, &boxBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, boxBuffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(float) * 16, // 4 times 4 floats
			vertices,
			GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		float textureCoords[8] =
		{
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f
		};

		GLuint coordBuffer = 0;

		glGenBuffers(1,&coordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(textureCoords),
			&textureCoords,
			GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_QUADS, 0, 4);

		glDeleteBuffers(1, &boxBuffer);
		glDeleteBuffers(1, &coordBuffer);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			LOGERROR("OpenGL error while rendering text");
			throw EngineException(string((char*)gluErrorString(errorCode)));
		}
	}

	void Renderer::clearScreen()
	{
		// Clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::renderSceneObjects(const shared_ptr<vector<shared_ptr<SceneObject> > > sceneObjects)
	{

		// Use the shaders prepared at initialisation
		glUseProgram(program);

		// Pick up each model in the scene and render it.
		for (std::vector<shared_ptr<SceneObject> >::iterator it =
			sceneObjects->begin(); it != sceneObjects->end(); it++)
		{
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
				it->get()->getModel().getVertexDataSize(),
				it->get()->getModel().getVertexData(),
				GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

			// Pass vertex indexes

			glGenBuffers(1, &indexBufferObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				it->get()->getModel().getIndexDataSize(),
				it->get()->getModel().getIndexData(),
				GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);


			// Index attribute array
			glEnableVertexAttribArray(1);

			// Lighting

			Vector3 lightDirection(0.0f, 0.9f, 0.2f);
			GLuint lightDirectionUniform = glGetUniformLocation(program,
				"lightDirection");
			float ld[3];
			lightDirection.getValueArray(ld);
			glUniform3fv(lightDirectionUniform, 1,
				ld);

			// Normals
			glGenBuffers(1, &normalsBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER, normalsBufferObject);
			glBufferData(GL_ARRAY_BUFFER,
				it->get()->getModel().getNormalsDataSize(),
				it->get()->getModel().getNormalsData(), GL_STATIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Find the colour uniform
			GLuint colourUniform = glGetUniformLocation(program, "colour");

			// Add texture if that is contained in the model
			shared_ptr<Image> textureObj = it->get()->getTexture();

			if (textureObj)
			{
				// "Disable" colour since there is a texture
				float cl[4] = {0.0f, 0.0f, 0.0f, 0.0f};

				glUniform4fv(colourUniform, 1, cl);

				texture = this->getTextureHandle(it->get()->getName());

				if (texture == 0)
				{
					texture = generateTexture(it->get()->getName(), textureObj->getData(), textureObj->getWidth(), textureObj->getHeight());
				}

				glBindTexture(GL_TEXTURE_2D, texture);

				// UV Coordinates

				glGenBuffers(1, &uvBufferObject);
				glBindBuffer(GL_ARRAY_BUFFER, uvBufferObject);
				glBufferData(GL_ARRAY_BUFFER,
					it->get()->getModel().getTextureCoordsDataSize(),
					it->get()->getModel().getTextureCoordsData(), GL_STATIC_DRAW);
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

			}
			else
			{
				// If there is no texture, use the colour of the object
				float objCol[4];
				it->get()->getColour()->getValueArray(objCol);
				glUniform4fv(colourUniform, 1, objCol);
			}

			// Rotation

			GLuint xRotationMatrixUniform = glGetUniformLocation(program,
				"xRotationMatrix");
			GLuint yRotationMatrixUniform = glGetUniformLocation(program,
				"yRotationMatrix");
			GLuint zRotationMatrixUniform = glGetUniformLocation(program,
				"zRotationMatrix");

			glUniformMatrix4fv(xRotationMatrixUniform, 1, GL_TRUE, rotateX(it->get()->getRotation()->x).valueArray);
			glUniformMatrix4fv(yRotationMatrixUniform, 1, GL_TRUE, rotateY(it->get()->getRotation()->y).valueArray);
			glUniformMatrix4fv(zRotationMatrixUniform, 1, GL_TRUE, rotateZ(it->get()->getRotation()->z).valueArray);

			GLuint offsetUniform = glGetUniformLocation(program, "offset");
			float offs[3];
			it->get()->getOffset()->getValueArray(offs);
			glUniform3fv(offsetUniform, 1, offs);

			// Throw an exception if there was an error in OpenGL, during
			// any of the above.
			GLenum errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				LOGERROR("OpenGL error while rendering scene");
				throw EngineException(string((char*)gluErrorString(errorCode)));
			}

			// Draw
			glDrawElements(GL_TRIANGLES,
				it->get()->getModel().getIndexDataIndexCount(),
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

		} // for std::vector<SceneObject>::iterator

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

		this->renderTexturedQuad(boxVerts, "text_" + text);
	}

	void Renderer::swapBuffers()
	{
		SDL_GL_SwapWindow(sdlWindow);
	}

}

