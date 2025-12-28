#ifndef TARIH_UTILS_H
#define TARIH_UTILS_H

#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

namespace TarihUtils {


    inline bool tarihiAyristir(const std::string& tarih, int& yil, int& ay, int& gun) {
        std::istringstream ss(tarih);
        char ayrac;
        ss >> yil >> ayrac >> ay >> ayrac >> gun;
        return !ss.fail();
    }


    inline time_t stringToTime(const std::string& tarih) {
        int yil, ay, gun;
        if (!tarihiAyristir(tarih, yil, ay, gun)) {
            return -1;
        }
        std::tm tm = {};
        tm.tm_year = yil - 1900;
        tm.tm_mon = ay - 1;
        tm.tm_mday = gun;
        return std::mktime(&tm);
    }


    inline int gunFarki(const std::string& tarih1, const std::string& tarih2) {
        time_t t1 = stringToTime(tarih1);
        time_t t2 = stringToTime(tarih2);
        if (t1 == -1 || t2 == -1) return 0;

        double saniyeFarki = std::difftime(t2, t1);
        const int SANIYE_PER_GUN = 60 * 60 * 24;
        return static_cast<int>(saniyeFarki / SANIYE_PER_GUN);
    }


    inline std::string timeToString(time_t zaman) {
        std::tm* tmPtr = std::localtime(&zaman);
        std::ostringstream ss;
        ss << (tmPtr->tm_year + 1900) << "-";
        if (tmPtr->tm_mon + 1 < 10) ss << "0";
        ss << (tmPtr->tm_mon + 1) << "-";
        if (tmPtr->tm_mday < 10) ss << "0";
        ss << tmPtr->tm_mday;
        return ss.str();
    }


    inline std::string bugunTarihi() {
        time_t simdi = std::time(nullptr);
        return timeToString(simdi);
    }


    inline std::string gunEkle(const std::string& tarih, int gunSayisi) {
        time_t baslangic = stringToTime(tarih);
        if (baslangic == -1) return "";

        const int SANIYE_PER_GUN = 60 * 60 * 24;
        time_t sonuc = baslangic + (gunSayisi * SANIYE_PER_GUN);
        return timeToString(sonuc);
    }

}

#endif