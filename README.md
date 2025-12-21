# Aplikasi Pemutar Musik
## [![Typing SVG](https://readme-typing-svg.demolab.com/?lines=Hello+gengs+!;Welcome+to+Aplikasi Pemutar Musik+🎧)](https://git.io/typing-svg)

Sistem ini dirancang untuk menjadi aplikasi pemutar musik berbasis konsol (CLI) yang mampu menyimpan dan mengelola banyak lagu dari berbagai artis, genre, album, dan tahun rilis. Sistem mendukung dua peran pengguna, yaitu Admin sebagai pengelola data lagu dan User sebagai pengguna aplikasi pemutar musik.

Sistem ini menggunakan tipe data bentukan (record) untuk merepresentasikan data lagu dan mengimplementasikan berbagai struktur data dinamis berbasis pointer untuk mendukung pengelolaan library, playlist, serta riwayat pemutaran lagu.

Seluruh proses pemutaran lagu pada sistem ini disimulasikan melalui perintah play / pause / next / previous yang ditampilkan dalam bentuk notifikasi pada console, tanpa memutar audio secara nyata.

## Fitur Utama

### 1. **Manajemen Data Lagu (Admin)**
- **Tambah Lagu**: Menambahkan lagu baru ke dalam library.
- **Edit Lagu**: Mengubah data lagu yang sudah ada (judul, artis, genre, durasi).
- **Hapus Lagu**: Menghapus lagu dari library.
- **Tampilkan Semua Lagu**: Melihat seluruh data lagu yang tersimpan.
- **Mini Recap Statistik**:
  - Total lagu
  - Total playlist
  - Jumlah artis unik
  - Jumlah genre unik

> Perubahan data lagu oleh Admin akan otomatis memengaruhi data lagu pada playlist User.

### 2. **Pemutaran Lagu (User)**
- **Play / Pause Lagu**
- **Next / Previous Lagu**
- **Now Playing Detail**:
  - Judul lagu
  - Artis
  - Durasi
  - Sumber lagu (Library atau Playlist)

### 3. **Manajemen Playlist (User)**
- Membuat playlist baru
- Menambahkan lagu ke playlist
- Menghapus lagu dari playlist
- Melihat isi playlist
- Memutar playlist

### 4. **Pencarian Lagu**
- Cari lagu berdasarkan **ID Lagu**
- Cari lagu berdasarkan **Judul Lagu**

### 5. **Fitur Tambahan**
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
- **Doubly Linked List** → Menyimpan data lagu (Library)
- **Singly Linked List** → Menyimpan data playlist
- **Singly Linked List (Relasi)** → Menghubungkan playlist dengan lagu
- **Stack** → Menyimpan riwayat pemutaran lagu
- **Struct & Pointer** → Mengelola status pemutar lagu (PlayerState)

Seluruh struktur data diimplementasikan menggunakan **alokasi memori dinamis**.

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
