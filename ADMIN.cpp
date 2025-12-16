#include <iostream>
#include <string>
#include "spotify.h"
using namespace std;

void tampilanDepanAdmin() {
    cout << "------------------------------------------------------------\n";
    cout << "                 ★  SPOTI-LITE DASHBOARD FOR ADMIN  ★\n";
    cout << "------------------------------------------------------------\n\n";

    cout << "Mini Recap\n";
    cout << "• Jumlah Artis  : 3\n";
    cout << "• Jumlah Album  : 5\n";
    cout << "• Jumlah Lagu   : 44\n";
    cout << "• Jumlah User   : 2\n\n";

    cout << "---------------Menu--------------- \n";
    cout << "[A] Tambah/Hapus \n";
    cout << "[B] Edit Data Lagu\n";
    cout << "[C] Tampilkan Data Semua Lagu Saat Ini\n";
    cout << "[X] Exit\n";
    cout << "---------------------------------------------\n";
    cout << "Pilih: \n";
}

/*   cout << "PLAYLIST (Doubly Linked List)\n";
    for (int i = 0; i < jumlah; i++) {
        if (i == indexLagu)
            cout << "-> " << playlist[i] << endl;   // lagu yg sedang diputar
        else
            cout << "   " << playlist[i] << endl;
    }*/
    
void AdminChoices2A(){
    cout << "Fitur Tambah/Hapus Lagu\n";
    cout << "[1] Tambah Lagu\n";
    cout << "[2] Hapus Lagu\n";
    cout << "Pilih: ";
    char subChoice;
    cin >> subChoice;

    if (subChoice == '1') {
        // Fitur Tambah Lagu
        Song data;
        cout << "ID Lagu (angka): "; 
        cin >> data.idSong;
            
        cout << "Judul (tanpa spasi): "; 
        cin >> data.title;
            
        cout << "Artis (tanpa spasi): "; 
        cin >> data.artist;
            
        cout << "Genre (tanpa spasi): "; 
        cin >> data.genre;

        insertSongLast(daftarLagu, allocateSong(data));
        cout << "Lagu berhasil disimpan!\n";
        return main();

    } else if (subChoice == '2') {
        // Fitur Hapus Lagu
        int idHapus;
        cout << "Masukkan ID Lagu yang mau dihapus: ";
        cin >> idHapus;

        adrSong p; // Variabel penampung
        deleteSongById(daftarLagu, idHapus, p, daftarPlaylist, antrian);
        cout << ">> Proses hapus selesai.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void AdminChoices2B(){
    cout << "Fitur Edit Data Lagu\n";
    cout << "Masukkan ID Lagu yang ingin diedit: ";
    int idToEdit;
    cin >> idToEdit;

    adrSong songToEdit = searchSongById(daftarLagu, idToEdit);
    if (songToEdit == nullptr) {
        cout << "Lagu dengan ID tersebut tidak ditemukan.\n";
        return;
    }

    cout << "Data Lagu Saat Ini:\n";
    cout << "ID: " << songToEdit->info.idSong << "\n";
    cout << "Judul: " << songToEdit->info.title << "\n";
    cout << "Artis: " << songToEdit->info.artist << "\n";
    cout << "Genre: " << songToEdit->info.genre << "\n";

    cout << "Masukkan data baru (tekan enter untuk melewati):\n";

    cout << "Judul Baru: ";
    string newTitle;
    if (!newTitle.empty()) {
        songToEdit->info.title = newTitle;
    }

    cout << "Artis Baru: ";
    string newArtist;
    if (!newArtist.empty()) {
        songToEdit->info.artist = newArtist;
    }

    cout << "Genre Baru: ";
    string newGenre;
    if (!newGenre.empty()) {
        songToEdit->info.genre = newGenre;
    }

    cout << "Data lagu berhasil diperbarui.\n";

}

void AdminChoices2C(){
    cout << "Fitur Tampilkan Data Semua Lagu Saat Ini\n";
    printSongList(daftarLagu);
    return main();
}
