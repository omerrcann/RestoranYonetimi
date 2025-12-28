#include <iostream>
#include <memory>
#include <vector>
#include <limits>
#include "repositories/Depo.hpp"
#include "services/RestoranServisi.hpp"
#include "entities/Masa.hpp"
#include "entities/Garson.hpp"
#include "entities/MenuKategori.hpp"
#include "entities/MenuItem.hpp"
#include "entities/Siparis.hpp"
#include "entities/SiparisKalemi.hpp"
#include "entities/Rezervasyon.hpp"
#include "utils/TarihUtils.h"

using namespace std;

void ayrac() {
    cout << "------------------------------------------------" << endl;
}

void menuYazdir() {
    cout << endl;
    cout << "=== ANA MENU ===" << endl;
    cout << "[1] Siparis Olustur (Masa Ac)" << endl;
    cout << "[2] Siparise Urun Ekle" << endl;
    cout << "[3] Hesap Goruntule (Fis Yazdir)" << endl;
    cout << "[4] Siparis Kapat (Odeme Al)" << endl;
    cout << "[5] Musait Masalari Listele" << endl;
    cout << "[6] Gunluk Ciro Raporu" << endl;
    cout << "[7] Rezervasyon Yap" << endl;
    cout << "[8] Yeni Masa Ekle" << endl;
    cout << "[9] Yeni Menu Ogesi Ekle" << endl;
    cout << "[0] CIKIS" << endl;
    cout << "Seciminiz: ";
}

