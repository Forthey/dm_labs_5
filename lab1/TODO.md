- ПЕРЕПИСАТЬ КОДИРОВАНИЕ!!!! Побитовое и СОХРАНЯЕТ РАЗРЯД -- нужно сдвигать право выражение, а не влево discharge
- Добавить возможность записи дерева и закодированной строки в файл
- Структура файла:
1. n(8 бит) - количество закодированных символов (0..255)
2. n повторений формата:
   1. 1 байт - символ
   2. k(6 бит) - длина кода символа в битах (0..63) 
   3. k бит - код символа
3. m(3 бита) - число занятых бит в последнем char (0..7)
4. Далее по файлу - поток битов, который считывается "чанками" char 
5. Если char - последний (peek() == eof), то считывается m бит. Иначе считывается весь
- Добавить выозможность вывода кодов на экран
- Добавить возможность чтения дерева и строки из файла
- Добавить возможность декодирования прочитанной из файла строки
- Возможность ввода аргументов из командной строки