#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Struct untuk menyimpan data pasien
struct Patient {
    string recordNumber;
    string name;
    int age;
    string gender;
    string visitDate;
    string diagnosis;
    string doctor;
};

// Fungsi untuk menambahkan data pasien baru
void addPatient(vector<Patient>& patients) {
    Patient p;
    
    cout << "\n--- Tambah Data Pasien ---\n";
    cout << "Nomor Rekam Medis: ";
    cin >> p.recordNumber;
    cin.ignore(); // Membersihkan buffer input
    
    cout << "Nama Pasien: ";
    getline(cin, p.name);
    
    cout << "Usia: ";
    cin >> p.age;
    cin.ignore();
    
    cout << "Jenis Kelamin: ";
    getline(cin, p.gender);
    
    cout << "Tanggal Kunjungan: ";
    getline(cin, p.visitDate);
    
    cout << "Diagnosa: ";
    getline(cin, p.diagnosis);
    
    cout << "Dokter yang Menangani: ";
    getline(cin, p.doctor);

    patients.push_back(p);

    // Simpan ke file
    ofstream file("patients.txt", ios::app);
    if (file.is_open()) {
        file << p.recordNumber << "|" << p.name << "|" << p.age << "|" << p.gender << "|"
             << p.visitDate << "|" << p.diagnosis << "|" << p.doctor << "\n";
        file.close();
        cout << "Data pasien berhasil disimpan!\n";
    } else {
        cout << "Gagal membuka file untuk menyimpan data!\n";
    }
}

// Fungsi untuk menampilkan riwayat pasien berdasarkan nomor rekam medis
void viewPatient(const vector<Patient>& patients) {
    string recordNumber;
    cout << "\n--- Lihat Riwayat Pasien ---\n";
    cout << "Masukkan Nomor Rekam Medis: ";
    cin >> recordNumber;

    bool found = false;
    for (const auto& p : patients) {
        if (p.recordNumber == recordNumber) {
            found = true;
            cout << "\n=== Riwayat Pasien ===\n";
            cout << "Nomor Rekam Medis: " << p.recordNumber << "\n";
            cout << "Nama: " << p.name << "\n";
            cout << "Usia: " << p.age << "\n";
            cout << "Jenis Kelamin: " << p.gender << "\n";
            cout << "Tanggal Kunjungan: " << p.visitDate << "\n";
            cout << "Diagnosa: " << p.diagnosis << "\n";
            cout << "Dokter: " << p.doctor << "\n";
        }
    }

    if (!found) {
        cout << "Data pasien tidak ditemukan!\n";
    }
}

// Fungsi untuk memuat data pasien dari file
void loadPatients(vector<Patient>& patients) {
    ifstream file("patients.txt");
    if (file.is_open()) {
        Patient p;
        string line;
        while (getline(file, line)) {
            size_t pos = 0;
            pos = line.find('|'); p.recordNumber = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find('|'); p.name = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find('|'); p.age = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
            pos = line.find('|'); p.gender = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find('|'); p.visitDate = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find('|'); p.diagnosis = line.substr(0, pos); line.erase(0, pos + 1);
            p.doctor = line;

            patients.push_back(p);
        }
        file.close();
    }
}

int main() {
    vector<Patient> patients;
    loadPatients(patients);

    int choice;
    do {
        cout << "\n=== Program Riwayat Kunjungan Pasien ===\n";
        cout << "1. Tambah Data Pasien\n";
        cout << "2. Lihat Riwayat Pasien\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatient(patients);
                break;
            case 2:
                viewPatient(patients);
                break;
            case 3:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 3);

    return 0;
}
