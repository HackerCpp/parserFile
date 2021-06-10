#ifndef COEFFS_H
#define COEFFS_H

#pragma pack(push, 1)

struct CoeffsLinearDependence{
    float k_a;
    float k_b;
};

class Coeffs
{
public:
    Coeffs();
};
#pragma pack(pop)
#endif // COEFFS_H
