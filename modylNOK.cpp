#include "modylNOK.h" // Подключение пользовательского заголовочного файла, содержащего прототипы функций для работы с большими числами
#include <algorithm> // Подключение стандартной библиотеки алгоритмов для использования функций, таких как std::all_of, std::sort, std::swap и других

// Функция для умножения больших чисел в строковом формате
string multiply(const string& num1, const string& num2) {
    int len1 = num1.size();  // Длина первого числа
    int len2 = num2.size();  // Длина второго числа
    string result(len1 + len2, '0');  // Резервируем место для результата

    // Обходим каждую цифру первого числа
    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;  // Перенос для следующей итерации
        // Обходим каждую цифру второго числа
        for (int j = len2 - 1; j >= 0; --j) {
            // Умножаем текущие цифры и добавляем к результату с учетом переноса
            int product = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + carry;
            carry = product / 10;  // Перенос на следующую позицию
            result[i + j + 1] = (product % 10) + '0';  // Оставшаяся часть числа
        }
        result[i] += carry;  // Учитываем остаточный перенос после завершения умножения текущей пары цифр
    }

    // Удаление ведущих нулей
    size_t pos = result.find_first_not_of('0');
    return (pos != string::npos) ? result.substr(pos) : "0";  // Возвращаем результат без ведущих нулей
}

// Функция для деления больших чисел в строковом формате
string divide(const string& num, const string& divisor) {
    string result;  // Результат деления
    string current;  // Текущая часть числа

    // Обходим каждую цифру в числе
    for (char digit : num) {
        current.push_back(digit);  // Добавляем текущую цифру к текущему числу

        // Удаляем ведущие нули, если они есть
        while (current.size() > 1 && current[0] == '0') {
            current.erase(current.begin());
        }

        int count = 0;  // Количество раз, когда деление возможно
        // Проверяем, может ли current быть делимым на divisor
        while (compare(current, divisor) >= 0) {
            current = subtract(current, divisor);  // Вычитаем divisor из current
            ++count;  // Увеличиваем счетчик
        }

        result.push_back(count + '0');  // Добавляем результат деления к итоговому результату
    }

    // Убираем ведущие нули из результата
    size_t pos = result.find_first_not_of('0');
    return (pos != string::npos) ? result.substr(pos) : "0";  // Возвращаем результат без ведущих нулей
}

// Функция для сравнения двух больших чисел в строковом формате
int compare(const string& num1, const string& num2) {
    // Сравниваем длины строк
    if (num1.size() != num2.size()) {
        return num1.size() > num2.size() ? 1 : -1;  // Если длины разные, возвращаем результат
    }

    // Сравниваем строки по символам
    for (size_t i = 0; i < num1.size(); ++i) {
        if (num1[i] != num2[i]) {
            return num1[i] > num2[i] ? 1 : -1;  // Если символы различаются, возвращаем результат сравнения
        }
    }

    return 0;  // Если строки равны
}

// Функция для вычитания больших чисел в строковом формате
string subtract(const string& num1, const string& num2) {
    string result = num1;  // Копируем первую строку в результат
    int borrow = 0;  // Переменная для учета заимствований

    // Обходим строки с конца
    for (int i = num1.size() - 1, j = num2.size() - 1; i >= 0; --i, --j) {
        int diff = (result[i] - '0') - borrow - (j >= 0 ? (num2[j] - '0') : 0);  // Вычисляем разницу

        if (diff < 0) {  // Если разница отрицательная, то нужно заимствовать у предыдущей цифры
            diff += 10;
            borrow = 1;  // Увеличиваем заимствование
        }
        else {
            borrow = 0;  // Если разница положительная, то заимствование равно нулю
        }
        result[i] = diff + '0';  // Устанавливаем разницу как текущую цифру результата
    }

    // Удаляем ведущие нули
    size_t pos = result.find_first_not_of('0');
    return (pos != string::npos) ? result.substr(pos) : "0";  // Возвращаем результат без ведущих нулей
}

// Функция для нахождения наибольшего общего делителя (НОД) больших чисел в строковом формате
string gcd(string a, string b) {
    // Пока b не равно "0"
    while (b != "0") {
        // Вычитаем из a разность a и (a // b) * b
        a = subtract(a, multiply(divide(a, b), b));

        // Меняем местами a и b
        swap(a, b);
    }
    return a;  // Возвращаем результат, когда b становится "0"
}

// Функция для нахождения наименьшего общего кратного (НОК) больших чисел в строковом формате
string lcm(const string& a, const string& b) {
    // Находим НОД двух чисел
    string gcd_result = gcd(a, b);

    // Делим первое число на НОД
    string temp = divide(a, gcd_result);

    // Умножаем результат деления на второе число, чтобы получить НОК
    return multiply(temp, b);
}

// Функция для проверки, является ли строка корректным числом
bool isValidNumber(const string& str) {
    // Проверяем, что строка не пустая
    if (str.empty()) {
        return false;  // Пустая строка не является корректным числом
    }

    // Проверяем, что каждый символ в строке является цифрой
    return all_of(str.begin(), str.end(), ::isdigit);
}

// Функция для проверки, что число >= 10^11
bool isAtLeast10To11(const string& str) {
    // Если длина строки больше 12, то число гарантированно больше 10^11
    if (str.length() > 12) return true;
    // Если длина строки меньше 12, то число гарантированно меньше 10^11
    if (str.length() < 12) return false;
    // Если длина строки равна 12, сравниваем строку с "100000000000"
    return str >= "100000000000";
}
