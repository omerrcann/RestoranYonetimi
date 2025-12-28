#include "entities/Rezervasyon.hpp"

Rezervasyon::Rezervasyon()
        : _id(0), _masa_id(0), _musteri_adi(""), _telefon(""), _tarih_saat(""), _kisi_sayisi(0) {}

Rezervasyon::Rezervasyon(int id, int masa_id, const std::string& musteri_adi, const std::string& telefon,
                         const std::string& tarih_saat, int kisi_sayisi)
        : _id(id), _masa_id(masa_id), _musteri_adi(musteri_adi), _telefon(telefon),
          _tarih_saat(tarih_saat), _kisi_sayisi(kisi_sayisi) {}

Rezervasyon::Rezervasyon(const Rezervasyon& other)
        : _id(other._id), _masa_id(other._masa_id), _musteri_adi(other._musteri_adi),
          _telefon(other._telefon), _tarih_saat(other._tarih_saat), _kisi_sayisi(other._kisi_sayisi) {}

Rezervasyon::~Rezervasyon() {}

int Rezervasyon::get_id() const { return _id; }