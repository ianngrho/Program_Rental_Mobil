#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

#define true 1
#define false 0

#define X_LINE_PASSWORD 21

#define MAX_ID 10
#define MAX_NAMA 50
#define MAX_JENIS 30
#define MAX_TANGGAL 20

#define MAX_KENDARAAN 50
#define MAX_KARYAWAN 50
#define MAX_PELANGGAN 100
#define MAX_ORDER 100

#define USERNAME "admin"
#define PASSWORD "admin"

#define clrscr() system("cls")


typedef struct {
    char idMobil[MAX_ID];
    char namaMobil[MAX_NAMA];
    char jenisMobil[MAX_JENIS];
    long int biayaRental;
    int statusDirental; // true or false
} DATA_MOBIL;

typedef struct {
    char idMobil[MAX_ID];
    char idPelanggan[MAX_ID];
    char idKaryawan[MAX_ID];
    char tanggalRental[MAX_TANGGAL];  // misal : 10 April 2020
    char tanggalKembali[MAX_TANGGAL]; // misal : 10 April 2020
    int lamaRental;
    long int totalBiaya;
} DATA_ORDER;

typedef struct {
    char idKaryawan[MAX_ID];
    char namaKaryawan[MAX_NAMA];
    char jabatan[MAX_JENIS];
} DATA_KARYAWAN;

typedef struct {
    char idPelanggan[MAX_ID];
    char namaPelanggan[MAX_NAMA];
/**
 * true or false
 */
    int member;
} DATA_PELANGGAN;

/* deklarasi variabel struct */
DATA_MOBIL dataKendaraan[MAX_KENDARAAN];
DATA_ORDER dataOrder[MAX_ORDER];
DATA_KARYAWAN dataKaryawan[MAX_KARYAWAN];
DATA_PELANGGAN dataPelanggan[MAX_PELANGGAN];
COORD coord = {0,0};


/* deklarasi jumlah data tersimpan untuk setiap struct */
int countKendaraan = 0;
int countOrder = 0;
int countKaryawan = 0;
int countPelanggan = 0;

/* function */
void enter(const char pesan[]) {
    printf("%s ", pesan);
    fflush(stdin);
    getchar();
}

