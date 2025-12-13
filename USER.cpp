#include "spotify.h"
#include <iostream>

using namespace std;

// DEKLARASI FUNGSI
void SearchMenu(SongList &songL);
void handlePlaylist(PlaylistList &playlistL, SongList &songL, PlayerState &PS, StackHistory &H);

void tampilanDepanUser(SongList &songL, PlaylistList &playlistL, PlayerState &PS, StackHistory &H) {
    cout << "------------------------------------------------------------\n";
    cout << "            SPOTI-LITE DASHBOARD FOR USER  \n";
    cout << "------------------------------------------------------------\n\n";

    //Top Song
    cout << ">> TOP SONG Minggu Ini << \n";
    printTopSong(songL);

    //Library
    cout << ">> LIBRARY << \n";
    adrSong p = songL.first;
    int count = 0;
    while (p != nullptr && count < 3) {
        cout << "   " << p->info.title << "\n";
        p = p->next;
        count++;
    }
    cout << "\n";

    // status play/pause
    cout << ketPlayStop(PS);
    cout << "\n";

    // MENU
    cout << "=============== MAIN MENU ================\n";
    cout << "  [A] Manage Playlist    [B] View Library\n";
    cout << "  [C] History            [D] List Singer\n";
    cout << "  [E] Search Song\n";

    cout << "\n=============== CONTROLLER ================\n";
    cout << "      [P] Prev   [F] Play/Pause   [N] Next\n";
    cout << "                 [L] Like Song\n";

    cout << "\n----------------------------------\n";
    cout << "  [X] Exit \n";
    cout << "----------------------------------\n";
    cout << "Pilih menu: ";
}

string ketPlayStop(PlayerState PS) {
    if (PS.currentSong == nullptr) {
        return "----\n[STOPPED] Belum ada lagu yang diputar.\n------\n";
    }

    string status;
    if (PS.isPlaying == true) {
        status = "[PLAYING] ";
    } else {
        status = "[PAUSED] ";
    }

    // 3. Cek Sumber Lagu: Apakah dari Library atau Playlist?
    string sourceInfo;
    if (PS.currentPlaylist != nullptr) {
        sourceInfo = "Playing from Playlist: " + PS.currentPlaylist->name;
    } else {
        sourceInfo = "Playing from: Library Utama";
    }

    return "------------------------------------\n" +
           status + PS.currentSong->info.title + " - " + PS.currentSong->info.artist + "\n" +
           "             " + PS.currentSong->info.durasi + "\n" +
           "             " + sourceInfo + "\n" +
           "------------------------------------\n";
}


void SearchMenu(SongList &songL) {
    char choice;

    cout << "\n--- Search Songs ---\n";
    cout << " [1] Search by ID\n";
    cout << " [2] Search by Title\n";
    cout << "Choose: ";
    cin >> choice;

    adrSong found = nullptr;

    if (choice == '1') {
        string id;
        cout << "Masukan ID Lagu: ";
        cin >> id;
        found = searchSongById(songL, id);

    } else if (choice == '2') {
        string title;
        cout << "Masukan judul lagu: ";
        cin >> title;
        found = searchSongByTitle(songL, title);
    }

    if (found != nullptr) {
        cout << "\n--- Lagu ditemukan! ---\n";
        cout << found->info.idSong << " | "
             << found->info.title << " | "
             << found->info.artist << " | "
             << found->info.genre << " | "
             << found->info.durasi << "\n";
    } else {
        cout << "\n Lagu tidak ditemukan!.\n";
    }
}

