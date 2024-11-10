/**
* @file interface.cpp
* @brief Интерфейс программы.
* 
* Этот файл содержит код интерфейса для взаимодействия с пользователем.
* 
* @version 2.0
* @date 05.11.2024
* @author Мочалин А.А.
* @copyright ИБСТ ПГУ
*/

#include "Client.h"
#include "termcolor.h"
#include <iomanip>  // Для форматирования вывода

using namespace std;

/**
 * @brief Печатает красивую рамку.
 */
void print_border() {
    cout << termcolor::bold << termcolor::green << setfill('=') << setw(50) << "=" << termcolor::reset << endl;
}

/**
 * @brief Печатает заголовок программы.
 */
void print_header() {
    print_border();
    cout << termcolor::bold << termcolor::yellow << setw(30) << "Добро пожаловать в программу клиента!" << termcolor::reset << endl;
    print_border();
}

/**
 * @brief Печатает справку по использованию программы.
 */
void print_help() {
    print_header();
    cout << termcolor::bold << termcolor::blue << "-help или -h — справка -> рекомендуем при первом использовании ознакомиться)" << termcolor::reset << endl;
    cout << termcolor::bold << termcolor::red << "-a — адрес сервера -> обязательный" << termcolor::reset << endl;
    cout << termcolor::bold << termcolor::blue << "-p — порт сервера -> необязательный (33333)" << termcolor::reset << endl;
    cout << termcolor::bold << termcolor::red << "-v — имя файла с исходными данными -> обязательный" << termcolor::reset << endl;
    cout << termcolor::bold << termcolor::red << "-r — имя файла в который необходимо сохранить результат -> обязательный" << termcolor::reset << endl;
    cout << termcolor::bold << termcolor::blue << "-l — имя файла для авторизации -> необязательный" << termcolor::reset << endl;
    print_border();
}

/**
 * @brief Основная функция интерфейса
 * 
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return int Возвращает 0 в случае успешного выполнения
 */
int main (int argc, char *argv[])
{
    Client Soedinenie;

    if(argc == 1) {
        print_help();
        return 0;
    }

    string server_address;
    string port = "33333"; // значение по умолчанию
    string input_file;
    string output_file;
    string auth_file;

    int opt;
    while ((opt = getopt(argc, argv, "ha:p:v:r:l:")) != -1) {
        switch(opt) {
            case 'h':
                print_help();
                return 0;

            case 'a':
                server_address = string(optarg);
                break;

            case 'p':
                port = string(optarg);
                break;

            case 'v':
                input_file = string(optarg);
                Soedinenie.vectora = input_file;
                break;

            case 'r':
                output_file = string(optarg);
                Soedinenie.result = output_file;
                break;

            case 'l':
                auth_file = string(optarg);
                Soedinenie.autification = auth_file;
                break;

            case '?':
                cout << termcolor::bold << termcolor::red << "Неверный параметр -> ознакомьтесь со справкой (-h или -help)" << termcolor::reset << endl;
                return 0;
        }
    }

    if (server_address.empty()) {
        cout << termcolor::bold << termcolor::red << "Ошибка: адрес сервера не указан! Используйте параметр -a для указания адреса." << termcolor::reset << endl;
        return 1;
    }

    cout << termcolor::bold << termcolor::green << "Подключение к серверу " << server_address << " на порту " << port << "..." << termcolor::reset << endl;

    Soedinenie.Server(server_address, port);

    cout << termcolor::bold << termcolor::green << "Выполнение завершено. Результаты сохранены в файл " << output_file << "." << termcolor::reset << endl;

    return 0;
}
