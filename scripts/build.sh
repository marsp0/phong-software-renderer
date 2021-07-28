# install dependencies
apt install libsdl2-dev
apt-cache search libsdl2-dev

# create dir for object files
if [ ! -d "./out" ]; then
  mkdir out
fi

make
