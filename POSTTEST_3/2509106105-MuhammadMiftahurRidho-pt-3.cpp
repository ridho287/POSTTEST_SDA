#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <limits>
using namespace std;

#define MAX_DATA 100

struct Hewan {
    int id;
    string nama;
    string jenis;
    int umur;
    int harga;
};

struct Tindakan {
    Hewan pasien;
    string rekamMedis;
};

Hewan daftarHewan[MAX_DATA] = {
    {1, "Sid", "Kucing", 12, 1500000},
    {2, "Lex", "Kelinci", 8, 2500000},
    {3, "Jett", "Burung", 6, 500000},
    {4, "Rocket", "Hamster", 10, 1800000},
    {5, "Slanky", "Anjing", 14, 3000000}
};

int jumlah = 5;

// ================= QUEUE & STACK =================
Hewan antrian[MAX_DATA];
int front = -1, rear = -1;

Tindakan riwayat[MAX_DATA];
int top = -1;

// ================= UTILITY =================
void swapData(Hewan *a, Hewan *b) {
    Hewan temp = *a;
    *a = *b;
    *b = temp;
}

// ================= SORT ID (UNTUK FIBONACCI) =================
void sortByID(Hewan *arr) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if ((arr + j)->id > (arr + j + 1)->id) {
                swapData(arr + j, arr + j + 1);
            }
        }
    }
}

// ================= DATA HEWAN =================
void tampilData(Hewan *arr) {
    if (jumlah == 0) {
        cout << "\nData kosong!\n";
        return;
    }

    cout << "\n=== DATA HEWAN PAWCARE PETSHOP ===\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "ID      : " << (arr + i)->id << endl;
        cout << "Nama    : " << (arr + i)->nama << endl;
        cout << "Jenis   : " << (arr + i)->jenis << endl;
        cout << "Umur    : " << (arr + i)->umur << " bulan\n";
        cout << "Harga   : " << (arr + i)->harga << endl;
        cout << "-----------------------------\n";
    }
}

void tambahData(Hewan *&arr) {
    cout << "\n=== Tambah Data Hewan ===\n";
    cout << "ID Hewan   : ";
    cin >> (arr + jumlah)->id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nama Hewan : ";
    getline(cin, (arr + jumlah)->nama);

    cout << "Jenis      : ";
    getline(cin, (arr + jumlah)->jenis);

    cout << "Umur (bln) : ";
    cin >> (arr + jumlah)->umur;

    cout << "Harga      : ";
    cin >> (arr + jumlah)->harga;

    jumlah++;
    cout << "Data berhasil ditambahkan!\n";
}

void bubbleSortNama(Hewan *arr) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if ((arr + j)->nama > (arr + j + 1)->nama) {
                swapData(arr + j, arr + j + 1);
            }
        }
    }
    cout << "Data berhasil diurutkan (Nama A-Z)\n";
}

void selectionSortHarga(Hewan *arr) {
    for (int i = 0; i < jumlah - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < jumlah; j++) {
            if ((arr + j)->harga < (arr + minIndex)->harga) {
                minIndex = j;
            }
        }
        swapData(arr + i, arr + minIndex);
    }
    cout << "Data berhasil diurutkan (Harga Termurah)\n";
}

void linearSearchNama(Hewan *arr) {
    string cari;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Masukkan nama hewan: ";
    getline(cin, cari);

    for (int i = 0; i < jumlah; i++) {
        if ((arr + i)->nama == cari) {
            cout << "\nData ditemukan!\n";
            cout << "ID    : " << (arr + i)->id << endl;
            cout << "Nama  : " << (arr + i)->nama << endl;
            cout << "Jenis : " << (arr + i)->jenis << endl;
            cout << "Harga : " << (arr + i)->harga << endl;
            return;
        }
    }
    cout << "Data tidak ditemukan!\n";
}

void fibonacciSearch(Hewan *arr) {
    sortByID(arr);
    cout << "Data diurutkan berdasarkan ID terlebih dahulu...\n";

    int x;
    cout << "Masukkan ID hewan: ";
    cin >> x;

    int fib2 = 0, fib1 = 1;
    int fib = fib1 + fib2;

    while (fib < jumlah) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    int offset = -1;

    while (fib > 1) {
        int i = min(offset + fib2, jumlah - 1);

        if ((arr + i)->id < x) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if ((arr + i)->id > x) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else {
            cout << "\nData ditemukan!\n";
            cout << "Nama  : " << (arr + i)->nama << endl;
            cout << "Jenis : " << (arr + i)->jenis << endl;
            cout << "Harga : " << (arr + i)->harga << endl;
            return;
        }
    }
    cout << "Data tidak ditemukan!\n";
}