void gotoxy(int x , int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loading(const char pesan[], int x, int y, int timer) {
    int countPesan = (int) strlen(pesan);
    int i;
    for(i = 0; i < countPesan; i++) {
        _sleep(timer);
        gotoxy(x++, y); printf("%c", pesan[i]);
    }
    printf("\n");
}

void information(const char pesan[]) {
    printf("\nInformation\n");
    printf("%s\n", pesan);
    getchar();
    printf("\n");
}

void error(const char pesan[]) {
    printf("\nERROR!!!\n");
    printf("%s\n", pesan);
    getchar();
    printf("\n");
}

void warning(const char pesan[]) {
    printf("\nWARNING!!!\n");
    printf("%s\n", pesan);
    getchar();
    printf("\n");
}


char inputYaAtauTidak(const char pesan[]) {
    char input;
    do {
        printf("%s", pesan);
        fflush(stdin);
        input = (char) toupper((char) getchar());
    } while(input == 0 || (input != 'Y' && input != 'T'));

    return input;
}

int inputInteger(const char pesan[]) {
    int nilai;
    do {
        printf("%s", pesan);
        scanf("%d", &nilai);

        if(nilai < 1) {
            printf("Nilai tidak boleh kurang dari nol (1)!\n");
        }

    } while(nilai < 1);

    return nilai;
}

long int inputLongInteger(const char pesan[]) {
    long int nilai;
    do {
        printf("%s", pesan);
        scanf("%ld", &nilai);

        if(nilai < 1) {
            printf("Nilai tidak boleh kurang dari nol (1)!\n");
        }

    } while(nilai < 1);

    return nilai;
}


int inputBoolean(const char pesan[]) {
    int status;
    do {
        printf("%s", pesan);
        scanf("%d", &status);

        if(status != 0 && status != 1) {
            printf("Input hanya 0 atau 1!\n");
        }

    } while(status != 0 && status != 1);

    return status;
}

char * inputString(int maxChar, const char pesan[]) {
    char * string = calloc(maxChar + 1, sizeof(char));
    do {
        strcpy(string, ""); // reset nilai dari variable string

        printf("%s", pesan);
        fflush(stdin);
        scanf("%[^\n]", string);

        if(strcmp(string, "") == 0) {
            printf("Input tidak boleh kosong!\n");
        } if(strlen(string) > maxChar) {
            printf("Input tidak boleh lebih dari %d karakter\n", maxChar);
        }
    } while(strcmp(string, "") == 0 || strlen(string) > maxChar);

    return string;
}

char * inputPassword(int maxChar, const char pesan[], int x, int y) {
    char * password = calloc(maxChar + 1, sizeof(char));
    do {
        strcpy(password, ""); // reset nilai dari variable string

        printf("%s", pesan);
        fflush(stdin);
        char c;
        int i = 0;
        x += X_LINE_PASSWORD;

        while((c = (char)getch()) != '\r') {

            if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
//                gotoxy(x,y); printf("%c",c);
                gotoxy(x,y); printf("*");
                password[i] = c;
                i++;
                x++;

            } else if(c == 32) {
//                gotoxy(x,y); printf("%c",c);
                gotoxy(x,y); printf("*");
                password[i] = c;
                i++;
                x++;

            } else if(c == '\b') {
                x--;
                gotoxy(x,y); printf(" ");
                i--;
                password[i] = '\0';
            }
        }

        printf("\n");
        if(strcmp(password, "") == 0) {
            printf("Input tidak boleh kosong!\n");
        } if(strlen(password) > maxChar) {
            printf("Input tidak boleh lebih dari %d karakter\n", maxChar);
        }

    } while(strcmp(password, "") == 0 || strlen(password) > maxChar);

    return password;
}

/* FUNGSI UNTUK MENU KENDARAAN */
char *getStatusDirental(int status) {
    if(status == 0) {
        return "Tersedia";
    } else {
        return "Dirental";
    }
}

void tampilSatuKendaraan(DATA_MOBIL kendaraan) {
    printf("ID Mobil        : %s\n", kendaraan.idMobil);
    printf("Nama Mobil      : %s\n", kendaraan.namaMobil);
    printf("Jenis Mobil     : %s\n", kendaraan.jenisMobil);
    printf("Biaya Rental    : %ld\n", kendaraan.biayaRental);
    printf("Status          : %s\n\n", getStatusDirental(kendaraan.statusDirental));
}

void tampilKendaraan() {
    if(countKendaraan == 0) {
        printf("Data kendaraan kosong!\n");
        return;
    }

    int i;
    for(i = 0; i < countKendaraan; i++) {
        printf("%d. ", (i+1));
        tampilSatuKendaraan(dataKendaraan[i]);
    }
}

void sortingKendaraan() {
    int i;
    printf("Mengurutkan data mobil berdasarkan biaya rentalnya...");
    for(i = 0; i < countKendaraan-1; i++) {
        int j;
        for(j = 0; j < countKendaraan-i-1; j++) {
            if(dataKendaraan[j].biayaRental > dataKendaraan[j+1].biayaRental) {
                DATA_MOBIL temp = dataKendaraan[j];
                dataKendaraan[j] = dataKendaraan[j+1];
                dataKendaraan[j+1] = temp;
            }
        }
    }
}

void cariKendaraan() {

    if(countKendaraan == 0) {
        printf("Data kendaraan kosong!\n");
        enter("Tekan enter untuk kembali ke menu kendaraan");
        return;
    }

    char cariNamaKendaraan[MAX_NAMA];
    strcpy(cariNamaKendaraan, inputString(MAX_NAMA, "Masukkan nama kendaraan yang ingin dicari : "));

    // jika id kendaraan yang dimasukan ketemu
    int status = -1;
    int i;
    for(i = 0; i < countKendaraan; i++) {
        if(strcmp(dataKendaraan[i].namaMobil, cariNamaKendaraan) == 0) {
            tampilSatuKendaraan(dataKendaraan[i]);
            status++;
        }
    }

    if(status == -1) {
        printf("Mobil %s tidak ditemukan\n", cariNamaKendaraan);
    }

    enter("Tekan enter untuk kembali ke menu kendaraan");
}

