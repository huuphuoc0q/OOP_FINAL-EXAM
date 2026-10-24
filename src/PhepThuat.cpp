#include "PhepThuat.h"
#include <iostream>

PhepThuat::PhepThuat(): 
    VuKhi("Phep mac dinh",25,1.0),
    loaiPhep_("Loi"),
    manaTieuThu_(5),
    manaHienTai_(30) {}

PhepThuat::PhepThuat(
    const std::string& tenVuKhi,
    int satThuong,
    double tocDo,
    const std::string& loaiPhep,
    int manaHienTai
):
    VuKhi(tenVuKhi, satThuong, tocDo),
    loaiPhep_(loaiPhep),
    manaTieuThu_(8),
    manaHienTai_(manaHienTai) {}

std::string PhepThuat::getLoaiPhep() const {
    return loaiPhep_;
}

int PhepThuat::getManaTieuThu() const {
    return manaTieuThu_;
}

int PhepThuat::getManaHienTai() const {
    return manaHienTai_;
}

void PhepThuat::setLoaiPhep(const std::string& newLoaiPhep) {
    if(!newLoaiPhep.empty())
        loaiPhep_ = newLoaiPhep;
}

void PhepThuat::setManaTieuThu(int newManaTieuThu) {
    if( newManaTieuThu >= 0)
        manaTieuThu_ = newManaTieuThu;
}

void PhepThuat::tanCong() {
    std::cout<<" * VUUT! Phep "<<loaiPhep_<<" bung no.\n";
}

int PhepThuat::satThuong(int t) const { 
    if(t<0 || manaHienTai_ < manaTieuThu_*t )
        return 0;
    return static_cast<int>(t*tocDo_)*satThuong_;
}

std::string PhepThuat::getLoai() const {
    return "Phep thuat";
}

bool PhepThuat::DuMana(int manaTieuThu) const {
    return manaHienTai_ >= manaTieuThu;
}

void PhepThuat::SuDungMana(int manaSuDung) {
    if( manaSuDung>0 && manaHienTai_ >= manaSuDung){
        manaHienTai_ -= manaSuDung;
    }
}

void PhepThuat::HoiMana() {
    manaHienTai_ = 30;
}

void PhepThuat::xuat(std::ostream&os) const {
    VuKhi::xuat(os);
    os<<"Loai phep: "<<loaiPhep_<<"\nMana tieu thu/giay: "<<manaTieuThu_<<"\nMana hien tai: "<<manaHienTai_<<"/30\n";
}

void PhepThuat::nhap(std::istream&is) {
    VuKhi::nhap(is);
    std::string newLoaiPhep;
    int newManaTieuThu;
    std::cout<<"Loai phep: "; is>>newLoaiPhep;
    std::cout<<"Mana tieu thu moi giay: "; is>>newManaTieuThu;
    if( is && !newLoaiPhep.empty() && newManaTieuThu >= 0) {
        loaiPhep_ = newLoaiPhep;
        manaTieuThu_ = newManaTieuThu; 
    }
}


