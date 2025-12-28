#include "entities/Masa.hpp"

Masa::Masa() : _id(0), _numara(0), _kapasite(0), _konum(""), _durum("Boş") {}

Masa::Masa(int id, int numara, int kapasite, const std::string& konum, const std::string& durum)
        : _id(id), _numara(numara), _kapasite(kapasite), _konum(konum), _durum(durum) {}

Masa::Masa(const Masa& other)
        : _id(other._id), _numara(other._numara), _kapasite(other._kapasite),
          _konum(other._konum), _durum(other._durum) {}

Masa::~Masa() {}

int Masa::get_id() const { return _id; }