void tambahKendaraan() {

    DATA_MOBIL kendaraan;

    strcpy(kendaraan.idMobil, inputString(MAX_ID, "Masukkan id mobil : "));
    strcpy(kendaraan.namaMobil, inputString(MAX_NAMA, "Masukkan nama mobil : "));
    strcpy(kendaraan.jenisMobil, inputString(MAX_JENIS, "Masukkan jenis mobil : "));
    kendaraan.biayaRental = inputLongInteger("Masukkan biaya rental : ");
    kendaraan.statusDirental = inputBoolean("Masukkan status dirental (1) true, (0) false : ");

    information("Data Mobil berhasil disimpan");

    dataKendaraan[countKendaraan] = kendaraan;

    countKendaraan++;
    enter("Tekan enter untuk kembali ke menu kendaraan");
}

void prosesRubah(int indexRubah) {

    DATA_MOBIL kendaraan;

    printf("PROSES RUBAH KENDARAAN\n");

    strcpy(kendaraan.idMobil, inputString(MAX_ID, "Masukkan id mobil (Baru) : "));
    strcpy(kendaraan.namaMobil, inputString(MAX_NAMA, "Masukkan nama mobil (Baru) : "));
    strcpy(kendaraan.jenisMobil, inputString(MAX_JENIS, "Masukkan jenis mobil (Baru) : "));
    kendaraan.biayaRental = inputLongInteger("Masukkan biaya rental (Baru) : ");
    kendaraan.statusDirental = inputBoolean("Masukkan status dirental (1) true, (0) false : ");

    information("Data Mobil berhasil dirubah");

    dataKendaraan[indexRubah] = kendaraan;

}

void rubahKendaraan() {
    int pilihan;

    printf("MENU RUBAH KENDARAAN\n");
    printf("=======================\n");

    if(countKendaraan == 0) {
        printf("Data kendaraan kosong!\n");
        enter("Tekan enter untuk kembali ke menu kendaraan");
        return;
    }

    tampilKendaraan();

    do {
        printf("Pilihan [0..%d]: ", countKendaraan);
        scanf("%d", &pilihan);
    } while(pilihan < 1 || pilihan > countKendaraan);

    pilihan--;
    char yakinRubah = inputYaAtauTidak("Yakin ingin merubah data kendaraan [Y/T] : ");
    if(yakinRubah == 'Y') {
        prosesRubah(pilihan);
    }
    enter("Tekan enter untuk kembali ke menu kendaraan");
}

void prosesHapus(int indexHapus) {
    int i;
    for(i = indexHapus; i < countKendaraan-1; i++) {
        dataKendaraan[i] = dataKendaraan[i+1];
    }
}

void hapusKendaraan() {
    int pilihan;

    printf("MENU HAPUS KENDARAAN\n");
    printf("=======================\n");

    if(countKendaraan == 0) {
        printf("Data kendaraan kosong!\n");
        enter("Tekan enter untuk kembali ke menu kendaraan");
        return;
    }

    tampilKendaraan();

    do {
        printf("Pilihan [0..%d]: ", countKendaraan);
        scanf("%d", &pilihan);
    } while(pilihan < 1 || pilihan > countKendaraan);

    pilihan--;
    char yakinHapus = inputYaAtauTidak("Yakin ingin menghapus kendaraan [Y/T] : ");
    if(yakinHapus == 'Y') {
        prosesHapus(pilihan);
        countKendaraan--;
        information("Mobil berhasil dihapus");
    }
    enter("Tekan enter untuk kembali ke menu kendaraan");
}

