#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Hewan {
    int id;
    string nama;
    string jenis;
    int umur;
    int harga;
};

Hewan daftarHewan[100] = {
    {1, "Sid", "Kucing", 12, 1500000},
    {2, "Lex", "Kelinci", 8, 2500000},
    {3, "Jett", "Burung", 6, 500000},
    {4, "Rocket", "Hamster", 10, 1800000},
    {5, "Slanky", "Anjing", 14, 3000000}
};

int jumlah = 5;

void swapData(Hewan *a, Hewan *b) {
    Hewan temp = *a;
    *a = *b;
    *b = temp;
}

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
    cin.ignore();

    cout << "Nama Hewan : ";
    getline(cin, (arr + jumlah)->nama);

    cout << "Jenis      : ";
    getline(cin, (arr + jumlah)->jenis);

    cout << "Umur (bulan): ";
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
    cin.ignore();

    cout << "Masukkan nama hewan: ";
    getline(cin, cari);

    bool ditemukan = false;

    for (int i = 0; i < jumlah; i++) {
        if ((arr + i)->nama == cari) {
            cout << "\nData ditemukan!\n";
            cout << "ID    : " << (arr + i)->id << endl;
            cout << "Nama  : " << (arr + i)->nama << endl;
            cout << "Jenis : " << (arr + i)->jenis << endl;
            cout << "Harga : " << (arr + i)->harga << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Data tidak ditemukan!\n";
    }
}

void fibonacciSearch(Hewan *arr) {
    int x;
    cout << "Masukkan ID hewan: ";
    cin >> x;

    int fib2 = 0;
    int fib1 = 1;
    int fib = fib1 + fib2;

    while (fib < jumlah) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    int offset = -1;

    cout << "\nProses pencarian:\n";

    while (fib > 1) {
        int i = min(offset + fib2, jumlah - 1);

        cout << "Cek index ke-" << i << endl;

        if ((arr + i)->id < x) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        else if ((arr + i)->id > x) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
        else {
            cout << "\nData ditemukan!\n";
            cout << "Nama  : " << (arr + i)->nama << endl;
            cout << "Jenis : " << (arr + i)->jenis << endl;
            cout << "Harga : " << (arr + i)->harga << endl;
            return;
        }
    }

    cout << "Data tidak ditemukan!\n";
}

void tampilMenu() {
    cout << "\n=== MENU PAWCARE PETSHOP ===\n";
    cout << "1. Tampil Data Hewan\n";
    cout << "2. Tambah Data Hewan\n";
    cout << "3. Cari Nama (Linear Search)\n";
    cout << "4. Cari ID (Fibonacci Search)\n";
    cout << "5. Urutkan Nama (Bubble Sort)\n";
    cout << "6. Urutkan Harga (Selection Sort)\n";
    cout << "7. Keluar\n";
    cout << "Pilih menu: ";
}

int main() {
    int pilih;
    Hewan *ptr = daftarHewan;

    do {
        tampilMenu();
        cin >> pilih;

        switch (pilih) {
            case 1: tampilData(ptr); break;
            case 2: tambahData(ptr); break;
            case 3: linearSearchNama(ptr); break;
            case 4: fibonacciSearch(ptr); break;
            case 5: bubbleSortNama(ptr); break;
            case 6: selectionSortHarga(ptr); break;
            case 7: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 7);
    
    return 0;
}