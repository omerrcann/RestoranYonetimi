#ifndef RESTORAN_SERVISI_HPP
#define RESTORAN_SERVISI_HPP

#include <memory>
#include <vector>
#include <string>
#include "../repositories/Depo.hpp"
#include "../entities/Masa.hpp"
#include "../entities/Garson.hpp"
#include "../entities/MenuKategori.hpp"
#include "../entities/MenuItem.hpp"
#include "../entities/Siparis.hpp"
#include "../entities/SiparisKalemi.hpp"
#include "../entities/Rezervasyon.hpp"

struct GarsonPerformans {
    int toplam_siparis;
    double toplam_ciro;
    double ortalama_siparis;
};

class RestoranServisi {
private:
    Depo<Masa>& _masaDepo;
    Depo<Garson>& _garsonDepo;
    Depo<MenuKategori>& _kategoriDepo;
    Depo<MenuItem>& _menuItemDepo;
    Depo<Siparis>& _siparisDepo;
    Depo<SiparisKalemi>& _siparisKalemiDepo;
    Depo<Rezervasyon>& _rezervasyonDepo;

public:
    RestoranServisi(
            Depo<Masa>& masaDepo, Depo<Garson>& garsonDepo,
            Depo<MenuKategori>& kategoriDepo, Depo<MenuItem>& menuItemDepo,
            Depo<Siparis>& siparisDepo, Depo<SiparisKalemi>& siparisKalemiDepo,
            Depo<Rezervasyon>& rezervasyonDepo
    );

    ~RestoranServisi() = default;

    // --- Servis Metodları  ---

    // 1. Masa Ekleme
    void masaEkle(int numara, int kapasite, const std::string& konum);

    // 2. Menü Öğesi Ekleme
    void menuItemEkle(const std::string& ad, const std::string& aciklama, double fiyat, int kategori_id, int hazirlik_suresi);

    // 3. Sipariş Oluşturma
    int siparisOlustur(int masa_id, int garson_id);

    // 4. Siparişe Ürün Ekleme
    void sipariseItemEkle(int siparis_id, int menu_item_id, int miktar, const std::string& notlar = "");

    // 5. Sipariş Kapatma
    void siparisKapat(int siparis_id);

    // 6. Hesap Yazdırma
    std::string hesapYazdir(int siparis_id);

    // 7. Rezervasyon Yapma
    void rezervasyonYap(int masa_id, const std::string& musteri_adi, const std::string& telefon, const std::string& tarih_saat, int kisi_sayisi);

    // 8. Müsait Masaları Listeleme
    std::vector<std::shared_ptr<Masa>> musaitMasalariGetir();

    // 9. Günlük Ciro Hesaplama
    double gunlukCiroHesapla(const std::string& tarih);

    // 10. En Popüler Yemekler
    std::vector<std::shared_ptr<MenuItem>> enPopulerYemekler(int limit);

    // 11. Garson Performansı
    GarsonPerformans garsonPerformansi(int garson_id);
};

#endif