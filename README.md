# DeltaShadow
Delta’s Shadow является идейным продолжением игр Power Blade и Power Blade 2. Оригинальный код игры Windows-версии был написан на языке C#. Данный репозиторий содержит конверсию оригинального кода в код на языке C++ стандарта 2011 года. Конверсия изначально была выполнена автоматически программой-конвертером, а после - приведена в рабочее состояние вручную.

**Авторы игры - команда Sanchez Crew:**
- автор идеи: Евгений Сухомлин (sinc LAIR)
- автор оригинального кода на C#: Александр Удотов (Sanchez)
- музыка: Олег Никитин (n1k-o)
- графика: Евгений Рогулин (ER)

**Сборка**
1 Cmake вариант:
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
2 QT вариант:
qmake DeltaShadow.pro
make

**Roadmap:**
- Переписать рендер на OpenGL.
- Заменить SdlDotNet и SDL на SDL2.

![](https://i.ibb.co/ctVSpS2/01.jpg)

![](https://i.ibb.co/hMKYxxC/02.png)
