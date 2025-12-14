#include <iostream>
#include "spotify.h"

using namespace std;

void tampilanDepanUser(SongList &songL, PlaylistList &playlistL, PlayerState &PS, StackHistory &H);
void handlePlaylist(PlaylistList &playlistL, SongList &songL, PlayerState &PS, StackHistory &H);
void SearchMenu(SongList &songL);

// DEKLARASI FUNGSI DARI ADMIN.CPP
void tampilanDepanAdmin(SongList L, PlaylistList PL);
void AdminChoices2A(SongList &daftarLagu, PlaylistList &daftarPlaylist, PlayerState &PS);
void AdminChoices2B(SongList &daftarLagu);
void AdminChoices2C(SongList &daftarLagu);


void loadDummyData(SongList &L, PlaylistList &PL) {
    cout << ">> [LOADING] Memuat Data Dummy 4 Artis & Playlist...\n";

    // ==========================================================
    // ARTIS 1: TULUS (Genre: Pop & Ballad)
    // Album 1: Monokrom (4 Lagu)
    // ==========================================================
    insertSongLast(L, allocateSong({"101", "ManusiaKuat", "Tulus", "Klasik", "03:05", 0}));
    insertSongLast(L, allocateSong({"102", "Pamit", "Tulus", "Ballad", "03:53", 0}));
    insertSongLast(L, allocateSong({"103", "RuangSendiri", "Tulus", "Klasik", "04:29", 0}));
    insertSongLast(L, allocateSong({"104", "Monokrom", "Tulus", "Ballad", "03:34", 0}));

    // Album 2: Manusia (4 Lagu)
    insertSongLast(L, allocateSong({"105", "HatiHatiDiJalan", "Tulus", "Ballad", "04:02", 0}));
    insertSongLast(L, allocateSong({"106", "Diri", "Tulus", "Pop", "03:42", 0}));
    insertSongLast(L, allocateSong({"107", "Interaksi", "Tulus", "Jazz", "02:50", 0}));
    insertSongLast(L, allocateSong({"108", "JatuhSuka", "Tulus", "Pop", "03:15", 0}));


    // ==========================================================
    // ARTIS 2: COLDPLAY (Genre: Rock & Ballad)
    // Album 1: Parachutes (5 Lagu)
    // ==========================================================
    insertSongLast(L, allocateSong({"201", "Yellow", "Coldplay", "Rock", "04:26", 0}));
    insertSongLast(L, allocateSong({"202", "Shiver", "Coldplay", "Metal", "04:59", 0}));
    insertSongLast(L, allocateSong({"203", "Sparks", "Coldplay", "Ballad", "03:47", 0})); 
    insertSongLast(L, allocateSong({"204", "Trouble", "Coldplay", "Ballad", "04:30", 0}));
    insertSongLast(L, allocateSong({"205", "DontPanic", "Coldplay", "Rock", "02:17", 0}));


    // ==========================================================
    // ARTIS 3: NEWJEANS (Genre: Pop & RnB)
    // Album 1: Get Up (4 Lagu)
    // ==========================================================
    insertSongLast(L, allocateSong({"301", "SuperShy", "NewJeans", "HipHop", "02:34", 0}));
    insertSongLast(L, allocateSong({"302", "ETA", "NewJeans", "Pop", "02:31", 0}));
    insertSongLast(L, allocateSong({"303", "CoolWithYou", "NewJeans", "RnB", "02:27", 0}));
    insertSongLast(L, allocateSong({"304", "GetUp", "NewJeans", "RnB", "00:36", 0}));


    // ==========================================================
    // ARTIS 4: SHEILA ON 7 (Genre: Pop & Rock)
    // Album 1: Kisah Klasik (4 Lagu)
    // ==========================================================
    insertSongLast(L, allocateSong({"401", "SahabatSejati", "SheilaOn7", "Pop", "04:16", 0}));
    insertSongLast(L, allocateSong({"402", "KisahKlasik", "SheilaOn7", "Jazz", "03:54", 0}));
    insertSongLast(L, allocateSong({"403", "PriaKesepian", "SheilaOn7", "Rock", "04:02", 0})); 
    insertSongLast(L, allocateSong({"404", "Sephia", "SheilaOn7", "Ballad", "04:52", 0}));


    // ==========================================================
    // AUTOMATIC PLAYLIST CREATION
    // Syarat: Minimal 1 playlist berisi minimal 2 lagu
    // ==========================================================

    // 1. Buat Playlist "MoodBooster"
    string plName = "MoodBooster";
    insertPlaylistLast(PL, allocatePlaylist(plName));
    adrPlaylist P = searchPlaylistByName(PL, plName);

    // 2. Masukkan Lagu ke Playlist (Hardcode ID)
    if (P != nullptr) {
        // Masukkan lagu Tulus (101)
        adrSong s1 = searchSongById(L, "101");
        if(s1) insertRelationLast(P, allocateRelation(s1));

        // Masukkan lagu NewJeans (301)
        adrSong s2 = searchSongById(L, "301");
        if(s2) insertRelationLast(P, allocateRelation(s2));

        // Masukkan lagu Coldplay (201)
        adrSong s3 = searchSongById(L, "201");
        if(s3) insertRelationLast(P, allocateRelation(s3));

        cout << ">> [INFO] Playlist '" << plName << "' berhasil dibuat otomatis (3 Lagu).\n";
    }

    cout << ">> [SUCCESS] Total 21 Lagu & 1 Playlist siap digunakan!\n";
}

