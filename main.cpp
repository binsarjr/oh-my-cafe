/**
 * @file main.cpp
 * @author Muhammad Albaab Ridho Pratama (21.11.4057)
 * @author Evi Zulfia Rahmah (21.11.4064)
 * @author Kalwabed Rizki (21.11.4078)
 * @author Ndaru Windra Sayidinaa (21.11.4089)
 * @author Firresa Alif Nurrahman (21.11.4104)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (c) 2022 Kelompok 7 -- 21 IF 04
 *
 */

#include <iomanip>
#include <iostream>

#include "VariadicTable.h"
#include "helpers.h"

using namespace std;

/**
 * @brief Menampung pesanan user
 */
struct Pesanan
{
  string nama;
  int index, jumlah, harga;
} pesanan[10];

/**
 * @brief Menampung item menu
 */
struct Item
{
  string nama;
  int harga, jumlah;
};

Item menu[10] = {
    {"Nasi Goreng", 10000, 0},
    {"Nasi Padang", 12000, 0},
    {"Mie ayam V1", 15000, 0},
    {"Mie Goreng", 18000, 0},
    {"Nasi Kuning", 20000, 0},
    {"V60", 30000, 0},
    {"Choco milk", 13000, 0},
    {"Long black", 20000, 0},
    {"Americano", 17000, 0},
    {"Cappucino", 18000, 0},
};

int totalHarga, indexPesanan = 0;

/**
 * @brief Menampilkan daftar menu yang tersedia
 */
void listMenu()
{
  // print menu with matrix style
  cout << "==============================" << endl;
  cout << "=          MAKANAN           =" << endl;
  cout << "==============================" << endl;
  for (int i = 0; i < 5; i++)
  {
    cout << i + 1 << ". " << formatTab(menu[i].nama);
    cout << menu[i].harga << endl;
  }

  // print menu with matrix style
  cout << "==============================" << endl;
  cout << "=          MINUMAN           =" << endl;
  cout << "==============================" << endl;
  for (int i = 5; i < 10; i++)
  {
    cout << i + 1 << ". " << formatTab(menu[i].nama);
    cout << menu[i].harga << endl;
  }

  cout << endl;
}

/**
 * @brief Menampilkan list pesanan
 *
 * @param mode  : 0 default, 1 update
 */
void tampilkanPesanan(int mode = 0)
{
  system("clear");

  switch (mode)
  {
  case 1:
    cout << "==============================" << endl;
    cout << "=        Ubah Pesanan        =" << endl;
    cout << "==============================" << endl;
    break;

  default:
    cout << "==============================" << endl;
    cout << "=        Pesanan             =" << endl;
    cout << "==============================" << endl;
    break;
  }

  VariadicTable<int, string, int, int, int> vt(
      {"No.", "Menu", "Jumlah", "Harga", "Subtotal"}, 10);

  // perulangan untuk menampilkan pesanan makanan dan harga makanan, jumlah
  // makanan dan subtotal makanan
  int indexNumber = 1;
  // tampilkan pesanan
  for (int i = 0; i < 10; i++)
  {
    if (pesanan[i].jumlah > 0)
    {
      vt.addRow(indexNumber++, pesanan[i].nama, pesanan[i].jumlah,
                menu[pesanan[i].index].harga, pesanan[i].harga);
    }
  }

  // mencetak tabel pesanan
  vt.print(cout);

  totalHarga = 0;
  for (int i = 0; i < 10; i++)
  {
    totalHarga += menu[pesanan[i].index].harga * pesanan[i].jumlah;
  }

  cout << "Total Harga Pesanan Anda : " << totalHarga << endl;
}

/**
 * @brief Prompt untuk mengubah pesanan
 */
void promptUbahPesanan()
{
  int nomorMenu, jumlahPesanan, subtotalBaru;

  tampilkanPesanan(1);
  cout << endl;
  cout << "Masukkan nomor menu yang ingin diubah : ";
  cin >> nomorMenu;
  cout << "Masukkan jumlah pesanan yang ingin diubah : ";
  cin >> jumlahPesanan;

  subtotalBaru = menu[pesanan[nomorMenu - 1].index].harga * jumlahPesanan;
  pesanan[nomorMenu - 1].jumlah = jumlahPesanan;
  pesanan[nomorMenu - 1].harga = subtotalBaru;
}

/**
 * @brief Masukkan item menu ke daftar pesanan
 *
 * @param index
 * @param indexMenu
 */
void assignPesanan(int index, int indexMenu)
{
  // memasukkan nilai pesanan ke dalam array pesanan
  pesanan[index].nama = menu[indexMenu].nama;
  pesanan[index].index = indexMenu;
  pesanan[index].jumlah = menu[indexMenu].jumlah;
  pesanan[index].harga = menu[indexMenu].harga * menu[indexMenu].jumlah;
}

int main()
{
  int pilihan, lanjut, uangPembayaran, totalKembalian = 0, ubahPesanan, donasi,
                                       isDonasi;

  cout << "==============================" << endl;
  cout << "=     SELAMAT DATANG DI      =" << endl;
  cout << "=        Oh My Cafe          =" << endl;
  cout << "==============================" << endl;

pilihMenu:
  listMenu();

  cout << "Masukkan pilihan menu: ";
  cin >> pilihan;

  for (int i = 0; i < 10; i++)
  {
    if (pilihan == i + 1)
    {
      cout << "Masukkan jumlah " << menu[i].nama << " yang ingin dipesan : ";
      cin >> menu[i].jumlah;

      assignPesanan(indexPesanan++, i);

      cout << endl;
      cout << "Apakah anda ingin memesan lagi? (1. Ya, 2. Tidak) : ";
      cin >> lanjut;

      if (lanjut == 1)
      {
        system("clear");
        goto pilihMenu;
      }
      break;
    }
  }

  tampilkanPesanan();

  cout << endl;
  cout << "Apakah anda ingin mengubah pesanan? (1. Ya, 2. Tidak) : ";
  cin >> ubahPesanan;

  if (ubahPesanan == 1)
  {
    promptUbahPesanan();
    tampilkanPesanan();

    cout << endl;
    cout << "Apakah anda ingin memesan lagi? (1. Ya, 2. Tidak) : ";
    cin >> lanjut;

    if (lanjut == 1)
    {
      goto pilihMenu;
    }
  }

  tampilkanPesanan();

bayar:
  cout << endl;
  cout << "Masukkan uang pembayaran: ";
  cin >> uangPembayaran;

  totalKembalian = uangPembayaran - totalHarga;

  if (totalKembalian < 0)
  {
    cout << "Uang pembayaran anda kurang" << endl;
    cout << "Tekan ENTER untuk kembali input uang...";
    cin.ignore();
    cin.get();
    goto bayar;
  }

  tampilkanPesanan();
  cout << "Uang pembayaran: " << uangPembayaran << endl;
  cout << "Total kembalian: " << totalKembalian << endl;

  if (totalKembalian > 0 && totalKembalian <= 500)
  {
    cout << endl;
    cout << "Apakah anda ingin mengirimkan donasi? (1. Ya, 2. Tidak) : ";
    cin >> isDonasi;
    if (isDonasi == 1)
    {
      donasi = totalKembalian;
      totalKembalian = 0;
      tampilkanPesanan();
      cout << "Uang pembayaran: " << uangPembayaran << endl;
      cout << "Total kembalian: " << totalKembalian << endl;
      cout << "Donasi: " << donasi << endl;
    }
  }

  cout << endl;
  cout << "--- Terima kasih telah berbelanja di Oh My Cafe ---" << endl;

  return 0;
}
