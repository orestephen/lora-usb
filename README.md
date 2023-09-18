# lora-usb
lora-usb

# build

**create build directory**

`mkdir build`

**configure build environment**

`cmake -B build/ -S .`

use `--toolchain <toolchain file>` for custom toolchaining or environment

**build binary**

`cmake --build build`

use `-j<number>` to use multiple cores

# DFU

`sudo dfu-util -a 0 -s 0x8000000:leave -D build/lora-usb.bin`
