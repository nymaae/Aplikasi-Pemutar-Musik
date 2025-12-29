# Aplikasi Pemutar Musik
## [![Typing SVG](https://readme-typing-svg.demolab.com/?lines=Hello+Guys+!;Welcome+to+Aplikasi_Pemutar_Musik+🎧)](https://git.io/typing-svg)

Sistem ini dirancang untuk menjadi aplikasi pemutar musik berbasis konsol (CLI) yang mampu menyimpan dan mengelola banyak lagu dari berbagai artis, genre, album, dan tahun rilis. Sistem mendukung dua peran pengguna, yaitu Admin sebagai pengelola data lagu dan User sebagai pengguna aplikasi pemutar musik.

Sistem ini menggunakan tipe data bentukan (record) untuk merepresentasikan data lagu dan mengimplementasikan berbagai struktur data dinamis berbasis pointer untuk mendukung pengelolaan library, playlist, serta riwayat pemutaran lagu.

Seluruh proses pemutaran lagu pada sistem ini disimulasikan melalui perintah play / pause / next / previous yang ditampilkan dalam bentuk notifikasi pada console, tanpa memutar audio secara nyata.

## Fitur Utama
### Role Admin
#### 1. Manajemen Data Lagu
- Tambah lagu
- Edit data lagu
- Hapus lagu
- Tampilkan semua lagu

> Perubahan data lagu oleh Admin akan otomatis memengaruhi data lagu pada playlist User karena playlist hanya menyimpan referensi lagu.

#### 2. Mini Recap Statistik
Menampilkan ringkasan data sistem menggunakan fungsi:
- `countTotalSongs`
- `countTotalPlaylists`
- `countUniqueArtists`
- `countUniqueGenres`

### Role User
#### 1. Pemutaran Lagu
- Play / Pause
- Next / Previous
- Menampilkan detail *Now Playing* (judul, artis, durasi, sumber lagu)

#### 2. Manajemen Playlist
- Membuat playlist
- Menambahkan lagu ke playlist
- Menghapus lagu dari playlist
- Melihat isi playlist
- Memutar playlist

#### 3. Riwayat Pemutaran Lagu
- Menyimpan lagu yang telah diputar
- Lagu terakhir diputar akan muncul paling atas

#### 4. Pencarian Lagu
- Berdasarkan ID lagu
- Berdasarkan judul lagu

#### 5. Library User
- Menampilkan seluruh lagu yang tersedia dalam aplikasi

#### 6. Dashboard User
Menampilkan:
- Informasi lagu yang sedang diputar
- Status pemutaran (play/pause)
- Lagu terpopuler berdasarkan *play count* tertinggi

## Fitur Tambahan
- **Riwayat Pemutaran (History)**  
  Lagu yang terakhir diputar disimpan menggunakan struktur data **Stack**.
- **Top Song**  
  Menampilkan lagu dengan jumlah pemutaran terbanyak.
- **Smart Shuffle / Rekomendasi Lagu**  
  Sistem otomatis memutar lagu yang:
  1. Memiliki artis yang sama
  2. Memiliki genre yang sama
  3. Fallback ke lagu lain jika tidak ditemukan
- **Like Song (Favorite)**  
  Lagu yang di-like otomatis masuk ke playlist **FAVORITE**.

## Struktur Data yang Digunakan
- **Doubly Linked List** → Menyimpan data lagu sebagai library utama.
- **Singly Linked List** → Menyimpan data playlist
- **Stack (LIFO)** → Menyimpan riwayat pemutaran lagu
- **Multi Linked List Tipe A** – Relasi Many to Many → Digunakan untuk menghubungkan data playlist dengan data lagu, dimana:
   - Satu lagu dapat masuk ke banyak playlist
   - Satu playlist dapat berisi banyak lagu
   - Data lagu tidak diduplikasi, hanya direferensikan
   - Seluruh struktur data diimplementasikan menggunakan **alokasi memori dinamis**.

## Algoritma yang Digunakan
- **Sequential Search** → Mencari data lagu berdasarkan ID lagu dan judul lagu dengan menelusuri node satu per satu pada Doubly Linked List

## Struktur Program

### Header File: `spotify.h`
Berisi:
- Definisi struktur data (Song, Playlist, Relation, Stack)
- Deklarasi fungsi dan prosedur utama

### File Implementasi:
- `main.cpp`  
  → Alur utama program dan pemilihan role (Admin/User)
- `spotify.cpp`  
  → Implementasi operasi dasar dan logika fitur
- `ADMIN.cpp`  
  → Implementasi fitur Admin
- `USER.cpp`  
  → Implementasi fitur User

---

## Data Dummy
Saat program dijalankan, sistem otomatis memuat:
- **21 lagu**
- **4 artis** (Tulus, Coldplay, NewJeans, Sheila On 7)
- **1 playlist otomatis** (`MoodBooster`)

## Cara Menjalankan Program
1. **Kompilasi Program**:
   ```bash
   g++ main.cpp spotify.cpp ADMIN.cpp USER.cpp -o  aplikasi_pemutar_musik
2. **Jalankan Program**:
   ```bash
   ./aplikasi_pemutar_musik
   ```
3. Program akan menampilkan menu pemilihan role: User atau Admin
   - Admin dapat:
     - Menambah, menghapus, dan mengedit data lagu
     - Melihat ringkasan data lagu dan playlist

   - User dapat:
     - Melihat library lagu
     - Memutar lagu (play, pause, next, previous)
     - Mengelola playlist
     - Melihat history pemutaran lagu
