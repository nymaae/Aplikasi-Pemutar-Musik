#ifndef SPOTIFY_H_INCLUDED
#define SPOTIFY_H_INCLUDED

struct Song {
    int id;
    string title;
    string artist;
    string genre;
};

typedef struct SongNode *adrSong;
struct SongNode {
    Song info;
    adrSong next;
    adrSong prev;
};

struct SongList {
    adrSong first;
    adrSong last;
};

typedef struct RelationNode *adrRelation;
typedef struct PlaylistNode *adrPlaylist;

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

typedef struct QueueNode *adrQueue;

struct QueueNode {
    adrSong song;
    adrQueue next;
};

struct PlayQueue {
    adrQueue head;
    adrQueue tail;
};

void removeSongFromQueue(PlayQueue &Q, adrSong songToRemove)
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
void createPlaylistList(PlaylistList &PL);
adrPlaylist allocatePlaylist(string name);
void insertPlaylistLast(PlaylistList &PL, adrPlaylist p);
void deletePlaylistByName(PlaylistList &PL, string name, adrPlaylist &p);
adrPlaylist searchPlaylistByName(PlaylistList PL, string name);
void addSongToPlaylist(adrPlaylist P, adrSong S);
void removeSongFromPlaylist(adrPlaylist P, int songId);
void printSongsInPlaylist(adrPlaylist P);
void cleanupSongReferences(PlaylistList &PL, adrSong deletedSong);

#endif // SPOTIFY_H_INCLUDED
