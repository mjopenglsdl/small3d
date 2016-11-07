/*
 *  Renderer.hpp
 *
 *  Created on: 2014/10/19
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#define GLM_FORCE_RADIANS

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <GL/glew.h>

#ifdef SMALL3D_GLFW
#include <GLFW/glfw3.h>
#else
#include <SDL_opengl.h>
#include <SDL.h>
#endif

#include "SceneObject.hpp"
#include "Logger.hpp"
#include <unordered_map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace small3d
{

  /**
   * @class Renderer
   * @brief Renderer class, which can render using either OpenGL v3.3 or v2.1
   */

  class Renderer
  {

  private:

#ifdef SMALL3D_GLFW
    GLFWwindow* window;
#else
    SDL_Window* window;
#endif

    GLuint perspectiveProgram;

    GLuint orthographicProgram;

    bool isOpenGL33Supported;

    bool noShaders;

    float frustumScale;

    float zNear;

    float zFar;

    float zOffsetFromCamera;

    FT_Library library;

    float textMemory[400000];

    std::unordered_map<std::string, FT_Face> fontFaces;

    /**
     * @brief Load a shader's source code from a file into a string
     * @param fileLocation The file's location, relative to the game path
     * @return String containing the shader's source code
     */
    std::string loadShaderFromFile(const std::string &fileLocation);

    /**
     * @brief Compile a shader's source code
     * @param shaderSource String containing the shader's source code
     * @param shaderType Type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER - the latter for OpenGL 3.3)
     * @return OpenGL shader reference
     */
    GLuint compileShader(const std::string &shaderSource, const GLenum shaderType);

    /**
     * @brief Retrieve the information of what went wrong when linking a shader program
     */
    std::string getProgramInfoLog(const GLuint linkedProgram) const;

    /**
     * @brief Retrieve the information of what went wrong when compiling a shader
     */
    std::string getShaderInfoLog(const GLuint shader) const;

    /**
    * @brief Initialise renderer (OpenGL, GLEW, etc)
    */
    void init(int width, int height, std::string windowTitle,
              float frustumScale , float zNear,
              float zFar, float zOffsetFromCamera,
              std::string shadersPath);

    /**
     * @brief Initialise the application window
     */
    void initWindow(int &width, int &height, const std::string &windowTitle = "");

    /**
     * @brief Detect if OpenGL 3.3 is supported. If not, fall back to OpenGL 2.1.
     * If neither of the two is supported, an exception is raised.
     */
    void detectOpenGLVersion();

    void checkForOpenGLErrors(std::string when, bool abort);

    /**
     * @brief Textures used in the scene, each corresponding to the name of one of
     * the rendered models
     */
    std::unordered_map<std::string, GLuint> *textures;

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

    /**
     * @brief Get the handle of a texture which has already been generated (see generateTexture)
     * @param name The name of the texture
     * @return The texture handle (0 if not found)
     */
    GLuint getTextureHandle(std::string name);

    /**
     * Render the bounding box set of an object. Useful for debugging collisions.
     * @param boundingBoxSet The bounding box set
     */
    void render(const BoundingBoxSet &boundingBoxSet, const glm::vec3 &offset,
                const glm::vec3 &rotation, const glm::mat4x4 &rotationAdjustment);

  public:

#ifdef SMALL3D_GLFW
    GLFWwindow* getWindow();
#else
    SDL_Window* getWindow();
#endif

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
     * @brief Constructor
     * @param windowTitle The title of the game's window
     * @param width The width of the window. If width and height are not set, or set to 0, the game will run in full screen mode.
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
    Renderer(std::string windowTitle = "", int width = 0, int height = 0,
             float frustumScale = 1.0f, float zNear = 1.0f,
             float zFar = 24.0f, float zOffsetFromCamera = -1.0f,
             std::string shadersPath = "resources/shaders/");

    /**
     * @brief Destructor
     */
    ~Renderer();

    /**
     * @brief Generate a texture in OpenGL, using the given data
     * @param name The name by which the texture will be known
     * @param texture The texture data
     * @param width The width of the texture, in pixels
     * @param height The height of the texture, in pixels
     * @return The texture handle
     */
    GLuint generateTexture(std::string name, const float *texture, unsigned long width, unsigned long height);

    /**
     * @brief Render a textured quad (rectangle), using two of its corners that are diagonally opposed to each
     * other. This function can be used for rendering the ground, the sky or a splash screen for example.
     * @param name The name of the texture to be used (must have been loaded with generateTexture())
     * @param bottomLeft The coordinates for the bottom left corner of the texture
     * @param topRight The coordinates for the top right corner of the texture
     * @param perspective If set to true, use perspective rendering, otherwise use simple (orthographic) rendering.
     */
    void renderTexture(std::string name, const glm::vec3 &bottomLeft, const glm::vec3 &topRight, bool perspective = false);

    /**
     * @brief Deletes the texture indicated by the given name.
     *
     * @param	name	The name of the texture.
     */

    void deleteTexture(std::string name);
    
    /**
     * @brief Render a scene object
     * @param sceneObject The scene object
     * @param showBoundingBoxes If true, also render the bounding boxes, otherwise don't (default)
     */
    void render(SceneObject &sceneObject, bool showBoundingBoxes = false);

    /**
     * @brief Render some text on the screen. A texture will be generated, containing the given
     * text and it will be rendered at a depth z of 0.5 in an orthographic coordinate space.
     * @param text The text to be rendered
     * @param colour The colour in which the text will be rendered (r, g, b)
     * @param bottomLeft The coordinates of the bottom left corner of the text rectangle (x, y)
     * @param topRight The coordinates of the top right corner of the text rectangle (x, y)
     * @param fontSize The size of the font which will be used
     * @param fontPath Path to the TrueType font (.ttf) which will be used
     */
    void write(std::string text, glm::vec3 colour, glm::vec2 bottomLeft, glm::vec2 topRight, int fontSize=48,
                std::string fontPath = "resources/fonts/CrusoeText/CrusoeText-Regular.ttf");

    /**
     * @brief Clear a scene object from the GPU buffers (the object itself remains intact)
     * @param sceneObject The scene object
     */
    void clearBuffers(SceneObject &sceneObject);

    /**
     * @brief Clears the screen.
     */
    void clearScreen();

    /**
     * @brief Clears the screen.
     * @param colour The colour with which the screen is to be cleared
     */
    void clearScreen(glm::vec4 colour);

    /**
     * @brief This is a double buffered system and this commands swaps
     * the buffers
     */
    void swapBuffers();

  };
}
