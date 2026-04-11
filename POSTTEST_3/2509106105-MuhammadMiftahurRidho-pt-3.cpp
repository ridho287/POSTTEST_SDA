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

// ================= SORT ID =================
void sortByID(Hewan *arr) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if ((arr + j)->id > (arr + j + 1)->id) {
                swapData(arr + j, arr + j + 1);
            }
        }
    }
}

// ================= MENU =================
void menu() {
    cout << "\n====================================\n";
    cout << "     MENU UTAMA PAWCARE PETSHOP\n";
    cout << "====================================\n";
    cout << "1.  Tampilkan Data Hewan\n";
    cout << "2.  Tambah Data Hewan\n";
    cout << "3.  Cari Nama Hewan\n";
    cout << "4.  Cari ID Hewan\n";
    cout << "5.  Urutkan Nama\n";
    cout << "6.  Urutkan Harga\n";
    cout << "------------------------------------\n";
    cout << "7.  Tambah ke Antrian\n";
    cout << "8.  Panggil Pasien\n";
    cout << "9.  Tampilkan Antrian\n";
    cout << "10. Tampilkan Riwayat\n";
    cout << "11. Hapus Riwayat Terakhir\n";
    cout << "12. Lihat Data Terdepan\n";
    cout << "13. Keluar\n";
    cout << "====================================\n";
    cout << "Pilih menu: ";
}

// ================= DATA =================
void tampilData(Hewan *arr) {
    if (jumlah == 0) {
        cout << "\n[INFO] Data kosong!\n";
        return;
    }

    cout << "\n========== DATA HEWAN ==========\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "Data ke-" << i+1 << endl;
        cout << "ID    : " << (arr + i)->id << endl;
        cout << "Nama  : " << (arr + i)->nama << endl;
        cout << "Jenis : " << (arr + i)->jenis << endl;
        cout << "Umur  : " << (arr + i)->umur << " bulan\n";
        cout << "Harga : Rp " << (arr + i)->harga << endl;
        cout << "-------------------------------\n";
    }
}

void tambahData(Hewan *&arr) {
    cout << "\n=== TAMBAH DATA HEWAN ===\n";

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
    cout << "[SUKSES] Data berhasil ditambahkan!\n";
}

// ================= SEARCH =================
void linearSearchNama(Hewan *arr) {
    string cari;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Masukkan nama hewan: ";
    getline(cin, cari);

    for (int i = 0; i < jumlah; i++) {
        if ((arr + i)->nama == cari) {
            cout << "\n[DATA DITEMUKAN]\n";
            cout << "ID    : " << (arr + i)->id << endl;
            cout << "Nama  : " << (arr + i)->nama << endl;
            cout << "Jenis : " << (arr + i)->jenis << endl;
            cout << "Harga : " << (arr + i)->harga << endl;
            return;
        }
    }
    cout << "[INFO] Data tidak ditemukan!\n";
}

void fibonacciSearch(Hewan *arr) {
    sortByID(arr);

    int x;
    cout << "Masukkan ID hewan: ";
    cin >> x;

    int fib2 = 0, fib1 = 1, fib = fib1 + fib2;

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
            cout << "\n[DATA DITEMUKAN]\n";
            cout << "Nama  : " << (arr + i)->nama << endl;
            cout << "Jenis : " << (arr + i)->jenis << endl;
            return;
        }
    }
    cout << "[INFO] Data tidak ditemukan!\n";
}

// ================= SORT =================
void bubbleSortNama(Hewan *arr) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if ((arr + j)->nama > (arr + j + 1)->nama) {
                swapData(arr + j, arr + j + 1);
            }
        }
    }
    cout << "[SUKSES] Data diurutkan berdasarkan nama!\n";
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
    cout << "[SUKSES] Data diurutkan berdasarkan harga!\n";
}

// ================= QUEUE =================
bool isQueueEmpty() {
    return front == -1 || front > rear;
}

void enqueueAntrian(Hewan *arr_hewan, Hewan *q) {
    cout << "\n=== TAMBAH ANTRIAN ===\n";

    int idCari;
    cout << "Masukkan ID hewan: ";
    cin >> idCari;

    for (int i = 0; i < jumlah; i++) {
        if ((arr_hewan + i)->id == idCari) {

            if (rear == MAX_DATA - 1) {
                cout << "[ERROR] Antrian penuh!\n";
                return;
            }

            if (front == -1) front = 0;
            rear++;

            *(q + rear) = *(arr_hewan + i);

            cout << "[SUKSES] " << (arr_hewan + i)->nama 
                 << " masuk ke antrian!\n";
            return;
        }
    }

    cout << "[ERROR] ID tidak ditemukan!\n";
}

void tampilAntrian(Hewan *q) {
    if (isQueueEmpty()) {
        cout << "\n[INFO] Antrian kosong!\n";
        return;
    }

    cout << "\n===== DAFTAR ANTRIAN =====\n";
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
        cout << "[ERROR] Stack penuh!\n";
        return;
    }
    top++;
    *(s + top) = t;
    cout << "[SUKSES] Riwayat disimpan!\n";
}

void popRiwayat(Tindakan *s) {
    if (isStackEmpty()) {
        cout << "[INFO] Riwayat kosong!\n";
        return;
    }
    cout << "[DIHAPUS] " << (s + top)->pasien.nama << endl;
    top--;
}

void tampilRiwayat(Tindakan *s) {
    if (isStackEmpty()) {
        cout << "[INFO] Riwayat kosong!\n";
        return;
    }

    cout << "\n===== RIWAYAT =====\n";
    for (int i = top; i >= 0; i--) {
        cout << "- " << (s + i)->pasien.nama
             << " -> " << (s + i)->rekamMedis << endl;
    }
}

// ================= PANGGIL =================
void panggilPasien(Hewan *q, Tindakan *s) {
    if (isQueueEmpty()) {
        cout << "[INFO] Tidak ada antrian!\n";
        return;
    }

    Hewan pasien = *(q + front);
    front++;

    if (front > rear) front = rear = -1;

    cout << "\n=== MEMANGGIL PASIEN ===\n";
    cout << "Nama : " << pasien.nama << endl;
    cout << "ID   : " << pasien.id << endl;

    Tindakan t;
    t.pasien = pasien;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan tindakan: ";
    getline(cin, t.rekamMedis);

    pushRiwayat(s, t);
}

// ================= PEEK =================
void peekData(Hewan *q, Tindakan *s) {
    cout << "\n===== PEEK =====\n";

    cout << "Antrian depan: ";
    if (!isQueueEmpty())
        cout << (q + front)->nama << endl;
    else
        cout << "Kosong\n";

    cout << "Riwayat terakhir: ";
    if (!isStackEmpty())
        cout << (s + top)->pasien.nama << endl;
    else
        cout << "Kosong\n";
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
            case 13: 
                cout << "\nTerima kasih telah menggunakan layanan Pawcare Petshop!\n"; 
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan masukkan angka 1-13.\n";
        }

    } while (pilih != 13);

    return 0;
}