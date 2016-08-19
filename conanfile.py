# Only building shared library, since the static library would not work
from conans import ConanFile, CMake, os
import os

class Small3dConan(ConanFile):
    name = "small3d"
    version = "1.0.3"
    generators = "cmake"
    settings = "os", "arch", "build_type", "compiler"
    url="http://github.com/coding3d/small3d"
    requires = "SDL2/2.0.4@lasote/stable","SDL2_ttf/2.0.14@lasote/stable","glew/1.13.0@coding3d/ci","libpng/1.6.23@lasote/stable","zlib/1.2.8@lasote/stable","gtest/1.7.0@lasote/stable"
    license="https://github.com/coding3d/small3d/blob/master/LICENSE"
    exports = "*"

    def build(self):
        cmake = CMake(self.settings)

        try:
            if self.settings.os == "Windows":
                self.run("rd /s /q _build")
            else:
                self.run("rm -rf _build")
        except:
            pass

        self.run("mkdir _build")
        cd_build = "cd _build"
        self.run("%s && cmake .. -DBUILD_WITH_CONAN=TRUE %s" % (cd_build, cmake.command_line))
        self.run("%s && cmake --build . %s" % (cd_build, cmake.build_config))

    def package(self):
        # Copying headers
        self.copy(pattern="*.hpp", dst="include", src="small3d/include", keep_path=True)
        self.copy(pattern="*.hpp", dst="include", src="glminclude", keep_path=True)

        if self.settings.os == "Windows":
            self.copy(pattern="*.dll", dst="bin", src=self.ZIP_FOLDER_NAME, keep_path=False)
            self.copy(pattern="*.lib", dst="lib", src=self.ZIP_FOLDER_NAME, keep_path=False)
        else:
            if self.settings.os == "Macos":
                self.copy(pattern="*.a", dst="lib", keep_path=False)
            else:
                self.copy(pattern="*.so*", dst="lib", src="..", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ['smal3d']
