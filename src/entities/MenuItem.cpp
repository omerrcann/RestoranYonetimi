#include "entities/MenuItem.hpp"

MenuItem::MenuItem() : _id(0), _ad(""), _aciklama(""), _fiyat(0.0), _kategori_id(0), _hazirlik_suresi(0) {}

MenuItem::MenuItem(int id, const std::string& ad, const std::string& aciklama,
                   double fiyat, int kategori_id, int hazirlik_suresi)
        : _id(id), _ad(ad), _aciklama(aciklama), _fiyat(fiyat),
          _kategori_id(kategori_id), _hazirlik_suresi(hazirlik_suresi) {}

MenuItem::MenuItem(const MenuItem& other)
        : _id(other._id), _ad(other._ad), _aciklama(other._aciklama), _fiyat(other._fiyat),
          _kategori_id(other._kategori_id), _hazirlik_suresi(other._hazirlik_suresi) {}

MenuItem::~MenuItem() {}

int MenuItem::get_id() const { return _id; }