/**
* @file md5.h
* @brief Заголовочный файл для модуля MD5.
* 
* Этот файл содержит объявления функций для вычисления хешей MD5.
* 
* @version 1.0
* @date 05.11.2024
* @author Мочалин А.А.
* @copyright ИБСТ ПГУ
*/

/**
* @brief Библиотеки Crypto++
*/
#include <cryptopp/hex.h> 
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h> 

using namespace std;

/**
 * @brief Вычисление хеша MD5.
 * 
 * Эта функция принимает строку и возвращает её MD5-хеш.
 * 
 * @param hash Входная строка для вычисления хеша.
 * @return string MD5-хеш входной строки.
 */
string MD5_hash(string hash);
