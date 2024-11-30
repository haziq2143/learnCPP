#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Kebiasaan
{
    string habits;
    string description;
    string frekuensi;
    int hari;
    bool done;
};

vector<Kebiasaan> dataKebiasaan;

void addData()
{
    Kebiasaan Kebiasaan;
    cout << "Masukkan kebiasaan yang ingin ditambahkan " << endl;
    cin.ignore();
    getline(cin, Kebiasaan.habits);
    cout << "Masukan deskripsi singkatnya " << endl;
    getline(cin, Kebiasaan.description);
    cout << "Masukan Berapa hari " << endl;
    cin >> Kebiasaan.hari;
    Kebiasaan.done = false;

    ofstream fileOutput("data Kebiasaan.txt", ios::app);
    if (fileOutput.is_open())
    {
        fileOutput << "Kebiasaan: " << Kebiasaan.habits << endl;
        fileOutput << "Deskripsi: " << Kebiasaan.description << endl;
        fileOutput << "Hari: " << Kebiasaan.hari << endl;
        fileOutput << "Sudah dilaksanakan? " << "Belum" << endl;
        fileOutput << "====================" << endl;

        fileOutput.close();

        cout << "Kebiasaan " << Kebiasaan.habits << " Berhasil ditambahkan :)" << endl;
    }
    dataKebiasaan.push_back(Kebiasaan);
}

void readData()
{
    // Kosongkan vector sebelum membaca data baru dari file
    dataKebiasaan.clear();

    ifstream fileInput("data Kebiasaan.txt");
    if (!fileInput.is_open())
    {
        cout << "File tidak ditemukan atau tidak bisa dibuka.\n";
        return;
    }

    Kebiasaan temp; // Struktur sementara untuk menyimpan data
    string line;    // Untuk membaca baris per baris

    while (getline(fileInput, line))
    {
        if (line.find("Kebiasaan: ") != string::npos)
        {
            temp.habits = line.substr(11); // Ambil teks setelah "Kebiasaan: "
        }
        else if (line.find("Deskripsi: ") != string::npos)
        {
            temp.description = line.substr(11); // Ambil teks setelah "Deskripsi: "
        }
        else if (line.find("Hari: ") != string::npos)
        {
            temp.hari = stoi(line.substr(6)); // Ambil angka setelah "Hari: "
        }
        else if (line.find("Sudah dilaksanakan? ") != string::npos)
        {
            string status = line.substr(20); // Ambil teks setelah "Sudah dilaksanakan? "
            temp.done = (status == "Sudah" || status == "1");
        }
        else if (line == "====================")
        {
            // Cek kelengkapan data sebelum menambah ke vector
            if (!temp.habits.empty() && !temp.description.empty() && temp.hari > 0)
            {
                dataKebiasaan.push_back(temp);
            }
            temp = Kebiasaan(); // Reset variabel sementara
        }
    }

    fileInput.close();

    // Cetak isi data setelah selesai membaca file
    cout << "\n======== Daftar Kebiasaan ========\n";
    for (size_t i = 0; i < dataKebiasaan.size(); i++)
    {
        cout << "====================" << endl;
        cout << i + 1 << ". Kebiasaan: " << dataKebiasaan[i].habits << endl;
        cout << "   Deskripsi: " << dataKebiasaan[i].description << endl;
        cout << "   Hari: " << dataKebiasaan[i].hari << endl;
        cout << "   Sudah?: " << (dataKebiasaan[i].done ? "Sudah" : "Belum") << endl;
    }
}
void updateData()
{
    dataKebiasaan.clear();

    ifstream fileInput("data Kebiasaan.txt");
    if (!fileInput.is_open())
    {
        cout << "File tidak ditemukan atau tidak bisa dibuka.\n";
        return;
    }

    Kebiasaan temp; // Struktur sementara untuk menyimpan data
    string line;    // Untuk membaca baris per baris

    while (getline(fileInput, line))
    {
        if (line.find("Kebiasaan: ") != string::npos)
        {
            temp.habits = line.substr(11); // Ambil teks setelah "Kebiasaan: "
        }
        else if (line.find("Deskripsi: ") != string::npos)
        {
            temp.description = line.substr(11); // Ambil teks setelah "Deskripsi: "
        }
        else if (line.find("Hari: ") != string::npos)
        {
            temp.hari = stoi(line.substr(6)); // Ambil angka setelah "Hari: "
        }
        else if (line.find("Sudah dilaksanakan? ") != string::npos)
        {
            string status = line.substr(20); // Ambil teks setelah "Sudah dilaksanakan? "
            temp.done = (status == "Sudah" || status == "1");
        }
        else if (line == "====================")
        {
            // Cek kelengkapan data sebelum menambah ke vector
            if (!temp.habits.empty() && !temp.description.empty() && temp.hari > 0)
            {
                dataKebiasaan.push_back(temp);
            }
            temp = Kebiasaan(); // Reset variabel sementara
        }
    }

    fileInput.close();

    if (!dataKebiasaan.empty())
    {
        cout << "\n======== Update Kebiasaan ========\n";
        for (size_t i = 0; i < dataKebiasaan.size(); i++)
        {
            cout << i + 1 << ". Habits: " << dataKebiasaan[i].habits << endl;
        }

        int n;
        cout << "Masukan Nomor Yang ingin Di Update: ";
        cin >> n;

        if (n < 1 || n > dataKebiasaan.size())
        {
            cout << "input yang bener" << endl;
        }
        else
        {
            string habits, deskripsi;
            int day;
            cout << "Masukan Kebiasaan yang baru: ";
            cin.ignore();
            getline(cin, habits);
            cout << "Masukan Deskripsi yang baru: ";
            getline(cin, deskripsi);
            cout << "Masukan Jumlah Hari yang baru: ";
            cin >> day;

            dataKebiasaan[n - 1].habits = habits;
            dataKebiasaan[n - 1].description = deskripsi;
            dataKebiasaan[n - 1].hari = day;

            cout << "Data Berhasil di update" << endl;

            ofstream fileOutput("data Kebiasaan.txt");
            for (size_t i = 0; i < dataKebiasaan.size(); i++)
            {
                fileOutput << "Kebiasaan: " << dataKebiasaan[i].habits << endl;
                fileOutput << "Deskripsi: " << dataKebiasaan[i].description << endl;
                fileOutput << "Hari: " << dataKebiasaan[i].hari << endl;
                fileOutput << "Sudah dilaksanakan? " << (dataKebiasaan[i].done ? "Sudah" : "Belum") << endl;
                fileOutput << "====================" << endl;
            }
            fileOutput.close();
        }
    }
    else
    {
        cout << "Tidak ada Kebiasaan" << endl;
    }
}

