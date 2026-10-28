#ifndef SUNG_H
#define SUNG_H
#include "VuKhi.h"
#include <windows.h>

class Sung : public VuKhi {
    private:
        int soDan_;
        double tocDoThayBang_; // giay

    public:
        //Constructor
        Sung();
        Sung(const std::string& tenVuKhi, int satThuong, double tocDo, int soDan, double tocDoThayBang);
        Sung(const Sung& other); 
        
        //Getter, setter
        int getSoDan() const;
        double getTocDoThayBang() const;
        void setSoDan(int newSoDan);
        void setTocDoThayBang(double newTocDoThayBang);

        //Xu ly
        void tanCong() override;
        int satThuong(int t) const override;
        std::string getLoai() const override;
        void NapDan();
        bool ConDan() const;
        void SuDungDan(int t);
        int soDanCanDung(int t) const; 

        //Qua tai nhap xuat
        void xuat(std::ostream& os) const override;
        void nhap(std::istream& is) override;

        
};
#endif
