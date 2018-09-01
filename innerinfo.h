#ifndef INNERINFO_H
#define INNERINFO_H
struct innerInfo{
    QString _name;
    int _quantity;

    friend QDebug operator<< (QDebug d, const innerInfo &model);
    inline innerInfo& operator++(){++_quantity;return *this;}
    inline innerInfo& operator--(){--_quantity;return *this;}
    inline bool operator>(int& other){return _quantity > other;}

};



inline QDebug operator<< (QDebug d, const innerInfo &model) {
    d <<  model._quantity;
 return d;
          }
#endif // INNERINFO_H
