#include "Kiem.h"
#include <iostream>

Kiem::Kiem():
    VuKhi("Kiem mac dinh", 18, 1.0),
    doBen_(100) {}

Kiem::Kiem(const std::string& tenVuKhi, int satThuong, double tocDo, int doBen, int doBenTieuThu):
    VuKhi(tenVuKhi, satThuong, tocDo),
    doBen_(doBen),
    doBenTieuThu_(doBenTieuThu) {}

Kiem::Kiem(const Kiem& other) {
    tenVuKhi_ = other.tenVuKhi_; 
    satThuong_ = other.satThuong_; 
    tocDo_ = other.tocDo_;
    doBen_ = other.doBen_; 
    doBenTieuThu_ = other.doBenTieuThu_; 
}

int Kiem::getDoBen() const {
    return doBen_;
}

int Kiem::getDoBenTieuThu() const {
    return doBenTieuThu_; 
}

int Kiem::doBenCanDung(int t) const {
    return (t*tocDo_*doBenTieuThu_);
}

void Kiem::setDoBen(int newDoBen) {
    if( newDoBen >= 0) 
        doBen_ = newDoBen;
}

void Kiem::tanCong() {
    std::cout<<" * XEO! Kiem "<<tenVuKhi_<<" chem mot nhat.\n";
}

int Kiem::satThuong(int t) const {
    if( t<0 || doBen_ <= 0)
        return 0;
    int soNhat = static_cast<int>(t*tocDo_);
    return soNhat*satThuong_;
}

std::string Kiem::getLoai() const {
    return "Kiem";
}

void Kiem::xuat(std::ostream&os) const {
    VuKhi::xuat(os);
    os<<"Loai: Kiem\nDo ben: "<<doBen_<<"/100\n";
}

void Kiem::nhap(std::istream&is) {
    VuKhi::nhap(is);
    int newDoBen;
    std::cout<<"Do ben: "; is>>newDoBen; 
    if(is && newDoBen>=0) 
        doBen_ = newDoBen;
}
