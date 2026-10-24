#ifndef VUKHI_H
#define VUKHI_H
#include <iostream>
#include <string>

class VuKhi {
    protected:
        std::string tenVuKhi_;
        int satThuong_;
        double tocDo_; // don/giay
    public:
        VuKhi();
        VuKhi(const std::string& tenVuKhi, int satThuong, double tocDo);
        virtual ~VuKhi() = default;

        std::string getTen() const;
        int getSatThuongCoBan() const;
        double getTocDoRaDon() const;
        void setTen(const std::string& newTenVuKhi);
        void setSatThuongCoBan(int satThuong);
        void setTocDoRaDon(double tocDo);

        virtual void tanCong() = 0;
        virtual int satThuong(int t) const = 0;
        virtual std::string getLoai() const = 0;

        virtual void xuat(std::ostream& os) const;
        virtual void nhap(std::istream& is);
        friend std::ostream& operator<<(std::ostream& os, const VuKhi& vuKhi);
        friend std::istream& operator>>(std::istream& is, VuKhi& vuKhi);
};
#endif
