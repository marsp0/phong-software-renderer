# install dependencies
apt-get update
apt install libsdl2-dev

# create dir for object files
if [ ! -d "./out" ]; then
  mkdir out
fi
