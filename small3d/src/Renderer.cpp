/*
 * Renderer.cpp
 *
 *  Created on: 2014/10/19
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "Renderer.hpp"
#include <stdexcept>
#include <fstream>
#include "MathFunctions.hpp"
#include <glm/gtc/type_ptr.hpp>

using namespace std;

namespace small3d {

  void error_callback(int error, const char* description)
  {
    LOGERROR(string(description));
  }
  
  string openglErrorToString(GLenum error);
  
  Renderer::Renderer(string windowTitle, int width, int height,
                     float frustumScale , float zNear,
                     float zFar, float zOffsetFromCamera,
                     string shadersPath, string basePath) {
    
    isOpenGL33Supported = false;
    window = 0;
    perspectiveProgram = 0;
    orthographicProgram = 0;
    textures = new unordered_map<string, GLuint>();
    noShaders = false;
    lightDirection = glm::vec3(0.0f, 0.9f, 0.2f);
    cameraPosition = glm::vec3(0, 0, 0);
    cameraRotation = glm::vec3(0, 0, 0);
    lightIntensity = 1.0f;
    
    this->basePath = basePath;
    
    init(width, height, windowTitle, frustumScale, zNear, zFar, zOffsetFromCamera, shadersPath);
    
    FT_Error ftError = FT_Init_FreeType( &library );
    
    if(ftError != 0)
      {
	throw runtime_error("Unable to initialise font system");
      }
  }
  
  Renderer& Renderer::getInstance(std::string windowTitle, int width, int height, float frustumScale, float zNear,
                                  float zFar, float zOffsetFromCamera, std::string shadersPath, std::string basePath) {
    static Renderer instance(windowTitle, width, height, frustumScale, zNear, zFar, zOffsetFromCamera, shadersPath, basePath);
    return instance;
  }
  
  Renderer::~Renderer() {
    LOGDEBUG("Renderer destructor running");
    for (unordered_map<string, GLuint>::iterator it = textures->begin();
         it != textures->end(); ++it) {
      LOGDEBUG("Deleting texture " + it->first);
      glDeleteTextures(1, &it->second);
    }
    delete textures;
    
    for(auto idFacePair : fontFaces) {
      FT_Done_Face(idFacePair.second);
    }
    
    FT_Done_FreeType(library);
    
    if (!noShaders) {
      glUseProgram(0);
    }
    
    if (orthographicProgram != 0) {
      glDeleteProgram(orthographicProgram);
    }
    
    if (perspectiveProgram != 0) {
      glDeleteProgram(perspectiveProgram);
    }
    
    glfwTerminate();
    
  }
  
  GLFWwindow* Renderer::getWindow() {
    return window;
  }
  
  string Renderer::loadShaderFromFile(string fileLocation) {
    initLogger();
    string shaderSource = "";
    ifstream file((basePath + fileLocation).c_str());
    string line;
    if (file.is_open()) {
      while (getline(file, line)) {
        shaderSource += line + "\n";
      }
    }
    return shaderSource;
  }
  
  string Renderer::getProgramInfoLog(const GLuint linkedProgram) const {
    
    GLint infoLogLength;
    
    glGetProgramiv(linkedProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    GLchar *infoLog = new GLchar[infoLogLength + 1];
    
    GLsizei lengthReturned = 0;
    
    glGetProgramInfoLog(linkedProgram, infoLogLength, &lengthReturned, infoLog);
    
    string infoLogStr(infoLog);
    
    if (lengthReturned == 0) {
      infoLogStr = "(No info)";
    }
    
    delete[] infoLog;
    
    return infoLogStr;
    
  }
  
  string Renderer::getShaderInfoLog(const GLuint shader) const {
    
    GLint infoLogLength;
    
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    GLchar *infoLog = new GLchar[infoLogLength + 1];
    
    GLsizei lengthReturned = 0;
    
    glGetShaderInfoLog(shader, infoLogLength, &lengthReturned, infoLog);
    
    string infoLogStr(infoLog);
    
    if (lengthReturned == 0) {
      infoLogStr = "(No info)";
    }
    
    delete[] infoLog;
    
    return infoLogStr;
    
  }
  
  GLuint Renderer::compileShader(string shaderSourceFile, const GLenum shaderType) {
    
    GLuint shader = glCreateShader(shaderType);
    
    string shaderSource = this->loadShaderFromFile(shaderSourceFile);
    
    if (shaderSource.length() == 0) {
      throw runtime_error("Shader source file '" + shaderSourceFile + "' is empty or not found.");
    }
    
    const char *shaderSourceChars = shaderSource.c_str();
    glShaderSource(shader, 1, &shaderSourceChars, NULL);
    
    glCompileShader(shader);
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE ) {
      
      throw runtime_error(
			  "Failed to compile shader:\n" + shaderSource + "\n"
			  + this->getShaderInfoLog(shader));
    }
    else {
      LOGDEBUG("Shader " + shaderSourceFile + " compiled successfully.");
    }
    
    return shader;
  }
  
  void Renderer::detectOpenGLVersion() {
#ifdef __APPLE__
    glewExperimental = GL_TRUE;
#endif
    GLenum initResult = glewInit();
    
    if (initResult != GLEW_OK) {
      throw runtime_error("Error initialising GLEW");
    }
    else {
      string glewVersion = reinterpret_cast<char *>(const_cast<GLubyte*>(glewGetString(GLEW_VERSION)));
      LOGINFO("Using GLEW version " + glewVersion);
    }
    
    checkForOpenGLErrors("initialising GLEW", false);
    
    string glVersion = reinterpret_cast<char *>(const_cast<GLubyte*>(glGetString(GL_VERSION)));
    glVersion = "OpenGL version supported by machine: " + glVersion;
    LOGINFO(glVersion);
    
    if (glewIsSupported("GL_VERSION_3_3")) {
      LOGINFO("Ready for OpenGL 3.3");
      isOpenGL33Supported = true;
    }
    else if (glewIsSupported("GL_VERSION_2_1")) {
      LOGINFO("Ready for OpenGL 2.1");
    }
    else {
      noShaders = true;
      throw runtime_error(
			  "None of the supported OpenGL versions (3.3 nor 2.1) are available.");
    }
  }
  
  void Renderer::checkForOpenGLErrors(string when, bool abort) {
    GLenum errorCode = glGetError();
    if (errorCode != GL_NO_ERROR) {
      LOGERROR("OpenGL error while " + when);
      
      do {
        LOGERROR(openglErrorToString(errorCode));
        errorCode = glGetError();
      }
      while (errorCode != GL_NO_ERROR);
      
      if (abort)
        throw runtime_error("OpenGL error while " + when);
    }
  }
  
  void Renderer::initWindow(int &width, int &height, const string &windowTitle) {
    
    glfwSetErrorCallback(error_callback);
    
    if (!glfwInit()){
      throw runtime_error("Unable to initialise GLFW");
    }
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    bool fullScreen = false;
    
    GLFWmonitor *monitor = nullptr; // If NOT null, a full-screen window will be created.
    
    if ((width == 0 && height != 0) || (width != 0 && height == 0)) {
      throw runtime_error("Screen width and height both have to be equal or not equal to zero at the same time.");
    }
    else if (width == 0) {
      
      fullScreen = true;
      
      monitor = glfwGetPrimaryMonitor();
      
      const GLFWvidmode* mode = glfwGetVideoMode(monitor);
      width = mode->width;
      height = mode->height;
      
      LOGINFO("Detected screen width " + intToStr(width) + " and height " + intToStr(height));
    }
    
    window = glfwCreateWindow(width, height, windowTitle.c_str(), monitor, nullptr);
    if (!window){
      throw runtime_error(string("Unable to create GLFW window"));
    }
    
    glfwMakeContextCurrent(window);
    
  }
  
  void Renderer::init(int width, int height, string windowTitle,
                      float frustumScale, float zNear,
                      float zFar, float zOffsetFromCamera,
                      string shadersPath) {
    
    int screenWidth = width;
    int screenHeight = height;
    
    this->initWindow(screenWidth, screenHeight, windowTitle);
    
    this->frustumScale = frustumScale;
    this->zNear = zNear;
    this->zFar = zFar;
    this->zOffsetFromCamera = zOffsetFromCamera;
    
    this->detectOpenGLVersion();
    
    string vertexShaderPath;
    string fragmentShaderPath;
    string simpleVertexShaderPath;
    string simpleFragmentShaderPath;
    
    if (isOpenGL33Supported) {
      vertexShaderPath = shadersPath + "OpenGL33/perspectiveMatrixLightedShader.vert";
      fragmentShaderPath = shadersPath + "OpenGL33/textureShader.frag";
      simpleVertexShaderPath =
	shadersPath + "OpenGL33/simpleShader.vert";
      simpleFragmentShaderPath = shadersPath + "OpenGL33/simpleShader.frag";
      
    }
    else {
      vertexShaderPath =
	shadersPath + "OpenGL21/perspectiveMatrixLightedShader.vert";
      fragmentShaderPath = shadersPath + "OpenGL21/textureShader.frag";
      simpleVertexShaderPath =
	shadersPath + "OpenGL21/simpleShader.vert";
      simpleFragmentShaderPath = shadersPath + "OpenGL21/simpleShader.frag";
    }
    
    glViewport(0, 0, static_cast<GLsizei>(screenWidth), static_cast<GLsizei>(screenHeight));
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 10.0f);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
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
    if (status == GL_FALSE) {
      throw runtime_error("Failed to link program:\n" + this->getProgramInfoLog(perspectiveProgram));
    }
    else {
      LOGDEBUG("Linked main rendering program successfully");
      
      glUseProgram(perspectiveProgram);
      
      // Perspective
      
      GLint perspectiveMatrixUniform = glGetUniformLocation(perspectiveProgram,
                                                            "perspectiveMatrix");
      
      float perspectiveMatrix[16];
      memset(perspectiveMatrix, 0, sizeof(float) * 16);
      perspectiveMatrix[0] = frustumScale;
      perspectiveMatrix[5] = frustumScale * ROUND_2_DECIMAL(screenWidth / screenHeight);
      perspectiveMatrix[10] = (zNear + zFar) / (zNear - zFar);
      perspectiveMatrix[14] = 2.0f * zNear * zFar / (zNear - zFar);
      perspectiveMatrix[11] = zOffsetFromCamera;
      
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
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    
    // Program (with shaders) for orthographic rendering for text
    
    GLuint simpleVertexShader = compileShader(simpleVertexShaderPath,
                                              GL_VERTEX_SHADER);
    GLuint simpleFragmentShader = compileShader(simpleFragmentShaderPath,
                                                GL_FRAGMENT_SHADER);
    
    orthographicProgram = glCreateProgram();
    glAttachShader(orthographicProgram, simpleVertexShader);
    glAttachShader(orthographicProgram, simpleFragmentShader);
    
    glLinkProgram(orthographicProgram);
    
    glGetProgramiv(orthographicProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
      throw runtime_error("Failed to link program:\n" + this->getProgramInfoLog(orthographicProgram));
    }
    else {
      LOGDEBUG("Linked orthographic rendering program successfully");
    }
    glDetachShader(orthographicProgram, simpleVertexShader);
    glDetachShader(orthographicProgram, simpleFragmentShader);
    glDeleteShader(simpleVertexShader);
    glDeleteShader(simpleFragmentShader);
    glUseProgram(0);
  }
  
  GLuint Renderer::generateTexture(string name, const float* data, unsigned long width, unsigned long height) {
    
    GLuint textureHandle;
    
    glGenTextures(1, &textureHandle);
    
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    
    GLint internalFormat = isOpenGL33Supported ? GL_RGBA32F : GL_RGBA;
    
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_RGBA,
                 GL_FLOAT, data);
    
    textures->insert(make_pair(name, textureHandle));
    
    return textureHandle;
  }

  void Renderer::generateTexture(std::string name, const Image image) {
    this->generateTexture(name, image.getData(), image.getWidth(), image.getHeight());
  }
  
  void Renderer::deleteTexture(string name) {
    unordered_map<string, GLuint>::iterator nameTexturePair = textures->find(name);
    
    if (nameTexturePair != textures->end()) {
      glDeleteTextures(1, &(nameTexturePair->second));
      textures->erase(name);
    }
  }
  
  GLuint Renderer::getTextureHandle(string name) {
    GLuint handle = 0;
    
    unordered_map<string, GLuint>::iterator nameTexturePair = textures->find(name);
    
    if (nameTexturePair != textures->end()) {
      handle = nameTexturePair->second;
    }
    
    return handle;
  }
  
  bool Renderer::supportsOpenGL33() {
    return isOpenGL33Supported;
  }
  
  void Renderer::positionNextObject(const glm::vec3 &offset, const glm::vec3 &rotation) {
    // Rotation
    
    GLint xRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
                                                        "xRotationMatrix");
    glUniformMatrix4fv(xRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateX(rotation.x)));
    
    GLint yRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
                                                        "yRotationMatrix");
    glUniformMatrix4fv(yRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateY(rotation.y)));
    
    GLint zRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
                                                        "zRotationMatrix");
    glUniformMatrix4fv(zRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateZ(rotation.z)));
    
    GLint offsetUniform = glGetUniformLocation(perspectiveProgram, "offset");
    glUniform3fv(offsetUniform, 1, glm::value_ptr(offset));
  }
  
  
  void Renderer::positionCamera() {
    // Camera rotation
    
    GLint xCameraRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
                                                              "xCameraRotationMatrix");
    GLint yCameraRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
                                                              "yCameraRotationMatrix");
    GLint zCameraRotationMatrixUniform = glGetUniformLocation(perspectiveProgram,
                                                              "zCameraRotationMatrix");
    
    
    glUniformMatrix4fv(xCameraRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateX(-cameraRotation.x)));
    glUniformMatrix4fv(yCameraRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateY(-cameraRotation.y)));
    glUniformMatrix4fv(zCameraRotationMatrixUniform, 1, GL_TRUE, glm::value_ptr(rotateZ(-cameraRotation.z)));
    
    // Camera position
    
    GLint cameraPositionUniform = glGetUniformLocation(perspectiveProgram, "cameraPosition");
    glUniform3fv(cameraPositionUniform, 1, glm::value_ptr(cameraPosition));
  }
  
  
  void Renderer::renderTexture(string name, const glm::vec3 topLeft, const glm::vec3 bottomRight,
                               bool perspective) {
    
    float vertices[16] = {
      bottomRight.x, bottomRight.y, bottomRight.z, 1.0f,
      bottomRight.x, topLeft.y, topLeft.z, 1.0f,
      topLeft.x, topLeft.y, topLeft.z, 1.0f,
      topLeft.x, bottomRight.y, bottomRight.z, 1.0f
    };
    
    glUseProgram(perspective ? perspectiveProgram : orthographicProgram);
    
    GLuint vao = 0;
    if (isOpenGL33Supported) {
      // Generate VAO
      glGenVertexArrays(1, &vao);
      glBindVertexArray(vao);
    }
    
    glEnableVertexAttribArray(0);
    
    GLuint boxBuffer = 0;
    glGenBuffers(1, &boxBuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, boxBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * 16,
                 &vertices[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    unsigned int vertexIndexes[6] =
      {
	2, 3, 0,
	0, 1, 2
      };
    
    GLuint indexBufferObject = 0;
    
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(unsigned int) * 6, vertexIndexes, GL_STATIC_DRAW);
    
    GLuint textureHandle = getTextureHandle(name);
    
    if (textureHandle == 0) {
      throw runtime_error("Texture " + name + "has not been generated");
    }
    
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    
    float textureCoords[8] =
      {
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f
      };
    
    GLuint coordBuffer = 0;
    
    glGenBuffers(1, &coordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * 8,
                 textureCoords,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(perspective ? 2 : 1);
    glVertexAttribPointer(perspective ? 2 : 1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    if (perspective) {
      // Find the colour uniform
      GLint colourUniform = glGetUniformLocation(perspectiveProgram, "colour");
      
      // "Disable" colour since there is a texture
      glUniform4fv(colourUniform, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
      
      // Lighting
      GLint lightDirectionUniform = glGetUniformLocation(perspectiveProgram,
                                                         "lightDirection");
      glUniform3fv(lightDirectionUniform, 1,
                   glm::value_ptr(lightDirection));
      
      GLint lightIntensityUniform = glGetUniformLocation(perspectiveProgram, "lightIntensity");
      glUniform1f(lightIntensityUniform, lightIntensity);
      
      positionNextObject(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
      positionCamera();
    }
    
    glDrawElements(GL_TRIANGLES,
                   6, GL_UNSIGNED_INT, 0);
    
    glDeleteBuffers(1, &indexBufferObject);
    glDeleteBuffers(1, &boxBuffer);
    glDeleteBuffers(1, &coordBuffer);
    
    
    glDisableVertexAttribArray(perspective ? 2 : 1);
    glDisableVertexAttribArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    if (isOpenGL33Supported) {
      glDeleteVertexArrays(1, &vao);
      glBindVertexArray(0);
    }
    
    checkForOpenGLErrors("rendering image", true);
  }
  
  void Renderer::renderSurface(glm::vec3 colour, const glm::vec3 topLeft, const glm::vec3 bottomRight, bool perspective) {
    float vertices[16] = {
      bottomRight.x, bottomRight.y, bottomRight.z, 1.0f,
      bottomRight.x, topLeft.y, topLeft.z, 1.0f,
      topLeft.x, topLeft.y, topLeft.z, 1.0f,
      topLeft.x, bottomRight.y, bottomRight.z, 1.0f
    };
    
    glUseProgram(perspective ? perspectiveProgram : orthographicProgram);
    
    GLuint vao = 0;
    if (isOpenGL33Supported) {
      // Generate VAO
      glGenVertexArrays(1, &vao);
      glBindVertexArray(vao);
    }
    
    glEnableVertexAttribArray(0);
    
    GLuint boxBuffer = 0;
    glGenBuffers(1, &boxBuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, boxBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * 16,
                 &vertices[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    unsigned int vertexIndexes[6] =
      {
	0, 1, 2,
	2, 3, 0
      };
    
    GLuint indexBufferObject = 0;
    
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(unsigned int) * 6, vertexIndexes, GL_STATIC_DRAW);
    
    // Find the colour uniform
    GLint colourUniform = glGetUniformLocation(perspective ? perspectiveProgram : orthographicProgram, "colour");
    
    // Set the colour
    glUniform4fv(colourUniform, 1, glm::value_ptr(glm::vec4(colour, 1.0f)));
    
    if (perspective) {
      
      // Lighting
      GLint lightDirectionUniform = glGetUniformLocation(perspectiveProgram,
                                                         "lightDirection");
      glUniform3fv(lightDirectionUniform, 1,
                   glm::value_ptr(lightDirection));
      
      GLint lightIntensityUniform = glGetUniformLocation(perspectiveProgram, "lightIntensity");
      glUniform1f(lightIntensityUniform, lightIntensity);
      
      positionNextObject(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
      positionCamera();
    }
    
    glDrawElements(GL_TRIANGLES,
                   6, GL_UNSIGNED_INT, 0);
    
    // Clear the colour uniform
    glUniform4fv(colourUniform, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
    
    
    glDeleteBuffers(1, &indexBufferObject);
    glDeleteBuffers(1, &boxBuffer);
    
    glDisableVertexAttribArray(0);
    
    if (isOpenGL33Supported) {
      glDeleteVertexArrays(1, &vao);
      glBindVertexArray(0);
    }
    
    checkForOpenGLErrors("rendering surface", true);
    
  }
  
  void Renderer::render(Model &model, glm::vec3 offset, glm::vec3 rotation, glm::vec4 colour, string textureName) {
    
    glUseProgram(perspectiveProgram);
    
    bool alreadyInGPU = true;
    bool copyData = false;
    
    if (model.positionBufferObjectId == 0) {
      alreadyInGPU = false;
      copyData = true;
    }
    
    // Either GPU data gets corrupted between frames on some older chipsets, or I am doing
    // something wrong for OpenGL 2.1 and I have not figured out what it
    // is. But re-copying data to the buffers, even for non-animated objects
    // resolves the issue. (or maybe not)
    // if (!isOpenGL33Supported) copyData = true;
    
    if (!alreadyInGPU) {
      if (isOpenGL33Supported) {
        glGenVertexArrays(1, &model.vaoId);
      }
      glGenBuffers(1, &model.indexBufferObjectId);
      glGenBuffers(1, &model.positionBufferObjectId);
      glGenBuffers(1, &model.normalsBufferObjectId);
      glGenBuffers(1, &model.uvBufferObjectId);
    }
    
    if (isOpenGL33Supported) {
      glBindVertexArray(model.vaoId);
    }
    
    if (copyData) {
      
      // Vertices
      glBindBuffer(GL_ARRAY_BUFFER, model.positionBufferObjectId);
      glBufferData(GL_ARRAY_BUFFER,
                   model.vertexDataSize,
                   model.vertexData.data(),
                   GL_STATIC_DRAW);
      
      // Vertex indexes
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.indexBufferObjectId);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   model.indexDataSize,
                   model.indexData.data(),
                   GL_STATIC_DRAW);
      
      // Normals
      glBindBuffer(GL_ARRAY_BUFFER, model.normalsBufferObjectId);
      if (copyData) {
        glBufferData(GL_ARRAY_BUFFER,
                     model.normalsDataSize,
                     model.normalsData.data(),
                     GL_STATIC_DRAW);
      }
    }
    
    // Attribute - vertex
    glBindBuffer(GL_ARRAY_BUFFER, model.positionBufferObjectId);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Attribute - normals
    glBindBuffer(GL_ARRAY_BUFFER, model.normalsBufferObjectId);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    
    
    // Find the colour uniform
    GLint colourUniform = glGetUniformLocation(perspectiveProgram, "colour");
    
    
    if (textureName != "") {
      
      // "Disable" colour since there is a texture
      glUniform4fv(colourUniform, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
      
      GLuint textureId = this->getTextureHandle(textureName);
      
      glBindTexture(GL_TEXTURE_2D, textureId);
      
      // UV Coordinates
      
      glBindBuffer(GL_ARRAY_BUFFER, model.uvBufferObjectId);
      
      if (copyData) {
        glBufferData(GL_ARRAY_BUFFER,
                     model.textureCoordsDataSize,
                     model.textureCoordsData.data(),
                     GL_STATIC_DRAW);
      }
      
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
      
    }
    else {
      // If there is no texture, use the given colour
      glUniform4fv(colourUniform, 1, glm::value_ptr(colour));
    }
    
    // Lighting
    GLint lightDirectionUniform = glGetUniformLocation(perspectiveProgram,
                                                       "lightDirection");
    glUniform3fv(lightDirectionUniform, 1,
                 glm::value_ptr(lightDirection));
    
    GLint lightIntensityUniform = glGetUniformLocation(perspectiveProgram, "lightIntensity");
    glUniform1f(lightIntensityUniform, lightIntensity);
    
    positionNextObject(offset, rotation);
    
    positionCamera();
    
    // Throw an exception if there was an error in OpenGL, during
    // any of the above.
    checkForOpenGLErrors("rendering scene", true);
    
    // Draw
    glDrawElements(GL_TRIANGLES,
                   static_cast<GLsizei>(model.indexData.size()),
                   GL_UNSIGNED_INT, 0);
    
    // Clear stuff
    if (textureName != "") {
      glDisableVertexAttribArray(2);
    }
    
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    
    glUseProgram(0);
    
  }

  void Renderer::render(Model &model, glm::vec3 offset, glm::vec3 rotation, string textureName) {

    this->render(model, offset, rotation, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), textureName);
  }
  
  void Renderer::write(string text, glm::vec3 colour, glm::vec2 topLeft, glm::vec2 bottomRight,
                       int fontSize, string fontPath)
  {
    
    string faceId = intToStr(fontSize) + fontPath;
    
    unordered_map<string, FT_Face>::iterator idFacePair = fontFaces.find(faceId);
    
    FT_Face face;
    
    FT_Error error;
    
    if (idFacePair == fontFaces.end()) {
      
      string faceFullPath = basePath + fontPath;
      LOGDEBUG("Loading font from " + faceFullPath);
      
      error = FT_New_Face(library, faceFullPath.c_str(), 0, &face);
      
      if (error != 0) {
        throw runtime_error("Failed to load font from " + faceFullPath);
      }
      else{
        LOGDEBUG("Font loaded successfully");
        fontFaces.insert(make_pair(faceId, face));
      }
    } else {
      face = idFacePair->second;
    }
    
    // Multiplying by 64 to convert to 26.6 fractional points. Using 100dpi.
    error = FT_Set_Char_Size(face, 64 * fontSize, 0, 100, 0);
    
    if (error != 0) {
      throw runtime_error("Failed to set font size.");
    }
    
    unsigned long width = 0, height =0;
    
    // Figure out bitmap dimensions
    for(char &c: text) {
      
      error = FT_Load_Char(face, (FT_ULong) c, FT_LOAD_RENDER);
      
      if (error != 0) {
        throw runtime_error("Failed to load character glyph.");
      }
      
      FT_GlyphSlot slot = face->glyph;
      
      width += slot->advance.x / 64;
      
      if (height < static_cast<unsigned long>(slot->bitmap.rows))
        height = slot->bitmap.rows;
    }
    
    textMemory.resize(4 * width * height * sizeof(float));
    
    memset(&textMemory[0], 0, 4 * width * height * sizeof(float));
    
    unsigned long totalAdvance = 0;
    
    for(char &c: text) {
      error = FT_Load_Char(face, (FT_ULong) c, FT_LOAD_RENDER);
      if (error != 0) {
        throw runtime_error("Failed to load character glyph.");
      }
      
      FT_GlyphSlot slot = face->glyph;
      
      if (slot->bitmap.width * slot->bitmap.rows > 0) {
        for (int row = 0; row < static_cast<int>(slot->bitmap.rows); ++row){
          for (int col = 0; col < static_cast<int>(slot->bitmap.width); ++col) {
            glm::vec4 colourAlpha = glm::vec4(colour, 0.0f);
            colourAlpha.a = floorf(100.0f *
                                   (static_cast<float>(slot->bitmap.buffer[row * slot->bitmap.width + col]) / 255.0f) + 0.5f) / 100.0f;
            memcpy(
                   &textMemory[4 * width * (height - static_cast<unsigned long>(slot->bitmap_top)
                                            + static_cast<unsigned long>(row)) // row position
                               + totalAdvance + 4 * (static_cast<unsigned long>(col)
                                                     + static_cast<unsigned long>(slot->bitmap_left)) // column position
                               ],
                   glm::value_ptr(colourAlpha),
                   4 * sizeof(float));
          }
        }
      }
      totalAdvance += 4 * static_cast<unsigned long>(slot->advance.x / 64);
      
    }
    
    string textureName = intToStr(fontSize) + "text_" + text;
    
    generateTexture(textureName, &textMemory[0], width, height);
    
    renderTexture(textureName, glm::vec3(topLeft.x, topLeft.y, -0.5f),
                  glm::vec3(bottomRight.x, bottomRight.y, -0.5f));
    
    deleteTexture(textureName);
  }
  
  void Renderer::clearBuffers(Model &model) {
    
    if (model.positionBufferObjectId != 0) {
      glDeleteBuffers(1, &model.positionBufferObjectId);
      model.positionBufferObjectId = 0;
    }
    
    if (model.indexBufferObjectId != 0) {
      glDeleteBuffers(1, &model.indexBufferObjectId);
      model.indexBufferObjectId = 0;
    }
    if (model.normalsBufferObjectId != 0) {
      glDeleteBuffers(1, &model.normalsBufferObjectId);
      model.normalsBufferObjectId = 0;
    }
    
    if (model.uvBufferObjectId != 0) {
      glDeleteBuffers(1, &model.uvBufferObjectId);
      model.uvBufferObjectId = 0;
    }
    
    if (isOpenGL33Supported) {
      if (model.vaoId != 0) {
        glDeleteVertexArrays(1, &model.vaoId);
        model.vaoId = 0;
      }
    }
    
  }
  
  void Renderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  
  void Renderer::clearScreen(glm::vec4 colour) {
    
    glClearColor(colour.r, colour.g, colour.b, colour.a);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  
  void Renderer::swapBuffers() {
    glfwSwapBuffers(window);
    
  }
  
  /**
   * Convert error enum returned from OpenGL to a readable string error message.
   * @param error The error code returned from OpenGL
   */
  string openglErrorToString(GLenum error) {
    string errorString;
    
    switch (error) {
    case GL_NO_ERROR:
      errorString = "GL_NO_ERROR: No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
      break;
    case GL_INVALID_ENUM:
      errorString = "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
      break;
    case GL_INVALID_VALUE:
      errorString = "GL_INVALID_VALUE: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
      break;
    case GL_INVALID_OPERATION:
      errorString = "GL_INVALID_OPERATION: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      errorString = "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
      break;
    case GL_OUT_OF_MEMORY:
      errorString = "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
      break;
    case GL_STACK_UNDERFLOW:
      errorString = "GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
      break;
    case GL_STACK_OVERFLOW:
      errorString = "GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
      break;
    default:
      errorString = "Unknown error";
      break;
    }
    return errorString;
  }
  
}
