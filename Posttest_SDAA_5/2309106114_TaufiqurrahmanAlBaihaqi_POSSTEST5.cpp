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

// Function prototypes for sorting
SarungNode* mergeSortAscending(SarungNode* head);
SarungNode* quickSortDescending(SarungNode* head);

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

// Merge Sort (Ascending) implementation
SarungNode* merge(SarungNode* left, SarungNode* right) {
    if (!left) return right;
    if (!right) return left;

    SarungNode* result = nullptr;

    if (left->sarung.merk <= right->sarung.merk) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

SarungNode* getMiddle(SarungNode* head) {
    if (!head) return head;
    SarungNode* slow = head;
    SarungNode* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

SarungNode* mergeSortAscending(SarungNode* head) {
    if (!head || !head->next) return head;

    SarungNode* middle = getMiddle(head);
    SarungNode* nextToMiddle = middle->next;
    middle->next = nullptr;

    SarungNode* left = mergeSortAscending(head);
    SarungNode* right = mergeSortAscending(nextToMiddle);

    return merge(left, right);
}

// Quick Sort (Descending) implementation
SarungNode* getTail(SarungNode* head) {
    while (head != nullptr && head->next != nullptr)
        head = head->next;
    return head;
}

SarungNode* partition(SarungNode* head, SarungNode* end, SarungNode** newHead, SarungNode** newEnd) {
    SarungNode* pivot = end;
    SarungNode* prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->sarung.merk > pivot->sarung.merk) {
            if (*newHead == nullptr)
                *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            SarungNode* tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if (*newHead == nullptr)
        *newHead = pivot;

    *newEnd = tail;
    return pivot;
}

SarungNode* quickSortRecur(SarungNode* head, SarungNode* end) {
    if (!head || head == end)
        return head;

    SarungNode* newHead = nullptr, *newEnd = nullptr;
    SarungNode* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        SarungNode* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = nullptr;

        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

SarungNode* quickSortDescending(SarungNode* head) {
    return quickSortRecur(head, getTail(head));
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
        cout << "11. Sort sarung (Ascending - Merge Sort)" << endl;
        cout << "12. Sort sarung (Descending - Quick Sort)" << endl;
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
        } else if (pilihanMenu == "11") {
            daftarSarung = mergeSortAscending(daftarSarung);
            cout << "Daftar sarung telah diurutkan secara ascending menggunakan Merge Sort." << endl;
        } else if (pilihanMenu == "12") {
            daftarSarung = quickSortDescending(daftarSarung);
            cout << "Daftar sarung telah diurutkan secara descending menggunakan Quick Sort." << endl;
        } else if (pilihanMenu == "0") {
            break;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }

    return 0;
}