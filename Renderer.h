/*
*  Renderer.h
*
*  Created on: 2014/10/19
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#pragma once

#ifndef SDLANDOPENGL
#define SDLANDOPENGL
#include "glew.h"
#include <miguel/sdl2/include/SDL_opengl.h>
#include <miguel/sdl2/include/SDL.h>
#include <miguel/sdl2_ttf/SDL_ttf.h>
#endif //SDLANDOPENGL

#include <memory>
#include "SceneObject.h"
#include <vector>
#include "Configuration.h"
#include "EngineLog.h"
#include <unordered_map>
#include <gl/GL.h>

//#include <glm/gtc/type_ptr.hpp>

using namespace std;

namespace small3d
{

/**
 * @class	Renderer
 *
 * @brief	Renderer class, which can render using OpenGL v2.1
 *
 */

class Renderer
{

private:

    shared_ptr<Configuration> cfg;
    shared_ptr<EngineLog> log;

	SDL_Window* sdlWindow;

    TTF_Font *font;

    GLuint program;

    GLuint textProgram;

    bool isOpenGL33Supported;

    bool noShaders;

    /**
     * Load a shader's source code from a file into a string
     * @param fileLocation The file's location, relative to the game path
     * @return String containing the shader's source code
     */
    string loadShaderFromFile(const string &fileLocation);

    /**
     * Compile a shader's source code
     * @param shaderSource String containing the shader's source code
     * @param shaderType Type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER - the latter for OpenGL 3.3)
     * @return OpenGL shader reference
     */
    GLuint compileShader(const string &shaderSource, const GLenum shaderType);

    /**
     * Initialise SDL
     */
    void initSDL(int width, int height, bool fullScreen);

    /**
     * Retrieve the information of what went wrong when linking a shader program
     */
    string getProgramInfoLog(const GLuint linkedProgram) const;

    /**
     * Detect if OpenGL 3.3 is supported. If not, fall back to OpenGL 2.1.
     * If neither of the two is supported, an exception is raised.
     */
    void detectOpenGLVersion();

    /**
     * Textures used in the scene, each corresponding to the name of one of
     * the rendered models
     */
    unordered_map<string, GLuint> *textures;

public:

    /**
     * Constructor
     * @param cfg The game's configuration object
     * @param log The game's logging object
     */
    Renderer(const shared_ptr<Configuration> cfg,
             const shared_ptr<EngineLog> log);

    /**
     * Initialise renderer (OpenGL, GLEW, etc)
     * @param width The width of the window
     * @param height The height of the window
     */
    void init(const int width, const int height, const bool fullScreen);

	/**
	 * Generate a texture in OpenGL, using the given data
	 * @param name The name by which the texture will be known
	 * @param texture The texture data
	 * @param width The width of the texture, in pixels
	 * @param height The height of the texture, in pixels
	 * @return The texture handle
	 */
	GLuint generateTexture(const string &name, const float *texture, const int width, const int height);

	/**
	 * Get the handle of a texture which has already been generated (see generateTexture)
	 * @param name The name of the texture
	 * @return The texture handle (0 if not found)
	 */
	GLuint getTextureHandle(const string &name);

	/**
	 * Render a textured quad
	 * @param vertices The vertices
	 * @param textureName The name of the texture (must have been loaded with generateTexture())
	 */
	void renderTexturedQuad(const float *vertices, const string &textureName);

	/**
	 * Clears the screen.
	 */
	void clearScreen();

    /**
     * Render the scene objects
     * @param sceneObjects The scene objects
     */
    void renderSceneObjects(
        const shared_ptr<vector<shared_ptr<SceneObject> > > sceneObjects);

    /**
     * Render some text on the screen. The text will be rendered at a depth z of 0.5
     * in an orthographic coordinate space
     * @param text The text to be rendered
     * @param colour The colour in which the text will be rendered
     * @param topX The top x coordinate of the text rectangle
     * @param topY The top y coordinate of the text rectangle
	 * @param bottomX The bottom x coordinate of the text rectangle
	 * @param bottomY The bottom y coordinate of the text rectangle
     */
	void renderText(const string &text, const SDL_Color &colour, 
		const float &topX, const float &topY, const float &bottomX, const float &bottomY);

    /**
     * This is a double buffered system and this commands swaps
     * the buffers
     */
    void swapBuffers();

    /**
     * Destructor
     */
    ~Renderer();
};

}
