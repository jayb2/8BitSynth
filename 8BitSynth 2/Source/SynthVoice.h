/*
  ==============================================================================

    SynthVoice.h
    Created: 11 Mar 2019 1:35:42pm
    Author:  asmprog

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "Wavetable.h"
#include "Filter.h"

class SynthVoice : public SynthesiserVoice
{
public:
    SynthVoice():m_phasor(44100,440),m_wavetable()
    {
        ADSR::Parameters perams;
        perams.attack = 0;
        perams.decay = 1;
        perams.sustain = 0.5;
        perams.release = 1;
        m_wavetable.fillSaw();
        m_envelope.setParameters(perams);
        m_envelope.setSampleRate(44100);
    
    }
    bool canPlaySound (SynthesiserSound* sound) override
    //must be overidden to return whether a voice can actually play sound
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentWheelPosition) override
    {
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        m_phasor.setFreq(frequency);
        std::cout << midiNoteNumber << std::endl;
        m_envelope.noteOn();
    }
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        level = 0;
        m_envelope.noteOff();
    }
    
    void pitchWheelMoved (int newPitchWheelValue) override
    {
        
    }
    
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }
    
    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        float* leftChannel = outputBuffer.getWritePointer(0);
        float* rightChannel = outputBuffer.getWritePointer(1);
        
        
        
        for (int n = 0; n < outputBuffer.getNumSamples(); n++)
        {
            float env = m_envelope.getNextSample();
            float currentSample = level;
            currentSample = m_wavetable.getSample(m_phasor.getPhase() * m_wavetable.getTableSize());
            m_phasor.tick();
            
            leftChannel[n] += currentSample * env;
            rightChannel[n]+= currentSample * env;
            
        }
        
    
        
    }

private:
    double frequency;
    double velocity;
    double level;
    
    Phasor m_phasor;
    Wavetable m_wavetable;
    
    ADSR m_envelope;
};
