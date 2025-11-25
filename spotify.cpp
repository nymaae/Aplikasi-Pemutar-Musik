#include <iostream>
#include <string>
#include "spotify.h"

using namespace std;

void removeSongFromQueue(PlayQueue &Q, adrSong songToRemove) {
    if (Q.head == nullptr) {
        return;
    }

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

void deleteSongById(SongList &L, int id, adrSong &p, PlaylistList &PL, PlayQueue &Q) {
    p = searchSongById(L, id);
    if (p == nullptr) {
        return;
    }

    cleanupSongReferences(PL, p);
    removeSongFromQueue(Q, p);

    if (p->prev == nullptr && p->next == nullptr) {
        L.first = nullptr;
        L.last = nullptr;
    } else if (p->prev == nullptr) {
        L.first = p->next;
        L.first->prev = nullptr;
        p->next = nullptr;
    } else if (p->next == nullptr) {
        L.last = p->prev;
        L.last->next = nullptr;
        p->prev = nullptr;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        p->next = nullptr;
        p->prev = nullptr;
    }

    delete p;
    p = nullptr;
}

adrSong searchSongById(SongList L, int id) {
    adrSong p = L.first;
    while (p != nullptr) {
        if (p->info.id == id) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

adrSong searchSongByTitle(SongList L, char title[]) {
    adrSong p = L.first;
    while (p != nullptr) {
        if (strcmpi(p->info.title, title) == 0) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

void updateSongData(adrSong p, Song newData) {
    if (p != nullptr) {
        p->info = newData;
    }
}

void printSongList(SongList L) {
    if (L.first == nullptr) {
        cout << "Song library is empty." << endl;
        return;
    }
    cout << "\n--- Song Library ---" << endl;

    adrSong p = L.first;
    while (p != nullptr) {
        cout <<
        p = p->next;
    }
    cout <<
}

void createPlaylistList(PlaylistList &PL) {
    PL.first = nullptr;
}

adrPlaylist allocatePlaylist(char name[]) {
    adrPlaylist p = new PlaylistNode;
    if (p != nullptr) {
        strcpy(p->name, name);
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
        while (q->next != nullptr) {
            q = q->next;
        }
        q->next = p;
    }
}

void deletePlaylistByName(PlaylistList &PL, char name[], adrPlaylist &p) {
    adrPlaylist current = PL.first;
    adrPlaylist prev = nullptr;

    while (current != nullptr && strcmpi(current->name, name) != 0) {
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
}

adrPlaylist searchPlaylistByName(PlaylistList PL, char name[]) {
    adrPlaylist p = PL.first;
    while (p != nullptr) {
        if (strcmpi(p->name, name) == 0) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

void addSongToPlaylist(adrPlaylist P, adrSong S) {
    if (P == nullptr || S == nullptr) {
        return;
    }
    adrRelation newRel = new RelationNode;
    newRel->song = S;
    newRel->next = nullptr;

    if (P->firstSong == nullptr) {
        P->firstSong = newRel;
    } else {
        adrRelation q = P->firstSong;
        while (q->next != nullptr) {
            q = q->next;
        }
        q->next = newRel;
    }
}

void removeSongFromPlaylist(adrPlaylist P, int songId) {
    if (P == nullptr || P->firstSong == nullptr) {
        return;
    }
    adrRelation current = P->firstSong;
    adrRelation prev = nullptr;

    while (current != nullptr && current->song->info.id != songId) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        return;
    }
    if (prev == nullptr) {
        P->firstSong = current->next;
    } else {
        prev->next = current->next;
    }
    delete current;
}

void printSongsInPlaylist(adrPlaylist P) {
    if (P == nullptr) {
        cout << "Playlist does not exist." << endl;
        return;
    }
    cout << "\nSongs in Playlist: " << P->name << " ---" << endl;

    if (P->firstSong == nullptr) {
        cout << "This playlist is empty." << endl;
        return;
    }
    cout <<
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