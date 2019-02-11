/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BitcrushAudioProcessorEditor  :  public AudioProcessorEditor

{
public:
    BitcrushAudioProcessorEditor (BitcrushAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~BitcrushAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    // Typdefs / Usings (Slider)
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BitcrushAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    
    // Sliders
    Label inGainLabel;
    Slider inGainSlider;
    std::unique_ptr<SliderAttachment> inGainAttachement;
    
    Label nBitsLabel;
    Slider nBitsSlider;
    std::unique_ptr<SliderAttachment> nBitsAttachement;
    
    Label clipSlopeLabel;
    Slider clipSlopeSlider;
    std::unique_ptr<SliderAttachment> clipSlopeAttachement;
    
    Label outGainLabel;
    Slider outGainSlider;
    std::unique_ptr<SliderAttachment> outGainAttachement;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitcrushAudioProcessorEditor)
};
