export CXX=`which clang++`
export CC=`which clang`
mkdir -p ./build
cd build
cmake .. -DBOOST_ROOT=/opt/boost -GNinja