void handlePlaylist(PlaylistList &playlistL, SongList &songL, PlayerState &PS, StackHistory &H) {
    cout << "\n ----------------- Manage Playlist -----------------\n";

    adrPlaylist p = nullptr;

    if (playlistL.first == nullptr) {
        cout << " Belum ada playlist yang dibuat! \n\n";

        cout << "Ingin membuat playlist baru? (y/n): ";
        char mauBuat;
        cin >> mauBuat;

        if (mauBuat == 'n' || mauBuat == 'N') {
            return;
        }

        string name;
        cout << "Masukkan Nama Playlist Baru: ";
        cin >> name;

        insertPlaylistLast(playlistL, allocatePlaylist(name));
        cout << ">> Playlist '" << name << "' berhasil dibuat!\n";
        p = searchPlaylistByName(playlistL, name);

    } else {
        cout << "Daftar Playlist Tersedia:\n";
        adrPlaylist ptr = playlistL.first;
        int i = 1;
        while (ptr != nullptr) {
            cout << " " << i << ". " << ptr->name << "\n";
            ptr = ptr->next;
            i++;
        }
        cout << "\n";

        string name;
        cout << "Masukkan NAMA Playlist (pilih dari atas / ketik baru): ";
        cin >> name;

        p = searchPlaylistByName(playlistL, name);

        if (p == nullptr) {
            cout << " Playlist '" << name << "' tidak ditemukan di daftar.\n";
            cout << "Apakah Anda ingin membuat playlist baru dengan nama ini? (y/n): ";
            char create; cin >> create;

            if (create == 'y' || create == 'Y') {
                insertPlaylistLast(playlistL, allocatePlaylist(name));
                cout << ">> Playlist '" << name << "' berhasil dibuat!\n";
                p = searchPlaylistByName(playlistL, name);
            } else {
                return;
            }
        }
    }

    if (p != nullptr) {
        bool stayInPlaylist = true;
        while (stayInPlaylist) {
            cout << "\n--- Mengelola Playlist: [" << p->name << "] ---\n";
            cout << " [1] Tambah Lagu (Add)\n";
            cout << " [2] Hapus Lagu (Remove)\n";
            cout << " [3] Lihat Isi Playlist\n";
            cout << " [4] Putar Playlist Ini\n";
            cout << " [X] Kembali\n";
            cout << "Pilih: ";

            string choice;
            cin >> choice;

            if (choice == "1") {
                cout << "\nLibrary Lagu:\n";
                printSongList(songL);

                string id;
                cout << "Masukkan ID Lagu yang mau ditambahkan: ";
                cin >> id;

                adrSong s = searchSongById(songL, id);

                if (s != nullptr) {
                    bool isDuplicate = false;
                    adrRelation r = p->firstSong;
                    while (r != nullptr) {
                        if (r->song == s) {
                            isDuplicate = true;
                            break;
                        }
                        r = r->next;
                    }

                    if (isDuplicate) {
                        cout << ">> Lagu sudah ada di dalam playlist ini!\n";
                    } else {
                        insertRelationLast(p, allocateRelation(s));
                        cout << ">> Lagu berhasil ditambahkan! \n";
                    }
                } else {
                    cout << "ID Lagu tidak ditemukan!\n";
                }

            } else if (choice == "2") {
                printSongsInPlaylist(p);
                if (p->firstSong != nullptr) {
                    string id;
                    cout << "Masukkan ID Lagu yang mau dihapus dari playlist: ";
                    cin >> id;
                    adrSong s = searchSongById(songL, id);
                    if (s != nullptr) {
                        deleteRelation(p, s);
                        cout << ">> Lagu dihapus dari playlist.\n";
                    }
                }

            } else if (choice == "3") {
                cout << "\nDaftar Lagu di " << p->name << ":\n";
                printSongsInPlaylist(p);

            } else if (choice == "4") {
                if (p->firstSong != nullptr) {
                    playSong(PS, H, p->firstSong->song, p);
                    cout << ">> Memutar Playlist: " << p->name << "...\n";
                    cout << ">> Sedang memutar: " << p->firstSong->song->info.title << "\n";
                } else {
                    cout << "Playlist ini kosong! \n";
                }
            } else if (choice == "x" || choice == "X") {
                stayInPlaylist = false;
            } else {
                cout << "Pilihan tidak valid.\n";
            }

        }
    }
}

void printTopSong(SongList L) {
    if (L.first == nullptr) {
        cout << "Belum ada data lagu! \n\n";
        return;
    }

    adrSong P = L.first;
    adrSong juara = L.first;

    while (P != nullptr) {
        if (P->info.playCount > juara->info.playCount) {
            juara = P;
        }
        P = P->next;
    }

    if (juara->info.playCount == 0) {
        cout << " Belum ada lagu yang diputar! \n\n";
    } else {
        cout << "    TOP LAGU MINGGU INI \n";
        cout << "   Judul  : " << juara->info.title << "\n";
        cout << "   Artis  : " << juara->info.artist << "\n";
        cout << "   Diputar: " << juara->info.playCount << " kali\n\n";
    }
}

void printSingers(SongList L){
    cout << "\n------ List Penyanyi Saat Ini ------\n";
        if (L.first == nullptr) {
            cout << "   (Belum ada data)\n";
            return;
    }

    adrSong p = L.first;
    int nomor = 1;

    while (p != nullptr) {
        bool isDuplicate = false;
        adrSong cek = L.first;

        while (cek != p) {
            if (cek->info.artist == p->info.artist) {
                isDuplicate = true;
                break;
            }
            cek = cek->next;
        }

        if (!isDuplicate) {
            cout << " " << nomor << ". " << p->info.artist << "\n";
            nomor++;
        }

        p = p->next;
    }
    cout << "-------------------------------------------------\n";
}
