#include <iostream>
#include <iomanip>
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
    Hewan* next;
};

struct Tindakan {
    Hewan pasien;
    string rekamMedis;
    Tindakan* next;
};

Hewan daftarHewan[MAX_DATA] = {
    {1, "Sid", "Kucing", 12, 1500000, NULL},
    {2, "Lex", "Kelinci", 8, 2500000, NULL},
    {3, "Jett", "Burung", 6, 500000, NULL},
    {4, "Rocket", "Hamster", 10, 1800000, NULL},
    {5, "Slanky", "Anjing", 14, 3000000, NULL}
};

int jumlah = 5;

Hewan *frontLL = NULL;
Hewan *rearLL = NULL;

Tindakan *topLL = NULL;

void menu() {
    cout << "\n====================================\n";
    cout << "     MENU UTAMA PAWCARE PETSHOP\n";
    cout << "====================================\n";
    cout << "1.  Tampilkan Data Hewan\n";
    cout << "2.  Tambah Data Hewan\n";
    cout << "3.  Tambah ke Antrian\n";
    cout << "4.  Hapus dari Antrian\n";
    cout << "5.  Panggil Pasien\n";
    cout << "6.  Tampilkan Antrian\n";
    cout << "7.  Hapus Riwayat Terakhir\n";
    cout << "8.  Tampilkan Riwayat\n";
    cout << "9.  Lihat Data Terdepan\n";
    cout << "10. Keluar\n";
    cout << "====================================\n";
    cout << "Pilih menu: ";
}

void tampilData(Hewan *arr) {
    if (jumlah == 0) {
        cout << "\nData kosong\n";
        return;
    }

    cout << "\n========== DATA HEWAN ==========\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "Data ke-" << i+1 << endl;
        cout << "ID    : " << (arr+i)->id << endl;
        cout << "Nama  : " << (arr+i)->nama << endl;
        cout << "Jenis : " << (arr+i)->jenis << endl;
        cout << "Umur  : " << (arr+i)->umur << " bulan\n";
        cout << "Harga : Rp " << (arr+i)->harga << endl;
        cout << "-------------------------------\n";
    }
}

void tambahData(Hewan *&arr) {
    cout << "ID: "; cin >> (arr+jumlah)->id;
    cin.ignore();

    cout << "Nama: "; getline(cin, (arr+jumlah)->nama);
    cout << "Jenis: "; getline(cin, (arr+jumlah)->jenis);
    cout << "Umur: "; cin >> (arr+jumlah)->umur;
    cout << "Harga: "; cin >> (arr+jumlah)->harga;

    (arr+jumlah)->next = NULL;
    jumlah++;

    cout << "Data berhasil ditambahkan\n";
}

void enqueueLL(Hewan *data) {
    Hewan *baru = new Hewan;
    *baru = *data;
    baru->next = NULL;

    if (frontLL == NULL) {
        frontLL = rearLL = baru;
    } else {
        rearLL->next = baru;
        rearLL = baru;
    }

    cout << data->nama << " ditambahkan ke antrian\n";
}

void dequeueLL(Hewan &keluar) {
    if (frontLL == NULL) {
        cout << "Antrian kosong\n";
        return;
    }

    Hewan *hapus = frontLL;
    keluar = *hapus;

    cout << "Menghapus dari antrian: " << hapus->nama << endl;

    frontLL = frontLL->next;

    if (frontLL == NULL) rearLL = NULL;

    delete hapus;
}

void tampilAntrianLL() {
    if (!frontLL) {
        cout << "\nAntrian kosong\n";
        return;
    }

    cout << "\n===== DAFTAR ANTRIAN =====\n";
    Hewan *temp = frontLL;
    int i = 1;

    while (temp) {
        cout << i++ << ". "
             << temp->nama << " (ID: " << temp->id << ")\n";
        temp = temp->next;
    }
}

void pushLL(Tindakan t) {
    Tindakan *baru = new Tindakan;
    *baru = t;
    baru->next = topLL;
    topLL = baru;
}

void popLL() {
    if (!topLL) {
        cout << "Riwayat kosong\n";
        return;
    }

    Tindakan *hapus = topLL;
    cout << "Menghapus riwayat: " << hapus->pasien.nama << endl;

    topLL = topLL->next;
    delete hapus;
}

void tampilRiwayatLL() {
    if (!topLL) {
        cout << "\nRiwayat kosong\n";
        return;
    }

    cout << "\n===== RIWAYAT PASIEN =====\n";
    Tindakan *temp = topLL;

    while (temp) {
        cout << "- " << temp->pasien.nama
             << " (ID: " << temp->pasien.id << ")\n";
        cout << "  Tindakan: " << temp->rekamMedis << endl;
        cout << "--------------------------\n";
        temp = temp->next;
    }
}

void tambahAntrianLL(Hewan *arr) {
    int id;
    cout << "Masukkan ID: ";
    cin >> id;

    for (int i = 0; i < jumlah; i++) {
        if ((arr+i)->id == id) {
            enqueueLL(arr+i);
            return;
        }
    }

    cout << "ID tidak ditemukan\n";
}

void panggilLL() {
    if (!frontLL) {
        cout << "\nTidak ada antrian\n";
        return;
    }

    Hewan pasien;
    dequeueLL(pasien);

    cout << "\n=== MEMANGGIL PASIEN ===\n";
    cout << "Nama : " << pasien.nama << endl;
    cout << "ID   : " << pasien.id << endl;

    Tindakan t;
    t.pasien = pasien;

    cin.ignore();
    cout << "Masukkan tindakan: ";
    getline(cin, t.rekamMedis);

    pushLL(t);
}

void peekLL() {
    cout << "\n===== DATA TERDEPAN =====\n";

    cout << "Antrian depan: ";
    if (frontLL)
        cout << frontLL->nama << endl;
    else
        cout << "Kosong\n";

    cout << "Riwayat terakhir: ";
    if (topLL)
        cout << topLL->pasien.nama << endl;
    else
        cout << "Kosong\n";
}

int main() {
    int pilih;
    Hewan *ptrData = daftarHewan;

    do {
        menu();
        cin >> pilih;

        switch (pilih) {
            case 1: tampilData(ptrData); break;
            case 2: tambahData(ptrData); break;
            case 3: tambahAntrianLL(ptrData); break;
            case 4: {
                Hewan temp;
                dequeueLL(temp);
                break;
            }
            case 5: panggilLL(); break;
            case 6: tampilAntrianLL(); break;
            case 7: popLL(); break;
            case 8: tampilRiwayatLL(); break;
            case 9: peekLL(); break;
            case 10: 
                cout << "\nTerima kasih telah menggunakan Pawcare Petshop\n"; 
                break;
            default: 
                cout << "\nPilihan tidak valid\n";
        }

    } while (pilih != 10);

    return 0;
}