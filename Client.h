/**
* @file Client.h
* @brief Заголовочный файл для модуля Client.
* 
* Этот файл содержит объявления классов и функций для клиента.
* 
* @version 1.0
* @date 05.11.2023
* @author Мочалин А.А.
* @copyright ИБСТ ПГУ
*/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

/**
 * @brief Класс клиента с переменными.
 * 
 * Этот класс предоставляет функции для взаимодействия с сервером и включает переменные для различных параметров.
 */
class Client
{
public:
    /**
     * @brief Функция клиента для взаимодействия с сервером.
     * 
     * @param str1 Адрес сервера.
     * @param str2 Порт сервера.
     * @return int Возвращает 0 в случае успешного выполнения.
     */
    int Server(string str1, string str2);

    int port;            /**< @brief Порт */
    uint32_t summa;      /**< @brief Сумма в кодировке uint32_t */
    string massage;      /**< @brief Сообщение */
    string vectora;      /**< @brief Переменная для векторов */
    string result;       /**< @brief Переменная для записи результата */
    string autification; /**< @brief Переменная для аутентификации */
    string username;     /**< @brief Переменная для записи Логина */
    string password;     /**< @brief Переменная для записи Пароля */
    string line;
};

/**
 * @brief Класс обработки ошибок.
 * 
 * Этот класс используется для обработки ошибок, возникающих в процессе работы клиента.
 */
class client_error: public invalid_argument
{
public:
    /**
     * @brief Конструктор с аргументом типа string.
     * 
     * @param what_arg Сообщение об ошибке.
     */
    explicit client_error (const string& what_arg):
        invalid_argument(what_arg) {}

    /**
     * @brief Конструктор с аргументом типа const char*.
     * 
     * @param what_arg Сообщение об ошибке.
     */
    explicit client_error (const char* what_arg):
        invalid_argument(what_arg) {}
};
