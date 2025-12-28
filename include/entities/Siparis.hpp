#ifndef SIPARIS_HPP
#define SIPARIS_HPP

#include <string>

class RestoranServisi;
template <typename T> class Depo;

class Siparis {
private:
    template <typename T> friend class Depo;
    friend class RestoranServisi;

    int _id;
    int _masa_id;
    int _garson_id;
    std::string _tarih_saat;
    std::string _durum;
    double _toplam;

public:
    Siparis();
    Siparis(int id, int masa_id, int garson_id, const std::string& tarih_saat, const std::string& durum, double toplam = 0.0);
    Siparis(const Siparis& other);
    ~Siparis();
    int get_id() const;
};

#endif