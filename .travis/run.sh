#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi
    pyenv activate conan
fi

git clone https://github.com/dimi309/conan-packages

cd conan-packages/small3d
conan export coding3d/stable
cd ../..
git clone https://github.com/dimi309/small3d-tutorial
cd small3d-tutorial/ChaseTheGoat3D
mkdir build
cd build
conan install .. --build missing
cmake -G"Visual Studio 14 2015 Win64" ..
cmake --build . --config Release
