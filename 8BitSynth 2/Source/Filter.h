/*
  ==============================================================================

    Filter.h
    Created: 26 Apr 2019 12:30:15pm
    Author:  asmprog

  ==============================================================================
*/

#pragma once
#include <math.h>
#include <vector>


enum {
    filterLowpass = 0,
    filterHighpass,
    filterBandpass
};

class Biquad
{
public:
    Biquad();
    Biquad(int type, double freq, double res, double peakGain);
    ~Biquad();
    
    void setType(int type);
    void setFreq(double freq);
    void setRes(double res);
    void setPeakGain(double peakGain);
    void setBiquad(int type, double freq, double res, double peakGain);
    float process(float in);

    
protected:
    void calculate(void);
    
    int type;
    double x0, x1, x2, y1, y2;
    double freq, res, peakGain;
    double z1, z2;
    
};

inline float Biquad::process(float in){
    double out = in * x0 + z1;
    z1 = in * x1 + z2 - y1 * out;
    z2 = in * x2 - y2 * out;
    return out;
}

Biquad::Biquad() {
    type = filterLowpass;
    x0 = 1.0;
    x1 = x2 = y1 = y2 = 0.0;
    freq = 0.50;
    res = 0.707;
    peakGain = 0.0;
    z1 = z2 = 0.0;
}

//https://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
