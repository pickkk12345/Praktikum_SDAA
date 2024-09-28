#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk varian sarung
struct VarianNode {
    string varian;
    VarianNode* next;  // Pointer ke node varian berikutnya
};

// Struktur Sarung
struct Sarung {
    string merk;
    VarianNode* headVarian;  // Pointer ke linked list varian
};

// Single Linked List untuk menyimpan sarung
struct SarungNode {
    Sarung sarung;
    SarungNode* next;  // Pointer ke node sarung berikutnya
};

SarungNode* daftarSarung = nullptr; // Head untuk linked list sarung

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
    cout << "Masukkan nama anda: ";
    cin >> inputNama;
    cout << "Masukkan NIM anda: ";
    cin >> inputNim;

    if (inputNama == nama && inputNim == nim) {
        cout << "Login berhasil" << endl;
        return true;
    } else {
        cout << "Login gagal" << endl;
        percobaanLogin++;
        return login();
    }
}

void tambahVarian(VarianNode*& head, const string& varian) {
    VarianNode* newNode = new VarianNode{varian, nullptr};
    if (head == nullptr) {
        head = newNode;
    } else {
        VarianNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void tambahSarung() {
    string merkSarung, varianSarung;
    cout << "Masukkan merk sarung: ";
    cin >> merkSarung;

    SarungNode* newNode = new SarungNode;
    newNode->sarung.merk = merkSarung;
    newNode->sarung.headVarian = nullptr;
    newNode->next = nullptr;

    cout << "Masukkan varian (ketik 'selesai' untuk berhenti): " << endl;
    cin.ignore();
    while (true) {
        getline(cin, varianSarung);
        if (varianSarung == "selesai") {
            break;
        }
        tambahVarian(newNode->sarung.headVarian, varianSarung);
    }

    if (daftarSarung == nullptr) {
        daftarSarung = newNode;
    } else {
        SarungNode* temp = daftarSarung;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void tampilkanSarung() {
    if (daftarSarung == nullptr) {
        cout << "Tidak ada sarung yang tersedia." << endl;
        return;
    }

    SarungNode* tempSarung = daftarSarung;
    while (tempSarung != nullptr) {
        cout << "Merk sarung: " << tempSarung->sarung.merk << endl;
        VarianNode* tempVarian = tempSarung->sarung.headVarian;
        while (tempVarian != nullptr) {
            cout << "  Varian: " << tempVarian->varian << endl;
            tempVarian = tempVarian->next;
        }
        tempSarung = tempSarung->next;
        cout << endl;
    }
}

void updateSarung() {
    string merkSarung, varianLama, varianBaru;
    cout << "Masukkan merk sarung yang ingin diupdate: ";
    cin >> merkSarung;

    SarungNode* tempSarung = daftarSarung;
    bool ditemukan = false;

    while (tempSarung != nullptr) {
        if (tempSarung->sarung.merk == merkSarung) {
            cout << "Masukkan varian yang ingin diupdate: ";
            cin.ignore();
            getline(cin, varianLama);

            VarianNode* tempVarian = tempSarung->sarung.headVarian;
            bool varianDitemukan = false;

            while (tempVarian != nullptr) {
                if (tempVarian->varian == varianLama) {
                    cout << "Masukkan varian baru: ";
                    getline(cin, varianBaru);
                    tempVarian->varian = varianBaru;
                    varianDitemukan = true;
                    break;
                }
                tempVarian = tempVarian->next;
            }

            if (!varianDitemukan) {
                cout << "Varian tidak ditemukan." << endl;
            }
            ditemukan = true;
            break;
        }
        tempSarung = tempSarung->next;
    }

    if (!ditemukan) {
        cout << "Merk sarung tidak ditemukan." << endl;
    }
}

void hapusSarung() {
    string merkSarung;
    cout << "Masukkan merk sarung yang ingin dihapus: ";
    cin >> merkSarung;

    SarungNode* tempSarung = daftarSarung;
    SarungNode* prevSarung = nullptr;

    while (tempSarung != nullptr) {
        if (tempSarung->sarung.merk == merkSarung) {
            if (prevSarung == nullptr) {
                daftarSarung = tempSarung->next;
            } else {
                prevSarung->next = tempSarung->next;
            }

            VarianNode* tempVarian = tempSarung->sarung.headVarian;
            while (tempVarian != nullptr) {
                VarianNode* toDelete = tempVarian;
                tempVarian = tempVarian->next;
                delete toDelete;
            }

            delete tempSarung;
            cout << "Sarung dengan merk " << merkSarung << " berhasil dihapus." << endl;
            return;
        }

        prevSarung = tempSarung;
        tempSarung = tempSarung->next;
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

    return 0;
}
