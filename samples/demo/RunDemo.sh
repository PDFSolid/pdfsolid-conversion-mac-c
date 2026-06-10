arch=$(uname -m)
echo "$arch"

demo_name="demo"

if [ -d "build" ]
then
    cd build
else
    mkdir build
    cd build
fi

cmake ..
make -j10

./$demo_name