// ================= QUEUE =================
bool isQueueEmpty() {
    return front == -1 || front > rear;
}

void enqueueAntrian(Hewan *arr_hewan, Hewan *q) {
    int idCari;
    cout << "\nMasukkan ID hewan: ";
    cin >> idCari;

    Hewan pasienBaru;
    bool found = false;

    for (int i = 0; i < jumlah; i++) {
        if ((arr_hewan + i)->id == idCari) {
            pasienBaru = *(arr_hewan + i);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "ID tidak ditemukan!\n";
        return;
    }

    if (rear == MAX_DATA - 1) {
        cout << "Antrian penuh!\n";
        return;
    }

    if (front == -1) front = 0;
    rear++;
    *(q + rear) = pasienBaru;

    cout << "Berhasil masuk antrian!\n";
}

void tampilAntrian(Hewan *q) {
    if (isQueueEmpty()) {
        cout << "\nAntrian kosong!\n";
        return;
    }

    for (int i = front; i <= rear; i++) {
        cout << (i - front + 1) << ". "
             << (q + i)->nama << " (ID: " << (q + i)->id << ")\n";
    }
}

// ================= STACK =================
bool isStackEmpty() {
    return top == -1;
}

void pushRiwayat(Tindakan *s, Tindakan t) {
    if (top == MAX_DATA - 1) {
        cout << "Stack penuh!\n";
        return;
    }
    top++;
    *(s + top) = t;
}

void popRiwayat(Tindakan *s) {
    if (isStackEmpty()) {
        cout << "Tidak ada riwayat!\n";
        return;
    }
    cout << "Menghapus: " << (s + top)->pasien.nama << endl;
    top--;
}

void tampilRiwayat(Tindakan *s) {
    if (isStackEmpty()) {
        cout << "Kosong!\n";
        return;
    }

    for (int i = top; i >= 0; i--) {
        cout << (s + i)->pasien.nama
             << " -> " << (s + i)->rekamMedis << endl;
    }
}

// ================= PANGGIL PASIEN =================
void panggilPasien(Hewan *q, Tindakan *s) {
    if (isQueueEmpty()) {
        cout << "Tidak ada antrian!\n";
        return;
    }

    Hewan pasien = *(q + front);
    front++;

    if (front > rear) {
        front = rear = -1;
    }

    cout << "Memanggil: " << pasien.nama << endl;

    Tindakan t;
    t.pasien = pasien;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan tindakan: ";
    getline(cin, t.rekamMedis);

    pushRiwayat(s, t);
}

// ================= PEEK =================
void peekData(Hewan *q, Tindakan *s) {
    cout << "\nQUEUE: ";
    if (!isQueueEmpty())
        cout << (q + front)->nama << endl;
    else
        cout << "Kosong\n";

    cout << "STACK: ";
    if (!isStackEmpty())
        cout << (s + top)->pasien.nama << endl;
    else
        cout << "Kosong\n";
}

// ================= MENU =================
void menu() {
    cout << "\n1. Tampil\n2. Tambah\n3. Cari Nama\n4. Cari ID\n";
    cout << "5. Sort Nama\n6. Sort Harga\n";
    cout << "7. Enqueue\n8. Panggil\n9. Antrian\n";
    cout << "10. Riwayat\n11. Pop\n12. Peek\n13. Keluar\n";
}

// ================= MAIN =================
int main() {
    int pilih;
    Hewan *ptrData = daftarHewan;
    Hewan *ptrQueue = antrian;
    Tindakan *ptrStack = riwayat;

    do {
        menu();
        cin >> pilih;

        switch (pilih) {
            case 1: tampilData(ptrData); break;
            case 2: tambahData(ptrData); break;
            case 3: linearSearchNama(ptrData); break;
            case 4: fibonacciSearch(ptrData); break;
            case 5: bubbleSortNama(ptrData); break;
            case 6: selectionSortHarga(ptrData); break;
            case 7: enqueueAntrian(ptrData, ptrQueue); break;
            case 8: panggilPasien(ptrQueue, ptrStack); break;
            case 9: tampilAntrian(ptrQueue); break;
            case 10: tampilRiwayat(ptrStack); break;
            case 11: popRiwayat(ptrStack); break;
            case 12: peekData(ptrQueue, ptrStack); break;
        }

    } while (pilih != 13);

    return 0;
}