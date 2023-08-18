# lora-usb
lora-usb

# build

create build directory and cd into it.

`mkdir build; cd build`

configure build environment.

`cmake ..`

# DFU

`sudo dfu-util -a 0 -s 0x8000000:leave -D example.bin`