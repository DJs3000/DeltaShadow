# DeltaShadow
Delta’s Shadow является идейным продолжением игр Power Blade и Power Blade 2. Оригинальный код игры Windows-версии был написан на языке C#. Данный репозиторий содержит конверсию оригинального кода в код на языке C++ стандарта 2011 года. Конверсия изначально была выполнена автоматически программой-конвертером, а после - приведена в рабочее состояние вручную.

**Авторы игры - команда Sanchez Crew:**
- автор идеи: Евгений Сухомлин (sinc LAIR)
- автор оригинального кода на C#: Александр Удотов (Sanchez)
- музыка: Олег Никитин (n1k-o)
- графика: Евгений Рогулин (ER)

**Сборка:**

Для сборки необходимо предустановить следующие пакеты: SDL, SDL_gfx, SDL_image, SDL_mixer.

1) CMake вариант:
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
2) Qt вариант:
```
qmake DeltaShadow.pro
make
```
Пример сборки (Debian 11):
```
sudo apt install cmake libsdl1.2-dev libsdl-gfx1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl1.2debian libsdl-gfx1.2-5 libsdl-image1.2 libsdl-mixer1.2
cd ~
mkdir DeltaShadow && cd DeltaShadow
git clone https://github.com/DJs3000/DeltaShadow.git
cd DeltaShadow
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

**Roadmap:**
- Переписать рендер на OpenGL.
- Заменить SdlDotNet и SDL на SDL2.

![](https://i.ibb.co/ctVSpS2/01.jpg)

![](https://i.ibb.co/hMKYxxC/02.png)