void bekle() {
    cout << "\nDevam etmek icin Enter'a basin...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    Depo<Masa> masaDepo;
    Depo<Garson> garsonDepo;
    Depo<MenuKategori> kategoriDepo;
    Depo<MenuItem> menuItemDepo;
    Depo<Siparis> siparisDepo;
    Depo<SiparisKalemi> siparisKalemiDepo;
    Depo<Rezervasyon> rezervasyonDepo;

    RestoranServisi restoran(
            masaDepo, garsonDepo, kategoriDepo, menuItemDepo,
            siparisDepo, siparisKalemiDepo, rezervasyonDepo
    );

    cout << "Sistem baslatiliyor ve varsayilan veriler yukleniyor..." << endl;

    restoran.masaEkle(1, 4, "Salon");
    restoran.masaEkle(2, 4, "Salon");
    restoran.masaEkle(3, 2, "Teras");
    restoran.masaEkle(4, 6, "Bahce");
    restoran.masaEkle(5, 8, "VIP");

    auto g1 = make_shared<Garson>(0, "G1", "Ali Yilmaz", "555-123", "Gunduz");
    garsonDepo.ekle(g1);

    restoran.menuItemEkle("Mercimek Corbasi", "Sicak", 50.0, 1, 5);
    restoran.menuItemEkle("Adana Kebap", "Acili", 220.0, 2, 20);
    restoran.menuItemEkle("Iskender", "Yogurtlu", 250.0, 2, 20);
    restoran.menuItemEkle("Mevsim Salata", "Taze", 80.0, 3, 10);
    restoran.menuItemEkle("Kola", "Soguk", 35.0, 4, 0);
    restoran.menuItemEkle("Ayran", "Yayik", 25.0, 4, 2);
    restoran.menuItemEkle("Kunefe", "Peynirli", 120.0, 5, 15);

    cout << "Sistem hazir! " << endl;


    int secim;
    while (true) {
        menuYazdir();
        if (!(cin >> secim)) {
            cout << "Lutfen gecerli bir sayi giriniz!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (secim == 0) {
            cout << "Cikis yapiliyor. Iyi gunler!" << endl;
            break;
        }

        ayrac();
        try {
            switch (secim) {
                case 1: { // Sipariş Oluştur
                    int masaId, garsonId;
                    cout << "Masa ID (1-5): "; cin >> masaId;
                    cout << "Garson ID (Genelde 1): "; cin >> garsonId;

                    int siparisId = restoran.siparisOlustur(masaId, garsonId);
                    cout << ">> BASARILI: Siparis olusturuldu. Siparis No: " << siparisId << endl;
                    break;
                }
                case 2: { // Siparişe Ürün Ekle
                    int siparisId, urunId, adet;
                    cout << "Siparis ID: "; cin >> siparisId;

                    cout << "\n--- HIZLI MENU LISTESI ---\n";
                    cout << "1. Corba (50 TL)\n2. Adana (220 TL)\n3. Iskender (250 TL)\n";
                    cout << "5. Kola (35 TL)\n6. Ayran (25 TL)\n7. Kunefe (120 TL)\n";
                    cout << "--------------------------\n";

                    cout << "Urun ID: "; cin >> urunId;
                    cout << "Adet: "; cin >> adet;

                    restoran.sipariseItemEkle(siparisId, urunId, adet);
                    cout << ">> BASARILI: Urunler siparise eklendi." << endl;
                    break;
                }
                case 3: { // Hesap Yazdır
                    int siparisId;
                    cout << "Siparis ID: "; cin >> siparisId;
                    cout << restoran.hesapYazdir(siparisId) << endl;
                    break;
                }
                case 4: { // Sipariş Kapat
                    int siparisId;
                    cout << "Kapatilacak Siparis ID: "; cin >> siparisId;
                    restoran.siparisKapat(siparisId);
                    cout << ">> BASARILI: Siparis kapatildi, masa bosaltildi." << endl;
                    break;
                }
                case 5: { // Müsait Masalar
                    auto masalar = restoran.musaitMasalariGetir();
                    cout << "Musait Masalar:" << endl;
                    if (masalar.empty()) {
                        cout << "  (Yok, hepsi dolu)" << endl;
                    } else {
                        for (const auto& m : masalar) {
                            cout << "  - Masa No: " << m->get_id() << endl;
                        }
                    }
                    break;
                }
                case 6: { // Ciro
                    string tarih = TarihUtils::bugunTarihi();
                    cout << "Bugunun (" << tarih << ") cirosu hesaplaniyor..." << endl;
                    double ciro = restoran.gunlukCiroHesapla(tarih);
                    cout << ">> TOPLAM CIRO: " << ciro << " TL" << endl;
                    break;
                }
                case 7: { // Rezervasyon
                    int mId, kisi;
                    string ad, tel, saat;
                    cout << "Masa ID: "; cin >> mId;
                    cout << "Musteri Adi (Bosluksuz): "; cin >> ad;
                    cout << "Telefon: "; cin >> tel;
                    cout << "Saat (HH:MM): "; cin >> saat;
                    cout << "Kisi Sayisi: "; cin >> kisi;

                    restoran.rezervasyonYap(mId, ad, tel, TarihUtils::bugunTarihi() + " " + saat, kisi);
                    cout << ">> BASARILI: Rezervasyon alindi." << endl;
                    break;
                }
                case 8: { // Yeni Masa
                    int num, kap;
                    string konum;
                    cout << "Masa No: "; cin >> num;
                    cout << "Kapasite: "; cin >> kap;
                    cout << "Konum (Salon/Bahce): "; cin >> konum;
                    restoran.masaEkle(num, kap, konum);
                    cout << ">> Masa eklendi." << endl;
                    break;
                }
                case 9: { // Yeni Ürün
                    string ad, aciklama;
                    double fiyat;
                    int sure;
                    cout << "Urun Adi (Bosluksuz): "; cin >> ad;
                    cout << "Aciklama (Bosluksuz): "; cin >> aciklama;
                    cout << "Fiyat: "; cin >> fiyat;
                    cout << "Hazirlik Suresi (dk): "; cin >> sure;
                    restoran.menuItemEkle(ad, aciklama, fiyat, 1, sure);
                    cout << ">> Menu ogesi eklendi." << endl;
                    break;
                }
                default:
                    cout << "Gecersiz secim!" << endl;
            }
        } catch (const exception& e) {
            cout << "\n!!! HATA OLUSTU: " << e.what() << " !!!" << endl;
        }

    }

    return 0;
}