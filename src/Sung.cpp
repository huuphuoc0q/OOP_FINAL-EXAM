#include "Sung.h"
#include <iostream>
#include <limits>

Sung::Sung() : 
    VuKhi("Sung mac dinh", 30, 1.0), 
    soDan_(5), 
    tocDoThayBang_(2.0) {}

Sung::Sung(const std::string& tenVuKhi, int satThuong, double tocDo, int soDan, double tocDoThayBang): 
    VuKhi(tenVuKhi, satThuong, tocDo),
    soDan_(soDan),
    tocDoThayBang_(tocDoThayBang) {}

int Sung::getSoDan() const {
    return soDan_;
}

double Sung::getTocDoThayBang() const {
    return tocDoThayBang_;
}

void Sung::setSoDan(int newSoDan) {
    if( newSoDan >= 0)
        soDan_ = newSoDan; 
}

void Sung::setTocDoThayBang(double newTocDoThayBang) {
    if( newTocDoThayBang > 0)
        tocDoThayBang_ = newTocDoThayBang; 
}

void Sung::tanCong() {
    std::cout<<" * BANG! Sung "<<tenVuKhi_<<" khai hoa.\n";
}

int Sung::satThuong(int t) const {
    if( t<0 || soDan_ <= 0)
        return 0; 
    int soPhat = static_cast<int>(t*tocDo_); 
    if( soPhat > soDan_) soPhat= soDan_;
    return soPhat*satThuong_;
}

std::string Sung::getLoai() const {
    return "Sung";
}

void Sung::NapDan() {
    soDan_ = 5;
}

bool Sung::ConDan() const {
    return soDan_ > 0;
}

void Sung::SuDungDan() {
    if(soDan_ > 0) --soDan_;
}

void Sung::xuat(std::ostream& os) const {
    VuKhi::xuat(os);os<<"Loai: Sung\nDan trong ong: "<<soDan_<<"\nThoi gian thay bang: "<<tocDoThayBang_<<" giay\n";
}

void Sung::nhap(std::istream& is) {
    VuKhi::nhap(is);
    int newSoDan;
    double newTocDoThayBang;
    std::cout<<"So dan trong ong: "; is>>newSoDan;
    std::cout<<"Thoi gian thay bang: "; is>>newTocDoThayBang;
    if( is && newSoDan>= 0 && newTocDoThayBang>0) {
        soDan_ = newSoDan;
        tocDoThayBang_ = newTocDoThayBang;
    }
}

