#include <iostream> // Mengimpor pustaka untuk input/output
#include <map>      // Mengimpor pustaka untuk menggunakan map (struktur data untuk menyimpan pasangan kunci-nilai)
#include <string>   // Mengimpor pustaka untuk menggunakan string
#include <iomanip>  // Mengimpor pustaka untuk manipulasi output (seperti format IPK)
#include <cstdlib>  // Mengimpor pustaka untuk fungsi exit()
#include <limits>   // Mengimpor pustaka untuk cin.ignore() yang digunakan untuk membersihkan input
#include <conio.h>

using namespace std;

// Struktur untuk menyimpan nilai grade dan IPK
struct Nilai
{
    map<string, float> gradeMap; // Map untuk menyimpan grade dan nilai numeriknya

    Nilai()
    { // Konstruktor untuk menginisialisasi gradeMap
        // Menetapkan nilai untuk setiap grade
        gradeMap["A"] = 4.0;
        gradeMap["A-"] = 3.75;
        gradeMap["B+"] = 3.5;
        gradeMap["B"] = 3.0;
        gradeMap["B-"] = 2.75;
        gradeMap["C+"] = 2.5;
        gradeMap["C"] = 2.0;
        gradeMap["D"] = 1.0;
        gradeMap["E"] = 0.0;
    }
};

// Struktur untuk menyimpan data mahasiswa
struct Mhs
{
    string nama;              // Nama mahasiswa
    string nim;               // Nomor Induk Mahasiswa
    string jurusan;           // Jurusan mahasiswa
    string alamat;            // Alamat mahasiswa
    float mk1, mk2, mk3, mk4; // Nilai mata kuliah
    float ipk;                // Indeks Prestasi Kumulatif
    string status;            // Status kelulusan (Cumlaude atau Memuaskan)
};

// Struktur untuk node dalam linked list
struct Node
{
    Mhs mhs;    // Data mahasiswa
    Node *next; // Pointer ke node berikutnya
};

// Kelas untuk mengelola linked list mahasiswa
class LinkedList
{
private:
    Node *head; // Pointer ke node pertama dalam linked list
public:
    LinkedList() : head(NULL) {} // Konstruktor untuk menginisialisasi head dengan NULL

    // Fungsi untuk menambahkan node baru ke linked list
    void addNode(Mhs mhs)
    {
        Node *newNode = new Node; // Membuat node baru
        newNode->mhs = mhs;       // Menyimpan data mahasiswa ke node baru
        newNode->next = NULL;     // Node baru tidak memiliki node berikutnya
        if (head == NULL)
        {                   // Jika linked list kosong
            head = newNode; // Node baru menjadi head
        }
        else
        {
            Node *temp = head; // Menggunakan temp untuk traversing
            while (temp->next != NULL)
            {                      // Mencari node terakhir
                temp = temp->next; // Melanjutkan ke node berikutnya
            }
            temp->next = newNode; // Menambahkan node baru di akhir
        }
    }

    // Fungsi untuk menghapus node berdasarkan jurusan
    void deleteNode(string jurusan)
    {
        Node *temp = head;    // Pointer untuk traversing
        Node *prev = NULL;    // Pointer untuk menyimpan node sebelumnya
        bool deleted = false; // Flag untuk menandakan apakah ada yang dihapus

        while (temp != NULL)
        { // Selama masih ada node
            if (temp->mhs.jurusan == jurusan)
            { // Jika jurusan sama
                if (temp == head)
                {                      // Jika node yang akan dihapus adalah head
                    head = temp->next; // Mengubah head ke node berikutnya
                    delete temp;       // Menghapus node
                    temp = head;       // Mengatur temp ke head baru
                }
                else
                {
                    prev->next = temp->next; // Menghubungkan node sebelumnya ke node berikutnya
                    delete temp;             // Menghapus node
                    temp = prev->next;       // Mengatur temp ke node berikutnya
                }
                deleted = true; // Menandakan bahwa ada yang dihapus
            }
            else
            {
                prev = temp;       // Memperbarui prev ke node saat ini
                temp = temp->next; // Melanjutkan ke node berikutnya
            }
        }

        // Menampilkan pesan berdasarkan hasil penghapusan
        if (deleted)
        {
            cout << "Data Berhasil Dihapus..." << endl;
        }
        else
        {
            cout << "Data Tidak Ditemukan!!!" << endl;
        }
    }

