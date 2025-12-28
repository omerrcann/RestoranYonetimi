#include "entities/Siparis.hpp"

Siparis::Siparis()
        : _id(0), _masa_id(0), _garson_id(0), _tarih_saat(""), _durum(""), _toplam(0.0) {
}

Siparis::Siparis(int id, int masa_id, int garson_id, const std::string& tarih_saat, const std::string& durum, double toplam)
        : _id(id), _masa_id(masa_id), _garson_id(garson_id), _tarih_saat(tarih_saat),
          _durum(durum), _toplam(toplam) {
}

Siparis::Siparis(const Siparis& other)
        : _id(other._id), _masa_id(other._masa_id), _garson_id(other._garson_id),
          _tarih_saat(other._tarih_saat), _durum(other._durum), _toplam(other._toplam) {
}

Siparis::~Siparis() {
}

int Siparis::get_id() const {
    return _id;
}