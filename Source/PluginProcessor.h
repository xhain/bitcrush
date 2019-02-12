/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//#define INGAIN_ID "inGain"
//#define INGAIN_NAME "inGain"

//==============================================================================
/**
*/
class BitcrushAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BitcrushAudioProcessor();
    ~BitcrushAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================

private:
    // State Tree
    AudioProcessorValueTreeState parameters;
    
    // My Paramter Variables
    float* inGain = nullptr;      // scalar Input Gain var
    float* outGain = nullptr;     // scalar Output Gain var
    float* clipSlope = nullptr;   // Slope of Softclipper
    float* nBits = nullptr;       // number of Bits (2^nBits) for Quantization
    
    // My Data Members
    float curSample;            // save current sample
    
    // My functions
    void bitCrush (AudioBuffer<float>&);
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitcrushAudioProcessor)
};
