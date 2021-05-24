/*
    Простой и быстрый парсер строк в отдельные подстроки и числа для Arduino
    Документация: 
    GitHub: https://github.com/GyverLibs/GParser
    Возможности:
    - Работает с указанным буфером (строкой), не создаёт свой
    - Разделяет строку на подстроки по указанному символу
    - Позволяет обращаться к подстрокам, переводить их в числа и сравнивать со строками
    - Доступ к подстрокам через []
    - Может распарсить строку в массив int или byte
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
*/

#ifndef GParser_h
#define GParser_h

class GParser {
public:
    // передать char array строку, можно указать символ разделитель
    GParser (char* data, char newDiv = ',') {
        buf = data;
        div = newDiv;
    }
    ~GParser() {
        clear();
    }
    
    // указать символ разделитель
    void setDiv(char newDiv) {
        div = newDiv;
    }
    
    // освободить буфер
    void clear() {
        if (str) free(str);
    }
    
    // количество разделённых данных в пакете
    int amount() {
        int i = 0, count = 0;
        while (buf[i++]) if (buf[i] == div) count++;  // подсчёт разделителей
        return ++count;
    }
    
    // разделить строку на подстроки
    int split() {
        int am = amount();            // количество данных
        clear();                      // освобождаем буфер
        str = (char**)malloc(am * sizeof(char*)); // создаём буфер
        str[0] = buf;                 // строка 0
        int i = 0, j = 0;             // счётчики
        while (buf[i]) {              // пока не NULL
            if (buf[i] == div) {        // если разделитель
                buf[i] = '\0';            // меняем на NULL
                str[++j] = buf + i + 1;   // запоминаем начало строки
            }
            i++;
        }
        return am;
    }
    
    // получить инт из выбранной подстроки
    int16_t getInt(int num) {
        return atol(str[num]);
    }
    
    // получить float из выбранной подстроки
    float getFloat(int num) {
        return atof(str[num]);
    }
    
    // сравнить подстроку с другой строкой
    bool equals(int num, const char* comp) {
        return !strcmp(str[num], comp);
    }
    
    // распарсить на инты
    int parseInts(int* data) {
        int count = 0;
        char* offset = buf;
        while (true) {
            data[count++] = atoi(offset);
            offset = strchr(offset, div);
            if (offset) offset++;
            else break;
        }
        return count;
    }
    
    // распарсить на байты
    int parseBytes(uint8_t* data) {
        int count = 0;
        char* offset = buf;
        while (true) {
            data[count++] = atoi(offset);
            offset = strchr(offset, div);
            if (offset) offset++;
            else break;
        }
        return count;
    }

    char* buf = NULL;
    char** str = NULL;

    char* operator [] (uint16_t idx) {
        return str[idx];
    }    
    
private:
    char div;
};

#endif