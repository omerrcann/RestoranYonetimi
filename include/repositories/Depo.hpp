#ifndef DEPO_HPP
#define DEPO_HPP

#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Depo {
public:
    using Ptr = std::shared_ptr<T>;
    using Elemanlar = std::vector<Ptr>;
    using AramaFonksiyonu = std::function<bool(const Ptr&)>;

private:
    Elemanlar _elemanlar;
    int _sonrakiId = 1;

public:
    void ekle(const Ptr& eleman) {
        if (!eleman) {
            throw std::invalid_argument("Null eleman eklenemez.");
        }

        if (eleman->get_id() == 0) {
            const_cast<T*>(eleman.get())->_id = _sonrakiId++;
        }

        _elemanlar.push_back(eleman);
    }

    Ptr getir(int id) const {
        auto it = std::find_if(_elemanlar.begin(), _elemanlar.end(),
                               [id](const Ptr& e) { return e->get_id() == id; });

        if (it != _elemanlar.end()) {
            return std::make_shared<T>(**it);
        }
        throw std::runtime_error("Eleman bulunamadi: ID " + std::to_string(id));
    }

    Elemanlar ara(AramaFonksiyonu kriter) const {
        Elemanlar sonuc;
        for (const auto& eleman : _elemanlar) {
            if (kriter(eleman)) {
                sonuc.push_back(std::make_shared<T>(*eleman));
            }
        }
        return sonuc;
    }

    void guncelle(const Ptr& yeniEleman) {
        if (!yeniEleman) throw std::invalid_argument("Guncellenecek eleman null olamaz.");

        auto it = std::find_if(_elemanlar.begin(), _elemanlar.end(),
                               [&](const Ptr& e) { return e->get_id() == yeniEleman->get_id(); });

        if (it != _elemanlar.end()) {
            *it = std::make_shared<T>(*yeniEleman);
        } else {
            throw std::runtime_error("Guncellenecek eleman bulunamadi: ID " + std::to_string(yeniEleman->get_id()));
        }
    }

    void sil(int id) {
        auto it = std::remove_if(_elemanlar.begin(), _elemanlar.end(),
                                 [id](const Ptr& e) { return e->get_id() == id; });

        if (it != _elemanlar.end()) {
            _elemanlar.erase(it, _elemanlar.end());
        } else {
            throw std::runtime_error("Silinecek eleman bulunamadi: ID " + std::to_string(id));
        }
    }

    Elemanlar tumunu() const {
        Elemanlar kopyaListe;
        kopyaListe.reserve(_elemanlar.size());
        for (const auto& eleman : _elemanlar) {
            kopyaListe.push_back(std::make_shared<T>(*eleman));
        }
        return kopyaListe;
    }

    size_t boyut() const { return _elemanlar.size(); }
    auto begin() { return _elemanlar.begin(); }
    auto begin() const { return _elemanlar.begin(); }
    auto end() { return _elemanlar.end(); }
    auto end() const { return _elemanlar.end(); }
};

#endif