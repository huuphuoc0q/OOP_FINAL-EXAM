#include "Sung.h"
#include <iostream>
#include <limits>

Sung::Sung() : 
    VuKhi("Sung mac dinh",30,1.0), 
    soDan(5), 
    tocdoThayBang(2.0) {}

Sung::Sung(const std::string& t,int s,double td,int d,double tb): 
    VuKhi(t,s,td),
    soDan(d),
    tocdoThayBang(tb) {}

int Sung::getSoDan() const {
    return soDan;
}

double Sung::getTocDoThayBang() const {
    return tocdoThayBang;
}

void Sung::setSoDan(int d) {
    if(d>=0)
        soDan=d;
}

void Sung::setTocDoThayBang(double g) {
    if(g>0)
        tocdoThayBang=g;
}

void Sung::TanCong() {
    std::cout<<" * BANG! Sung "<<tenVuKhi_<<" khai hoa.\n";
}

int Sung::SatThuong(int t) const {
    if(t<0||soDan<=0)
        return 0; 
    int soPhat=static_cast<int>(t*tocDo_); 
    if(soPhat>soDan) soPhat=soDan;
    return soPhat*satThuong_;
}

std::string Sung::getLoai() const {
    return "Sung";
}

void Sung::NapDan() {
    soDan=5;
}

bool Sung::ConDan() const {
    return soDan>0;
}

void Sung::SuDungDan() {
    if(soDan>0)--soDan;
}

void Sung::xuat(std::ostream& os) const {
    VuKhi::xuat(os);os<<"Loai: Sung\nDan trong ong: "<<soDan<<"\nThoi gian thay bang: "<<tocdoThayBang<<" giay\n";
}

void Sung::nhap(std::istream& is) {
    VuKhi::nhap(is);
    int d;
    double tb;
    std::cout<<"So dan trong ong: "; is>>d;
    std::cout<<"Thoi gian thay bang: "; is>>tb;
    if(is&&d>=0&&tb>0) {
        soDan=d;
        tocdoThayBang=tb;
    }
}

