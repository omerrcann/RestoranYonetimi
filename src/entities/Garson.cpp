#include "entities/Garson.hpp"

Garson::Garson() : _id(0), _sicil_no(""), _ad_soyad(""), _telefon(""), _vardiya("") {}

Garson::Garson(int id, const std::string& sicil_no, const std::string& ad_soyad,
               const std::string& telefon, const std::string& vardiya)
        : _id(id), _sicil_no(sicil_no), _ad_soyad(ad_soyad), _telefon(telefon), _vardiya(vardiya) {}

Garson::Garson(const Garson& other)
        : _id(other._id), _sicil_no(other._sicil_no), _ad_soyad(other._ad_soyad),
          _telefon(other._telefon), _vardiya(other._vardiya) {}

Garson::~Garson() {}

int Garson::get_id() const { return _id; }