void menuKendaraan() {
    int pilihan;
    do {
        int x = 0;
        int y = 0;
        clrscr();

        gotoxy(x, y);   printf("+======================================================+");
        gotoxy(x, ++y); //printf("                  MENU KENDARAAN                     ");
        gotoxy(x, ++y); printf("+------------------------------------------------------+");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("| 1. Tampil Kendaraan                                  |");
        gotoxy(x, ++y); printf("| 2. Cari Kendaraan                                    |");
        gotoxy(x, ++y); printf("| 3. Tambah Kendaraan                                  |");
        gotoxy(x, ++y); printf("| 4. Rubah Kendaraan                                   |");
        gotoxy(x, ++y); printf("| 5. Hapus Kendaraan                                   |");
        gotoxy(x, ++y); printf("| 6. Kembali ke menu utama                             |");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("| Pilihan :                                            |");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("+======================================================+");
        loading("                  MENU KENDARAAN                     ", x, y-12, 20);
        gotoxy(x+12, y-2); scanf("%d", &pilihan);

        clrscr();
        switch (pilihan) {
            case 1:
                printf("MENU TAMPIL KENDARAAN\n");
                tampilKendaraan();

                char inginMengurutkanMobil = inputYaAtauTidak("Ingin mengurutkan mobil [Y/T]: ");
                if(inginMengurutkanMobil == 'Y') {
                    sortingKendaraan();
                    printf("MOBIL SETELAH DIURUTKAN\n");
                    tampilKendaraan();
                }

                enter("Tekan enter untuk kembali ke menu kendaraan");
                break;
            case 2:
                cariKendaraan();
                break;
            case 3:
                tambahKendaraan();
                break;
            case 4:rubahKendaraan();
                break;
            case 5:
                hapusKendaraan();
                break;
        }
    } while (pilihan != 6);
}
/* AKHIR FUNGSI UNTUK MENU KENDARAAN */

/* FUNGSI UNTUK MENU KARYAWAN */
void tampilSatuKaryawan(DATA_KARYAWAN karyawan) {
    printf("ID Karyawan   : %s\n", karyawan.idKaryawan);
    printf("Nama Karyawan : %s\n", karyawan.namaKaryawan);
    printf("Jabatan       : %s\n", karyawan.jabatan);
}

void tampilKaryawan() {
    if(countKaryawan == 0) {
        printf("Data karyawan kosong!\n");
        return;
    }

    int i;
    for(i = 0; i < countKaryawan; i++) {
        printf("%d. ", (i+1));
        tampilSatuKaryawan(dataKaryawan[i]);
    }
}

void tambahKaryawan() {

    DATA_KARYAWAN karyawan;

    strcpy(karyawan.idKaryawan, inputString(MAX_ID, "Masukkan id karyawan : "));
    strcpy(karyawan.namaKaryawan, inputString(MAX_NAMA, "Masukkan nama karyawan : "));
    strcpy(karyawan.jabatan, inputString(MAX_JENIS, "Masukkan jabatan : "));

    information("Data karyawan berhasil disimpan");
    dataKaryawan[countKaryawan] = karyawan;
    countKaryawan++;
    enter("Tekan enter untuk kembali ke menu karyawan");
}

void prosesRubahKaryawan(int indexRubah) {
    DATA_KARYAWAN karyawan;
    printf("PROSES RUBAH KARYAWAN\n");

    strcpy(karyawan.idKaryawan, inputString(MAX_ID, "Masukkan id karyawan (Baru) : "));
    strcpy(karyawan.namaKaryawan, inputString(MAX_NAMA, "Masukkan nama karyawan (Baru) : "));
    strcpy(karyawan.jabatan, inputString(MAX_JENIS, "Masukkan jabatan (Baru) : "));

    information("Data karyawan berhasil dirubah");
    dataKaryawan[indexRubah] = karyawan;
}

