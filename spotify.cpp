#include <iostream>
#include <string>
#include <stack>
#include "spotify.h"

using namespace std;

// SONG LIST FUNCTIONS
void removeSongFromQueue(PlayQueue &Q, adrSong songToRemove) {
    if (Q.head == nullptr) return;

    adrQueue current = Q.head;
    adrQueue prev = nullptr;

    while (current != nullptr) {
        if (current->song == songToRemove) {
            adrQueue temp = current;
            if (prev == nullptr) {
                Q.head = current->next;
                current = Q.head;
            } else {
                prev->next = current->next;
                current = prev->next;
            }
            if (temp == Q.tail) {
                Q.tail = prev;
            }
            delete temp;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void createSongList(SongList &L) {
    L.first = nullptr;
    L.last = nullptr;
}

adrSong allocateSong(Song x) {
    adrSong p = new SongNode;
    if (p != nullptr) {
        p->info = x;
        p->next = nullptr;
        p->prev = nullptr;
    }
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

adrSong searchSongById(SongList L, const string &id) {
    adrSong p = L.first;
    while (p != nullptr) {
        if (p->info.idSong == id) return p;
        p = p->next;
    }
    return nullptr;
}

adrSong searchSongByTitle(SongList L, const string &title) {
    adrSong p = L.first;
    while (p != nullptr) {
        if (p->info.title == title) return p;
        p = p->next;
    }
    return nullptr;
}

void updateSongData(adrSong p, Song newData) {
    if (p != nullptr) p->info = newData;
}

void printSongList(SongList L) {
    if (L.first == nullptr) {
        cout << "Song library is empty." << endl;
        return;
    }

    cout << "\n--- Song Library ---\n";
    adrSong p = L.first;
    while (p != nullptr) {
        cout << p->info.idSong << " | "
             << p->info.title << " | "
             << p->info.artist << " | "
             << p->info.genre << endl;
        p = p->next;
    }
}

void printSongInfo(adrSong s) {
    if (s == nullptr) {
        cout << "(null song)\n";
        return;
    }
    cout << "ID     : " << s->info.idSong << endl;
    cout << "Title  : " << s->info.title << endl;
    cout << "Artist : " << s->info.artist << endl;
    cout << "Genre  : " << s->info.genre << endl;
}

void deleteSongById(SongList &L, string &id, adrSong &p, PlaylistList &PL, PlayQueue &Q) {
    p = searchSongById(L, id);
    if (p == nullptr) return;

    cleanupSongReferences(PL, p);
    removeSongFromQueue(Q, p);

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
    p = nullptr;
}

void cleanupSongReferences(PlaylistList &PL, adrSong deletedSong) {
    adrPlaylist pList = PL.first;

    while (pList != nullptr) {
        adrRelation current = pList->firstSong;
        adrRelation prev = nullptr;

        while (current != nullptr) {
            if (current->song == deletedSong) {
                adrRelation temp = current;
                if (prev == nullptr) {
                    pList->firstSong = current->next;
                    current = pList->firstSong;
                } else {
                    prev->next = current->next;
                    current = prev->next;
                }
                delete temp;
            } else {
                prev = current;
                current = current->next;
            }
        }
        pList = pList->next;
    }
}

// PLAYLIST FUNCTIONS
void createPlaylistList(PlaylistList &PL) {
    PL.first = nullptr;
}

adrPlaylist allocatePlaylist(const string &name) {
    adrPlaylist p = new PlaylistNode;
    if (p != nullptr) {
        p->name = name;
        p->firstSong = nullptr;
        p->next = nullptr;
    }
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

void deletePlaylistByName(PlaylistList &PL, const string &name, adrPlaylist &p) {
    adrPlaylist current = PL.first;
    adrPlaylist prev = nullptr;

    while (current != nullptr && current->name != name) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        p = nullptr;
        return;
    }

    p = current;

    if (prev == nullptr) {
        PL.first = current->next;
    } else {
        prev->next = current->next;
    }

    adrRelation rel = current->firstSong;
    while (rel != nullptr) {
        adrRelation temp = rel;
        rel = rel->next;
        delete temp;
    }

    delete p;
    p = nullptr;
}

adrPlaylist searchPlaylistByName(PlaylistList PL, const string &name) {
    adrPlaylist p = PL.first;
    while (p != nullptr) {
        if (p->name == name) return p;
        p = p->next;
    }
    return nullptr;
}

void addSongToPlaylist(adrPlaylist P, adrSong S) {
    if (P == nullptr || S == nullptr) return;

    adrRelation check = P->firstSong;
    while (check != nullptr) {
        if (check->song == S) return;
        check = check->next;
    }

    adrRelation newRel = new RelationNode;
    newRel->song = S;
    newRel->next = nullptr;

    if (P->firstSong == nullptr) {
        P->firstSong = newRel;
    } else {
        adrRelation q = P->firstSong;
        while (q->next != nullptr) q = q->next;
        q->next = newRel;
    }
}

void removeSongFromPlaylist(adrPlaylist P, const string &songId) {
    if (P == nullptr || P->firstSong == nullptr) return;

    adrRelation current = P->firstSong;
    adrRelation prev = nullptr;

    while (current != nullptr && current->song->info.idSong != songId) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return;

    if (prev == nullptr) {
        P->firstSong = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
}

void printSongsInPlaylist(adrPlaylist P) {
    if (P == nullptr) {
        cout << "Playlist does not exist.\n";
        return;
    }

    cout << "\n--- Playlist: " << P->name << " ---\n";

    if (P->firstSong == nullptr) {
        cout << "(Empty Playlist)\n";
        return;
    }

    adrRelation r = P->firstSong;
    while (r != nullptr) {
        cout << r->song->info.idSong << " - "
             << r->song->info.title << " ("
             << r->song->info.artist << ")" << endl;
        r = r->next;
    }
}

// Globals 
adrSong currentSong = nullptr;
adrPlaylist currentPlaylist = nullptr;
bool isPlaying = false;
stack<adrSong> historyStack;

void pushHistory(adrSong s) {
    if (s != nullptr) {
        historyStack.push(s);
    }
}

void printHistory() {
    cout << "\n--- PLAY HISTORY (Most Recent First) ---\n";

    if (historyStack.empty()) {
        cout << "No songs have been played yet.\n";
    } else {
        stack<adrSong> tempStack = historyStack;
        int i = 1;
        while (!tempStack.empty()) {
            adrSong song = tempStack.top();
            cout << i++ << ". " << song->info.title
                 << " by " << song->info.artist << endl;
            tempStack.pop();
        }
    }

    cout << "----------------------------------------\n";
}

void playSong(adrSong s, adrPlaylist p) {
    if (s != nullptr) {
        currentSong = s;
        currentPlaylist = p;
        isPlaying = true;

        pushHistory(s);

        cout << "\n[INFO] Now playing: " << s->info.title
             << " by " << s->info.artist << endl;
    } else {
        cout << "\n[ERROR] Cannot play. Song is invalid.\n";
    }
}

void pauseSong() {
    if (currentSong != nullptr && isPlaying) {
        isPlaying = false;
        cout << "\n[INFO] Song paused.\n";
    } else {
        cout << "\n[INFO] Nothing is currently playing.\n";
    }
}

void resumeSong() {
    if (currentSong != nullptr && !isPlaying) {
        isPlaying = true;
        cout << "\n[INFO] Song resumed.\n";
    } else {
        cout << "\n[INFO] The song is already playing or none loaded.\n";
    }
}

adrRelation findRelationNode(adrPlaylist p, adrSong s) {
    if (p == nullptr || s == nullptr) {
        return nullptr;
    }

    adrRelation R = p->firstSong;

    while (R != nullptr) {
        if (R->song == s) return R;
        R = R->next;
    }
    return nullptr;
}

void playNext() {
    if (currentSong == nullptr || currentPlaylist == nullptr) {
        cout << "\n[INFO] No playlist is active.\n";
        return;
    }

    adrRelation R = findRelationNode(currentPlaylist, currentSong);

    if (R != nullptr && R->next != nullptr) {
        playSong(R->next->song, currentPlaylist);
    } else {
        cout << "\n[INFO] End of playlist reached.\n";
    }
}

void playPrev() {
    if (currentSong == nullptr || currentPlaylist == nullptr) {
        cout << "\n[INFO] No playlist is active.\n";
        return;
    }

    adrRelation current = currentPlaylist->firstSong;
    adrRelation prev = nullptr;

    while (current != nullptr && current->song != currentSong) {
        prev = current;
        current = current->next;
    }

    if (prev != nullptr) {
        playSong(prev->song, currentPlaylist);
    } else {
        cout << "\n[INFO] Start of playlist reached.\n";
    }
}
