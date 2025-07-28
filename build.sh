clear

mkdir -p build
cd build

mkdir -p linux
cd linux

mkdir -p cmake
mkdir -p out
cd cmake

cmake ../../../
make

chmod +x pwd
mv pwd ../out

cd ../out
echo ""

./pwd
