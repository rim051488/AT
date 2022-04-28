#include<random>
#include<iostream>
#include<windows.h>

using namespace std;

int main() {
	// 予測不能な乱数を作るときはこれが必要
	random_device rd;
	auto seed = rd();
	std::mt19937 mt(seed);
	// 乱数の範囲を指定する
	uniform_int_distribution<int> dist(20,80);
	uniform_real_distribution<float> kdist(0.0, 1.0);
	for (int i = 0; i <= 20; ++i)
	{
		cout << kdist(mt) << endl;
	}
}