void rubahKaryawan() {
    int pilihan;

    printf("MENU RUBAH KARYAWAN\n");
    printf("=======================\n");

    if(countKaryawan == 0) {
        printf("Data karyawan kosong!\n");
        enter("Tekan enter untuk kembali ke menu karyawan");
        return;
    }

    tampilKaryawan();

    do {
        printf("Pilihan [0..%d]: ", countKaryawan);
        scanf("%d", &pilihan);
    } while(pilihan < 1 || pilihan > countKaryawan);

    pilihan--;
    char yakinRubah = inputYaAtauTidak("Yakin ingin merubah data karyawan [Y/T] : ");
    if(yakinRubah == 'Y') {
        prosesRubahKaryawan(pilihan);
    }
    enter("Tekan enter untuk kembali ke menu karyawan");
}

void prosesHapusKaryawan(int indexHapus) {
    int i;
    for(i = indexHapus; i < countKaryawan-1; i++) {
        dataKaryawan[i] = dataKaryawan[i+1];
    }
}

void hapusKaryawan() {
    int pilihan;

    printf("MENU HAPUS KARYAWAN\n");
    printf("=======================\n");

    if(countKaryawan == 0) {
        printf("Data karyawan kosong!\n");
        enter("Tekan enter untuk kembali ke menu karyawan");
        return;
    }

    tampilKaryawan();

    do {
        printf("Pilihan [0..%d]: ", countKaryawan);
        scanf("%d", &pilihan);
    } while(pilihan < 1 || pilihan > countKaryawan);

    pilihan--;
    char yakinHapus = inputYaAtauTidak("Yakin ingin menghapus karyawan [Y/T] : ");
    if(yakinHapus == 'Y') {
        prosesHapusKaryawan(pilihan);
        countKaryawan--;
        information("Karyawan berhasil dihapus");
    }
    enter("Tekan enter untuk kembali ke menu karyawan");
}

void menuKaryawan() {
    int pilihan;
    do {
        int x = 0;
        int y = 0;
        clrscr();

        gotoxy(x, y);   printf("+======================================================+");
        gotoxy(x, ++y); //printf("                   MENU KARYAWAN                     ");
        gotoxy(x, ++y); printf("+------------------------------------------------------+");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("| 1. Tampil Karyawan                                   |");
        gotoxy(x, ++y); printf("| 2. Tambah Karyawan                                   |");
        gotoxy(x, ++y); printf("| 3. Rubah Karyawan                                    |");
        gotoxy(x, ++y); printf("| 4. Hapus Karyawan                                    |");
        gotoxy(x, ++y); printf("| 5. Kembali ke menu utama                             |");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("| Pilihan :                                            |");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("+======================================================+");
        loading("                   MENU KARYAWAN                     ", x, y-11, 20);
        gotoxy(x+12, y-2); scanf("%d", &pilihan);

        clrscr();
        switch (pilihan) {
            case 1:
                tampilKaryawan();
                enter("Tekan enter untuk kembali ke menu karyawan");
                break;
            case 2:
                tambahKaryawan();
                break;
            case 3:
                rubahKaryawan();
                break;
            case 4:
                hapusKaryawan();
                break;
        }
    } while (pilihan != 5);
}
/* AKHIR FUNGSI UNTUK MENU KARYAWAN */

/* FUNGSI UNTUK MENU PELANGGAN */
void tampilSatuPelanggan(DATA_PELANGGAN pelanggan) {
    printf("ID Pelanggan   : %s\n", pelanggan.idPelanggan);
    printf("Nama Pelanggan : %s\n", pelanggan.namaPelanggan);
}

void tampilPelanggan() {
    if(countPelanggan == 0) {
        printf("Data pelanggan kosong!\n");
        return;
    }

    int i;
    for(i = 0; i < countPelanggan; i++) {
        printf("%d. ", (i+1));
        tampilSatuPelanggan(dataPelanggan[i]);
    }
}

void tambahPelanggan() {

    DATA_PELANGGAN pelanggan;

    strcpy(pelanggan.idPelanggan, inputString(MAX_ID, "Masukkan id pelanggan : "));
    strcpy(pelanggan.namaPelanggan, inputString(MAX_NAMA, "Masukkan nama pelanggan : "));

    information("Data pelanggan berhasil disimpan");
    dataPelanggan[countPelanggan] = pelanggan;
    countPelanggan++;
    enter("Tekan enter untuk kembali ke menu pelanggan");
}

