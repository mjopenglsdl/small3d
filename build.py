from conan.packager import ConanMultiPackager
import os, platform

if __name__ == "__main__":
    builder = ConanMultiPackager(args="--build missing")
    builder.add_common_builds()
    filtered_builds = []
    for settings, options, env_vars, build_requires in builder.builds:
        if not (settings["compiler"] == "Visual Studio" and (settings["arch"] == "x86" or settings["compiler.runtime"] not in ("MD", "MDd"))) and \
           not ((settings["compiler"] == "gcc" and (settings["arch"] == "x86") or settings["compiler.version"] == "4.6")) and \
           not (settings["compiler"] == "clang" and (settings["arch"] == "x86"):
            if settings["compiler"] == "gcc" or settings["compiler"] == "clang":
                settings["compiler.libcxx"]="libstdc++11"
            filtered_builds.append([settings, options, env_vars, build_requires])
    builder.builds = filtered_builds
    builder.run()
