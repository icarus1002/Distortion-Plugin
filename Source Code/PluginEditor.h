/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/


class ZacharyWFinalProjectDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
public juce::Slider::Listener
{
public:
    ZacharyWFinalProjectDistortionAudioProcessorEditor (ZacharyWFinalProjectDistortionAudioProcessor&);
    ~ZacharyWFinalProjectDistortionAudioProcessorEditor() override;
    
    
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    
    
private:
    
    
    juce::Slider driveDial;
    juce::Slider toneDial;
    juce::Slider mixDial;
    juce::Slider levelDial;
    juce::TextButton bypassButton;
    
    juce::Label driveLabel;
    juce::Label toneLabel;
    juce::Label mixLabel;
    juce::Label levelLabel;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ZacharyWFinalProjectDistortionAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZacharyWFinalProjectDistortionAudioProcessorEditor)
};
