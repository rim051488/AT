#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

void Func(int idx) {
    cout << "Func" << endl;
}
void Sub(int idx) {
    cout << "Sub" << endl;
}

class Janken {
private:
    void Guu()
    {
        cout << "グー" << endl;
        pFunc = &Janken::Choki;
    }
    void Choki()
    {
        cout << "チョキ" << endl;
        pFunc = &Janken::Paa;
    }
    void Paa()
    {
        cout << "パー" << endl;
        pFunc = &Janken::Guu;
    }
    void (Janken::* pFunc)() = nullptr;
public:
    Janken() :pFunc(nullptr) {
        pFunc = &Janken::Guu;
    }
    void Update() {
        (this->*pFunc)();
    }
};

int main()
{
    //// 関数ポインタ
    //void(*pFunc) () = nullptr;
    //pFunc = Func();
    //cout << "start" << endl;
    //int a[] = { 1,2,3,4,5,6,7 };
    //for_each(begin(a), end(a), Func);
    ////pFunc();
    ////pFunc = Func;
    ////pFunc();
    //// 関数オブジェクト
    //function<void(int)> func1 = [](int idx) {
    //    cout << "func" << idx*2 << endl;
    //};
    ////auto func1 = [](int idx) {
    ////    cout << "func" << idx*2 << endl;
    ////};
    //for_each(begin(a), end(a), func1);
    //class Functor {
    //public:
    //    void operator()(int idx) {
    //        cout << "functor" << idx * 3 << endl;
    //    }
    //};
    //auto func = Functor();
    //func(15);
    //for_each(begin(a), end(a), func);
    Janken janken;
    for (int i = 0; i < 20; ++i) {
        janken.Update();
    }
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