    // ```cpp
    // Fungsi untuk memperbarui data mahasiswa berdasarkan NIM
    void updateNode(string nim)
    {
        Node *temp = head;  // Pointer untuk traversing
        bool found = false; // Flag untuk menandakan apakah data ditemukan

        while (temp != NULL)
        { // Selama masih ada node
            if (temp->mhs.nim == nim)
            {                 // Jika NIM sama
                found = true; // Menandakan bahwa data ditemukan
                Nilai nilai;  // Membuat objek nilai untuk grade

                if (temp->mhs.ipk < 3.00)
                { // Memeriksa apakah IPK kurang dari 3.00
                    cout << "IPK anda tidak memenuhi syarat untuk mengupdate nilai" << endl;
                    return; // Keluar dari fungsi jika tidak memenuhi syarat
                }
                else
                {
                    cout << "Update Data Mahasiswa\n";                                                   // Menampilkan pesan update
                    inputNilai(temp->mhs, nilai);                                                        // Memasukkan nilai baru
                    temp->mhs.ipk = (temp->mhs.mk1 + temp->mhs.mk2 + temp->mhs.mk3 + temp->mhs.mk4) / 4; // Menghitung IPK baru
                    temp->mhs.status = (temp->mhs.ipk > 3.5) ? "Cumlaude" : "Memuaskan";                 // Menentukan status kelulusan

                    cout << "Data berhasil di update!!!" << endl; // Menampilkan pesan berhasil
                    return;                                       // Keluar dari fungsi setelah memperbarui
                }
            }
            temp = temp->next; // Melanjutkan ke node berikutnya
        }
        if (!found)
        { // Jika data tidak ditemukan
            cout << "Data Mahasiswa Dengan NIM: " << nim << " Tidak Ditemukan.\n";
        }
    }

    // Fungsi untuk membaca dan menampilkan IPK mahasiswa berdasarkan jurusan
    void readIpk(string jurusan)
    {
        Node *temp = head;  // Pointer untuk traversing
        bool found = false; // Flag untuk menandakan apakah ada mahasiswa dengan jurusan tersebut

        while (temp != NULL)
        { // Selama masih ada node
            if (temp->mhs.jurusan == jurusan)
            {                                // Jika jurusan sama
                displayMahasiswa(temp->mhs); // Menampilkan data mahasiswa
                found = true;                // Menandakan bahwa ada mahasiswa ditemukan
            }
            temp = temp->next; // Melanjutkan ke node berikutnya
        }
        if (!found)
        { // Jika tidak ada mahasiswa dengan jurusan tersebut
            cout << "Jurusan " << jurusan << " Tidak Ditemukan.\n";
        }
    }

    // Fungsi untuk mengurutkan mahasiswa berdasarkan IPK
    void sortIpk()
    {
        if (head == NULL)
        { // Jika linked list kosong
            cout << "Data Kosong" << endl;
            return; // Keluar dari fungsi
        }

        bool swapped; // Flag untuk menandakan apakah ada pertukaran
        Node *temp;   // Pointer untuk traversing

        do
        {
            swapped = false; // Mengatur flag swapped ke false
            temp = head;     // Mengatur temp ke head
            while (temp->next != NULL)
            { // Selama masih ada node berikutnya
                if (temp->mhs.ipk < temp->next->mhs.ipk)
                {                                     // Jika IPK saat ini lebih kecil dari IPK berikutnya
                    swap(temp->mhs, temp->next->mhs); // Tukar data mahasiswa
                    swapped = true;                   // Menandakan bahwa ada pertukaran
                }
                temp = temp->next; // Melanjutkan ke node berikutnya
            }
        } while (swapped); // Ulangi jika ada pertukaran

        cout << "IPK Mahasiswa Diurutkan dari yang terbesar ke terkecil" << endl; // Menampilkan pesan
        displayAll();                                                             // Menampilkan semua data mahasiswa
    }

    // Fungsi untuk menampilkan semua data mahasiswa
    void displayAll()
    {
        Node *temp = head; // Pointer untuk traversing
        while (temp != NULL)
        {                                // Selama masih ada node
            displayMahasiswa(temp->mhs); // Menampilkan data mahasiswa
            temp = temp->next;           // Melanjutkan ke node berikutnya
        }
    }

