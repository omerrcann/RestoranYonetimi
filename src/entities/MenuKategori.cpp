#include "entities/MenuKategori.hpp"

MenuKategori::MenuKategori() : _id(0), _ad(""), _aciklama("") {}

MenuKategori::MenuKategori(int id, const std::string& ad, const std::string& aciklama)
        : _id(id), _ad(ad), _aciklama(aciklama) {}

MenuKategori::MenuKategori(const MenuKategori& other)
        : _id(other._id), _ad(other._ad), _aciklama(other._aciklama) {}

MenuKategori::~MenuKategori() {}

int MenuKategori::get_id() const { return _id; }