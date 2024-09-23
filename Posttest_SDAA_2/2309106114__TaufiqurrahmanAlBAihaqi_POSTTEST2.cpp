#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_VARIAN = 10;

struct Sarung {
    string merk;
    string varian[MAX_VARIAN];
    int jumlahVarian;
};

vector<Sarung*> daftarSarung;

string nama = "opick";
string nim = "114";
int percobaanLogin = 0;
int batasLogin = 3;

// Fungsi login
bool login() {
    if (percobaanLogin == batasLogin) {
        cout << "Login gagal, silahkan coba lagi nanti." << endl;
        return false;
    }

    string inputNama, inputNim;
    cout << "Masukkan nama anda : ";
    cin >> inputNama;
    cout << "Masukkan NIM anda : ";
    cin >> inputNim;

    if (inputNama == nama && inputNim == nim) {
        cout << "Login berhasil" << endl;
        return true;
    } else {
        cout << "Login gagal" << endl;
        percobaanLogin++;
        return login(); // Rekursif untuk mencoba login lagi
    }
}

// Prosedur menampilkan daftar sarung
void tampilkanSarung() {
    if (daftarSarung.empty()) {
        cout << "Tidak ada sarung yang tersedia." << endl;
        return;
    }

    for (const auto& sarungPtr : daftarSarung) {
        cout << "Merk sarung: " << sarungPtr->merk << endl;
        for (int i = 0; i < sarungPtr->jumlahVarian; i++) {
            cout << "  Varian: " << sarungPtr->varian[i] << endl;
        }
        cout << endl;
    }
}

// Fungsi untuk menambahkan sarung
void tambahSarung() {
    string merkSarung, varianSarung;
    cout << "Masukkan merk sarung: ";
    cin >> merkSarung;

    Sarung* sarungBaru = new Sarung;
    sarungBaru->merk = merkSarung;
    sarungBaru->jumlahVarian = 0;

    cout << "Masukkan varian (ketik 'selesai' untuk berhenti): " << endl;
    cin.ignore();
    while (true) {
        getline(cin, varianSarung);
        if (varianSarung == "selesai") {
            break;
        }
        if (sarungBaru->jumlahVarian < MAX_VARIAN) {
            sarungBaru->varian[sarungBaru->jumlahVarian++] = varianSarung;
        } else {
            cout << "Jumlah varian telah mencapai batas maksimum." << endl;
            break;
        }
    }

    if (sarungBaru->jumlahVarian > 0) {
        daftarSarung.push_back(sarungBaru);
    } else {
        delete sarungBaru;
        cout << "Tidak ada varian sarung yang ditambahkan." << endl;
    }
}

// Fungsi untuk memperbarui sarung
void updateSarung() {
    string merkSarung, varianLama, varianBaru;
    cout << "Masukkan merk sarung yang ingin diupdate: ";
    cin >> merkSarung;

    bool ditemukan = false;
    for (auto& sarungPtr : daftarSarung) {
        if (sarungPtr->merk == merkSarung) {
            cout << "Masukkan varian yang ingin diupdate: ";
            cin.ignore();
            getline(cin, varianLama);

            bool varianDitemukan = false;
            for (int i = 0; i < sarungPtr->jumlahVarian; i++) {
                if (sarungPtr->varian[i] == varianLama) {
                    cout << "Masukkan varian baru: ";
                    getline(cin, varianBaru);
                    sarungPtr->varian[i] = varianBaru;
                    varianDitemukan = true;
                    break;
                }
            }

            if (!varianDitemukan) {
                cout << "Varian tidak ditemukan." << endl;
            }
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Merk sarung tidak ditemukan." << endl;
    }
}

// Fungsi untuk menghapus sarung
void hapusSarung() {
    string merkSarung;
    cout << "Masukkan merk sarung yang ingin dihapus: ";
    cin >> merkSarung;

    for (auto it = daftarSarung.begin(); it != daftarSarung.end(); ++it) {
        if ((*it)->merk == merkSarung) {
            delete *it;
            daftarSarung.erase(it);
            cout << "Sarung dengan merk " << merkSarung << " berhasil dihapus." << endl;
            return;
        }
    }

    cout << "Merk sarung tidak ditemukan." << endl;
}

int main() {
    cout << "Selamat datang program admin" << endl;
      cout << "'sarung setia samarinda'" << endl;

    if (!login()) {
        cout << "Login gagal, program akan keluar." << endl;
        return 1;
    }

    string pilihanMenu;

    while (true) {
        cout << "Menu: " << endl;
        cout << "1. Tampilkan semua sarung" << endl;
        cout << "2. Tambah sarung" << endl;
        cout << "3. Update sarung" << endl;
        cout << "4. Hapus sarung" << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanMenu;

        if (pilihanMenu == "1") {
            tampilkanSarung();
        } else if (pilihanMenu == "2") {
            tambahSarung();
        } else if (pilihanMenu == "3") {
            updateSarung();
        } else if (pilihanMenu == "4") {
            hapusSarung();
        } else if (pilihanMenu == "5") {
            cout << "Terima kasih telah menggunakan program ini. Sampai jumpa!" << endl;
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    for (auto& sarungPtr : daftarSarung) {
        delete sarungPtr;
    }

    return 0;
}
