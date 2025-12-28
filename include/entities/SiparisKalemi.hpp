#ifndef SIPARIS_KALEMI_HPP
#define SIPARIS_KALEMI_HPP

#include <string>

class RestoranServisi;
template <typename T> class Depo;

class SiparisKalemi {
private:
    template <typename T> friend class Depo;
    friend class RestoranServisi;

    int _id;
    int _siparis_id;
    int _menu_item_id;
    int _miktar;
    std::string _notlar;

public:
    SiparisKalemi();
    SiparisKalemi(int id, int siparis_id, int menu_item_id, int miktar, const std::string& notlar = "");
    SiparisKalemi(const SiparisKalemi& other);
    ~SiparisKalemi();
    int get_id() const;
};

#endif