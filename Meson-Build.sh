if [ ! -d "buildir" ]; then
  meson setup builddir --native-file=native-file.ini
fi 

meson compile -C builddir