void prosesRubahPelanggan(int indexRubah) {
    DATA_PELANGGAN pelanggan;
    printf("PROSES RUBAH PELANGGAN\n");

    strcpy(pelanggan.idPelanggan, inputString(MAX_ID, "Masukkan id pelanggan (Baru) : "));
    strcpy(pelanggan.namaPelanggan, inputString(MAX_NAMA, "Masukkan nama pelanggan (Baru) : "));

    information("Data pelanggan berhasil dirubah");
    dataPelanggan[indexRubah] = pelanggan;
}

void rubahPelanggan() {
    int pilihan;

    printf("MENU RUBAH PELANGGAN\n");
    printf("=======================\n");

    if(countPelanggan == 0) {
        printf("Data pelanggan kosong!\n");
        enter("Tekan enter untuk kembali ke menu pelanggan");
        return;
    }

    tampilPelanggan();

    do {
        printf("Pilihan [0..%d]: ", countPelanggan);
        scanf("%d", &pilihan);
    } while(pilihan < 1 || pilihan > countPelanggan);

    pilihan--;
    char yakinRubah = inputYaAtauTidak("Yakin ingin merubah data pelanggan [Y/T] : ");
    if(yakinRubah == 'Y') {
        prosesRubahPelanggan(pilihan);
    }
    enter("Tekan enter untuk kembali ke menu pelanggan");
}

void prosesHapusPelanggan(int indexHapus) {
    int i;
    for(i = indexHapus; i < countPelanggan-1; i++) {
        dataPelanggan[i] = dataPelanggan[i+1];
    }
}

void hapusPelanggan() {
    int pilihan;

    printf("MENU HAPUS PELANGGAN\n");
    printf("=======================\n");

    if(countPelanggan == 0) {
        printf("Data pelanggan kosong!\n");
        enter("Tekan enter untuk kembali ke menu pelanggan");
        return;
    }

    tampilPelanggan();
    do {
        printf("Pilihan [0..%d]: ", countPelanggan);
        scanf("%d", &pilihan);
    } while(pilihan < 1 || pilihan > countPelanggan);

    pilihan--;
    char yakinHapus = inputYaAtauTidak("Yakin ingin menghapus pelanggan [Y/T] : ");
    if(yakinHapus == 'Y') {
        prosesHapusPelanggan(pilihan);
        countPelanggan--;
        information("Pelanggan berhasil dihapus");
    }
    enter("Tekan enter untuk kembali ke menu pelanggan");
}

void menuPelanggan() {
    int pilihan;
    do {
        int x = 0;
        int y = 0;
        clrscr();

        gotoxy(x, y);   printf("+======================================================+");
        gotoxy(x, ++y); //printf("");
        gotoxy(x, ++y); printf("+------------------------------------------------------+");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("| 1. Tampil Pelanggan                                  |");
        gotoxy(x, ++y); printf("| 2. Tambah Pelanggan                                  |");
        gotoxy(x, ++y); printf("| 3. Rubah Pelanggan                                   |");
        gotoxy(x, ++y); printf("| 4. Hapus Pelanggan                                   |");
        gotoxy(x, ++y); printf("| 5. Kembali ke menu utama                             |");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("| Pilihan :                                            |");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("+======================================================+");
        loading("                   MENU PELANGGAN                    ", x, y-11, 20);
        gotoxy(x+12, y-2); scanf("%d", &pilihan);

        clrscr();
        switch (pilihan) {
            case 1:
                tampilPelanggan();
                enter("Tekan enter untuk kembali ke menu pelanggan");
                break;
            case 2:
                tambahPelanggan();
                break;
            case 3:
                rubahPelanggan();
                break;
            case 4:
                hapusPelanggan();
                break;
        }
    } while (pilihan != 5);
}
/* AKHIR FUNGSI UNTUK MENU PELANGGAN */

