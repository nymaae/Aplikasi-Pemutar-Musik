#ifndef SPOTIFY_H_INCLUDED
#define SPOTIFY_H_INCLUDED

#include <iostream>
#include <string>
#include <stack>

struct Record {
    std::string idSong;
    std::string title;
    std::string artist;
    std::string genre;
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
    std::string name;
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

// Song list functions
void createSongList(SongList &L);
adrSong allocateSong(Song x);
void insertSongLast(SongList &L, adrSong p);
void deleteSongById(SongList &L, const std::string &id, adrSong &p, PlaylistList &PL, PlayQueue &Q);
adrSong searchSongById(SongList L, const std::string &id);
adrSong searchSongByTitle(SongList L, const std::string &title);
void updateSongData(adrSong p, Song newData);
void printSongList(SongList L);
void printSongInfo(adrSong s);

// Playlist functions 
void createPlaylistList(PlaylistList &PL);
adrPlaylist allocatePlaylist(const std::string &name);
void insertPlaylistLast(PlaylistList &PL, adrPlaylist p);
void deletePlaylistByName(PlaylistList &PL, const std::string &name, adrPlaylist &p);
adrPlaylist searchPlaylistByName(PlaylistList PL, const std::string &name);

void addSongToPlaylist(adrPlaylist P, adrSong S);
void removeSongFromPlaylist(adrPlaylist P, const std::string &songId);
void printSongsInPlaylist(adrPlaylist P);
void cleanupSongReferences(PlaylistList &PL, adrSong deletedSong);

// Queue functions
void removeSongFromQueue(PlayQueue &Q, adrSong songToRemove);

// Playback & history (prototypes)
extern adrSong currentSong;
extern adrPlaylist currentPlaylist;
extern bool isPlaying;
extern std::stack<adrSong> historyStack;

void pushHistory(adrSong s);
void printHistory();

void playSong(adrSong s, adrPlaylist p);
void pauseSong();
void resumeSong();
void playNext();
void playPrev();
adrRelation findRelationNode(adrPlaylist p, adrSong s);

#endif // SPOTIFY_H_INCLUDED
