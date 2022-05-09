# DeltaShadow
Delta’s Shadow является идейным продолжением игр Power Blade и Power Blade 2. Оригинальный код игры Windows-версии был написан на языке C#. Данный репозиторий содержит конверсию оригинального кода в код на языке C++ стандарта 2011 года. Конверсия изначально была выполнена автоматически программой-конвертером, а после - приведена в рабочее состояние вручную.

**Авторы игры - команда Sanchez Crew:**
- автор идеи: Евгений Сухомлин (sinc LAIR)
- автор оригинального кода на C#: Александр Удотов (Sanchez)
- музыка: Олег Никитин (n1k-o)
- графика: Евгений Рогулин (ER)

**Сборка**<br>
1 Cmake вариант:<br>
mkdir build && cd build<br>
cmake -DCMAKE_BUILD_TYPE=Release ..<br>
make<br>
2 QT вариант:<br>
qmake DeltaShadow.pro<br>
make<br>

**Roadmap:**
- Переписать рендер на OpenGL.
- Заменить SdlDotNet и SDL на SDL2.

![](https://i.ibb.co/ctVSpS2/01.jpg)

![](https://i.ibb.co/hMKYxxC/02.png)
