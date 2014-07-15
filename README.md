# HeartRateMonitor
Множество людей в мире страдают сердечными заболеваниями, включая меня. 
Поэтому мне захотелось создать такую программу. Это будет web сервис и мобильное
приложение для Android смартфонов с камерой оснащённой вспышкой.

## Build
### Linux
1. install dependencies
```
sudo apt-get install ant libbz2-dev libboost-dev libgtest-dev libgtk2.0-dev pkg-config
```
or
```
../scripts/install_dependencies.sh
```

2. ```mkdir build```
3. ```cd build```
4. ```cmake ..```
5. ```make```

### Android
1. Install dependencies:
```
sudo ../scripts/install_dependencies.sh
```
2. Download, build and install libpng
```
-- Download libpng 1.6.12 tarball from sourceforge
-- tar xf libpng-1.6.12.tar.xf
-- cd 
```
1. Build Boost-for-Android:
clone Boost-for-Android git repository.
```
git clone https://github.com/MysticTreeGames/Boost-for-Android.git
```
2. run building
```
./build_android.sh --boost=1.55.0 --prefix=<android-gcc48-toolchain-sysroot-user>
```

```
./bootstrap

./b2 install
```
### Windows... coming soon
1. using Qt Creator with mingw32-4.8.
2. build boost with mingw
3. build OpenCV with mingw and cmake
4. build fftw3 with configure and mingw
5. build heart rate monitor with mingw and cmake
