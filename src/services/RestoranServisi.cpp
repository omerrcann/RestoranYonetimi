#include "services/RestoranServisi.hpp"
#include "utils/TarihUtils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

RestoranServisi::RestoranServisi(
        Depo<Masa>& masaDepo, Depo<Garson>& garsonDepo,
        Depo<MenuKategori>& kategoriDepo, Depo<MenuItem>& menuItemDepo,
        Depo<Siparis>& siparisDepo, Depo<SiparisKalemi>& siparisKalemiDepo,
        Depo<Rezervasyon>& rezervasyonDepo
) : _masaDepo(masaDepo), _garsonDepo(garsonDepo),
    _kategoriDepo(kategoriDepo), _menuItemDepo(menuItemDepo),
    _siparisDepo(siparisDepo), _siparisKalemiDepo(siparisKalemiDepo),
    _rezervasyonDepo(rezervasyonDepo)
{
}

// 1. Masa Ekleme
void RestoranServisi::masaEkle(int numara, int kapasite, const std::string& konum) {
    auto yeniMasa = std::make_shared<Masa>(0, numara, kapasite, konum, "Boş");
    _masaDepo.ekle(yeniMasa);
}

// 2. Menü Öğesi Ekleme
void RestoranServisi::menuItemEkle(const std::string& ad, const std::string& aciklama, double fiyat, int kategori_id, int hazirlik_suresi) {
    auto yeniUrun = std::make_shared<MenuItem>(0, ad, aciklama, fiyat, kategori_id, hazirlik_suresi);
    _menuItemDepo.ekle(yeniUrun);
}

// 3. Sipariş Oluşturma
int RestoranServisi::siparisOlustur(int masa_id, int garson_id) {
    auto masa = _masaDepo.getir(masa_id);
    if (masa->_durum != "Boş") {
        throw std::runtime_error("Masa dolu, siparis acilamaz! (Masa ID: " + std::to_string(masa_id) + ")");
    }

    masa->_durum = "Dolu";
    _masaDepo.guncelle(masa);

    std::string tarih = TarihUtils::bugunTarihi();
    auto yeniSiparis = std::make_shared<Siparis>(0, masa_id, garson_id, tarih, "Açık", 0.0);

    _siparisDepo.ekle(yeniSiparis);

    return yeniSiparis->get_id();
}

// 4. Siparişe Ürün Ekleme
void RestoranServisi::sipariseItemEkle(int siparis_id, int menu_item_id, int miktar, const std::string& notlar) {
    auto siparis = _siparisDepo.getir(siparis_id);
    auto urun = _menuItemDepo.getir(menu_item_id);

    if (siparis->_durum != "Açık") {
        throw std::runtime_error("Kapalı siparise ekleme yapilamaz!");
    }

    auto yeniKalem = std::make_shared<SiparisKalemi>(0, siparis_id, menu_item_id, miktar, notlar);
    _siparisKalemiDepo.ekle(yeniKalem);

    siparis->_toplam += (urun->_fiyat * miktar);
    _siparisDepo.guncelle(siparis);
}

// 5. Sipariş Kapatma
void RestoranServisi::siparisKapat(int siparis_id) {
    auto siparis = _siparisDepo.getir(siparis_id);

    if (siparis->_durum == "Kapalı") {
        throw std::runtime_error("Siparis zaten kapali.");
    }

    siparis->_durum = "Kapalı";
    _siparisDepo.guncelle(siparis);

    auto masa = _masaDepo.getir(siparis->_masa_id);
    masa->_durum = "Boş";
    _masaDepo.guncelle(masa);
}

// 6. Hesap Yazdırma (Fiş Görünümü)
std::string RestoranServisi::hesapYazdir(int siparis_id) {
    auto siparis = _siparisDepo.getir(siparis_id);
    std::stringstream ss;

    ss << "=== HESAP FISI ===\n";
    ss << "Siparis No: " << siparis->_id << "\n";
    ss << "Tarih: " << siparis->_tarih_saat << "\n";
    ss << "------------------\n";

    auto kalemler = _siparisKalemiDepo.ara([siparis_id](const std::shared_ptr<SiparisKalemi>& k) {
        return k->_siparis_id == siparis_id;
    });

    for (const auto& kalem : kalemler) {
        auto urun = _menuItemDepo.getir(kalem->_menu_item_id);
        ss << urun->_ad << " x " << kalem->_miktar
           << " (" << (urun->_fiyat * kalem->_miktar) << " TL)\n";
    }

    ss << "------------------\n";
    ss << "TOPLAM: " << siparis->_toplam << " TL\n";
    ss << "==================";

    return ss.str();
}

// 7. Rezervasyon Yapma
void RestoranServisi::rezervasyonYap(int masa_id, const std::string& musteri_adi, const std::string& telefon, const std::string& tarih_saat, int kisi_sayisi) {
    _masaDepo.getir(masa_id);

    auto rez = std::make_shared<Rezervasyon>(0, masa_id, musteri_adi, telefon, tarih_saat, kisi_sayisi);
    _rezervasyonDepo.ekle(rez);
}

// 8. Müsait Masaları Listeleme
std::vector<std::shared_ptr<Masa>> RestoranServisi::musaitMasalariGetir() {
    return _masaDepo.ara([](const std::shared_ptr<Masa>& m) {
        return m->_durum == "Boş";
    });
}

// 9. Günlük Ciro Hesaplama
double RestoranServisi::gunlukCiroHesapla(const std::string& tarih) {
    auto siparisler = _siparisDepo.ara([tarih](const std::shared_ptr<Siparis>& s) {
        return s->_tarih_saat.find(tarih) == 0 && s->_durum == "Kapalı";
    });

    double toplamCiro = 0.0;
    for (const auto& s : siparisler) {
        toplamCiro += s->_toplam;
    }
    return toplamCiro;
}

// 10. En Popüler Yemekler
std::vector<std::shared_ptr<MenuItem>> RestoranServisi::enPopulerYemekler(int limit) {
    std::map<int, int> satisSayilari;

    auto tumKalemler = _siparisKalemiDepo.tumunu();
    for (const auto& k : tumKalemler) {
        satisSayilari[k->_menu_item_id] += k->_miktar;
    }

    std::vector<std::pair<int, int>> siraliListe(satisSayilari.begin(), satisSayilari.end());

    std::sort(siraliListe.begin(), siraliListe.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              }
    );

    std::vector<std::shared_ptr<MenuItem>> sonuc;
    int sayac = 0;
    for (const auto& p : siraliListe) {
        if (sayac >= limit) break;
        try {
            sonuc.push_back(_menuItemDepo.getir(p.first));
            sayac++;
        } catch (...) {
        }
    }
    return sonuc;
}

// 11. Garson Performansı
GarsonPerformans RestoranServisi::garsonPerformansi(int garson_id) {
    GarsonPerformans rapor = {0, 0.0, 0.0};

    auto siparisler = _siparisDepo.ara([garson_id](const std::shared_ptr<Siparis>& s) {
        return s->_garson_id == garson_id && s->_durum == "Kapalı";
    });

    for (const auto& s : siparisler) {
        rapor.toplam_siparis++;
        rapor.toplam_ciro += s->_toplam;
    }

    if (rapor.toplam_siparis > 0) {
        rapor.ortalama_siparis = rapor.toplam_ciro / rapor.toplam_siparis;
    }

    return rapor;
}