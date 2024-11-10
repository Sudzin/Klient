/**
* @file md5.cpp
* @brief Модуль хэширования.
* 
* Этот файл содержит определения функций для вычисления хешей MD5.
* 
* @version 1.0
* @date 05.11.2024
* @author Мочалин А.А.
* @copyright ИБСТ ПГУ
*/
 
#include "md5.h"

/**
* @brief Объявление именного пространства CryptoPP.
*/
using namespace CryptoPP;

/**
 * @brief Вычисление хеша MD5.
 * 
 * Эта функция принимает строку и возвращает её MD5-хеш.
 * 
 * @param hash Сообщение, получаемое для хэширования.
 * @return string Хешированное сообщение.
 */
string MD5_hash(string hash)
{
    /**
     * @brief Переменная для хранения хешированного сообщения.
     */
    string massange; 
    
    Weak1::MD5 hashmd4;  
    
    /**
     * @brief Класс для чтения данных из источника и записи их в приемник.
     */
    StringSource(hash, true, 
                    new HashFilter(hashmd4, 
                                    /**
                                     * @brief Класс для преобразования двоичных данных в шестнадцатеричную строку.
                                     */
                                    new HexEncoder( 
                                        /**
                                         * @brief Класс для записи данных в приемник.
                                         */
                                        new StringSink(massange)))); 
                                        
    /**
     * @return Возвращает хешированное сообщение.
     */
    return massange;
}
