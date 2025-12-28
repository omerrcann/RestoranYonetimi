#include "entities/SiparisKalemi.hpp"

SiparisKalemi::SiparisKalemi() : _id(0), _siparis_id(0), _menu_item_id(0), _miktar(0), _notlar("") {}

SiparisKalemi::SiparisKalemi(int id, int siparis_id, int menu_item_id, int miktar, const std::string& notlar)
        : _id(id), _siparis_id(siparis_id), _menu_item_id(menu_item_id), _miktar(miktar), _notlar(notlar) {}

SiparisKalemi::SiparisKalemi(const SiparisKalemi& other)
        : _id(other._id), _siparis_id(other._siparis_id), _menu_item_id(other._menu_item_id),
          _miktar(other._miktar), _notlar(other._notlar) {}

SiparisKalemi::~SiparisKalemi() {}

int SiparisKalemi::get_id() const { return _id; }