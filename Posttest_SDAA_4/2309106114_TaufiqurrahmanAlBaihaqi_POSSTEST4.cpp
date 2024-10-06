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

// Struktur Node untuk Stack dan Queue
struct StackNode {
    string data;
    StackNode* next;
};

struct QueueNode {
    string data;
    QueueNode* next;
};

SarungNode* daftarSarung = nullptr; // Head untuk linked list sarung
StackNode* top = nullptr;           // Head untuk Stack
QueueNode* front = nullptr;         // Head untuk Queue (front)
QueueNode* rear = nullptr;          // Tail untuk Queue (rear)

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

// Fungsi Stack
void pushStack(const string& data) {
    StackNode* newNode = new StackNode{data, top};
    top = newNode;
}

void popStack() {
    if (top == nullptr) {
        cout << "Stack kosong!" << endl;
        return;
    }
    StackNode* temp = top;
    top = top->next;
    cout << "Data '" << temp->data << "' dihapus dari stack." << endl;
    delete temp;
}

void displayStack() {
    if (top == nullptr) {
        cout << "Stack kosong!" << endl;
        return;
    }
    StackNode* temp = top;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// Fungsi Queue
void enqueueQueue(const string& data) {
    QueueNode* newNode = new QueueNode{data, nullptr};
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeueQueue() {
    if (front == nullptr) {
        cout << "Queue kosong!" << endl;
        return;
    }
    QueueNode* temp = front;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    cout << "Data '" << temp->data << "' dihapus dari queue." << endl;
    delete temp;
}

void displayQueue() {
    if (front == nullptr) {
        cout << "Queue kosong!" << endl;
        return;
    }
    QueueNode* temp = front;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
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
        cout << "5. Tambah data ke Stack" << endl;
        cout << "6. Hapus data dari Stack" << endl;
        cout << "7. Tampilkan Stack" << endl;
        cout << "8. Tambah data ke Queue" << endl;
        cout << "9. Hapus data dari Queue" << endl;
        cout << "10. Tampilkan Queue" << endl;
        cout << "0. Keluar" << endl;

        cout << "Pilihan: ";
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
            string data;
            cout << "Masukkan data untuk Stack: ";
            cin >> data;
            pushStack(data);
        } else if (pilihanMenu == "6") {
            popStack();
        } else if (pilihanMenu == "7") {
            displayStack();
        } else if (pilihanMenu == "8") {
            string data;
            cout << "Masukkan data untuk Queue: ";
            cin >> data;
            enqueueQueue(data);
        } else if (pilihanMenu == "9") {
            dequeueQueue();
        } else if (pilihanMenu == "10") {
            displayQueue();
        } else if (pilihanMenu == "0") {
            break;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }

    return 0;
}
