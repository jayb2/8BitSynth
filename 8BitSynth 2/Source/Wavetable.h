/*
  ==============================================================================

    Wavetable.h
    Created: 24 Apr 2019 2:53:24pm
    Author:  asmprog

  ==============================================================================
*/

#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>

class Phasor
{
    double m_sampleRate, m_freq, m_phase, m_phaseInc;
    
    
    public :
    
    Phasor(double sampleRate = 44100, double freq = 1) :
    m_sampleRate(sampleRate),
    m_freq(freq),
    m_phase(0)
    {
        m_phaseInc = m_freq / m_sampleRate;
        std::cout<<"Phasor Constructed"<<std::endl;
    }
    
    void setFreq(double freq)
    {
        m_freq = freq;
        m_phaseInc = m_freq / m_sampleRate;
    }
    
    void setSampleRate (double sampleRate)
    {
        m_sampleRate = sampleRate;
        setFreq(m_freq);
    }
    
    double getPhase()
    {
        return m_phase;
    }
    
    void tick()
    {
        m_phase += m_phaseInc;
        
        while (m_phase >= 1)
        {
            m_phase -= 1;
        }
    }
    
};

class Wavetable
{
    std::vector<double> m_table;
    
    public :
    Wavetable(int tableSize = 512) :
    m_table(tableSize)
    {
        
    }
    
    int getTableSize()
    {
        return m_table.size();
    }
    
    void fillSaw()
    {
        double size = m_table.size() - 1;
        float phase = 0;
        
        for (int n = 0; n < size; ++n)
        {
            double ret = fmodf(phase, 1) * 2 - 1;
            m_table[n] = ret;
            phase += 1.f / size;
        }
    }
    
    void fillSine()
    {
        double size = m_table.size() - 1;
        
        for (int n = 0; n < size; ++n)
        {
            m_table[n] = sin((6.2831853071 * n) / size);
        }
        
        
    }
    
    void fillSquare()
    {
        double size = m_table.size() - 1;
        //float phase = 0;
        
        for (int n = 0; n < size; ++n)
        {
//        m_table[n] = 1 - 2 * (fmodf(2,(phase/1)));
//
//            phase++;
            if(n < size *0.5){
                m_table[n] = 1;
            }
             else if(n > size * 0.5){
                m_table[n] = -1;
            }
            
        }
    }
    
    void fillTriangle()
    {
        double size = m_table.size() - 1;
        float phase = 0;
        
        for (int n = 0; n < size; ++n)
        {
            double ret = abs(fmodf(phase, 1) * 2 - 1) -1;
            m_table[n] = ret;
            phase += 1.f / size;
        }
    }
    
    double getSample(int n)
    {
        while (n >= getTableSize()) n -= getTableSize();
        while (n < 0) n += getTableSize();
        
        return m_table[n];
    }
    
};
