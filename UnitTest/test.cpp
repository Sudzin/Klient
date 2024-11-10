#include <UnitTest++/UnitTest++.h>
#include "md5.h"
#include "Client.h"
#include "termcolor.h"

using namespace std;

// Структура для создания и удаления экземпляра клиента для каждого теста
struct Test {
    Client * p;
    Test() {
        p = new Client();
    }
    ~Test() {
        delete p;
    }
};

SUITE(Server) {
    // Тест успешного подключения с корректными параметрами
    TEST_FIXTURE(Test, Ok) {
        p->vectora = "/home/stud/Desktop/Kurs_Toxa/vhod.bin";
        p->result = "/home/stud/Desktop/Kurs_Toxa/reza.txt";
        p->autification = "/home/stud/Desktop/Kurs_Toxa/vclient.conf";
        CHECK_EQUAL(0, p->Server("127.0.0.1", "33333"));
    }

    // Тест использования порта по умолчанию при отсутствии переданного параметра
    TEST_FIXTURE(Test, DefaultPort) {
        p->vectora = "/home/stud/Desktop/Kurs_Toxa/vhod.bin";
        p->result = "/home/stud/Desktop/Kurs_Toxa/reza.txt";
        p->autification = "/home/stud/Desktop/Kurs_Toxa/vclient.conf";
        CHECK_EQUAL(0, p->Server("127.0.0.1", ""));
    }

    // Тест обработки ошибки при отсутствии файла с векторами
    TEST_FIXTURE(Test, NonExistentVectorFile) {
        p->vectora = "/home/stud/Desktop/Kurs_Toxa/nonexistent.bin";
        p->result = "/home/stud/Desktop/Kurs_Toxa/reza.txt";
        p->autification = "/home/stud/Desktop/Kurs_Toxa/vclient.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }

    // Тест обработки ошибки при некорректном IP-адресе
    TEST_FIXTURE(Test, InvalidIpAddress) {
        p->vectora = "/home/stud/Desktop/Kurs_Toxa/vhod.bin";
        p->result = "/home/stud/Desktop/Kurs_Toxa/reza.txt";
        p->autification = "/home/stud/Desktop/Kurs_Toxa/vclient.conf";
        CHECK_THROW(p->Server("999.999.999.999", "33333"), client_error);
    }

    // Тест обработки ошибки при пустом файле с векторами
    TEST_FIXTURE(Test, EmptyVectorFile) {
        p->vectora = "/home/stud/Desktop/Kurs_Toxa/empty.bin";
        p->result = "/home/stud/Desktop/Kurs_Toxa/reza.txt";
        p->autification = "/home/stud/Desktop/Kurs_Toxa/vclient.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }

    // Тест успешного создания файла для записи результата, если его нет
    TEST_FIXTURE(Test, NonExistentResultFile) {
        p->vectora = "/home/stud/Desktop/Kurs_Toxa/vhod.bin";
        p->result = "/home/stud/Desktop/Kurs_Toxa/nonexistent_result.txt";
        p->autification = "/home/stud/Desktop/Kurs_Toxa/vclient.conf";
        CHECK_EQUAL(0, p->Server("127.0.0.1", "33333"));
    }

    // Тест обработки ошибки при отсутствии файла для аутентификации
    TEST_FIXTURE(Test, NonExistentAutificationFile) {
        p->vectora = "/home/stud/Desktop/Kurs_Toxa/vhod.bin";
        p->result = "/home/stud/Desktop/Kurs_Toxa/reza.txt";
        p->autification = "/home/stud/Desktop/Kurs_Toxa/nonexistent.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }

    // Тест обработки ошибки при пустом файле для аутентификации
    TEST_FIXTURE(Test, EmptyAutificationFile) {
        p->vectora = "/home/stud/Desktop/Kurs_Toxa/vhod.bin";
        p->result = "/home/stud/Desktop/Kurs_Toxa/reza.txt";
        p->autification = "/home/stud/Desktop/Kurs_Toxa/empty.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }
}

int main() {
    return UnitTest::RunAllTests();
}
