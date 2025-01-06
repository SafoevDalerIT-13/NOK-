#include <iostream>

using namespace std;


long long NOD(long long a, long long b) {
	return b == 0 ? a : NOD(b, a % b);
}

long long NOK(long long m, long long n) {
	return (m * n) / NOD(m, n);
}

int main() {
	setlocale(LC_ALL, "RU");
	cout << "Здравствуйте, эта программа вычисляет НОК чисел m и n(m,n >= 10^11)." << endl << endl;
	long long m, n;
	cout << "Введите число m: ";
	cin >> m;
	while (true) {
		if (m < 100000000000LL) {
			cout << "Число m должно быть больше или равно 10^11 !!!\nПожалуйста попробуйте снова." << endl;
			cout << "Введите число m: ";
			cin >> m;
		}
		else
			break;
	}
	cout << "Введите число n: ";
	cin >> n;
	while (true) {
		if (n < 100000000000LL) {
			cout << "Число n должно быть больше или равно 10^11 !!!\nПожалуйста попробуйте снова." << endl;
			cout << "Введите число n: ";
			cin >> n;
		}
		else
			break;
	}
	long long res = NOK(m, n);
	cout << "НОК чисел m = " << m << " и n = " << n << " равен: " << res;

	return 0;
}
