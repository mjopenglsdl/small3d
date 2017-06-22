from conans import ConanFile, CMake
from conans.tools import os_info, ConanException
import subprocess

class Small3dConan(ConanFile):
    name = "small3d"
    version = "master"
    description = "A small, cross-platform 3D game engine (C++, OpenGL, GLFW) - runs on Win/MacOS/Linux"
    generators = "cmake"
    settings = "os", "arch", "build_type", "compiler"
    url="http://github.com/dimi309/conan-packages"
    requires = "glfw/3.2.1@dimi309/stable", "freetype/2.6.3@lasote/stable","glew/2.0.0@dimi309/stable", \
        "libpng/1.6.23@lasote/stable","zlib/1.2.8@lasote/stable","glm/0.9.8.4@dimi309/stable", \
        "vorbis/1.3.5@dimi309/stable", "portaudio/rc.v190600.20161001@jgsogo/stable"
    license="https://github.com/dimi309/small3d/blob/master/LICENSE"
    exports = ["small3d/*", "FindSMALL3D.cmake", "CMakeLists.txt", "LICENSE"]

    def configure(self):
        if self.settings.os == "Windows" and self.settings.compiler != "Visual Studio":
            raise ConanException("On Windows, only Visual Studio compilation is supported for the time being.")
        if (self.settings.compiler == "gcc" or self.settings.compiler == "clang") and self.settings.compiler.libcxx != "libstdc++11":
            raise ConanException("When building with gcc or clang, compiler.libcxx must be equal to libstdc++11.")

    def rpm_package_installed(self, package):
        p = subprocess.Popen(['rpm', '-q', package], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, _ = p.communicate()
        return 'install ok' in out or 'not installed' not in out

    def ensure_rpm_dependency(self, package):
        if not self.rpm_package_installed(package):
            self.output.warn(package + " is not installed in this machine! Conan will try to install it.")
            # Note: yum is automatically redirected to dnf on modern Fedora distros (see 'man yum2dnf')
            self.run("sudo yum install -y " + package)
            if not self.rpm_package_installed(package):
                self.output.error(package + " Installation doesn't work... install it manually and try again")
                exit(1)

    def debian_package_installed(self, package):
        p = subprocess.Popen(['dpkg', '-s', package], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, _ = p.communicate()
        return 'install ok' in out

    def ensure_debian_dependency(self, package):
        if not self.debian_package_installed(package):
            self.output.warn(package + " is not installed in this machine! Conan will try to install it.")
            self.run("sudo apt-get update && sudo apt-get install -y " + package)
            if not self.debian_package_installed(package):
                self.output.error(package + " Installation doesn't work... install it manually and try again")
                exit(1)

    def system_requirements(self):
        if os_info.is_linux:
            if subprocess.call("which apt-get", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE) == 0:
                self.ensure_debian_dependency("libglu1-mesa-dev")
            elif subprocess.call("which yum", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE) == 0:
                self.ensure_rpm_dependency("mesa-libGL-devel")
            else:
                self.output.warn("Could not determine package manager, skipping Linux system requirements installation.")
    
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
