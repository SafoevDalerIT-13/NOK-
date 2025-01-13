#include "modylNOK.h"
#include <iostream>

using namespace std;

/**
  Главная функция программы: Программа вычисляет наименьшее общее кратное (НОК) двух чисел m и n,
  где оба числа вводятся пользователем в виде строки и должны быть >= 10^11.
 */

int main() {
    setlocale(LC_ALL, "RU"); // Устанавливаем локализацию для вывода сообщений на русском языке.
    string strM, strN;
    // Приветствие и вводные сообщения
    cout << "Здравствуйте! Эта программа вычисляет НОК чисел m и n (m, n >= 10^11)." << endl << endl;

    // Цикл ввода первого числа с проверкой
    do {
        cout << "Введите первое число m (>= 10^11): ";
        cin >> strM;
        // Проверка на корректность ввода: только цифры
        if (!isValidNumber(strM)) {
            cout << "Ошибка: Введите корректное число.\n";
        }
        // Проверка на соответствие условию: число >= 10^11
        else if (!isAtLeast10To11(strM)) {
            cout << "Ошибка: Число m должно быть >= 10^11.\n";
        }
    } while (!isValidNumber(strM) || !isAtLeast10To11(strM));  // Повторяем, пока ввод некорректен

    // Цикл ввода второго числа с проверкой
    do {
        cout << "Введите второе число n (>= 10^11): ";
        cin >> strN;
        // Проверка на корректность ввода: только цифры
        if (!isValidNumber(strN)) {
            cout << "Ошибка: Введите корректное число.\n";
        }
        // Проверка на соответствие условию: число >= 10^11
        else if (!isAtLeast10To11(strN)) {
            cout << "Ошибка: Число n должно быть >= 10^11.\n";
        }
    } while (!isValidNumber(strN) || !isAtLeast10To11(strN));  // Повторяем, пока ввод некорректен

    // Преобразование введенных строк в вектор цифр
    vector<int> m = stringToVector(strM);
    vector<int> n = stringToVector(strN);

    // Вычисление НОК двух чисел
    vector<int> result = lcm(m, n);

    // Вывод результата
    cout << "Наименьшее общее кратное m = " << strM << " и n = " << strN << " равно: ";
    printVector(result);

    return 0; // Завершение программы
}
