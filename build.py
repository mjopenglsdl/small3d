from conan.packager import ConanMultiPackager
import os,platform

if __name__ == "__main__":
    builder = ConanMultiPackager(args="--build missing")
    builder.add_common_builds()
    filtered_builds = []
    for settings, options in builder.builds:
        if not (settings["compiler"] == "Visual Studio" and (settings["compiler.version"] != "14" or
        settings["arch"] == "x86" or settings["compiler.runtime"] not in ("MD", "MDd"))) and \
        not ((settings["compiler"] == "gcc" and (settings["arch"] == "x86") or 
        settings["compiler.version"] == "4.6")):
            filtered_builds.append([settings, options])
    builder.builds = filtered_builds
    builder.run()
