from conan.packager import ConanMultiPackager
import os,platform

if __name__ == "__main__":
    builder = ConanMultiPackager(args="--build missing")
    if platform.system() == 'Windows':
        builder.add({'compiler.version': '14', 'arch': 'x86_64', 'build_type': 'Debug', 'compiler': 'Visual Studio', 'compiler.runtime': 'MTd'})
        builder.add({'compiler.version': '14', 'arch': 'x86_64', 'build_type': 'Release', 'compiler': 'Visual Studio', 'compiler.runtime': 'MT'})
    elif platform.system() == 'Linux':
        builder.add({'compiler.version': '4.8', 'arch': 'x86_64', 'build_type': 'Debug', 'compiler': 'gcc'})
        builder.add({'compiler.version': '4.9', 'arch': 'x86_64', 'build_type': 'Debug', 'compiler': 'gcc'})
        builder.add({'compiler.version': '5.2', 'arch': 'x86_64', 'build_type': 'Debug', 'compiler': 'gcc'})
        builder.add({'compiler.version': '5.3', 'arch': 'x86_64', 'build_type': 'Debug', 'compiler': 'gcc'})

        builder.add({'compiler.version': '4.8', 'arch': 'x86_64', 'build_type': 'Release', 'compiler': 'gcc'})
        builder.add({'compiler.version': '4.9', 'arch': 'x86_64', 'build_type': 'Release', 'compiler': 'gcc'})
        builder.add({'compiler.version': '5.2', 'arch': 'x86_64', 'build_type': 'Release', 'compiler': 'gcc'})
        builder.add({'compiler.version': '5.3', 'arch': 'x86_64', 'build_type': 'Release', 'compiler': 'gcc'})
    elif platform.system() == 'Darwin':
        builder.add({'compiler.version': '7.3', 'arch': 'x86_64', 'build_type': 'Debug', 'compiler': 'apple-clang'})
        builder.add({'compiler.version': '7.0', 'arch': 'x86_64', 'build_type': 'Debug', 'compiler': 'apple-clang'})
        builder.add({'compiler.version': '6.1', 'arch': 'x86_64', 'build_type': 'Debug', 'compiler': 'apple-clang'})
        builder.add({'compiler.version': '6.0', 'arch': 'x86_64', 'build_type': 'Debug', 'compiler': 'apple-clang'})

        builder.add({'compiler.version': '7.3', 'arch': 'x86_64', 'build_type': 'Release', 'compiler': 'apple-clang'})
        builder.add({'compiler.version': '7.0', 'arch': 'x86_64', 'build_type': 'Release', 'compiler': 'apple-clang'})
        builder.add({'compiler.version': '6.1', 'arch': 'x86_64', 'build_type': 'Release', 'compiler': 'apple-clang'})
        builder.add({'compiler.version': '6.0', 'arch': 'x86_64', 'build_type': 'Release', 'compiler': 'apple-clang'})

    builder.run()
