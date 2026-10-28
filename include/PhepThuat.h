#ifndef PHEPTHUAT_H
#define PHEPTHUAT_H
#include "VuKhi.h"
class PhepThuat : public VuKhi {
    private:
        std::string loaiPhep_;
        int manaTieuThu_;
        int manaHienTai_;
    public:
        //Constructor
        PhepThuat();
        PhepThuat(const std::string& tenVuKhi, int satThuong, double tocDo, const std::string& loaiPhep, int manaHienTai);
        PhepThuat(const PhepThuat& other); 
        //Getter, setter
        std::string getLoaiPhep() const;
        int getManaTieuThu() const;
        int getManaHienTai() const;
        void setLoaiPhep(const std::string& newLoaiPhep);
        void setManaTieuThu(int newManaTieuThu);

        //Ham xu ly
        void tanCong() override;
        int satThuong(int t) const override;
        std::string getLoai() const override;
        bool DuMana(int manaTieuThu) const;
        void SuDungMana(int manaSuDung);
        void HoiMana();
        int soManaCanDung(int t) const;
        
        //Qua tai nhap xuat
        void xuat(std::ostream& os) const override;
        void nhap(std::istream& is) override;
        
};
#endif
