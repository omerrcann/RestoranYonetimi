#ifndef REZERVASYON_HPP
#define REZERVASYON_HPP

#include <string>

class RestoranServisi;
template <typename T> class Depo;

class Rezervasyon {
private:
    template <typename T> friend class Depo;
    friend class RestoranServisi;

    int _id;
    int _masa_id;
    std::string _musteri_adi;
    std::string _telefon;
    std::string _tarih_saat;
    int _kisi_sayisi;

public:
    Rezervasyon();
    Rezervasyon(int id, int masa_id, const std::string& musteri_adi, const std::string& telefon, const std::string& tarih_saat, int kisi_sayisi);
    Rezervasyon(const Rezervasyon& other);
    ~Rezervasyon();
    int get_id() const;
};

#endif