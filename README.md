# Proselytize
This application is a FOSS program intending to utilise the full power of the GPU when converting video files. 

## Notes For Developers

### Requirements to Build and Compile
- This project uses the meson build system, so ensure you have meson installed
- You will also require the rocm-hip-sdk and the hipcc compiler

A shell script has been provided with the repo that can be used to setup the meson builddir if not present and compile the program using hipcc.
