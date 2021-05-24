![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
# GParser
Простой и быстрый парсер строк в отдельные подстроки и числа для Arduino
- Работает с указанным буфером (строкой), не создаёт свой
- Разделяет строку на подстроки по указанному символу
- Позволяет обращаться к подстрокам, переводить их в числа и сравнивать со строками
- Доступ к подстрокам через []
- Может распарсить строку в массив int или byte

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GParser** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GParser/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
```cpp
// передать char array строку, можно указать символ разделитель (по умолч ',')
GParser (char* data);
GParser (char* data, char newDiv = ',');
```

<a id="usage"></a>
## Использование
```cpp
void setDiv(char newDiv);       // указать символ разделитель
void clear();                   // освободить буфер
int amount();                   // количество разделённых данных в пакете
int split();                    // разделить строку на подстроки
int16_t getInt(int num);        // получить инт из выбранной подстроки
float getFloat(int num);        // получить float из выбранной подстроки
bool equals(int num, const char* comp); // сравнить подстроку с другой строкой
int parseInts(int* data);       // распарсить на инты
int parseBytes(byte* data);     // распарсить на байты
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
// тест парсера строк
#include <GParser.h>

void setup() {
  Serial.begin(9600);

  // ==================== ПРИМЕР 1 ======================
  // строка для примера
  // данные разделены разделителем, например запятой
  // могут быть получены из Serial/UDP/TCP/MQTT итд
  char str[] = "1234,3.14,hello,4567,lolkek,qwerty";

  // кормим строку парсеру, указываем разделитель (умолч. запятая)
  GParser data(str, ',');

  // разделяем
  // ВНИМАНИЕ! Операция "ломает" строку, заменяя разделители на NULL
  int am = data.split();
  // получаем количество данных

  Serial.println(am); // выводим количество

  // можем обратиться к полученным строкам как data[i] или data.str[i]
  for (byte i = 0; i < am; i++) Serial.println(data[i]);

  // также можно получить их в виде int и float чисел
  // передав индекс строки
  Serial.println(data.getInt(0));
  Serial.println(data.getFloat(1));

  // можно сравнить со строкой (номер парс строки, строка для сравнения)
  if (data.equals(2, "hello")) Serial.println("true");
  else Serial.println("false");
  
  Serial.println();
  
  // ==================== ПРИМЕР 2 ======================
  // быстрый парсинг целочисленных данных с разделителем
  char str2[] = "123,456,789,222,333,444";
  GParser data2(str2);   // кормим строку парсеру

  // создаём массив с количеством ячеек data2.amount() - столько данных в пакете
  int ints[data2.amount()];
  
  int am2 = data2.parseInts(ints);  // раскидает в указанный массив и вернёт количество
  // фактически тут am2 == data2.amount() - количество данных
  // выводим
  for (byte i = 0; i < am; i++) Serial.println(ints[i]);
}

void loop() {
}

```

<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!