int main() {
    // Inisialisasi
    SongList daftarLagu;
    PlaylistList daftarPlaylist;
    PlayerState PS;

    StackHistory historyStack;
    createSongList(daftarLagu);
    createPlaylistList(daftarPlaylist);
    createStack(historyStack);

    PS.currentSong = nullptr;
    PS.currentPlaylist = nullptr;
    PS.isPlaying = false;

    loadDummyData(daftarLagu, daftarPlaylist);

    char choice;
while (true) {
        cout << "\n----------Selamat datang di Spoti-Lite!----------\n";
        cout << "Pilih Role Anda:\n";
        cout << "[1] User\n";
        cout << "[2] Admin\n";
        cout << "[X] Exit\n";
        cout << "---------------------------------------------\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> choice;

        // === MASUK MENU USER ===
        if (choice == '1') {
            if (daftarLagu.first == nullptr) {
                cout << "\n Library Lagu masih kosong, Masuk sebagai Admin dahulu!\n";
            } else {
                char choice2;
                do {
                    tampilanDepanUser(daftarLagu, daftarPlaylist, PS, historyStack);
                    cin >> choice2;

                    if (choice2 == 'A' || choice2 == 'a') {
                        handlePlaylist(daftarPlaylist, daftarLagu, PS, historyStack);
                    } else if (choice2 == 'B' || choice2 == 'b') {
                        printSongList(daftarLagu);
                        if (daftarLagu.first != nullptr) {
                            cout << "Masukkan ID lagu untuk diputar ([X] batal): ";
                            string id; cin >> id;
                            if(id != "x" || id != "X"){
                                adrSong s = searchSongById(daftarLagu, id);
                                if(s) playSong(PS, historyStack, s, nullptr);
                            }
                        }
                    } else if (choice2 == 'C' || choice2 == 'c') {
                        cout << "History (Lagu Terakhir Diputar):\n";
                        printStack(historyStack);

                    } else if (choice2 == 'D' || choice2 == 'd') {
                        printSingers(daftarLagu);

                    } else if (choice2 == 'E' || choice2 == 'e') {
                        SearchMenu(daftarLagu);
                    } else if (choice2 == 'F' || choice2 == 'f') {
                        if (PS.currentSong != nullptr) {
                            pauseSong(PS);
                        } else {
                            if (daftarLagu.first != nullptr) {
                                playSong(PS, historyStack, daftarLagu.first, nullptr); // nullptr artinya mode Library
                                cout << ">> Memutar lagu pertama dari Library.\n";
                            } else {
                                cout << "Library kosong, tidak ada lagu untuk diputar.\n";
                            }
                        }
                    } else if (choice2 == 'N'|| choice2 == 'n') {
                        playNext(PS, historyStack, daftarLagu);
                    } else if (choice2 == 'P'|| choice2 == 'p') {
                        playPrev(PS, historyStack, daftarLagu);
                    } else if (choice2 == 'L' || choice2 == 'l') {
                        if (PS.currentSong == nullptr) {
                            cout << "Putar lagu dulu baru bisa di-like!\n";
                        } else {
                            string favName = "FAVORITE";
                            adrPlaylist pFav = searchPlaylistByName(daftarPlaylist, favName);
                            if (pFav == nullptr) {
                                insertPlaylistLast(daftarPlaylist, allocatePlaylist(favName));
                                pFav = searchPlaylistByName(daftarPlaylist, favName);
                        }

                        insertRelationLast(pFav, allocateRelation(PS.currentSong));
                        cout << ">> Lagu masuk ke playlist 'FAVORITE'\n";
                        }
                    } else if (choice2 == 'X'|| choice2 == 'x') {
                        cout << "Keluar dari User.\n";
                    } else {
                        cout << "Pilihan tidak valid.\n";
                    }
                } while (choice2 != 'X' && choice2 != 'x');
            }

        // === MASUK MENU ADMIN ===
        } else if (choice == '2') {
            char choice2;
            do {
                tampilanDepanAdmin(daftarLagu, daftarPlaylist);
                cin >> choice2;

                if (choice2 == 'A' || choice2 == 'a') {
                    AdminChoices2A(daftarLagu, daftarPlaylist, PS);
                } else if (choice2 == 'B' || choice2 == 'b') {
                    AdminChoices2B(daftarLagu);
                } else if (choice2 == 'C' || choice2 == 'c') {
                    AdminChoices2C(daftarLagu);
                } else if (choice2 == 'X' || choice2 == 'x') {
                    cout << "Keluar dari Admin.\n";
                } else {
                    cout << "Pilihan tidak valid.\n";
                }
            } while (choice2 != 'X' && choice2 != 'x');

        // === EXIT PROGRAM ===
        } else if (choice == 'X' || choice == 'x') {
            cout << "Terima kasih telah menggunakan Spoti-Lite!\n";
            break;

        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
}
