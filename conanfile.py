from conans import ConanFile, CMake
from conans.tools import ConanException

class Small3dConan(ConanFile):
    name = "small3d"
    version = "master"
    description = "A small, cross-platform 3D game engine (C++, OpenGL, GLFW) - runs on Win/MacOS/Linux"
    generators = "cmake"
    settings = "os", "arch", "build_type", "compiler"
    default_options = "gtest:shared=False"
    url="http://github.com/dimi309/conan-packages"
    requires = "glfw/master@dimi309/stable", "freetype/2.6.3@lasote/stable","glew/2.1.0@dimi309/stable", \
        "libpng/1.6.23@lasote/stable","zlib/1.2.8@lasote/stable","glm/0.9.8@g-truc/stable", \
        "vorbis/master@dimi309/stable", "portaudio/rc.v190600.20161001@jgsogo/stable"
    license="https://github.com/dimi309/small3d/blob/master/LICENSE"
    exports = ["small3d/*", "FindSMALL3D.cmake", "CMakeLists.txt", "LICENSE"]

    def configure(self):
        if self.settings.os == "Windows" and self.settings.compiler != "Visual Studio":
            raise ConanException("On Windows, only Visual Studio compilation is supported for the time being.")

        if self.settings.compiler == "gcc" and self.settings.compiler.libcxx != "libstdc++11":
            raise ConanException("When using the gcc compiler, small3d requires libstdc++11 as compiler.libcxx, in the conan.conf file or via the -s parameter.")

        if self.settings.os == "Linux" and self.settings.compiler == "clang" and self.settings.compiler.libcxx != "libstdc++11":
            raise ConanException("When using the clang compiler on Linux, small3d requires libstdc++11 as compiler.libcxx, in the conan.conf file or via the -s parameter.")

        if self.scope.dev:
            self.requires("gtest/1.8.0@lasote/stable")

    def build(self):
        
        cmake = CMake(self)
        flag_build_tests = "-DBUILD_TESTS=ON" if self.scope.dev else "-DBUILD_TESTS=OFF"
        self.run("cmake %s %s %s" % (self.conanfile_directory, flag_build_tests, cmake.command_line))
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

    def imports(self):
        if self.scope.dev and self.settings.os == "Windows":
            self.copy(pattern="*.dll", dst="bin", src="bin")
            self.copy(pattern="*.pdb", dst="bin", src="bin")
            
    def package_info(self):
        self.cpp_info.libs = ['small3d']
        if self.settings.os == "Windows":
            self.cpp_info.cppflags.append("/EHsc")
            self.cpp_info.exelinkflags.append('-NODEFAULTLIB:LIBCMTD')
            self.cpp_info.exelinkflags.append('-NODEFAULTLIB:LIBCMT')
        else:
            self.cpp_info.cppflags.append("-std=c++11")
