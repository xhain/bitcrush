/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitcrushAudioProcessor::BitcrushAudioProcessor():
#ifndef JucePlugin_PreferredChannelConfigurations
     AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                     #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
            parameters (*this, nullptr, "PARAMETERS",createParameterLayout())
{
    inGain = parameters.getRawParameterValue ("inGain");
    nBits = parameters.getRawParameterValue ("nBits");
    outGain = parameters.getRawParameterValue ("outGain");
    clipSlope = parameters.getRawParameterValue("clipSlope");
}

BitcrushAudioProcessor::~BitcrushAudioProcessor()

{
}

//==============================================================================

AudioProcessorValueTreeState::ParameterLayout BitcrushAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<RangedAudioParameter>> params;
    
    auto inGainParam = std::make_unique<AudioParameterFloat>("inGain", "Input Gain", NormalisableRange<float> (-60.0f, 6.0f, 0.1f), 0.0f);
    auto nBitsParam = std::make_unique<AudioParameterFloat>("nBits", "Number of Bits", NormalisableRange<float> (0, 16, 1), 16);
    auto outGainParam = std::make_unique<AudioParameterFloat>("outGain", "Output Gain", NormalisableRange<float> (-60.0f, 6.0f, 0.1f), 0.0f);
    auto clipSlopeParam = std::make_unique<AudioParameterFloat>("clipSlope", "Clip Slope", NormalisableRange<float> (0.1f, 10.0f, 0.1f), 0.1f);
    
    params.push_back(std::move(inGainParam));
    params.push_back(std::move(nBitsParam));
    params.push_back(std::move(outGainParam));
    params.push_back(std::move(clipSlopeParam));
    
    return { params.begin(), params.end() };
}

const String BitcrushAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BitcrushAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BitcrushAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BitcrushAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BitcrushAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BitcrushAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BitcrushAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BitcrushAudioProcessor::setCurrentProgram (int index)
{
}

const String BitcrushAudioProcessor::getProgramName (int index)
{
    return {};
}

void BitcrushAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BitcrushAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BitcrushAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BitcrushAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif
#


// >> - - - - - - - P R O C E S S  B L O C K - - - - - - - >>
void BitcrushAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    bitCrush(buffer);
}

void BitcrushAudioProcessor::bitCrush(AudioBuffer<float>& buffer)
{
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // get raw values from pointers & dereference
    auto inGainVal = pow (10, *inGain / 20);
    auto outGainVal = pow (10, *outGain / 20);
    auto nBitsVal = *nBits;
    auto clipSlopeVal = *clipSlope;
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            
            // Change Input Gain
            curSample = buffer.getSample(channel, sample) * inGainVal;
            // Quantize Sample via Dual Rounding
            curSample = round(curSample * pow(2, nBitsVal)) / pow(2, nBitsVal);
            // Change Output Gain
            curSample = curSample * outGainVal;
            
            // Hard Clip (ugly way to clip, I guess? Question: How is this done nicer? Where would I build a "clip" function and link it?)
            // Soft Clip (a la https://www.desmos.com/calculator/nzwdskl4je )
            if (curSample > 1.0)
            {
                curSample = atan(curSample * clipSlopeVal) * (2 / MathConstants<float>::pi);
            }
            else if (curSample < -1.0)
            {
                curSample = atan(curSample * clipSlopeVal) * (2 / MathConstants<float>::pi);
            }
            
            // Output vector
            channelData[sample] = curSample;
        }
    }
}


//==============================================================================
bool BitcrushAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BitcrushAudioProcessor::createEditor()
{
    return new BitcrushAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void BitcrushAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BitcrushAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BitcrushAudioProcessor();
}