/* FUNGSI UNTUK MENU ORDER */
void tampilSatuHistory(DATA_ORDER history) {
    printf("ID mobil            : %s\n", history.idMobil);
    printf("ID pelanggan        : %s\n", history.idPelanggan);
    printf("ID karyawan         : %s\n", history.idKaryawan);
    printf("Tanggal rental      : %s\n", history.tanggalRental);
    printf("Tanggal kembali     : %s\n", history.tanggalKembali);
    printf("Lama rental         : %d\n", history.lamaRental);
    printf("Total biaya         : %ld\n\n", history.totalBiaya);
}

void tampilHistory() {
    if(countOrder == 0) {
        printf("Data history kosong!\n");
        return;
    }

    int i;
    for(i = 0; i < countOrder; i++) {
        printf("%d. ", (i+1));
        tampilSatuHistory(dataOrder[i]);
    }
}

void tambahOrder() {

    int pilihKendaraan;
    int pilihPelanggan;
    int pilihKaryawan;

    // pilih mobil yang ingin dirental
    tampilKendaraan();
    do {
        printf("Pilihan [0..%d]: ", countKendaraan);
        scanf("%d", &pilihKendaraan);
    } while(pilihKendaraan < 0 || pilihKendaraan > countKendaraan);
    pilihKendaraan--;

    // pilih pelanggan yang akan melakukan rental
    tampilPelanggan();
    do {
        printf("Pilihan [0..%d]: ", countPelanggan);
        scanf("%d", &pilihPelanggan);
    } while(pilihPelanggan < 0 || pilihPelanggan > countPelanggan);
    pilihPelanggan--;

    // pilih karyawan yang melayani pengorderan
    tampilKaryawan();
    do {
        printf("Pilihan [0..%d]: ", countKaryawan);
        scanf("%d", &pilihKaryawan);
    } while(pilihKaryawan < 0 || pilihKaryawan > countKaryawan);
    pilihKaryawan--;

    // masukkan kedalam variabel struct
    DATA_ORDER order;
    strcpy(order.idMobil,dataKendaraan[pilihKendaraan].idMobil);
    strcpy(order.idPelanggan,dataPelanggan[pilihPelanggan].idPelanggan);
    strcpy(order.idKaryawan,dataKaryawan[pilihKaryawan].idKaryawan);

    strcpy(order.tanggalRental, inputString(MAX_TANGGAL, "Masukkan tanggal rental : "));
    strcpy(order.tanggalKembali, inputString(MAX_TANGGAL, "Masukkan tanggal kembali : "));

    int lamaRental = inputInteger("Masukkan lama rental : ");
    order.lamaRental = lamaRental;
    long int totalBiaya = dataKendaraan[pilihKendaraan].biayaRental * lamaRental;
    order.totalBiaya = totalBiaya;
    printf("Total biaya : %ld\n", totalBiaya);

    information("Data order berhasil disimpan");
    dataOrder[countOrder] = order;
    countOrder++;
    enter("Tekan enter untuk kembali ke menu order");
}

void prosesHapusHistory(int indexHapus) {
    int i;
    for(i = indexHapus; i < countOrder-1; i++) {
        dataOrder[i] = dataOrder[i+1];
    }
}

void hapushistory() {
    int pilihan;

    printf("MENU HAPUS HISTORY ORDER\n");
    printf("=======================\n");

    if(countOrder == 0) {
        printf("Data history kosong!\n");
        enter("Tekan enter untuk kembali ke menu order");
        return;
    }

    tampilHistory();

    do {
        printf("Pilihan [1..%d]: ", countOrder);
        scanf("%d", &pilihan);
    } while(pilihan < 1 || pilihan > countOrder);

    pilihan--;
    char yakinHapus = inputYaAtauTidak("Yakin ingin menghapus history order [Y/T] : ");
    if(yakinHapus == 'Y') {
        prosesHapusHistory(pilihan);
        countOrder--;
        information("History order berhasil dihapus");
    }
    enter("Tekan enter untuk kembali ke menu order");
}

