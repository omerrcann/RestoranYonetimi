# 🍽️ Restoran Yönetim Sistemi (Restaurant Management System)

![Language](https://img.shields.io/badge/language-C%2B%2B17-blue)
![Build](https://img.shields.io/badge/build-CMake-green)
![Architecture](https://img.shields.io/badge/architecture-3--Tier-orange)

**Restoran Yönetim Sistemi**, bir restoranın masa düzeninden sipariş takibine, stok yönetiminden personel performansına kadar tüm süreçlerini dijitalleştiren; **Modern C++** ve **Katmanlı Mimari** prensipleriyle geliştirilmiş kapsamlı bir otomasyon projesidir.

---

## 🚀 Proje Hakkında

Bu proje, nesne yönelimli programlama (OOP) ve yazılım mühendisliği standartlarına (SOLID, Clean Code) sadık kalınarak geliştirilmiştir. Spagetti kod yapısından kaçınılmış, **Entity (Veri)**, **Repository (Erişim)** ve **Service (İş Mantığı)** katmanları birbirinden izole edilmiştir.

### 🎯 Temel Özellikler
* **Masa Yönetimi:** Masaların durumu (Boş/Dolu/Rezerve) ve kapasite takibi.
* **Sipariş Sistemi:** Masaya özel sipariş açma, ürün ekleme ve anlık tutar hesaplama.
* **Raporlama:** Günlük ciro hesaplama ve garson performans analizleri.
* **Akıllı Bellek Yönetimi:** `std::shared_ptr` kullanılarak güvenli bellek yönetimi (No Memory Leaks).
* **Veri Yapıları:** Generic Repository yapısı ile tüm veriler üzerinde esnek CRUD işlemleri.

---

## 🛠️ Kullanılan Teknolojiler

| Teknoloji | Açıklama |
| :--- | :--- |
| **C++17** | Projenin ana programlama dili. |
| **CMake** | Cross-platform derleme ve build sistemi. |
| **3-Tier Architecture** | Entity, Service ve Repository katmanlı mimari. |
| **Dependency Injection** | Bağımlılıkları azaltmak için ana bloktan servise nesne aktarımı. |

---

## 📸 Veri Modeli (Database Schema)

Sistem çalıştığında bellekte tutulan örnek veri yapıları aşağıdaki gibidir:

| Tablo | Açıklama |
| :--- | :--- |
| **Masalar** | Restoranın fiziksel yerleşim planı ve doluluk durumları. |
| **Menü** | Kategorilere ayrılmış yemek ve içecek listesi. |
| **Siparişler** | Tarih, masa ve garson bazlı aktif/geçmiş siparişler. |
| **Personel** | Garsonların vardiya ve iletişim bilgileri. |

*(Detaylı veri tabloları kaynak kod içerisindeki `Depo` sınıflarında incelenebilir.)*

---

## 💻 Kurulum ve Çalıştırma

Proje **CMake** altyapısını kullanır. İşletim sisteminize göre aşağıdaki adımları izleyebilirsiniz.

### 🍎 MacOS & 🐧 Linux
Terminali açın ve proje dizininde şu komutları çalıştırın:

```bash
mkdir build
cd build
cmake ..
make
./restoran_yonetim