    // Fungsi untuk memasukkan nilai mahasiswa
    void inputNilai(Mhs &mhs, Nilai &nilai)
    {
        string gradeInput;
        for (int i = 1; i <= 4; i++)
        { // Loop untuk memasukkan nilai 4 mata kuliah
            while (true)
            {                                                                    // Loop hingga nilai valid dimasukkan
                cout << "Input Nilai " << i << " (A, A-, B+, B, B-, C, D, E): "; // Menampilkan prompt input
                cin >> gradeInput;                                               // Menerima input grade
                float grade = nilai.gradeMap[gradeInput];                        // Mengambil nilai numerik dari grade
                if (grade > 0 || gradeInput == "E")
                { // Memeriksa apakah grade valid
                    if (i == 1)
                        mhs.mk1 = grade; // Menyimpan nilai mk1
                    else if (i == 2)
                        mhs.mk2 = grade; // Menyimpan nilai mk2
                    else if (i == 3)
                        mhs.mk3 = grade; // Menyimpan nilai mk3
                    else
                        mhs.mk4 = grade; // Menyimpan nilai mk4
                    break;               // Keluar dari loop jika nilai valid
                }
                else
                {
                    cout << "Grade Tidak Valid!!" << endl; // Menampilkan pesan jika grade tidak valid
                }
            }
        }
    }

    // Fungsi untuk menampilkan data mahasiswa
    void displayMahasiswa(Mhs &mhs)
    {
        cout << "Nama: " << mhs.nama << "\nNIM: " << mhs.nim                                     // Menampilkan nama dan NIM
             << "\nJurusan: " << mhs.jurusan << "\nIPK: " << fixed << setprecision(2) << mhs.ipk // Menampilkan jurusan dan IPK
             << "\nStatus: " << mhs.status << "\n---------------------------\n";                 // Menampilkan status
    }

    // Fungsi untuk mendapatkan mahasiswa dengan IPK tertinggi dan terendah
    void getIpkHighestAndLowest()
    {
        if (head == NULL)
        {                                   // Jika linked list kosong
            cout << "Data kosong." << endl; // Menampilkan pesan
            return;                         // Keluar dari fungsi
        }

        Node *mhs = head;             // Pointer untuk traversing
        float highest = mhs->mhs.ipk; // Mengatur nilai tertinggi awal
        float lowest = mhs->mhs.ipk;  // Mengatur nilai terendah awal
        Node *highestStudent = mhs;   // Menyimpan pointer mahasiswa dengan IPK tertinggi
        Node *lowestStudent = mhs;    // Menyimpan pointer mahasiswa dengan IPK terendah

        while (mhs != NULL)
        { // Selama masih ada node
            if (mhs->mhs.ipk > highest)
            {                           // Jika IPK lebih tinggi dari nilai tertinggi
                highest = mhs->mhs.ipk; // Memperbarui nilai tertinggi
                highestStudent = mhs;   // Memperbarui pointer mahasiswa dengan IPK tertinggi
            }

            if (mhs->mhs.ipk < lowest)
            {                          // Jika IPK lebih rendah dari nilai terendah
                lowest = mhs->mhs.ipk; // Memperbarui nilai terendah
                lowestStudent = mhs;   // Memperbarui pointer mahasiswa dengan IPK terendah
            }
            mhs = mhs->next; // Melanjutkan ke node berikutnya
        }
        // Menampilkan mahasiswa dengan IPK tertinggi dan terendah
        cout << "Mahasiswa dengan IPK tertinggi: " << highestStudent->mhs.nama
             << " (IPK: " << highestStudent->mhs.ipk << ")\n";
        cout << "Mahasiswa dengan IPK terendah: " << lowestStudent->mhs.nama
             << " (IPK: " << lowestStudent->mhs.ipk << ")\n";
    }

    // Fungsi untuk mencari data mahasiswa berdasarkan NIM
    void searchData()
    {
        string nim;                                 // Variabel untuk menyimpan NIM yang dicari
        cout << "Cari Mahasiswa Berdasarkan NIM: "; // Menampilkan prompt
        cin >> nim;                                 // Menerima input NIM

        bool found = false; // Flag untuk menandakan apakah data ditemukan
        Node *mhs = head;   // Pointer untuk traversing

        while (mhs != NULL)
        { // Selama masih ada node
            if (mhs->mhs.nim == nim)
            { // Jika NIM sama
                // Menampilkan data mahasiswa yang ditemukan
                cout << " Mahasiswa Dengan NIM: " << nim << " Ditemukan:" << endl;
                cout << "Nama: " << mhs->mhs.nama << endl;
                cout << "NIM: " << mhs->mhs.nim << endl;
                cout << "Jurusan: " << mhs->mhs.jurusan << endl;
                cout << "IPK: " << mhs->mhs.ipk << endl;

                found = true; // Menandakan bahwa data ditemukan
                break;        // Keluar dari loop setelah menemukan data
            }
            mhs = mhs->next; // Melanjutkan ke node berikutnya
        }
        if (!found)
        {                                                                      // Jika data tidak ditemukan
            cout << "Data dengan NIM: " << nim << " Tidak Ditemukan." << endl; // Menampilkan pesan
        }
    }

