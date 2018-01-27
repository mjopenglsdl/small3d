from conans import ConanFile, CMake
from conans.tools import ConanException

class Small3dConan(ConanFile):
    name = "small3d"
    version = "master"
    description = "A small, cross-platform 3D game engine (C++, OpenGL, GLFW) - runs on Win/MacOS/Linux"
    generators = "cmake"
    settings = "os", "arch", "build_type", "compiler"
    options = {"development": [True, False], "vulkan": [True, False]}
    default_options = "gtest:shared=False", "development=False", "vulkan=False"
    url="http://github.com/dimi309/conan-packages"
    requires = "glfw/3.2.1@bincrafters/stable", "freetype/2.8.1@bincrafters/stable", "glm/0.9.8.5@g-truc/stable", \
               "vorbis/master@dimi309/stable", "portaudio/v190600.20161030@bincrafters/stable"
    license="https://github.com/dimi309/small3d/blob/master/LICENSE"
    exports = ["small3d/*", "FindSMALL3D.cmake", "CMakeLists.txt", "LICENSE"]

    def configure(self):
        if self.settings.compiler == "gcc" and self.settings.compiler.libcxx != "libstdc++11":
            raise ConanException("When using the gcc compiler, small3d requires libstdc++11 as compiler.libcxx, in the conan.conf file or via the -s parameter.")

        if self.settings.os == "Linux" and self.settings.compiler == "clang" and self.settings.compiler.libcxx != "libstdc++11":
            raise ConanException("When using the clang compiler on Linux, small3d requires libstdc++11 as compiler.libcxx, in the conan.conf file or via the -s parameter.")

        if self.options.development:
            self.requires("gtest/1.7.0@bincrafters/stable")

        if not self.options.vulkan:
            self.requires("glew/2.1.0@dimi309/stable")

    def build(self):
        
        cmake = CMake(self)
        cmake.definitions['BUILD_FOR_VULKAN'] = self.options.vulkan
        if self.options.development:
            cmake.definitions['BUILD_TESTS'] = True
        else:
            cmake.definitions['BUILD_TESTS'] = False
        cmake.configure()
        cmake.build()

    def package(self):

        self.copy("FindSMALL3D.cmake", ".", ".")
        self.copy(pattern="*", dst="shaders", src="%s/small3d/resources/shaders" % self.build_folder, keep_path=True)
        self.copy(pattern="*.hpp", dst="include", src="%s/small3d/include" % self.build_folder, keep_path=True)
        self.copy("LICENSE*", dst="licenses",  ignore_case=True, keep_path=False)

        if self.settings.compiler == "Visual Studio":
            self.copy(pattern="*.pdb", dst="bin", keep_path=False)
            self.copy(pattern="*.lib", dst="lib", keep_path=False)
        else:
            self.copy(pattern="*.a", dst="lib", keep_path=False)

    def imports(self):
        if self.options.development and self.settings.os == "Windows":
            self.copy(pattern="*.dll", dst="bin", src="bin")
            self.copy(pattern="*.pdb", dst="bin", src="bin")
            
    def package_info(self):
        self.cpp_info.libs = ['small3d']
        if self.settings.os == "Windows":
            if self.settings.compiler == "Visual Studio":
                self.cpp_info.cppflags.append("/EHsc")
                self.cpp_info.exelinkflags.append('-NODEFAULTLIB:LIBCMTD')
                self.cpp_info.exelinkflags.append('-NODEFAULTLIB:LIBCMT')
        else:
            self.cpp_info.cppflags.append("-std=c++11")
