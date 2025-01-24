#!/usr/bin/env bash

set -x
set -e

root_dir=`git rev-parse --show-toplevel`
dawn_dir=$root_dir/deps/dawn
pushd $dawn_dir
cp scripts/standalone.gclient .gclient

python tools/fetch_dawn_dependencies.py --use-test-deps

mkdir -p out/Debug
cd out/Debug
cmake -GNinja ../.. -DDAWN_ENABLE_INSTALL=ON -DCMAKE_INSTALL_PREFIX=$root_dir/deps/install/mac/dawn
ninja install







