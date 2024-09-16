#include <iostream>
using namespace std;
    
int hitungPascal(int baris, int kolom) {
    if (kolom == 0 || kolom == baris) {
        return 1;
    }

    return hitungPascal(baris - 1, kolom - 1) + hitungPascal(baris - 1, kolom);
}

int main() {
    int jumlahTingkat = 3;

    cout << "Segitiga Pascal 3 tingkat (siku-siku):" << endl;

    for (int baris = 0; baris < jumlahTingkat; baris++) {
        for (int kolom = 0; kolom <= baris; kolom++) {
            cout << hitungPascal(baris, kolom) << " ";
        }
        cout << endl; 
    }

    return 0;
}
