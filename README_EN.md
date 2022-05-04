This is an automatic translation, may be incorrect in some places. See sources and examples!

# GParser
A simple and fast parser for strings into separate substrings and numbers for Arduino
- Works with the specified buffer (string), does not create its own
- Splits the string into substrings by the specified character
- Allows you to access substrings, convert them to numbers and compare with strings
- Access to substrings via []
- Can parse a string into an array of int or byte

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **GParser** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/GParser/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82Cranberries D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
// pass char array a string, you can specify a separator character (default ',')
GParser(char*data);
GParser (char* data, char newDiv = ',');
```

<a id="usage"></a>
## Usage
### GParser class
```cpp
void setDiv(char newDiv); // specify separator character
void clear(); // free buffer
int amount(); // amount of split data in the packet
int split(); // split the string into substrings
int16_t getInt(int num); // get an int from the selected substring
float getFloat(int num); // get a float from the selected substring
bool equals(int num, const char* comp); // compare substring with another string
int parseInts(int*data); // parse into ints
int parseBytes(byte*data); // parse into bytes
void restore(); // restore the original form of the string (return separators)
```

### Separate parsing functions
See example **testUtils**

```cpp
// number of substrings in the list list with div separator
uint8_t GP_listSize(char* list, char div = ',');

// split list with div delimiter into substrings (see example)
char* GP_splitList(char* list, char div = ',');

// get the number under which name is included in the list with a separator div. -1 if not included
int8_t GP_inList(char* name, char* list, char div = ',');

// convert int to string (3-10 times faster than ltoa + base)
void GP_numToChar(int32_t n, char* buf, uint8_t base);

// convert float to string
void GP_floatToChar(double f, char *buf, uint8_t decimals);

// convert string to number
int32_t GP_charToNum(char* buf, uint8_t base);

// convert string to float
double GP_charToFloat(char*buf);

// get the number at index idx in the list list with a div separator
int GP_numFromList(char* list, int idx, char div = ',');

// rewrite list list with delimiterdiv into an array of numbers data with size size
uint8_t GP_listToNum(char* list, int* data, uint8_t size, char div = ',');

// convert text color (0x, #) to number
uint32_t GP_decodeColor(char* hex);
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
// string parser test
#include <GParser.h>

void setup() {
  Serial.begin(9600);

  // ==================== EXAMPLE 1 ======================
  // example string
  // data is separated by a delimiter, such as a comma
  // can be obtained from Serial/UDP/TCP/MQTT etc
  char str[] = "1234,3.14,hello,4567,lolkek,qwerty";

  // feed the string to the parser, specify the separator (default comma)
  GParser data(str, ',');

  // split
  // ATTENTION! The operation "breaks" the string, replacing the delimiters with NULL
  intam = data.split();
  // get the amount of data

  Serial println(am); // display the amount

  // we can refer to the received strings as data[i] or data.str[i]
  for (byte i = 0; i < am; i++) Serial.println(data[i]);

  // you can also get them as int and float numbers
  // passing the row index
  Serial.println(data.getInt(0));
  Serial.println(data.getFloat(1));

  // can be compared with a string (line pars number, string to compare)
  if (data. equals(2, "hello")) Serial. println("true");
  else Serial.println("false");
  
  Serial.println();
  
  // ==================== EXAMPLE 2 ======================
  // fast parsing of delimited integer data
  char str2[] ​​= "123,456,789,222,333,444";
  GParserdata2(str2); // feed the string to the parser

  // create an array with the number of cells data2.amount() - how much data is in the package
  int ints[data2.amount()];
  
  int am2 = data2.parseInts(ints); // scatters into the specified array and returns the amount
  // actually here am2 == data2.amount() - amount of data
  // output
  for (byte i = 0; i < am; i++) Serial.println(ints[i]);
}

void loop() {
}

```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - added separate tools forCranberries for parsing
- v1.2 - added more parsing tools
- v1.3 - added the ability to restore the string
- v1.3.1 - fix warning

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!