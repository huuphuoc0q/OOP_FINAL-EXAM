#ifndef NHANVAT_H
#define NHANVAT_H
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include "VuKhi.h"
class NhanVat {
    private:
        std::string tenNhanVat_;
        int mau_, mauToiDa_;
        std::vector<std::unique_ptr<VuKhi>> danhSachVuKhi_;
        
    public:
        //Constructor
        NhanVat();
        NhanVat(const std::string& tenNhanVat,int mau);
        NhanVat(const NhanVat& other); 
        
        //Getter, setter
        std::string getTen() const;
        int getMau() const;
        int getMauToiDa() const;
        void setTen(const std::string& newTenNhanVat);
        void setMau(int newMau);
        VuKhi* getVuKhi(int index);

        //Ham xu ly
        void themVuKhi(std::unique_ptr<VuKhi> vuKhi);
        int soVuKhi() const;
        void nhanSatThuong(int satThuong);
        void hoiMau();
        void hienThiTrangThai() const;
};
#endif
