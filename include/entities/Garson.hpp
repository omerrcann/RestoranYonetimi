#ifndef GARSON_HPP
#define GARSON_HPP

#include <string>

class RestoranServisi;
template <typename T> class Depo;

class Garson {
private:
    template <typename T> friend class Depo;
    friend class RestoranServisi;

    int _id;
    std::string _sicil_no;
    std::string _ad_soyad;
    std::string _telefon;
    std::string _vardiya;

public:
    Garson();
    Garson(int id, const std::string& sicil_no, const std::string& ad_soyad, const std::string& telefon, const std::string& vardiya);
    Garson(const Garson& other);
    ~Garson();
    int get_id() const;
};

#endif