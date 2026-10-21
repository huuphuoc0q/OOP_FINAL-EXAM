#ifndef PHEPTHUAT_H
#define PHEPTHUAT_H
#include "VuKhi.h"
class PhepThuat : public VuKhi {
    private:
        std::string loaiPhep;
        int manaTieuThu;
        int manaHienTai;
    public:
        //Constructor
        PhepThuat();
        PhepThuat(const std::string& ten,int satThuong,double tocDo,const std::string& loai,int mana);

        //Getter, setter
        std::string getLoaiPhep() const;
        int getManaTieuThu() const;
        int getManaHienTai() const;
        void setLoaiPhep(const std::string& loai);
        void setManaTieuThu(int mana);

        //Ham xu ly
        void TanCong() override;
        int SatThuong(int t) const override;
        std::string getLoai() const override;
        bool DuMana(int manaTieuThu) const;
        void SuDungMana(int t);
        void HoiMana();

        //Qua tai nhap xuat
        void xuat(std::ostream& os) const override;
        void nhap(std::istream& is) override;
        
};
#endif
