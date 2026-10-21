#ifndef SUNG_H
#define SUNG_H
#include "VuKhi.h"
class Sung : public VuKhi {
    private:
        int soDan;
        double tocdoThayBang; // giay
    public:
        //Constructor
        Sung();
        Sung(const std::string& ten, int satThuong, double tocDo, int dan, double thayBang);

        //Getter, setter
        int getSoDan() const;
        double getTocDoThayBang() const;
        void setSoDan(int dan);
        void setTocDoThayBang(double giay);

        //Xu ly
        void TanCong() override;
        int SatThuong(int t) const override;
        std::string getLoai() const override;
        void NapDan();
        bool ConDan() const;
        void SuDungDan();
        
        //Qua tai nhap xuat
        void xuat(std::ostream& os) const override;
        void nhap(std::istream& is) override;

        
};
#endif
