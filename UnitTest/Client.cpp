/**
* @file Client.cpp
* @brief Модуль клиента
* @details Модуль для подключения клиента к серверу, аутентификации и отправки данных.
* @version 1.0
* @date 05.11.2024
* @author Мочалин А.А.
* @copyright ИБСТ ПГУ
*/

#include "md5.h"
#include "Client.h"
#include "termcolor.h"
#include <fstream>
#include <vector>
#include <unistd.h> // Для получения текущего каталога
#include <sys/stat.h> // Для проверки существования файла

using namespace std;

/**
 * @brief Функция для проверки существования файла.
 * @param name Имя файла.
 * @return true, если файл существует, false в противном случае.
 */
bool file_exists(const string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

/**
 * @brief Функция клиента для соединения с сервером, аутентификации и обработки данных.
 * @param ip_address IP-адрес сервера.
 * @param port Порт сервера.
 * @return 0 в случае успешного выполнения, 1 в случае ошибки.
 */
int Client::Server(string ip_address, string port)
{
    // Порт по умолчанию
    if(port == "") {
        port = "33333";
    }
    // Проверка на пустую строку файла аутентификации, назначение по умолчанию
    if(autification == "") {
        autification = "vclient.conf";
    }

    // Открытие файла для аутентификации
    ifstream fautf(autification);
    if(!fautf.is_open()) {
        throw client_error(string("Функция: autification.\nОшибка открытия файла для аутентификации"));
    }
    if(fautf.peek() == EOF) {
        fautf.close();
        throw client_error(string("Функция: autification.\nФайл для аутентификации пуст"));
    }

    string line;
    getline(fautf, line);
    int k = line.find(" ");
    username = line.substr(0, k);
    password = line.erase(0, k+1);

    // Вывод текущего каталога программы
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cout << termcolor::bold << termcolor::yellow << "Текущий каталог программы: " << cwd << termcolor::reset << endl;
    } else {
        perror("getcwd() error");
        return 1;
    }

    // Проверка существования файла
    if (!file_exists(vectora)) {
        cerr << termcolor::bold << termcolor::red << "Ошибка: Файл не найден: " << vectora << termcolor::reset << endl;
        throw client_error(string("Функция: vectora.\nФайл не найден"));
    }

    // Открытие двоичного файла для чтения векторов
    ifstream fvector(vectora, ios::binary);
    if (!fvector.is_open()) {
        cerr << termcolor::bold << termcolor::red << "Ошибка: Невозможно открыть файл с векторами: " << vectora << termcolor::reset << endl;
        throw client_error(string("Функция: vectora.\nОшибка открытия исходного двоичного файла с векторами"));
    }
    if (fvector.peek() == EOF) {
        fvector.close();
        cerr << termcolor::bold << termcolor::red << "Ошибка: Файл с векторами пуст: " << vectora << termcolor::reset << endl;
        throw client_error(string("Функция: vectora.\nФайл с векторами пуст"));
    }

    // Открытие файла для записи результата
    ofstream fresultat(result);
    if(!fresultat.is_open()) {
        fresultat.close();
        throw client_error(string("Функция: result.\nОшибка открытия файла для записи результата"));
    }

    char buf[255];

    try {
        strcpy(buf, ip_address.c_str());
    } catch (...) {
        throw client_error(std::string("Функция: buf.\nНевозможно получить адрес"));
    }

    try {
        this->port = stoi(port);
    } catch (...) {
        throw client_error(string("Функция: port.\nНевозможно получить порт"));
    }

    // Соединение клиента с сервером
    sockaddr_in *selfAddr = new (sockaddr_in);
    selfAddr->sin_family = AF_INET;
    selfAddr->sin_port = 0;
    selfAddr->sin_addr.s_addr = 0;

    sockaddr_in *remoteAddr = new (sockaddr_in);
    remoteAddr->sin_family = AF_INET;
    remoteAddr->sin_port = htons(this->port);
    remoteAddr->sin_addr.s_addr = inet_addr(buf);

    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if(mySocket == -1) {
        close(mySocket);
        throw client_error(string("Функция: mySocket.\nОшибка создания сокета"));
    }

    int rc = bind(mySocket, (const sockaddr *) selfAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: selfAddr.\nОшибка привязки сокета с локальным адресом"));
    }

    rc = connect(mySocket, (const sockaddr *) remoteAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: remoteAddr.\nОшибка подключения сокета к удаленному серверу"));
    }

    char *buffer = new char[4096];
    strcpy(buffer, username.c_str());
    int massageLen = strlen(buffer);

    rc = send(mySocket, buffer, massageLen, 0);
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: buffer.\nОшибка отправки логина"));
    }
    cout << termcolor::bold << termcolor::green << "Логин: " << buffer << termcolor::reset << endl;

    rc = recv(mySocket, buffer, 4096, 0);
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: buffer.\nОшибка получения ответа"));
    }
    string s1 = string(buffer);
    buffer[rc] = '\0';
    cout << termcolor::bold << termcolor::green << "Соль: " << buffer << termcolor::reset << endl;

    string hsh = s1 + password;
    massage = MD5_hash(hsh);

    strcpy(buffer, massage.c_str());
    rc = send(mySocket, buffer, massage.length(), 0);
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: massage.\nОшибка отправки хэша"));
    }
    cout << termcolor::bold << termcolor::green << "Отправка хэша: " << buffer << termcolor::reset << endl;

    rc = recv(mySocket, buffer, sizeof(buffer), 0);
    buffer[rc] = '\0';
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: buffer.\nОшибка получения ответа об аутентификации"));
    }
    cout << termcolor::bold << termcolor::green << "Ответ об аутентификации: " << buffer << termcolor::reset << endl;

    // Пример чтения двоичного файла
    fvector.seekg(0, ios::end);
    size_t fileSize = fvector.tellg();
    fvector.seekg(0, ios::beg);

    vector<char> fileBuffer(fileSize);
    fvector.read(fileBuffer.data(), fileSize);

    rc = send(mySocket, fileBuffer.data(), fileSize, 0);
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: buffer.\nОшибка отправки данных файла"));
    }
    cout << termcolor::bold << termcolor::green << "Отправка данных файла: " << fileBuffer.data() << termcolor::reset << endl;

    // Получение результата
    uint32_t summa;
    rc = recv(mySocket, &summa, sizeof(summa), 0);
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: buffer.\nОшибка получения результата"));
    }
    cout << termcolor::bold << termcolor::green << "Результат вычислений: " << summa << termcolor::reset << endl;

    fresultat << static_cast<uint32_t>(summa);
    fresultat.close();

    close(mySocket);
    delete selfAddr;
    delete remoteAddr;
    delete[] buffer;

    return 0;
}
