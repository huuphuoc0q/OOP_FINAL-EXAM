#include "PhepThuat.h"
#include <iostream>

PhepThuat::PhepThuat(): 
    VuKhi("Phep mac dinh",25,1.0),
    loaiPhep("Loi"),
    manaTieuThu(5),
    manaHienTai(30) {}
PhepThuat::PhepThuat(
    const std::string& t,
    int s,
    double td,
    const std::string& l,
    int m
):
    VuKhi(t, s, td),
    loaiPhep(l),
    manaTieuThu(8),
    manaHienTai(m){}

std::string PhepThuat::getLoaiPhep() const {
    return loaiPhep;
}

int PhepThuat::getManaTieuThu() const {
    return manaTieuThu;
}

int PhepThuat::getManaHienTai() const {
    return manaHienTai;
}

void PhepThuat::setLoaiPhep(const std::string&l) {
    if(!l.empty())
        loaiPhep=l;
}

void PhepThuat::setManaTieuThu(int m) {
    if(m>=0)
        manaTieuThu=m;
}

void PhepThuat::TanCong() {
    std::cout<<" * VUUT! Phep "<<loaiPhep<<" bung no.\n";
}

int PhepThuat::SatThuong(int t) const { 
    if(t<0 || manaHienTai < manaTieuThu*t )
        return 0;
    return static_cast<int>(t*tocDo_)*satThuong_;
}

std::string PhepThuat::getLoai() const {
    return "Phep thuat";
}

bool PhepThuat::DuMana(int manaTieuThu) const {
    return manaHienTai >= manaTieuThu;
}

void PhepThuat::SuDungMana(int t) {
    if(t>0 && manaHienTai>=t){
        manaHienTai-=t;
    }
}

void PhepThuat::HoiMana() {
    manaHienTai=30;
}

void PhepThuat::xuat(std::ostream&os) const {
    VuKhi::xuat(os);
    os<<"Loai phep: "<<loaiPhep<<"\nMana tieu thu/giay: "<<manaTieuThu<<"\nMana hien tai: "<<manaHienTai<<"/30\n";
}

void PhepThuat::nhap(std::istream&is) {
    VuKhi::nhap(is);
    std::string l;
    int m;
    std::cout<<"Loai phep: "; is>>l;
    std::cout<<"Mana tieu thu moi giay: "; is>>m;
    if(is&&!l.empty()&&m>=0) {
        loaiPhep=l;
        manaTieuThu=m;
    }
}


