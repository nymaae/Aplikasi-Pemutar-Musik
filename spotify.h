#ifndef SPOTIFY_H_INCLUDED
#define SPOTIFY_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

struct Record {
    string idSong;
    string title;
    string artist;
    string genre;
};

typedef Record Song;

typedef struct SongNode *adrSong;
typedef struct RelationNode *adrRelation;
typedef struct PlaylistNode *adrPlaylist;
typedef struct QueueNode *adrQueue;

struct SongNode {
    Song info;
    adrSong next;
    adrSong prev;
};

struct SongList {
    adrSong first;
    adrSong last;
};

struct RelationNode {
    adrSong song;
    adrRelation next;
};

struct PlaylistNode {
    string name;
    adrRelation firstSong;
    adrPlaylist next;
};

struct PlaylistList {
    adrPlaylist first;
};

struct QueueNode {
    adrSong song;
    adrQueue next;
};

struct PlayQueue {
    adrQueue head;
    adrQueue tail;
};

void createSongList(SongList &L);
adrSong allocateSong(Song x);
void insertSongLast(SongList &L, adrSong p);
void deleteSongById(SongList &L, int id, adrSong &p, PlaylistList &PL, PlayQueue &Q);
adrSong searchSongById(SongList L, int id);
adrSong searchSongByTitle(SongList L, string title);
void updateSongData(adrSong p, Song newData);
void printSongList(SongList L);

void createPlaylistList(PlaylistList &PL);
adrPlaylist allocatePlaylist(string name);
void insertPlaylistLast(PlaylistList &PL, adrPlaylist p);
void deletePlaylistByName(PlaylistList &PL, string name, adrPlaylist &p);
adrPlaylist searchPlaylistByName(PlaylistList PL, string name);

void addSongToPlaylist(adrPlaylist P, adrSong S);
void removeSongFromPlaylist(adrPlaylist P, int songId);
void printSongsInPlaylist(adrPlaylist P);
void cleanupSongReferences(PlaylistList &PL, adrSong deletedSong);

void removeSongFromQueue(PlayQueue &Q, adrSong songToRemove);

#endif // SPOTIFY_H_INCLUDED