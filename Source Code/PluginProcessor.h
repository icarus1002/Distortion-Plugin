/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Mu45FilterCalc/Mu45FilterCalc.h"
#include "StkLite-4.6.2/BiQuad.h"

#define PI 3.14159265358979323846


//==============================================================================
/**
*/
class ZacharyWFinalProjectDistortionAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ZacharyWFinalProjectDistortionAudioProcessor();
    ~ZacharyWFinalProjectDistortionAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    

private:
    
    
    // defining methods/functions
    void calcAlgorithmParams();
    
    // user parameters
    juce::AudioParameterFloat* zDriveParam;     // drive parameter
    juce::AudioParameterFloat* zToneParam;      // tone parameter
    juce::AudioParameterFloat* zMixParam;       // wet and dry mix parameter
    juce::AudioParameterFloat* zVolParam;       // volume parameter
    
    /*
    juce::AudioParameterFloat* LSGainParam;     // low shelf filter parameters
    juce::AudioParameterFloat* LSFcParam;
    
    juce::AudioParameterFloat* HSGainParam;     // high shelf filter parameters
    juce::AudioParameterFloat* HSFcParam;
    
    juce::AudioParameterFloat* LPFFcParam;      // low pass filter parameters
    juce::AudioParameterFloat* LPFQParam;
     */
    
    // alg parameters
    float zGainLin;                             // linear gain
    //float zWetGain, zDryGain;                   // wet and dry gains
    float zMix;                                 // wet and dry mix
    
    // Member objects
    float zFs;                                  // sampling rate
    float Drive;                                // drive
    float Tone;                                 // tone
    /*
    float LDT, RDT;                             // both drives*tones
    stk::BiQuad LSFilter;                       // low shelf filters
    stk::BiQuad HSFilter;                       // high shelf filters
    stk::BiQuad LPFilter;                       // low pass filter
    */
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZacharyWFinalProjectDistortionAudioProcessor)
};