void menuOrder() {
    int pilihan;
    do {
        int x = 0;
        int y = 0;
        clrscr();

        gotoxy(x, y);   printf("+======================================================+");
        gotoxy(x, ++y); //printf("                     MENU ORDER                      ");
        gotoxy(x, ++y); printf("+------------------------------------------------------+");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("| 1. Tampil History                                    |");
        gotoxy(x, ++y); printf("| 2. Tambah Pesanan                                    |");
        gotoxy(x, ++y); printf("| 3. Hapus History                                     |");
        gotoxy(x, ++y); printf("| 4. Kembali ke menu utama                             |");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("| Pilihan :                                            |");
        gotoxy(x, ++y); printf("|                                                      |");
        gotoxy(x, ++y); printf("+======================================================+");
        loading("                     MENU ORDER                      ", x, y-10, 20);
        gotoxy(x+12, y-2); scanf("%d", &pilihan);

        clrscr();
        switch (pilihan) {
            case 1:
                tampilHistory();
                enter("Tekan enter untuk kembali ke menu order");
                break;
            case 2:
                tambahOrder();
                break;
            case 3:
                hapushistory();
                break;
        }
    } while (pilihan != 4);
}
/* AKHIR FUNGSI UNTUK MENU ORDER */

void halamanUtama() {
    int pilihan;
    do {
        int x = 0;
        int y = 0;
        clrscr();

        gotoxy(x, y);   printf("+=============================================+");
        gotoxy(x, ++y); //printf(" SELAMAT DATANG DI APLIKASI RENTAL MOBIL");
        gotoxy(x, ++y); printf("+---------------------------------------------+");
        gotoxy(x, ++y); printf("|                                             |");
        gotoxy(x, ++y); printf("| 1. Manage Mobil                             |");
        gotoxy(x, ++y); printf("| 2. Manage Karyawan                          |");
        gotoxy(x, ++y); printf("| 3. Manage Pelanggan                         |");
        gotoxy(x, ++y); printf("| 4. Manage Order                             |");
        gotoxy(x, ++y); printf("| 5. Exit                                     |");
        gotoxy(x, ++y); printf("|                                             |");
        gotoxy(x, ++y); printf("| Pilihan :                                   |");
        gotoxy(x, ++y); printf("|                                             |");
        gotoxy(x, ++y); printf("+=============================================+");
        loading(" SELAMAT DATANG DI APLIKASI RENTAL MOBIL", x, y-11, 40);
        gotoxy(x+12, y-2); scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                menuKendaraan();
                break;
            case 2:
                menuKaryawan();
                break;
            case 3:
                menuPelanggan();
                break;
            case 4:
                menuOrder();
                break;
        }
    } while (pilihan != 5);
}

void login() {
    char username[MAX_NAMA];
    char password[MAX_NAMA];
    int loginSuccess = false;

    do {
        clrscr();
        int x = 20;
        int y = 20;
        gotoxy(x, ++y); printf("SELAMAT DATANG DI PROGRAM RENTAL MOBIL");
        gotoxy(x, ++y); printf("===========================================");
        y += 4;

        gotoxy(x, ++y); printf("===========================================");

        y -= 4;
        gotoxy(x, y);   strcpy(username, inputString(MAX_NAMA, " Masukkan username : "));
        gotoxy(x, ++y); strcpy(password, inputPassword(MAX_NAMA, " Masukkan password : ", x, y));

        if (strcmp(username, USERNAME) != 0 || strcmp(password, PASSWORD) != 0) {
            gotoxy(x, ++y); printf("Username dan password salah!\n");
            enter("Tekan sembarang");
        } else {
            char pesan[100] = "SELAMAT DATANG ";
            loading(strcat(pesan, USERNAME), ++x, ++y, 40);
            enter("Tekan sembarang");

            loginSuccess = true;
            halamanUtama();
        }
    } while(!loginSuccess);
}

int main() {

    login();

    return 0;
}
