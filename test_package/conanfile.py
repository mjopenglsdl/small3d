from conans import ConanFile, CMake
import os

channel = os.getenv("CONAN_CHANNEL", "testing")
username = os.getenv("CONAN_USERNAME", "dimi309")

class TestSmall3d(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "small3d/master@%s/%s" % (username, channel)
    generators = "cmake"

    def build(self):
        cmake = CMake(self.settings)
        self.run('cmake "%s" %s' % (self.conanfile_directory, cmake.command_line))
        self.run("cmake --build . %s" % cmake.build_config)

    def test(self):
        self.run(os.sep.join(["cd bin && .", "test_small3d"]))

    def imports(self):
        if self.settings.os == "Windows":
            self.copy(pattern="*.dll", dst="bin", src="bin")
        if self.settings.os == "Macos":
            self.copy(pattern="*.dylib", dst="bin", src="lib")
