#!/bin/bash

# Проверка неверного порта сервера
echo "Тест 3: Вывод ошибки при неверном порте"
./client -a 127.0.0.1 -p 7777 -v vhod.bin -r rez.txt -l vclient.conf
