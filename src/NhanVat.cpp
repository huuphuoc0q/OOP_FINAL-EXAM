#include "NhanVat.h"
#include <iostream>

NhanVat::NhanVat():
    tenNhanVat_("Hac Si"),
    mau_(160),
    mauToiDa_(160) {}

NhanVat::NhanVat(const std::string& tenNhanVat,int mau):
    tenNhanVat_(tenNhanVat),
    mau_(std::max(0, mau)),
    mauToiDa_(std::max(1, mau)) {}

NhanVat::NhanVat(const NhanVat& other){
    tenNhanVat_ = other.tenNhanVat_;
    mau_ = other.mau_;
    mauToiDa_ = other.mauToiDa_; 
}

std::string NhanVat::getTen() const {
    return tenNhanVat_;
}

int NhanVat::getMau() const { 
    return mau_;
}

int NhanVat::getMauToiDa() const {
    return mauToiDa_;
}

void NhanVat::setTen(const std::string& newTenNhanVat) {
    if(!newTenNhanVat.empty())
        tenNhanVat_ = newTenNhanVat;
}

void NhanVat::setMau(int newMau) {
    mau_ = std::clamp(newMau ,0 ,mauToiDa_);
}

void NhanVat::themVuKhi(std::unique_ptr<VuKhi>  vuKhi) {
    if (vuKhi) danhSachVuKhi_.push_back(std::move(vuKhi));
}

VuKhi* NhanVat::getVuKhi(int index) {
    return (index >= 0 && index < (danhSachVuKhi_.size())) // ép kiểu size về int vì size trả về số nguyên không dấu (tránh trường so sánh 2 số nguyên có dấu và không dấu)
           ? danhSachVuKhi_[index].get() 
           : nullptr;
}

int NhanVat::soVuKhi() const { 
    return (int)danhSachVuKhi_.size();
}

void NhanVat::nhanSatThuong(int satThuong) {
    mau_ = std::max(0,mau_-std::max(0,satThuong));
}

void NhanVat::hoiMau() {
    mau_ = mauToiDa_;
}

void NhanVat::hienThiTrangThai() const {
    std::cout<<"Nhan vat: "<<tenNhanVat_<<" | HP: "<<mau_<<"/"<<mauToiDa_<<"\n";
    for(size_t i=0;i<danhSachVuKhi_.size();++i)
        std::cout<<i+1<<". "<<danhSachVuKhi_[i]->getTen()<<" ["<<danhSachVuKhi_[i]->getLoai()<<"] - sat thuong "<<danhSachVuKhi_[i]->getSatThuongCoBan()<<"\n";
}
