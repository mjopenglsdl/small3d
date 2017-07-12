/*
 *  Renderer.hpp
 *
 *  Created on: 2014/10/19
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#define GLM_FORCE_RADIANS

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Logger.hpp"
#include "Image.hpp"
#include "Model.hpp"
#include <unordered_map>
#include <vector>
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

    std::string basePath;
    
    GLFWwindow* window;

    GLuint perspectiveProgram;

    GLuint orthographicProgram;

    bool isOpenGL33Supported;

    bool noShaders;

    float frustumScale;

    float zNear;

    float zFar;

    float zOffsetFromCamera;

    FT_Library library;

    std::vector<float> textMemory;
    
    std::unordered_map<std::string, FT_Face> fontFaces;

    /**
     * @brief Load a shader's source code from a file into a string
     * @param fileLocation The file's location, relative to the game path
     * @return String containing the shader's source code
     */
    std::string loadShaderFromFile(std::string fileLocation);

    /**
     * @brief Compile a shader's source code
     * @param shaderSource String containing the shader's source code
     * @param shaderType Type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER - the latter for OpenGL 3.3)
     * @return OpenGL shader reference
     */
    GLuint compileShader(std::string shaderSource, const GLenum shaderType);

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

    void positionNextObject(const glm::vec3 &offset, const glm::vec3 &rotation);

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

    GLuint generateTexture(std::string name, const float *data, unsigned long width, unsigned long height);

    /**
     * Hidden constructor, because Renderer is a singleton
     */
    Renderer(std::string windowTitle, int width, int height, float frustumScale, float zNear,
             float zFar, float zOffsetFromCamera, std::string shadersPath, std::string basePath);
    
    Renderer() {};
    
  public:
    
    Renderer(Renderer const&) = delete;
    void operator=(Renderer const&) = delete;
    Renderer(Renderer &&) = delete;
    void operator=(Renderer &&) = delete;
    
    // Get the GLFW window object, associated with the Renderer.
    GLFWwindow* getWindow();

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
     * @brief Get the isntance of the Renderer (the Renderer is a singleton).
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
     * @param basePath          The path under which all accessed files and directories are
     *                          to be found. If this is not set, it is assumed to be the directory
     *                          from where the execution command is entered.
     * @return The Renderer object. It can only be assigned to a pointer by its address (Renderer *r = &Renderer::getInstance(...), 
     *         sicne declaring another Renderer variable and assigning to it would invoke the default constructor, which has 
     *         been deleted.
     */
    static Renderer& getInstance(std::string windowTitle = "", int width = 0, int height = 0,
				 float frustumScale = 1.0f, float zNear = 1.0f,
				 float zFar = 24.0f, float zOffsetFromCamera = -1.0f,
				 std::string shadersPath = "resources/shaders/", std::string basePath = "");

    /**
     * @brief Destructor
     */
    ~Renderer();

    /**
     * @brief Generate a texture on the GPU from the given image
     * @param name The name by which the texture will be known
     * @param image The image from which the texture will be generated
     */
    void generateTexture(std::string name, const Image image);

    /**
     * @brief Render a textured quad (rectangle), using two of its corners that are diagonally opposed to each
     * other. This function can be used for rendering the ground, the sky or a splash screen for example.
     * @param name The name of the texture to be used (must have been loaded with generateTexture())
     * @param topLeft Where to place the top left corner of the texture
     * @param bottomRight Where to place the bottom right corner of the texture
     * @param perspective If set to true, use perspective rendering. Otherwise use orthographic rendering.
     */
    void renderTexture(std::string name, const glm::vec3 topLeft, const glm::vec3 bottomRight, bool perspective = false);

    /**
     * @brief Deletes the texture indicated by the given name.
     *
     * @param	name	The name of the texture.
     */

    void deleteTexture(std::string name);

    /**
     * @brief Is OpenGL 3.3 supported?
     *
     * @return True if OpenGL 3.3 is supported, false otherwise
     */

    bool supportsOpenGL33();

    /**
     * @brief Render a single-coloured surface.
     *
     * @param colour The colour of the surface (vector of 3 components for r, g, b)
     * @param topLeft Where to place the top left corner of the surface
     * @param bottomRight Where to place the bottom right corner of the surface
     * @param perspective If set to true, use perspective rendering. Otherwise use orthographic rendering.
     */
    
    void renderSurface(glm::vec3 colour, const glm::vec3 topLeft, const glm::vec3 bottomRight, bool perspective = false);
    
    /**
     * @brief Render a Model
     * @param model The model
     * @param offset The offset (position) where to draw the model
     * @param rotation Rotation (x, y, z)
     * @param colour The colour of the model
     * @param textureName The name of the texture to attach to the model (optional). The texture has to have been generated already.
     *                    If this is set, the colour parameter will be ignored
     */
    void render(Model &model, glm::vec3 offset, glm::vec3 rotation, glm::vec4 colour, std::string textureName="");

    /**
     * @brief Render a Model
     * @param model The model
     * @param offset The offset (position) where to draw the model
     * @param rotation Rotation (x, y, z)
     * @param textureName The name of the texture to attach to the model. The texture has to have been generated already.
     */
    void render(Model &model, glm::vec3 offset, glm::vec3 rotation, std::string textureName);

    /**
     * @brief Render some text on the screen.
     * @param text The text to be rendered
     * @param colour The colour in which the text will be rendered (r, g, b)
     * @param topLeft Where to place the top left corner of the text rectangle
     * @param bottomRight Where to place the bottom right corner of the text rectangle
     * @param fontSize The size of the font which will be used
     * @param fontPath Path to the TrueType font (.ttf) which will be used
     */
    void write(std::string text, glm::vec3 colour, glm::vec2 topLeft, glm::vec2 bottomRight, int fontSize=48,
	       std::string fontPath = "resources/fonts/CrusoeText/CrusoeText-Regular.ttf");

    /**
     * @brief Clear a Model from the GPU buffers (the object itself remains intact)
     * @param sceneObject The scene object
     */
    void clearBuffers(Model &model);

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
     * @brief This is a double buffered system and this command swaps
     * the buffers.
     */
    void swapBuffers();

  };
  
}
