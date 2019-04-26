/*
  ==============================================================================

    SynthSound.h
    Created: 11 Mar 2019 1:35:59pm
    Author:  asmprog

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
    bool appliesToNote (int midiNoteNumber)
    {
        return true;
    };
    
    bool appliesToChannel (int midiChannel)
    {
        return true;
    };
};
