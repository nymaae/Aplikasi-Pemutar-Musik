#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

// --- STRUKTUR DATA ---

struct Record {
    string idSong;
    string title;
    string artist;
    string genre;
    string durasi;
    int playCount;
};
typedef Record Song;

typedef struct SongNode *adrSong;
typedef struct RelationNode *adrRelation;
typedef struct PlaylistNode *adrPlaylist;
typedef struct QueueNode *adrQueue;
typedef struct ElmHistory *adrHistory;

// 1. LIST LAGU (Doubly Linked List)
struct SongNode {
    Song info;
    adrSong next;
    adrSong prev;
};

struct SongList {
    adrSong first;
    adrSong last;
};

// 2. RELASI PLAYLIST (Single Linked List)
struct RelationNode {
    adrSong song;
    adrRelation next;
};

// 3. LIST PLAYLIST (Single Linked List)
struct PlaylistNode {
    string name;
    adrRelation firstSong;
    adrPlaylist next;
};

struct PlaylistList {
    adrPlaylist first;
};

struct PlayerState {
    adrSong currentSong;
    adrPlaylist currentPlaylist;
    bool isPlaying;
};

struct ElmHistory {
    adrSong info;
    adrHistory next;
};

struct StackHistory {
    adrHistory top;
};

// --- PRIMITIF (OPERASI DASAR) ---

// Lagu
void createSongList(SongList &L);
adrSong allocateSong(Song x);
void insertSongLast(SongList &L, adrSong p);
void deleteSongPrimitif(SongList &L, adrSong p);
adrSong searchSongById(SongList L, string id);
adrSong searchSongByTitle(SongList L, string title);
void printSongList(SongList L);

// Playlist
void createPlaylistList(PlaylistList &PL);
adrPlaylist allocatePlaylist(string name);
void insertPlaylistLast(PlaylistList &PL, adrPlaylist p);
adrPlaylist searchPlaylistByName(PlaylistList PL, string name);

// Relasi Playlist
adrRelation allocateRelation(adrSong s);
void insertRelationLast(adrPlaylist P, adrRelation r);
void deleteRelation(adrPlaylist P, adrSong s);
void printSongsInPlaylist(adrPlaylist P);

void createStack(StackHistory &S);
void pushStack(StackHistory &S, adrSong pLagu);
void printStack(StackHistory S);

// --- FITUR LOGIKA ---

void deleteSongComplete(SongList &L, PlaylistList &PL, PlayerState &PS, string id);
void playSong(PlayerState &PS, StackHistory &H, adrSong s, adrPlaylist context);
void pauseSong(PlayerState &PS);
void playNext(PlayerState &PS, StackHistory &H, SongList L);
void playPrev(PlayerState &PS, StackHistory &H, SongList L);
string ketPlayStop(PlayerState PS);
adrSong findSimilarSong(SongList L, adrSong current);

int countTotalSongs(SongList L);
int countTotalPlaylists(PlaylistList PL);
int countUniqueArtists(SongList L);
int countUniqueGenres(SongList L);

void printTopSong(SongList L);
void printSingers(SongList L);

#endif // TUBES_H_INCLUDED
