#include <iostream>
#include <string>
#include "spotify.h"

using namespace std;

void SearchMenu(SongList &songL) {
    char choice;

    cout << "\n--- Search Songs ---\n";
    cout << " [1] Search by ID\n";
    cout << " [2] Search by Title\n";
    cout << "Choose: ";
    cin >> choice;
    cin.ignore();

    adrSong found = nullptr;

    if (choice == '1') {
        int id;
        cout << "Enter Song ID: ";
        cin >> id;
        cin.ignore();
        found = searchSongById(songL, id);

    } else if (choice == '2') {
        string title;
        cout << "Enter Song Title: ";
        getline(cin, title);
        found = searchSongByTitle(songL, title);
    }

    if (found != nullptr) {
        cout << "\n--- Song Found ---\n";
        cout << found->info.idSong << " | " 
             << found->info.title << " | "
             << found->info.artist << " | "
             << found->info.genre << "\n";
    } else {
        cout << "\n[INFO] Song not found.\n";
    }
}

void handlePlaylist(PlaylistList &playlistL, SongList &songL) {
    cout << "\n--- Playlist ---\n";

    string name;
    cout << "Enter playlist name: ";
    getline(cin, name);

    adrPlaylist p = searchPlaylistByName(playlistL, name);

    if (p == nullptr) {
        cout << "[ERROR] Playlist not found.\n";
        return;
    }

    cout << "\nManaging Playlist: " << p->name << endl;
    cout << " [1] Add Song\n";
    cout << " [2] Remove Song\n";
    cout << " [3] View Songs\n";
    cout << " [4] Play Playlist\n";
    cout << "Choose: ";

    char choice;
    cin >> choice;
    cin.ignore();

    if (choice == '1') {
        int id;
        cout << "Enter Song ID: ";
        cin >> id;
        cin.ignore();

        adrSong s = searchSongById(songL, id);
        if (s != nullptr) addSongToPlaylist(p, s);
        else cout << "[ERROR] Song not found.\n";

    } else if (choice == '2') {
        int id;
        cout << "Enter Song ID to remove: ";
        cin >> id;
        cin.ignore();
        removeSongFromPlaylist(p, id);

    } else if (choice == '3') {
        printSongsInPlaylist(p);

    } else if (choice == '4') {
        if (p->firstSong != nullptr)
            playSong(p->firstSong->song);
        else
            cout << "[INFO] Playlist is empty.\n";
    }
}

void tampilanDepanUser(SongList &songL, PlaylistList &playlistL) {
    cout << "------------------------------------------------------------\n";
    cout << "           ★  SPOTI-LITE DASHBOARD FOR USER  ★\n";
    cout << "------------------------------------------------------------\n\n";

    // TOP SONG 
    cout << "📜TOP SONG This Week \n";
    cout << "-> Favorite\n";
    cout << "   Neon Dreams\n";
    cout << "   Solar Wind\n";
    cout << "   Crystal Rain\n\n";

    // LIBRARY 
    cout << "📜LIBRARY \n";
    cout << "-> Favorite\n";

    adrSong p = songL.first;
    int count = 0;
    while (p != nullptr && count < 3) {  
        cout << "   " << p->info.title << "\n";
        p = p->next;
        count++;
    }
    cout << "\n";

    // STATUS PLAY / PAUSE
    cout << ketPlayStop();  
    cout << "\n";

    // MENU
    cout << "---------------Menu----------------- \n";
    cout << "[A] Playlist         [B] Library\n";
    cout << "[C] History          [D] Singer\n"; 
    cout << "[E] Search           [X] Exit\n";
    cout << "------------------------------------\n";
    
    cout << "Pilih: ";

    char pilihan;
    cin >> pilihan;
    cin.ignore();

    switch (toupper(pilihan)) {
        case 'A':
            handlePlaylist(playlistL, songL);
            break;
        case 'B':
            printSongList(songL);
            break;
        case 'C':
            printHistory();
            break;
        case 'D':
            cout << "\n--- Singer List ---\n(coming soon)\n";
            break;
        case 'E':
            SearchMenu(songL);
            break;
        case 'X':
            cout << "\nExiting program...\n";
            exit(0);
        default:
            cout << "\n[INFO] Invalid option.\n";
    }
}

string ketPlayStop() {
    if (currentSong == nullptr) {
        return "[⏹️ STOPPED]\n";
    }

    if (isPlaying) {
        return "[▶️ PLAYING] " + currentSong->info.title + "\n";
    } else {
        return "[⏸️ PAUSED] " + currentSong->info.title + "\n";
    }
}
