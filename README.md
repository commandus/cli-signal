# Signal messenger CLI client

## Run

```
echo "Message" | ./cli-signal -t phone
```

## Build

automake:

```
autogen.sh
./configure
make
sudo make install
```

cmake (Clang):

```
mkdir build
cd build
export CC=/usr/bin/clang;export CXX=/usr/bin/clang++;cmake ..
make
```

## Configuration files


## Thitd-party dependencies

[argtable3](https://github.com/argtable/argtable3)

[libsignal-protocol-c](https://github.com/signalapp/libsignal-protocol-c)

[axc](https://github.com/gkdr/axc)