    // Fungsi untuk menambahkan data mahasiswa baru
    void addMhs()
    {
        Mhs mhs;     // Membuat objek mahasiswa
        Nilai nilai; // Membuat objek nilai untuk grade
        cout << "Nama: ";
        getline(cin, mhs.nama); // Menerima input nama
        cout << "NIM: ";
        getline(cin, mhs.nim); // Menerima input NIM
        cout << "Jurusan: ";
        getline(cin, mhs.jurusan);                               // Menerima input jurusan
        inputNilai(mhs, nilai);                                  // Memasukkan nilai mahasiswa
        mhs.ipk = (mhs.mk1 + mhs.mk2 + mhs.mk3 + mhs.mk4) / 4;   // Menghitung IPK
        mhs.status = (mhs.ipk > 3.5) ? "Cumlaude" : "Memuaskan"; // Menentukan status kelulusan
        addNode(mhs);                                            // Menambahkan data mahasiswa ke linked list
        cout << "Data Berhasil Ditambahkan" << endl;
    }
};

// Fungsi untuk menampilkan menu dan menangani pilihan pengguna
void menu()
{
    LinkedList dataMhs; // Membuat objek linked list untuk menyimpan data mahasiswa
    Nilai nilai;        // Membuat objek nilai untuk grade
    int pilihan;        // Variabel untuk menyimpan pilihan pengguna
    do
    {
        // Menampilkan menu pilihan
        cout << "\n1. Tambah Data\n2. Hapus Data\n3. Update Data\n4. Cek IPK per Jurusan\n5. Urutkan IPK\n6. Tampilkan Semua\n7. IPK Terbesar Dan Terkecil\n8. Cari Data Mahasiswa Berdasarkan NIM\n0. Keluar\nPilihan: ";
        cin >> pilihan;                                      // Menerima input pilihan
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan input buffer

        // Menangani pilihan pengguna
        if (pilihan == 1)
        {
            dataMhs.addMhs(); // Menambahkan data mahasiswa
            getch();
            system("cls");
        }
        else if (pilihan == 2)
        {
            string jurusan; // Variabel untuk menyimpan jurusan yang akan dihapus
            cout << "Masukan Jurusan Anda: ";
            cin >> jurusan;              // Menerima input jurusan
            dataMhs.deleteNode(jurusan); // Menghapus data berdasarkan jurusan
            getch();
            system("cls");
        }
        else if (pilihan == 3)
        {
            string nim; // Variabel untuk menyimpan NIM yang akan diupdate
            cout << "Input NIM: ";
            cin >> nim;              // Menerima input NIM
            dataMhs.updateNode(nim); // Memperbarui data mahasiswa berdasarkan NIM
            getch();
            system("cls");
        }
        else if (pilihan == 4)
        {
            string jurusan; // Variabel untuk menyimpan jurusan yang akan dicek
            cout << "Masukan Jurusan: ";
            cin >> jurusan;           // Menerima input jurusan
            dataMhs.readIpk(jurusan); // Menampilkan IPK mahasiswa berdasarkan jurusan
            getch();
            system("cls");
        }
        else if (pilihan == 5)
        {
            dataMhs.sortIpk(); // Mengurutkan mahasiswa berdasarkan IPK
            getch();
            system("cls");
        }
        else if (pilihan == 6)
        {
            dataMhs.displayAll(); // Menampilkan semua data mahasiswa
            getch();
            system("cls");
        }
        else if (pilihan == 7)
        {
            dataMhs.getIpkHighestAndLowest(); // Menampilkan mahasiswa dengan IPK tertinggi dan terendah
            getch();
            system("cls");
        }
        else if (pilihan == 8)
        {
            dataMhs.searchData(); // Mencari data mahasiswa berdasarkan NIM
            getch();
            system("cls");
        }
    } while (pilihan != 0); // Ulangi hingga pengguna memilih untuk keluar
}

// Fungsi utama
int main()
{
    menu(); // Memanggil fungsi menu untuk menjalankan program
}