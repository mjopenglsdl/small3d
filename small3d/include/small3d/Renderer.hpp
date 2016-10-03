/*
 *  Renderer.hpp
 *
 *  Created on: 2014/10/19
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */


#pragma once

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL.h>

#include <memory>
#include "SceneObject.hpp"
#include <vector>
#include "Logger.hpp"
#include <unordered_map>
#include <glm/glm.hpp>
#include <SDL_ttf.h>

using namespace std;

namespace small3d
{

  /**
   * @class Renderer
   * @brief Renderer class, which can render using either OpenGL v3.3 or v2.1
   */

  class Renderer
  {

  private:

    SDL_Window* sdlWindow;

    GLuint perspectiveProgram;

    GLuint orthographicProgram;

    bool isOpenGL33Supported;

    bool noShaders;

    float frustumScale;

    float zNear;

    float zFar;

    float zOffsetFromCamera;

    unordered_map<string, TTF_Font*> fonts;

    /**
     * @brief Load a shader's source code from a file into a string
     * @param fileLocation The file's location, relative to the game path
     * @return String containing the shader's source code
     */
    string loadShaderFromFile(const string &fileLocation);

    /**
     * @brief Compile a shader's source code
     * @param shaderSource String containing the shader's source code
     * @param shaderType Type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER - the latter for OpenGL 3.3)
     * @return OpenGL shader reference
     */
    GLuint compileShader(const string &shaderSource, const GLenum shaderType);

    /**
    * @brief Initialise renderer (OpenGL, GLEW, etc)
    */
    void init(int width, int height, string windowTitle,
              float frustumScale , float zNear,
              float zFar, float zOffsetFromCamera,
              string shadersPath);

    /**
     * @brief Initialise SDL
     */
    void initSDL(int &width, int &height, const string &windowTitle = "");

    /**
     * @brief Retrieve the information of what went wrong when linking a shader program
     */
    string getProgramInfoLog(const GLuint linkedProgram) const;

    /**
     * @brief Detect if OpenGL 3.3 is supported. If not, fall back to OpenGL 2.1.
     * If neither of the two is supported, an exception is raised.
     */
    void detectOpenGLVersion();

    void checkForOpenGLErrors(string when, bool abort);

    /**
     * @brief Textures used in the scene, each corresponding to the name of one of
     * the rendered models
     */
    unordered_map<string, GLuint> *textures;

    /**
     * @brief Positions the next object to be rendered.
     * @param offset The offset (location coordinates)
     * @param rotation The rotation (around the x, y and z axes)
     * @param rotationAdjustment The matrix potentially containing an adjustment to the object's rotation (see SceneObject.adjustRotation)
     */
    void positionNextObject(const glm::vec3 &offset, const glm::vec3 &rotation,
                            const glm::mat4x4 &rotationAdjustment);

    /**
     * @brief Position the camera (Calculates offset and rotation matrices and sends them to OpenGL).
     */

    void positionCamera();

  public:

    /**
     * Constructor
     * @param windowTitle The title of the game's window
     * @param width The width of the window. If width and height are not set, the game will run in full screen mode.
     * @param height The height of the window
     * @param frustumScale	How much the frustum scales the items rendered
     * @param zNear		Projection plane z coordinate (use positive value)
     * @param zFar		Far end of frustum z coordinate (use positive value)
     * @param zOffsetFromCamera	The position of the projection plane with regard to the camera.
     * @param shadersPath	The path where the shaders will be stored, relative
     * 				to the application's executing directory. It
     * 				defaults to the path provided by the engine, but
     * 				it can be changed, so as to accommodate for executables
     * 				which are going to be using it. Even though the path to
     * 				the folder can be changed, the folder structure within
     * 				it and the names of the shaders must remain as provided.
     * 				The shader code can be changed, provided that their inputs
     * 				and outputs are maintained the same.
     */
    Renderer(string windowTitle = "", int width = 0, int height = 0,
             float frustumScale = 1.0f, float zNear = 1.0f,
             float zFar = 24.0f, float zOffsetFromCamera = -1.0f,
             string shadersPath = "resources/shaders/");

    /**
     * @brief Vector, indicating the direction of the light in the scene.
     */

    glm::vec3 lightDirection;

    /**
     * @brief The camera position in world space.
     */

    glm::vec3 cameraPosition;

    /**
     * @brief The camera rotation (around the x, y and z axes)
     */

    glm::vec3 cameraRotation;

    /**
     * @brief The light intensity (set to -1.0f if no lighting is to be used).
     */

    float lightIntensity;

    /**
     * @brief Generate a texture in OpenGL, using the given data
     * @param name The name by which the texture will be known
     * @param texture The texture data
     * @param width The width of the texture, in pixels
     * @param height The height of the texture, in pixels
     * @return The texture handle
     */
    GLuint generateTexture(string name, const float *texture, int width, int height);

    /**
     * @brief Deletes the texture indicated by the given name.
     *
     * @param	name	The name of the texture.
     */

    void deleteTexture(string name);

    /**
     * @brief Get the handle of a texture which has already been generated (see generateTexture)
     * @param name The name of the texture
     * @return The texture handle (0 if not found)
     */
    GLuint getTextureHandle(string name);

    /**
     * @brief Render an image. The image is in effect a textured quad, since 4 vertex positions are
     * passed to this method, in order to define its position and size.
     * @param vertices The vertices
     * @param textureName The name of the texture, containing the image (must have been loaded with
     * 					 generateTexture())
     * @param perspective If set to true, use perspective rendering, otherwise use simple (orthographic) rendering.
     * @param offset	The offset (position) at which the quad of the image will be drawn.
     */
    void render(const float *vertices, string textureName, bool perspective = false,
		     glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));

    /**
     * @brief Render a scene object
     * @param sceneObject The scene object
     */
    void render(SceneObject &sceneObject);

    /**
     * @brief Render some text on the screen. A texture will be generated, containing the given
     * text and it will be rendered at a depth z of 0.5 in an orthographic coordinate space.
     * @param text The text to be rendered
     * @param colour The colour in which the text will be rendered (r, g, b and a)
     * @param topLeft The coordinates of the top left corner of the text rectangle (x, y)
     * @param bottomRight The coordinates of the bottom right corner of the text rectangle (x, y)
     * @param fontPath Path to the TrueType font (.ttf) which will be used
     * @param fontSize The size of the font which will be used
     */
    void render(string text, glm::uvec4 colour, glm::vec2 topLeft, glm::vec2 bottomRight,
                string fontPath = "resources/fonts/CrusoeText/CrusoeText-Regular.ttf", int fontSize=48);

    /**
     * @brief Clears the screen.
     */
    void clearScreen();

    /**
     * @brief This is a double buffered system and this commands swaps
     * the buffers
     */
    void swapBuffers();

    /**
     * @brief Destructor
     */
    ~Renderer();
  };

}
