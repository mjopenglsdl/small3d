from conans import ConanFile, CMake, os
import os

class Small3dConan(ConanFile):
    name = "small3d"
    version = "1.0.5"
    ZIP_FOLDER_NAME = "%s-%s" % (name, version)
    generators = "cmake"
    settings = "os", "arch", "build_type", "compiler"
    url="http://github.com/dimi309/small3d"
    requires = "SDL2/2.0.4@lasote/stable","SDL2_ttf/2.0.14@coding3d/ci","glew/1.13.0@coding3d/stable", \
        "libpng/1.6.23@lasote/stable","zlib/1.2.8@lasote/stable","glm/0.9.7.6@dlarudgus20/stable", \
        "vorbis/1.3.5@coding3d/stable", "portaudio/master@jgsogo/stable"
    license="https://github.com/dimi309/small3d/blob/master/LICENSE"
    exports = "CMakeLists.txt", "small3d/*", "FindSMALL3D.cmake", "cmake/*"

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
        self.copy("FindSMALL3D.cmake", ".", ".")
        self.copy(pattern="*.hpp", dst="include", src="small3d/include", keep_path=True)

        if self.settings.os == "Windows":
            self.copy(pattern="*.dll", dst="bin", keep_path=False)
            self.copy(pattern="*.lib", dst="lib", keep_path=False)
        else:
            if self.settings.os == "Macos":
                self.copy(pattern="*.a", dst="lib", keep_path=False)
            else:
                self.copy(pattern="*.so*", dst="lib", keep_path=False)
                self.copy(pattern="*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ['small3d']
