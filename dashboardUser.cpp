#include <iostream>
using namespace std;

void tampilanDepanUser() {
    cout << "------------------------------------------------------------\n";
    cout << "           ★  SPOTI-LITE DASHBOARD FOR USER  ★\n";
    cout << "------------------------------------------------------------\n\n";

    cout << "📜TOP SONG This Week \n";
    //fungsi menampilkan top song berdasarkan play count
    cout << "-> Favorite\n";
    cout << "   Neon Dreams\n";
    cout << "   Solar Wind\n";
    cout << "   Crystal Rain\n\n";

    cout << "📜LIBRARY \n";
    //fungsi menampilkan lagu yang ada secara acak
    cout << "-> Favorite\n";
    cout << "   Neon Dreams\n";
    cout << "   Solar Wind\n";
    cout << "   Crystal Rain\n\n";

    cout << ketPlayStop();


    cout << "---------------Menu----------------- \n";
    cout << "[A] Playlist         [B] Library\n";
    cout << "[C] History          [D] Singer\n"; 
    cout << "[E] Search           [X] Exit\n"
    cout << "------------------------------------\n";
    
    cout << "Pilih: \n";
   
}

void ketPlayStop() {

    bool isPlaying = true;
    if (isPlaying) {
        cout << "[▶️ PLAYING]\n";
    } else {
        cout << "[⏸️ PAUSED]\n";
    }
    return "";
}

/*   cout << "PLAYLIST (Doubly Linked List)\n";
    for (int i = 0; i < jumlah; i++) {
        if (i == indexLagu)
            cout << "-> " << playlist[i] << endl;   // lagu yg sedang diputar
        else
            cout << "   " << playlist[i] << endl;
}
                cout << "[N] Next     [P] Previous\n";

    cout << "NOW PLAYING\n";
    cout << "• Title  : Electric Heart\n";
    cout << "• Artist : Nova\n";
    cout << "• Album  : Midnight Pulse\n";
    cout << "• Status : PLAYING\n\n";
    }*/
