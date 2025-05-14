#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Barang {
    string nama;
    string kode;
    int harga;
    int stok;
    Barang* next;
};

Barang* head = nullptr;


void tambahBarang(string nama, string kode, int harga, int stok) {
    Barang* baru = new Barang{nama, kode, harga, stok, nullptr};
    if (!head) {
        head = baru;
    } else {
        Barang* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
}

void tampilkanBarang(bool termurah) {
    Barang* arr[100];
    int count = 0;
    Barang* temp = head;

    while (temp) {
        arr[count++] = temp;
        temp = temp->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool kondisi = termurah ? arr[j]->harga > arr[j + 1]->harga : arr[j]->harga < arr[j + 1]->harga;
            if (kondisi) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    cout << "===============================================\n";
    cout << "| Kode   | Nama Barang         | Harga  | Stok |\n";
    cout << "===============================================\n";
    for (int i = 0; i < count; i++) {
        cout << "| " << setw(6) << arr[i]->kode 
             << " | " << setw(20) << arr[i]->nama 
             << " | " << setw(6) << arr[i]->harga 
             << " | " << setw(4) << arr[i]->stok << " |\n";
    }
    cout << "===============================================\n";
}

// Fungsi hapus barang
void hapusBarang() {
    cout << "\n===== DAFTAR STOK SAAT INI =====\n";
    if (!head) {
        cout << "Stok kosong, tidak ada yang bisa dihapus.\n";
        return;
    }

    tampilkanBarang(true); 

    string nama;
    cout << "\nMasukkan nama barang yang ingin dihapus: ";
    getline(cin, nama);

    Barang* temp = head;
    Barang* prev = nullptr;

    while (temp && temp->nama != nama) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Barang \"" << nama << "\" tidak ditemukan!\n";
        return;
    }

    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Barang \"" << nama << "\" berhasil dihapus.\n";

    cout << "\n===== DAFTAR STOK TERBARU =====\n";
    if (head)
        tampilkanBarang(true);
    else
        cout << "Stok sekarang kosong.\n";
}


void inputData() {
    int jumlah;
    cout << "Jumlah barang yang akan ditambahkan: ";
    cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; ++i) {
        string nama, kode;
        int harga, stok;

        cout << "Barang ke-" << i + 1 << endl;
        cout << "Nama barang  : "; getline(cin, nama);
        cout << "Harga barang : "; cin >> harga;
        cout << "Kode barang  : "; cin >> kode;
        cout << "Jumlah stok  : "; cin >> stok;
        cin.ignore();

        tambahBarang(nama, kode, harga, stok);
    }
}

void menu() {
    int pilihan;

    do {
        cout << "\n=============================================\n";
        cout << "|     SISTEM MANAJEMEN STOK GUDANG          |\n";
        cout << "=============================================\n";
        cout << "| 1. Input stok barang                      |\n";
        cout << "| 2. Lihat daftar stok                      |\n";
        cout << "| 3. Hapus barang dari stok                 |\n";
        cout << "| 0. Keluar                                 |\n";
        cout << "=============================================\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                inputData();
                break;
            case 2: {
                int opsi;
                cout << "1. Urutkan dari harga termurah\n";
                cout << "2. Urutkan dari harga termahal\n";
                cout << "Pilih: ";
                cin >> opsi;
                cin.ignore();
                tampilkanBarang(opsi == 1);
                break;
            }
            case 3:
                hapusBarang();
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);
}


int main() {
    menu();
    return 0;
}