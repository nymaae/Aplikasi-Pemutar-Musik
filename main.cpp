#include <iostream>
#include "spotify.h"
#include "dashboardAdmin.cpp"
#include "dashboardUser.cpp"

using namespace std;

int main() {

    int choice1, choice2, choice3;

    cout << "----------Selamat datang di Spoti-Lite!----------\n";
    cout << "Pilih Role Anda:\n";
    cout << "[1] User\n";
    cout << "[2] Admin\n";
    cout << "[X] Exit\n";
    cout << "---------------------------------------------\n";
    cout << "Masukkan pilihan Anda: ";  
    
    cin >> choice;
    if (choice == '1') {
        tampilanDepanUser();
        cin >> choice2; 
        if choice2 == 'A' || choice2 == 'a' { 
            //fungsi history
        } else if (choice2 == 'B' || choice2 == 'b') {
            //fungsi queue
        } else if (choice2 == 'C' || choice2 == 'c') {
            //fungsi playlist
        } else if (choice2 == 'D' || choice2 == 'd') {
            //fungsi singer
        } else if (choice2 == 'E' || choice2 == 'e') {
            //fungsi search
        } else if (choice2 == 'X' || choice2 == 'x') {
            cout << "Terima kasih telah menggunakan Spoti-Lite!\n";
            return 0;
        } else {
            cout << "Pilihan tidak valid. Silahkan pilih kembali!\n";
            return tampilanDepanUser();
        }

    } else if (choice == '2') {
        tampilanDepanAdmin();
        cin >> choice2; 
        if choice2 == 'A' || choice2 == 'a' {
            //fungsi tambah/hapus
        } else if (choice2 == 'B' || choice2 == 'b') {
            //fungsi edit data lagu
        } else if (choice2 == 'C' || choice2 == 'c') {
            //fungsi tampilkan data semua lagu saat ini
        } else if (choice2 == 'X' || choice2 == 'x') {
            cout << "Terima kasih telah menggunakan Spoti-Lite!\n";
            return 0;
        } else {
            cout << "Pilihan tidak valid. Silahkan pilih kembali!\n";
            return tampilanDepanAdmin();
        }

    } else {
        cout << "Pilihan tidak valid. Silahkan pilih kembali!\n";
        return main();
    } 

}
