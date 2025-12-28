#ifndef MASA_HPP
#define MASA_HPP

#include <string>

class RestoranServisi;
template <typename T> class Depo;

class Masa {
private:
    template <typename T> friend class Depo;
    friend class RestoranServisi;

    int _id;
    int _numara;
    int _kapasite;
    std::string _konum;
    std::string _durum;

public:
    Masa();
    Masa(int id, int numara, int kapasite, const std::string& konum, const std::string& durum);
    Masa(const Masa& other);
    ~Masa();
    int get_id() const;
};

#endif