void statusData()
{
    cout << "\n======== Status Kebiasaan ========\n";
    dataKebiasaan.clear();

    ifstream fileInput("data Kebiasaan.txt");
    if (!fileInput.is_open())
    {
        cout << "File tidak ditemukan atau tidak bisa dibuka.\n";
        return;
    }

    Kebiasaan temp; // Struktur sementara untuk menyimpan data
    string line;    // Untuk membaca baris per baris

    while (getline(fileInput, line))
    {
        if (line.find("Kebiasaan: ") != string::npos)
        {
            temp.habits = line.substr(11); // Ambil teks setelah "Kebiasaan: "
        }
        else if (line.find("Deskripsi: ") != string::npos)
        {
            temp.description = line.substr(11); // Ambil teks setelah "Deskripsi: "
        }
        else if (line.find("Hari: ") != string::npos)
        {
            temp.hari = stoi(line.substr(6)); // Ambil angka setelah "Hari: "
        }
        else if (line.find("Sudah dilaksanakan? ") != string::npos)
        {
            string status = line.substr(20); // Ambil teks setelah "Sudah dilaksanakan? "
            temp.done = (status == "Sudah" || status == "1");
        }
        else if (line == "====================")
        {
            // Cek kelengkapan data sebelum menambah ke vector
            if (!temp.habits.empty() && !temp.description.empty() && temp.hari > 0)
            {
                dataKebiasaan.push_back(temp);
            }
            temp = Kebiasaan(); // Reset variabel sementara
        }
    }

    fileInput.close();

    for (size_t i = 0; i < dataKebiasaan.size(); i++)
    {
        if (dataKebiasaan[i].done == false)
        {
            cout << i + 1 << ". Habits: " << dataKebiasaan[i].habits << endl;
        }
    }
    int n;
    cout << "Input nomor yang ingin di tandai 'Sudah': ";
    cin >> n;

    if (n < 1 || n > dataKebiasaan.size())
    {
        cout << "Input Tidak Valid" << endl;
    }
    else
    {
        dataKebiasaan[n - 1].done = true;

        ofstream fileOutput("data Kebiasaan.txt");
        for (size_t i = 0; i < dataKebiasaan.size(); i++)
        {
            fileOutput << "Kebiasaan: " << dataKebiasaan[i].habits << endl;
            fileOutput << "Deskripsi: " << dataKebiasaan[i].description << endl;
            fileOutput << "Hari: " << dataKebiasaan[i].hari << endl;
            fileOutput << "Sudah dilaksanakan? " << (dataKebiasaan[i].done ? "Sudah" : "Belum") << endl;
            fileOutput << "====================" << endl;
        }
        fileOutput.close();
        cout << "Data Berhasil Ditandai 'Sudah'" << endl;
    }
}
void menuUtama()
{
    int menu;
    do
    {
        cout << "====== HABIFY ======" << endl;
        cout << "1. Tambah Kebiasaan" << endl;
        cout << "2. Lihat Kebiasaan" << endl;
        cout << "3. Update Kebiasaan" << endl;
        cout << "4. Memberi Status Kebiasaan" << endl; /* menu mirip delete*/
        cout << "5. Exit" << endl;
        cout << "pilih menu: ";
        cin >> menu;
        if (menu == 1)
        {
            addData();
        }
        else if (menu == 2)
        {
            readData();
        }
        else if (menu == 3)
        {
            updateData();
        }
        else if (menu == 4)
        {
            statusData();
        }
        else if (menu == 5)
        {
            cout << "Terimakasih Telah Menggunakan Aplikasi Ini" << endl;
        }
        else
        {
            cout << "menu tidak ada pak, bapak typo :)" << endl;
        }
    } while (menu != 5);
}

int main()
{
    menuUtama();

    return 0;
}

void tambahmenu()
{
}