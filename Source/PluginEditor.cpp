/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitcrushAudioProcessorEditor::BitcrushAudioProcessorEditor (BitcrushAudioProcessor& p, AudioProcessorValueTreeState& vts)
: AudioProcessorEditor (&p), processor (p), valueTreeState (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 400);
    
    // Input Gains
    inGainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    inGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    inGainSlider.setRange(-60.0, 0, 0.1);
    inGainSlider.setValue(-3.0);
    inGainAttachement.reset (new SliderAttachment (valueTreeState, "inGain", inGainSlider));
    addAndMakeVisible(inGainSlider);
    
    // N Bits Quant Slider
    nBitsSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    nBitsSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    nBitsSlider.setRange(0, 16, 1);
    nBitsSlider.setValue(16);
    nBitsAttachement.reset (new SliderAttachment (valueTreeState, "nBits", nBitsSlider));
    addAndMakeVisible(nBitsSlider);
    
    // Output Gain
    outGainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    outGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    outGainSlider.setRange(-60.0, 0, 0.1);
    outGainSlider.setValue(-3.0);
    outGainAttachement.reset (new SliderAttachment (valueTreeState, "outGain", outGainSlider));
    addAndMakeVisible(outGainSlider);
    
    // Soft Clip
    clipSlopeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    clipSlopeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    clipSlopeSlider.setRange(0.1, 10, 0.1);
    clipSlopeSlider.setValue(0.1);
    clipSlopeAttachement.reset (new SliderAttachment (valueTreeState, "clipSlope", clipSlopeSlider));
    addAndMakeVisible(clipSlopeSlider);
}

BitcrushAudioProcessorEditor::~BitcrushAudioProcessorEditor()
{
}

//==============================================================================
void BitcrushAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.drawFittedText ("Bitcrusher", 0, 10, 150, 50, Justification::centred, 1);
}

void BitcrushAudioProcessorEditor::resized()
{
    
    // Draw Sliders
    inGainSlider.setBounds(25, 50, 50, 300);
    outGainSlider.setBounds(225, 50, 50, 300);
    clipSlopeSlider.setBounds(325, 50, 50, 300);
    nBitsSlider.setBounds(125, 50, 50, 300);

}
