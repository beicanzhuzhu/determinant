//
// Created by bcyz on 24-10-17.
//

#include "determinant.h"

#include <iostream>

#ifndef __USE_GMP__
#include <map>
static std::map<Determinant, long long> history;
#endif


Determinant::Determinant(const uint64_t n_m)
{
    //更新行列式大小
    n=n_m;
    det.resize(n,std::vector<Element>(0));
    for (auto &i:det)
        i.resize(n,0);
}

void Determinant::set_n(const uint64_t n_m)
{
    //更新行列式大小
    n=n_m;
    det.resize(n,std::vector<Element>(0));
    for (auto &i:det)
        i.resize(n,0);
}

bool Determinant::set_value(const uint64_t i, const uint64_t j, const Element& num)
{
    if (i>n-1 || j>n-1)
        return false;
    det[i][j] = num;
    return true;
}

Determinant Determinant::get_sub(const uint64_t i_m, const uint64_t j_m) const
{
    if (n==0)
    {
        return Determinant(0);
    }
    Determinant new_det{n-1};
    for (uint64_t i=0; i< n; ++i)
    {
        if (i == i_m)
            continue;
        for (uint64_t j=0; j<n; ++j)
        {
            if (j == j_m) continue;
            new_det.set_value(i>i_m ? i-1 : i,j>j_m ? j-1 :j, det[i][j]);
        }
    }
    return new_det;
}

#ifdef __USE_GMP__

Determinant::Element Determinant::get_sum() const
{
    Element ans=1;
    auto det_m =  det;
    for (uint64_t i=0; i<n; ++i)
    {
        uint64_t k=i;
        for (uint64_t j=i+1; j<n; ++j)
            if(abs(det_m[j][i]) > abs(det_m[k][i])) k=j;
        if(det_m[k][i] == 0)
            return 0;
        if(i!=k)
        {
            swap(det_m[k], det_m[i]);
            ans = 0-ans;
        }
        ans *= det_m[i][i];
        for (uint64_t j = i + 1; j < n; ++j) det_m[i][j] /= det_m[i][i];
        for (uint64_t j = 0; j < n; ++j)
            if (j != i && det_m[j][i] != 0 )
                for (uint64_t m = i + 1; m < n; ++m) det_m[j][m] -= det_m[i][m] * det_m[j][i];
    }
    return ans;
}

#else

long long Determinant::m_get_sum() const
{
    if (n==1)
    {
        return det[0][0];
    } else if(n==0)
    {
        return 0;
    }

    long long sum = 0;
    for(uint64_t j=0; j<n; ++j)
    {
        if (det[0][j] == 0) continue;
        const int f = j&1 ? -1 : 1;
        Determinant  d  = get_sub(0,j);
        if (history.contains(d))
        {
            sum += f * det[0][j] * history[d];
        }else
        {
            Element sub_sum = d.m_get_sum();
            history[d] = sub_sum;
            sum += f * det[0][j] * sub_sum;
        }
    }

    return sum;
}

Determinant::Element Determinant::get_sum()const
{
    history.clear();
    return m_get_sum();
}

#endif



std::ostream & operator<<(std::ostream & os, const Determinant & det)
{
    for(int i=0;i<det.get_n(); ++i)
    {
        os<<"| ";
        for(uint64_t j=0;j<det.get_n();++j)
        {
            os<<det[i][j]<<" ";
        }
        os<<"|"<<std::endl;
    }
    return os;
}

std::istream & operator>>(std::istream & is, Determinant & det)
{
    std::cout<<"input n: ";
    int n;
    is>>n;
    det.set_n(n);
    for (int i=0; i<n; i++)
    {
        std::cout<<"input line "<<i+1<<" : ";
        for (int j=0; j<n; j++)
        {
            Determinant::Element temp;std::cin>>temp;
            det.set_value(i,j,temp);
        }
    }
    return is;
}
#ifndef __USE_GMP__

bool Determinant::operator<(const Determinant& det_m) const
{
    if(n != det_m.n)
    {
        return n<det_m.n;
    }

    for(uint64_t i=0; i<n; ++i)
        for(uint64_t j=0; j<n; ++j)
            if(det[i][j] != det_m.det[i][j])
                return det[i][j]<det_m.det[i][j];
    return false;
}

#endif