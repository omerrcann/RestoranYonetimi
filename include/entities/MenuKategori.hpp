#ifndef MENU_KATEGORI_HPP
#define MENU_KATEGORI_HPP

#include <string>

class RestoranServisi;
template <typename T> class Depo;

class MenuKategori {
private:
    template <typename T> friend class Depo;
    friend class RestoranServisi;

    int _id;
    std::string _ad;
    std::string _aciklama;

public:
    MenuKategori();
    MenuKategori(int id, const std::string& ad, const std::string& aciklama);
    MenuKategori(const MenuKategori& other);
    ~MenuKategori();
    int get_id() const;
};

#endif