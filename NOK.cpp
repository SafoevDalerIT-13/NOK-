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
	cout << "������������, ��� ��������� ��������� ��� ����� m � n(m,n >= 10^11)." << endl << endl;
	long long m, n;
	cout << "������� ����� m: ";
	cin >> m;
	while (true) {
		if (m < 100000000000LL) {
			cout << "����� m ������ ���� ������ ��� ����� 10^11 !!!\n���������� ���������� �����." << endl;
			cout << "������� ����� m: ";
			cin >> m;
		}
		else
			break;
	}
	cout << "������� ����� n: ";
	cin >> n;
	while (true) {
		if (n < 100000000000LL) {
			cout << "����� n ������ ���� ������ ��� ����� 10^11 !!!\n���������� ���������� �����." << endl;
			cout << "������� ����� m: ";
			cin >> n;
		}
		else
			break;
	}
	long long res = NOK(m, n);
	cout << "��� ����� m = " << m << " � n = " << n << " �����: " << res;

	return 0;
}