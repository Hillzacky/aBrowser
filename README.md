# aBrowser
aBrowser adalah peramban web yang berfokus pada privasi dan keamanan. Peramban ini dirancang untuk mencegah pelacakan online dan fingerprinting.
### Fitur
 * Spoofing canvas, WebGL, navigator, zona waktu, geolocation, perangkat media, layar, baterai, font, dan plugin.
 * Pengaturan proksi.
 * Penghapusan cache, cookie, dan riwayat.
 * Mode incognito.
 * Pengelola bookmark.
 * Pengelola unduhan.
 * Dukungan ekstensi.
 * API untuk kontrol eksternal.
 * dan masih banyak lagi.
### Cara Build
Berikut adalah langkah-langkah untuk membangun aBrowser menggunakan CMake:
#### Prasyarat
 * Qt (Qt Creator, Qt libraries, dan qmake)
 * CEF (Chromium Embedded Framework)
 * CMake
 * Compiler C++ (GCC, Clang, MSVC)
#### Langkah-langkah Build
 * Unduh dan Instal CEF:
   * Unduh distribusi biner CEF [disini](https://cef-builds.spotifycdn.com/index.html).
   * Ekstrak arsip ke direktori yang diinginkan (misalnya, ~/cef).
 * Konfigurasi CMake:
   * Buat direktori build di dalam direktori proyek Anda (misalnya, build).
   * Buka terminal dan navigasikan ke direktori build.
   * Jalankan perintah CMake berikut:
```bash
cmake -DCEF_ROOT=~/cef -DCMAKE_PREFIX_PATH=/path/to/Qt ~/aBrowser
```
   * Ganti ~/cef dengan jalur ke direktori CEF Anda dan /path/to/Qt dengan jalur ke instalasi Qt Anda.
 * Build Proyek:
   * Setelah konfigurasi CMake berhasil, jalankan perintah build berikut:
```bash
cmake --build .
```

   * Ini akan membangun executable aBrowser.
#### Menjalankan Aplikasi:
   Setelah proses build selesai, executable aBrowser akan berada pada folder build. Jalankan executable tersebut untuk menjalankan aplikasi.
##### Catatan
 * Pastikan variabel lingkungan PATH Anda menyertakan direktori yang berisi executable Qt dan CEF.
 * Jika Anda mengalami masalah build, periksa log CMake dan pastikan semua prasyarat telah terpenuhi.
#### Instalasi
 * Setelah build berhasil, salin file executable ke direktori yang diinginkan.
 * (Opsional) Tambahkan direktori ke PATH sistem Anda.
#### Cara Penggunaan
 * Jalankan file executable aBrowser.
 * Masukkan URL di bilah alamat dan tekan Enter.
 * Gunakan menu dan toolbar untuk mengakses berbagai fitur.
### Dokumentasi
 * Spoofing: Pengaturan spoofing dapat dikonfigurasi di menu Pengaturan.
 * Proksi: Pengaturan proksi dapat dikonfigurasi di menu Pengaturan.
 * Mode Incognito: Mode incognito dapat diaktifkan dari menu File.
 * Bookmark: Bookmark dapat ditambahkan dan dikelola dari menu Bookmark.
 * Unduhan: Unduhan dapat dikelola dari menu Alat.
 * Ekstensi: Ekstensi dapat diinstal dan dikelola dari menu Alat.
### Dokumentasi API
aBrowser menyediakan API untuk kontrol eksternal melalui antarmuka baris perintah atau komunikasi antar-proses. Berikut adalah beberapa perintah API yang tersedia:
 * loadURL(url): Memuat URL yang ditentukan di tab saat ini.
 * goBack(): Kembali ke halaman sebelumnya.
 * goForward(): Maju ke halaman berikutnya.
 * reload(): Memuat ulang halaman saat ini.
 * executeJS(code): Menjalankan kode JavaScript yang ditentukan di halaman saat ini.
 * getHTML(): Mengembalikan sumber HTML dari halaman saat ini.
 * getURL(): Mengembalikan URL dari halaman saat ini.
 * getCookies(): Mengembalikan cookie dari halaman saat ini.
 * setProxy(proxy): Mengatur proksi yang ditentukan.
 * setSettings(settingsJSON): Mengatur pengaturan peramban dari JSON yang ditentukan.
 * takeScreenshot(filePath): Mengambil tangkapan layar dari halaman saat ini dan menyimpannya ke jalur file yang ditentukan.
### Kontribusi
Kontribusi dipersilakan! Silakan kirim pull request atau laporkan masalah di GitHub.
### Lisensi
Proyek ini dilisensikan di bawah Lisensi MIT.
