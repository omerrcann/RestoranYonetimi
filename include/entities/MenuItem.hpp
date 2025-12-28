#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <string>

class RestoranServisi;
template <typename T> class Depo;

class MenuItem {
private:
    template <typename T> friend class Depo;
    friend class RestoranServisi;

    int _id;
    std::string _ad;
    std::string _aciklama;
    double _fiyat;
    int _kategori_id;
    int _hazirlik_suresi;

public:
    MenuItem();
    MenuItem(int id, const std::string& ad, const std::string& aciklama, double fiyat, int kategori_id, int hazirlik_suresi);
    MenuItem(const MenuItem& other);
    ~MenuItem();
    int get_id() const;
};

#endif