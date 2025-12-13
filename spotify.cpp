#include "spotify.h"

// ================= PRIMITIF LAGU =================
void createSongList(SongList &L) {
    L.first = nullptr;
    L.last = nullptr;
}

adrSong allocateSong(Song x) {
    adrSong p = new SongNode;
    p->info = x;
    p->info.playCount = 0;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void insertSongLast(SongList &L, adrSong p) {
    if (L.first == nullptr) {
        L.first = p;
        L.last = p;
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
}

void deleteSongPrimitif(SongList &L, adrSong p) {
    if (p == L.first && p == L.last) {
        L.first = nullptr;
        L.last = nullptr;
    } else if (p == L.first) {
        L.first = p->next;
        if (L.first) L.first->prev = nullptr;
    } else if (p == L.last) {
        L.last = p->prev;
        if (L.last) L.last->next = nullptr;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    delete p;
}

adrSong searchSongById(SongList L, string id) {
    adrSong p = L.first;
    while (p != nullptr) {
        if (p->info.idSong == id) return p;
        p = p->next;
    }
    return nullptr;
}

adrSong searchSongByTitle(SongList L, string title) {
    adrSong p = L.first;
    while (p != nullptr) {
        if (p->info.title == title) return p;
        p = p->next;
    }
    return nullptr;
}

void printSongList(SongList L) {
    if (L.first == nullptr) {
        cout << "(Data Lagu Kosong)\n";
        return;
    }
    adrSong p = L.first;
    while (p != nullptr) {
        cout << "--------------------------------------------------\n";
        cout << "ID: " << p->info.idSong << " | " << p->info.title << "\n";
        cout << "      " << p->info.artist << " (" << p->info.genre << ") "
             << "- [" << p->info.durasi << "]\n";
        p = p->next;
    }
}

// ================= PRIMITIF PLAYLIST =================
void createPlaylistList(PlaylistList &PL) {
    PL.first = nullptr;
}

adrPlaylist allocatePlaylist(string name) {
    adrPlaylist p = new PlaylistNode;
    p->name = name;
    p->firstSong = nullptr;
    p->next = nullptr;
    return p;
}

void insertPlaylistLast(PlaylistList &PL, adrPlaylist p) {
    if (PL.first == nullptr) {
        PL.first = p;
    } else {
        adrPlaylist q = PL.first;
        while (q->next != nullptr) q = q->next;
        q->next = p;
    }
}

adrPlaylist searchPlaylistByName(PlaylistList PL, string name) {
    adrPlaylist p = PL.first;
    while (p != nullptr) {
        if (p->name == name) return p;
        p = p->next;
    }
    return nullptr;
}

adrRelation allocateRelation(adrSong s) {
    adrRelation r = new RelationNode;
    r->song = s;
    r->next = nullptr;
    return r;
}

void insertRelationLast(adrPlaylist P, adrRelation r) {
    if (P->firstSong == nullptr) {
        P->firstSong = r;
    } else {
        adrRelation q = P->firstSong;
        while (q->next != nullptr) q = q->next;
        q->next = r;
    }
}

void deleteRelation(adrPlaylist P, adrSong s) {
    adrRelation curr = P->firstSong;
    adrRelation prev = nullptr;
    while (curr != nullptr) {
        if (curr->song == s) {
            if (prev == nullptr) {
                P->firstSong = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void printSongsInPlaylist(adrPlaylist P) {
    if (P->firstSong == nullptr) {
        cout << "(Playlist Kosong)\n";
        return;
    }
    adrRelation r = P->firstSong;
    while (r != nullptr) {
        cout << "-> " << r->song->info.title << " (" << r->song->info.artist << ")\n";
        r = r->next;
    }
}

//==================PRIMITIF STACK==================

void createStack(StackHistory &S) {
    S.top = nullptr;
}

void pushStack(StackHistory &S, adrSong pLagu) {
    adrHistory p = new ElmHistory;
    p->info = pLagu;
    p->next = nullptr;

    // Insert First
    if (S.top == nullptr) {
        S.top = p;
    } else {
        p->next = S.top;
        S.top = p;
    }
}

void printStack(StackHistory S) {
    if (S.top == nullptr) {
        cout << "(History Kosong)\n";
        return;
    }

    adrHistory p = S.top;
    int i = 1;
    while (p != nullptr) {
        cout << i << ". " << p->info->info.title
             << " - " << p->info->info.artist << endl;
        p = p->next;
        i++;
    }
}

// ================= LOGIKA FITUR =================

void deleteSongComplete(SongList &L, PlaylistList &PL, PlayerState &PS, string id) {
    adrSong p = searchSongById(L, id);
    if (p == nullptr) return;

    // Stop jika sedang main
    if (PS.currentSong == p) {
        PS.isPlaying = false;
        PS.currentSong = nullptr;
        PS.currentPlaylist = nullptr;
    }

    // Hapus dari semua playlist
    adrPlaylist currP = PL.first;
    while (currP != nullptr) {
        deleteRelation(currP, p);
        currP = currP->next;
    }

    // Hapus dari library
    deleteSongPrimitif(L, p);
}

void playSong(PlayerState &PS, StackHistory &H, adrSong s, adrPlaylist context) {
    if (s != nullptr) {
        PS.currentSong = s;
        PS.currentPlaylist = context;
        PS.isPlaying = true;
        s->info.playCount++;
        pushStack(H, s);
    }
}

void pauseSong(PlayerState &PS) {
    if (PS.currentSong != nullptr) {
        if (PS.isPlaying) PS.isPlaying = false;
        else PS.isPlaying = true;
    }
}

adrSong findSimilarSong(SongList L, adrSong current) {
    if (current == nullptr) return L.first;

    // 1. Cari Artis Sama
    adrSong p = L.first;
    while (p != nullptr) {
        if (p != current && p->info.artist == current->info.artist) return p;
        p = p->next;
    }
    // 2. Cari Genre Sama
    p = L.first;
    while (p != nullptr) {
        if (p != current && p->info.genre == current->info.genre) return p;
        p = p->next;
    }

    if (current->next != nullptr) return current->next;
    return L.first;
}

void playNext(PlayerState &PS, StackHistory &H, SongList L) {
    if (PS.currentSong == nullptr) return;

    adrSong nextSong = nullptr;

    if (PS.currentPlaylist != nullptr) {
        adrRelation r = PS.currentPlaylist->firstSong;
        while (r != nullptr) {
            if (r->song == PS.currentSong) {
                if (r->next != nullptr) nextSong = r->next->song;
                else if (PS.currentPlaylist->firstSong != nullptr)
                    nextSong = PS.currentPlaylist->firstSong->song;
                break;
            }
            r = r->next;
        }
    } else {
        nextSong = findSimilarSong(L, PS.currentSong);
    }

    if (nextSong != nullptr) {
        playSong(PS, H, nextSong, PS.currentPlaylist);
    }
}

void playPrev(PlayerState &PS, StackHistory &H, SongList L) {
    if (PS.currentSong == nullptr) return;

    adrSong prevSong = nullptr;

    if (PS.currentPlaylist != nullptr) {
        adrRelation r = PS.currentPlaylist->firstSong;
        adrRelation prev = nullptr;
        while (r != nullptr) {
            if (r->song == PS.currentSong) break;
            prev = r;
            r = r->next;
        }
        if (prev != nullptr) prevSong = prev->song;
    } else {
        if (PS.currentSong->prev != nullptr) prevSong = PS.currentSong->prev;
    }

    if (prevSong != nullptr) {
        playSong(PS, H, prevSong, PS.currentPlaylist);
    }
}


int countUniqueArtists(SongList L) {
    if (L.first == nullptr) return 0;

    int count = 0;
    adrSong p = L.first;

    while (p != nullptr) {
        // Cek ke belakang (dari first sampai sebelum p)
        bool isDuplicate = false;
        adrSong checker = L.first;
        while (checker != p) {
            if (checker->info.artist == p->info.artist) {
                isDuplicate = true;
                break;
            }
            checker = checker->next;
        }

        if (!isDuplicate) {
            count++;
        }
        p = p->next;
    }
    return count;
}

int countUniqueGenres(SongList L) {
    if (L.first == nullptr) return 0;

    int count = 0;
    adrSong p = L.first;

    while (p != nullptr) {
        // Cek ke belakang
        bool isDuplicate = false;
        adrSong checker = L.first;
        while (checker != p) {
            if (checker->info.genre == p->info.genre) {
                isDuplicate = true;
                break;
            }
            checker = checker->next;
        }

        if (!isDuplicate) {
            count++;
        }
        p = p->next;
    }
    return count;
}

int countTotalSongs(SongList L) {
    int jumlah = 0;
    adrSong p = L.first;
    while (p != nullptr) {
        jumlah++;
        p = p->next;
    }
    return jumlah;
}

int countTotalPlaylists(PlaylistList PL) {
    int jumlah = 0;
    adrPlaylist p = PL.first;
    while (p != nullptr) {
        jumlah++;
        p = p->next;
    }
    return jumlah;
}