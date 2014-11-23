/*
*  Renderer.h
*
*  Created on: 2014/10/19
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

// bii://dimitrikourk/small3d/resources/shaders/OpenGL33/perspectiveMatrixLightedShader.vert
// bii://dimitrikourk/small3d/resources/shaders/OpenGL33/textureShader.frag
// bii://dimitrikourk/small3d/resources/shaders/OpenGL33/simpleShader.vert
// bii://dimitrikourk/small3d/resources/shaders/OpenGL33/simpleShader.frag
// bii://dimitrikourk/small3d/resources/shaders/OpenGL21/perspectiveMatrixLightedShader.vert
// bii://dimitrikourk/small3d/resources/shaders/OpenGL21/textureShader.frag
// bii://dimitrikourk/small3d/resources/shaders/OpenGL21/simpleShader.vert
// bii://dimitrikourk/small3d/resources/shaders/OpenGL21/simpleShader.frag


#pragma once

#ifndef SDLANDOPENGL
#define SDLANDOPENGL
#include <dimitrikourk/glew/glew.h>
#include <miguel/sdl2/include/SDL_opengl.h>
#include <miguel/sdl2/include/SDL.h>
#endif //SDLANDOPENGL

#include <memory>
#include "SceneObject.h"
#include <vector>
#include "Logger.h"
#include <unordered_map>
#include <dimitrikourk/glm/glm/glm.hpp>

using namespace std;

namespace small3d
{

	/**
	* @class	Renderer
	*
	* @brief	Renderer class, which can render using either OpenGL v3.3 or v2.1
	*
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

		void checkForOpenGLErrors(string when, bool abort);

		/**
		* Textures used in the scene, each corresponding to the name of one of
		* the rendered models
		*/
		unordered_map<string, GLuint> *textures;

	public:

		/**
		* Constructor
		*/
		Renderer();

		/**
		* Initialise renderer (OpenGL, GLEW, etc)
		* @param width The width of the window
		* @param height The height of the window
		* @param fullScreen	Will the Renderer run in full screen mode? If set to true,
		* 					the width and height have to correspond to the active screen
		* 					resolution, in order for the scene to be displayed properly.				 
		* @param frustumScale	How much the frustum scales the items rendered
		* @param zNear			Projection plane z coordinate (use positive value)
		* @param zFar			Far end of frustum z coordinate (use positive value)
		* @param zOffsetFromCamera	The position of the projection plane with regard to the camera.
		* @param shadersPath	The path where the shaders will be stored, relative
		* 						to the application's executing directory. It
		* 						defaults to the path provided by the engine, but
		* 						it can be changed, so as to accommodate for executables
		* 						which are going to be using it. Even though the path to
		* 						the folder can be changed, the folder structure within
		* 						it and the names of the shaders must remain as provided.
		* 						The shader code can be changed, provided that their inputs
		* 						and outputs are maintained the same.
		*/
		void init(const int width, const int height, const bool fullScreen, 
			const float &frustumScale = 1.0f, const float &zNear = 1.0f, 
			const float &zFar = 24.0f, const float &zOffsetFromCamera = -1.0f,
			const string &shadersPath = "dimitrikourk/small3d/resources/shaders/");

		/**
		* @brief	Vector indicating the direction of the light in the scene.
		*/

		glm::vec3 lightDirection;

		/**
		 * @brief	The camera position in world space.
		 */

		glm::vec3 cameraPosition;

		/**
		 * @brief	The camera rotation (around the x, y and z axes)
		 */

		glm::vec3 cameraRotation;

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
		 * @fn	void Renderer::deleteTexture(const string &name);
		 *
		 * @brief	Deletes the texture indicated by the given name.
		 *
		 * @param	name	The name of the texture.
		 */

		void deleteTexture(const string &name);

		/**
		* Get the handle of a texture which has already been generated (see generateTexture)
		* @param name The name of the texture
		* @return The texture handle (0 if not found)
		*/
		GLuint getTextureHandle(const string &name);

		/**
		 * @fn	void Renderer::positionSceneObject(const glm::vec3 &offset, const glm::vec3 &rotation);
		 *
		 * @brief	Positions the scene object (sets offset and rotation)
		 *
		 * @param	offset  	The offset (x, y, z values).
		 * @param	rotation	The rotation (around the x, y and z axes).
		 */

		void positionSceneObject(const glm::vec3 &offset, const glm::vec3 &rotation);

		/**
		 * @fn	void Renderer::positionCamera();
		 *
		 * @brief	Position the camera.
		 *
		 */

		void positionCamera();

		/**
		* Render an image. The image is in effect a textured quad, since 4 vertex positions are
		* passed to this method, in order to define its position and size.
		* @param vertices The vertices
		* @param textureName The name of the texture, containing the image (must have been loaded with 
		* 					 generateTexture())
		* @param perspective If set to true, use perspective rendering, otherwise use simple (orthographic) rendering.
		* @param offset	The offset (position) at which the quad of the image will be drawn.
		*/
		void renderImage(const float *vertices, const string &textureName, const bool &perspective = false, 
			const glm::vec3 &offset = glm::vec3(0.0f, 0.0f, 0.0f));

		/**
		* Render a scene object
		* @param sceneObject The scene object
		*/
		void renderSceneObject(shared_ptr<SceneObject> sceneObject);

		/**
		* Clears the screen.
		*/
		void clearScreen();

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
