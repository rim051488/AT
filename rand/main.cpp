#include<random>
#include<iostream>
#include<windows.h>

using namespace std;

int main() {
	// �\���s�\�ȗ��������Ƃ��͂��ꂪ�K�v
	random_device rd;
	auto seed = rd();
	std::mt19937 mt(seed);
	// �����͈̔͂��w�肷��
	uniform_int_distribution<int> dist(20,80);
	uniform_real_distribution<float> kdist(0.0, 1.0);
	for (int i = 0; i <= 20; ++i)
	{
		cout << kdist(mt) << endl;
	}
}