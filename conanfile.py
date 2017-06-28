from conans import ConanFile, CMake
from conans.tools import ConanException

class Small3dConan(ConanFile):
    name = "small3d"
    version = "master"
    description = "A small, cross-platform 3D game engine (C++, OpenGL, GLFW) - runs on Win/MacOS/Linux"
    generators = "cmake"
    settings = "os", "arch", "build_type", "compiler"
    url="http://github.com/dimi309/conan-packages"
    requires = "glfw/3.2.1@dimi309/stable", "freetype/2.6.3@lasote/stable","glew/2.0.0@dimi309/stable", \
        "libpng/1.6.23@lasote/stable","zlib/1.2.8@lasote/stable","glm/master@g-truc/stable", \
        "vorbis/1.3.5@dimi309/stable", "portaudio/rc.v190600.20161001@jgsogo/stable"
    license="https://github.com/dimi309/small3d/blob/master/LICENSE"
    exports = ["small3d/*", "FindSMALL3D.cmake", "CMakeLists.txt", "LICENSE"]

    def configure(self):
        if self.settings.os == "Windows" and self.settings.compiler != "Visual Studio":
            raise ConanException("On Windows, only Visual Studio compilation is supported for the time being.")

        if self.settings.compiler == "gcc" and self.settings.compiler.libcxx != "libstdc++11":
            raise ConanException("When using the gcc compiler, small3d requires libstdc++11 as compiler.libcxx, in the conan.conf file or via the -s parameter.")

    def build(self):
        
        cmake = CMake(self)
        self.run("cmake %s %s" % (self.conanfile_directory, cmake.command_line))
        self.run("cmake --build . %s" % cmake.build_config)

    def package(self):

        self.copy("FindSMALL3D.cmake", ".", ".")
        self.copy(pattern="*", dst="shaders", src="%s/small3d/resources/shaders" % self.conanfile_directory, keep_path=True)
        self.copy(pattern="*.hpp", dst="include", src="%s/small3d/include" % self.conanfile_directory, keep_path=True)
        self.copy("LICENSE*", dst="licenses",  ignore_case=True, keep_path=False)

        if self.settings.os == "Windows":
            self.copy(pattern="*.pdb", dst="bin", keep_path=False)
            self.copy(pattern="*.lib", dst="lib", keep_path=False)
        else:
            self.copy(pattern="*.a", dst="lib", keep_path=False)
            
    def package_info(self):
        self.cpp_info.libs = ['small3d']
        if self.settings.os == "Windows":
            self.cpp_info.cppflags.append("/EHsc")
            self.cpp_info.exelinkflags.append('-NODEFAULTLIB:LIBCMTD')
            self.cpp_info.exelinkflags.append('-NODEFAULTLIB:LIBCMT')
        else:
            self.cpp_info.cppflags.append("-std=c++11")
            if self.settings.os == "Macos":
                self.cpp_info.cppflags.append("-stdlib=libc++")
