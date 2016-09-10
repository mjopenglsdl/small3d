from conan.packager import ConanMultiPackager
import os

if __name__ == "__main__":
    builder = ConanMultiPackager(archs=['x86_64'], args="--build glew freetype SDL2_ttf portaudio")
    builder.add_common_builds()
    builder.run()
