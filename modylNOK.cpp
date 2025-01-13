#include "modylNOK.h"
#include <algorithm>
#include <iostream>

// Функция для преобразования строки в вектор цифр
vector<int> stringToVector(const string& str) {
    vector<int> result;
    for (char ch : str) {
        result.push_back(ch - '0'); // Преобразуем каждый символ в цифру и добавляем в вектор
    }
    return result;
}

//  Функция для проверки, что строка содержит только цифры
bool isValidNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit); // Проверяем, что строка состоит только из цифр
}

// Функция для проверки, что число >= 10^11
bool isAtLeast10To11(const string& str) {
    if (str.length() > 12) return true; // Длина больше 12 гарантирует >= 10^11
    if (str.length() < 12) return false; // Длина меньше 12 гарантирует < 10^11
    return str >= "100000000000"; // Сравниваем строку
}

// Функция для умножения больших чисел (вектор на вектор)
vector<int> multiply(const vector<int>& num1, const vector<int>& num2) {
    vector<int> result(num1.size() + num2.size(), 0); // Результат имеет размер суммы длин двух векторов
    for (int i = num1.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = num2.size() - 1; j >= 0; --j) {
            int product = num1[i] * num2[j] + result[i + j + 1] + carry;
            result[i + j + 1] = product % 10; // Остаток от деления на 10 (разряд в результате)
            carry = product / 10; // Перенос в следующую разряд
        }
        result[i] += carry; // Добавляем остаток из carry
    }
    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin()); // Удаляем ведущие нули
    }
    return result;
}

// Функция для деления одного большого числа на другое (приблизительное деление)
vector<int> divide(const vector<int>& num, const vector<int>& divisor) {
    vector<int> result; // Результат деления
    vector<int> current;

    for (size_t i = 0; i < num.size(); ++i) {
        current.push_back(num[i]); // Постепенно добавляем цифры из num
        while (current.size() > 1 && current[0] == 0) {
            current.erase(current.begin()); // Удаляем ведущие нули
        }

        int count = 0;
        while (compare(current, divisor) >= 0) {
            current = subtract(current, divisor); // Вычитаем делитель из текущего остатка
            ++count;
        }
        result.push_back(count); // Добавляем количество целых частей
    }

    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin()); // Удаляем ведущие нули
    }

    return result;
}

// Функция для сравнения двух больших чисел
int compare(const vector<int>& num1, const vector<int>& num2) {
    if (num1.size() != num2.size()) {
        return num1.size() > num2.size() ? 1 : -1; // Сравниваем размеры векторов
    }
    for (size_t i = 0; i < num1.size(); ++i) {
        if (num1[i] != num2[i]) {
            return num1[i] > num2[i] ? 1 : -1;  // Сравниваем цифры
        }
    }
    return 0;
}

// Функция для вычитания двух больших чисел
vector<int> subtract(const vector<int>& num1, const vector<int>& num2) {
    vector<int> result(num1); // Копируем первое число в результат
    int borrow = 0; // Займ для вычитания

    for (int i = num1.size() - 1, j = num2.size() - 1; i >= 0; --i, --j) {
        int diff = result[i] - borrow - (j >= 0 ? num2[j] : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1; // Если разница отрицательная, добавляем перенос
        }
        else {
            borrow = 0;  // В противном случае перенос не нужен
        }
        result[i] = diff; // Записываем результат
    }

    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin()); // Удаляем ведущие нули
    }

    return result;
}

//  Функция для нахождения НОД двух чисел
vector<int> gcd(vector<int> a, vector<int> b) {
    while (!(b.size() == 1 && b[0] == 0)) {
        a = subtract(a, multiply(divide(a, b), b)); // Находим остаток от деления
        swap(a, b);  // Меняем значения
    }
    return a;
}

// Функция для нахождения НОК двух чисел
vector<int> lcm(const vector<int>& a, const vector<int>& b) {
    vector<int> gcd_result = gcd(a, b);
    vector<int> temp = divide(a, gcd_result);
    return multiply(temp, b);
}

//  Функция для вывода числа
void printVector(const vector<int>& num) {
    for (int digit : num) {
        cout << digit;
    }
    cout << endl;
}
