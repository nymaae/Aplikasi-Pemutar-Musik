#include "spotify.h"
#include <iostream>

using namespace std;

void tampilanDepanAdmin(SongList L, PlaylistList PL) {
    cout << "------------------------------------------------------------\n";
    cout << "                 SPOTI-LITE DASHBOARD FOR ADMIN  \n";
    cout << "------------------------------------------------------------\n\n";

    int totalLagu = countTotalSongs(L);
    int totalPlaylist = countTotalPlaylists(PL);
    int totalArtis = countUniqueArtists(L);
    int totalGenre = countUniqueGenres(L);

    cout << "Mini Recap Data\n";
    cout << "Jumlah Lagu     : " << totalLagu << "\n";
    cout << "Jumlah Artis    : " << totalArtis << "\n";
    cout << "Jumlah Genre    : " << totalGenre << "\n";
    cout << "Jumlah Playlist : " << totalPlaylist << "\n";
    cout << "\n";

    cout << "---------------Menu--------------- \n";
    cout << "[A] Tambah/Hapus \n";
    cout << "[B] Edit Data Lagu\n";
    cout << "[C] Tampilkan Data Semua Lagu Saat Ini\n";
    cout << "[X] Exit\n";
    cout << "---------------------------------------------\n";
    cout << "Pilih: \n";
}

void AdminChoices2A(SongList &daftarLagu, PlaylistList &daftarPlaylist, PlayerState &PS){
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

        cout << "Durasi (mm:ss): ";
        cin >> data.durasi;

        insertSongLast(daftarLagu, allocateSong(data));
        cout << "Lagu berhasil disimpan!\n";

    } else if (subChoice == '2') {
        // Fitur Hapus Lagu
        if (daftarLagu.first == nullptr) {
            cout << "\nLibrary lagu masih kosong. Tidak ada data untuk dihapus.\n";
            return;
        }

        string idHapus;
        cout << "Masukkan ID Lagu yang mau dihapus: ";
        cin >> idHapus;
        deleteSongComplete(daftarLagu, daftarPlaylist, PS, idHapus);
        cout << ">> Proses selesai.\n";

    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void AdminChoices2B(SongList &daftarLagu){
    cout << "Edit Data Lagu\n";
    cout << "Masukkan ID Lagu yang ingin diedit: ";
    string idToEdit;
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

    cout << "Masukkan data baru (tekan enter/ketik '-' untuk melewati):\n";

    string temp;
    cout << "Judul Baru: "; cin >> temp;
    if (temp != "-") songToEdit->info.title = temp;

    cout << "Artis Baru: "; cin >> temp;
    if (temp != "-") songToEdit->info.artist = temp;

    cout << "Genre Baru: "; cin >> temp;
    if (temp != "-") songToEdit->info.genre = temp;

    cout << "Durasi Baru: "; cin >> temp;
    if (temp != "-") songToEdit->info.durasi = temp;

    cout << "Data lagu berhasil diperbarui.\n";
}

void AdminChoices2C(SongList &daftarLagu){
    cout << "Data Semua Lagu Saat Ini\n";
    printSongList(daftarLagu);
}
