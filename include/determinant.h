//
// Created by bcyz on 24-10-17.
//

#ifndef DETERMINANT_H
#define DETERMINANT_H


#include <vector>
#include <cstdint>

#include "gmpxx.h"

class Determinant
{

private:
#ifdef __USE_GMP__
    using Element=mpq_class;
#else
    using Element=int64_t;
#endif

    uint64_t n=0;
    std::vector<std::vector<Element>> det;
#ifndef __USE_GMP__
    [[nodiscard]] Element m_get_sum()const;
#endif


public:
    Determinant() = default;
    explicit Determinant(uint64_t n_m);
    void set_n(uint64_t n_m);

    [[nodiscard]] uint64_t get_n() const{return n;};
    [[nodiscard]] Determinant get_sub(uint64_t i_m, uint64_t j_m) const;
    [[nodiscard]] Element get_sum()const;

    bool set_value(uint64_t i, uint64_t j, const Element& num);
    explicit operator Element() const{return get_sum();};
    const std::vector<Element>& operator [](const uint64_t x)const {return det[x];}

#ifndef  __USE_GMP__
    bool operator <(const Determinant& det)const;
#endif

    friend std::ostream & operator<<(std::ostream & os, const Determinant & det);
    friend std::istream & operator>>(std::istream & is, Determinant & det);

    ~Determinant()=default;
};



#endif //DETERMINANT_H
