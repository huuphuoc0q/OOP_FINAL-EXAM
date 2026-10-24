#ifndef KIEM_H
#define KIEM_H
#include "VuKhi.h"
class Kiem : public VuKhi {
    private:
        int doBen_;
    public:
        //Constructor
        Kiem();
        Kiem(const std::string& tenVuKhi, int satThuong, double tocDo, int doBen);

        //Getter, setter
        int getDoBen() const;
        void setDoBen(int doBen);

        //Ham xu ly
        void tanCong() override;
        int satThuong(int t) const override;
        std::string getLoai() const override;

        //Qua tai nhap xuat
        void xuat(std::ostream& os) const override;
        void nhap(std::istream& is) override;
};
#endif
