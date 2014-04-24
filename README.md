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
```
./bootstrap

./b2 install
```
### Windows... coming soon
