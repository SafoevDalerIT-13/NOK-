#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype> // Для isdigit

using namespace std;

// Декларации функций
vector<int> multiply(const vector<int>& num1, const vector<int>& num2);
vector<int> divide(const vector<int>& num, const vector<int>& divisor);
int compare(const vector<int>& num1, const vector<int>& num2);
vector<int> subtract(const vector<int>& num1, const vector<int>& num2);
vector<int> gcd(vector<int> a, vector<int> b);
vector<int> lcm(const vector<int>& a, const vector<int>& b);
vector<int> stringToVector(const string& str);
void printVector(const vector<int>& num);
bool isValidNumber(const string& str);
bool isAtLeast10To11(const string& str);

// Функция для умножения больших чисел (вектор на вектор)
vector<int> multiply(const vector<int>& num1, const vector<int>& num2) {
    vector<int> result(num1.size() + num2.size(), 0);
    for (int i = num1.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = num2.size() - 1; j >= 0; --j) {
            int product = num1[i] * num2[j] + result[i + j + 1] + carry;
            result[i + j + 1] = product % 10;
            carry = product / 10;
        }
        result[i] += carry;
    }
    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }
    return result;
}

// Функция для деления одного большого числа на другое (приблизительное деление)
vector<int> divide(const vector<int>& num, const vector<int>& divisor) {
    vector<int> result;
    vector<int> current;

    for (size_t i = 0; i < num.size(); ++i) {
        current.push_back(num[i]);
        while (current.size() > 1 && current[0] == 0) {
            current.erase(current.begin());
        }

        int count = 0;
        while (compare(current, divisor) >= 0) {
            current = subtract(current, divisor);
            ++count;
        }
        result.push_back(count);
    }

    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}

// Функция для сравнения двух больших чисел
int compare(const vector<int>& num1, const vector<int>& num2) {
    if (num1.size() != num2.size()) {
        return num1.size() > num2.size() ? 1 : -1;
    }
    for (size_t i = 0; i < num1.size(); ++i) {
        if (num1[i] != num2[i]) {
            return num1[i] > num2[i] ? 1 : -1;
        }
    }
    return 0;
}

// Функция для вычитания двух больших чисел
vector<int> subtract(const vector<int>& num1, const vector<int>& num2) {
    vector<int> result(num1);
    int borrow = 0;

    for (int i = num1.size() - 1, j = num2.size() - 1; i >= 0; --i, --j) {
        int diff = result[i] - borrow - (j >= 0 ? num2[j] : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result[i] = diff;
    }

    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}

// Функция для нахождения НОД двух чисел
vector<int> gcd(vector<int> a, vector<int> b) {
    while (!(b.size() == 1 && b[0] == 0)) {
        a = subtract(a, multiply(divide(a, b), b));
        swap(a, b);
    }
    return a;
}

// Функция для нахождения НОК двух чисел
vector<int> lcm(const vector<int>& a, const vector<int>& b) {
    vector<int> gcd_result = gcd(a, b);
    vector<int> temp = divide(a, gcd_result);
    return multiply(temp, b);
}

// Функция для проверки, что строка содержит только цифры
bool isValidNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

// Функция для проверки, что число >= 10^11
bool isAtLeast10To11(const string& str) {
    if (str.length() > 12) return true; // Длина больше 12 гарантирует >= 10^11
    if (str.length() < 12) return false; // Длина меньше 12 гарантирует < 10^11
    return str >= "100000000000"; // Сравниваем строку
}

// Функция для преобразования строки в вектор цифр
vector<int> stringToVector(const string& str) {
    vector<int> result;
    for (char ch : str) {
        result.push_back(ch - '0');
    }
    return result;
}

// Функция для вывода числа
void printVector(const vector<int>& num) {
    for (int digit : num) {
        cout << digit;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    string strM, strN;
    cout << "Здравствуйте, эта программа вычисляет НОК чисел m и n(m,n >= 10^11)." << endl << endl; //Дружелюбный интерфейс
    // Ввод первого числа с проверками
    do {
        cout << "Введите первое число m (>= 10^11): ";
        cin >> strM;
        if (!isValidNumber(strM)) {
            cout << "Ошибка: Введите корректное число.\n";
        }
        else if (!isAtLeast10To11(strM)) {
            cout << "Ошибка: Число m должно быть >= 10^11.\n";
        }
    } while (!isValidNumber(strM) || !isAtLeast10To11(strM));

    // Ввод второго числа с проверками
    do {
        cout << "Введите второе число n (>= 10^11): ";
        cin >> strN;
        if (!isValidNumber(strN)) {
            cout << "Ошибка: Введите корректное число.\n";
        }
        else if (!isAtLeast10To11(strN)) {
            cout << "Ошибка: Число n должно быть >= 10^11.\n";
        }
    } while (!isValidNumber(strN) || !isAtLeast10To11(strN));

    // Преобразование и расчет НОК
    vector<int> m = stringToVector(strM);
    vector<int> n = stringToVector(strN);
    vector<int> result = lcm(m, n);

    cout << "Наименьшее общее кратное m = " << strM << " и " << "n = " << strN << " равен: ";
    printVector(result);

    return 0;
}
