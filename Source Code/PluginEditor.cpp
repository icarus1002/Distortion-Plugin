/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ZacharyWFinalProjectDistortionAudioProcessorEditor::ZacharyWFinalProjectDistortionAudioProcessorEditor (ZacharyWFinalProjectDistortionAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    setSize (300, 400);
    
    auto& params = audioProcessor.getParameters();

    auto dialSize = 125.0;
    //auto buttonWidth = getWidth() * 0.1;
    //auto buttonHeight = buttonWidth * 0.5;
    
    
    
    //Sliders
    
    // Drive Slider
    juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(0);
    driveDial.setTitle("Drive");
    driveDial.setBounds(0, 50, dialSize, dialSize); // x, y, width, height
    driveDial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    driveDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 32);
    driveDial.setColour(driveDial.textBoxTextColourId, juce::Colours::black);
    //driveDial.setTextValueSuffix("dB");
    driveDial.setRange(audioParam->range.start, audioParam->range.end);
    driveDial.setValue(*audioParam);
    //driveDial.setDoubleClickReturnValue(true, audioParam->range.start);
    driveDial.addListener(this);
    addAndMakeVisible(driveDial);
    
    // Tone Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(1);
    toneDial.setTitle("Tone");
    toneDial.setBounds(0, 250, dialSize, dialSize); // x, y, width, height
    toneDial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    toneDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 32);
    toneDial.setColour(toneDial.textBoxTextColourId, juce::Colours::black);
    //toneDial.setTextValueSuffix("Hz");
    toneDial.setRange(audioParam->range.start, audioParam->range.end);
    toneDial.setValue(*audioParam);
    //toneDial.setDoubleClickReturnValue(true, audioParam->range.start);
    toneDial.addListener(this);
    addAndMakeVisible(toneDial);
    
    // Mix Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(2);
    mixDial.setTitle("Mix");
    mixDial.setBounds(175, 250, dialSize, dialSize); // x, y, width, height
    mixDial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mixDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 32);
    mixDial.setColour(mixDial.textBoxTextColourId, juce::Colours::black);
    mixDial.setTextValueSuffix("%");
    mixDial.setRange(audioParam->range.start, audioParam->range.end);
    mixDial.setValue(*audioParam);
    //mixDial.setDoubleClickReturnValue(true, audioParam->range.start);
    mixDial.addListener(this);
    addAndMakeVisible(mixDial);
    
    // Volume Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(3);
    levelDial.setTitle("Level");
    levelDial.setBounds(175, 50, dialSize, dialSize); // x, y, width, height
    levelDial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    levelDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 32);
    levelDial.setColour(levelDial.textBoxTextColourId, juce::Colours::black);
    //levelDial.setTextValueSuffix("dB");
    levelDial.setRange(audioParam->range.start, audioParam->range.end);
    levelDial.setValue(*audioParam);
    //levelDial.setDoubleClickReturnValue(true, audioParam->range.start);
    levelDial.addListener(this);
    addAndMakeVisible(levelDial);
    
    /* wip
    // Bypass Button
    addAndMakeVisible(bypassButton);
    bypassButton.setButtonText("Bypass");
    bypassButton.setClickingTogglesState(true);
    bypassButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::red);
    bypassButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::dimgrey);
    bypassButton.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::black);
    bypassButton.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::black);
    bypassButton.setBounds(130, 25, buttonWidth, buttonHeight);
     */
    
    
    // Labels
    
    // Drive Label
    addAndMakeVisible(driveLabel);
    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.attachToComponent(&driveDial, false);
    driveLabel.setJustificationType(juce::Justification::centred);
    driveLabel.setColour (juce::Label::textColourId ,juce::Colours::black);
    driveLabel.setColour (juce::Label::outlineColourId ,juce::Colours::white);
    
    // Tone Label
    addAndMakeVisible(toneLabel);
    toneLabel.setText("Tone", juce::dontSendNotification);
    toneLabel.attachToComponent(&toneDial, false);
    toneLabel.setJustificationType(juce::Justification::centred);
    toneLabel.setColour (juce::Label::textColourId ,juce::Colours::black);
    toneLabel.setColour (juce::Label::outlineColourId ,juce::Colours::white);
    
    // Mix Label
    addAndMakeVisible(mixLabel);
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent(&mixDial, false);
    mixLabel.setJustificationType(juce::Justification::centred);
    mixLabel.setColour (juce::Label::textColourId,juce::Colours::black);
    mixLabel.setColour (juce::Label::outlineColourId ,juce::Colours::white);
    
    // Level Label
    addAndMakeVisible(levelLabel);
    levelLabel.setText("Level", juce::dontSendNotification);
    levelLabel.attachToComponent(&levelDial, false);
    levelLabel.setJustificationType(juce::Justification::centred);
    levelLabel.setColour (juce::Label::textColourId, juce::Colours::black);
    levelLabel.setColour (juce::Label::outlineColourId ,juce::Colours::white);
    
    
    
    

    
    
}

ZacharyWFinalProjectDistortionAudioProcessorEditor::~ZacharyWFinalProjectDistortionAudioProcessorEditor()
{
}



//==============================================================================
void ZacharyWFinalProjectDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::blue);
    g.setFont (15.0f);
}

void ZacharyWFinalProjectDistortionAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    auto& params = audioProcessor.getParameters();
    
    // compare pointer to slider that was changed w/ address of our slider
    if (slider == &driveDial)
    {
        // get a pointer to the first param in the processor
        juce::AudioParameterFloat* zDriveParam = (juce::AudioParameterFloat*)params.getUnchecked(0);
        
        // use value from slider to set param in processor
        float sliderValue = driveDial.getValue();
        *zDriveParam = sliderValue;     // set the param
        
        
        // we can use DBG() for simple print debugging
        DBG("Drive Slider Changed to " << sliderValue);
    }
    // compare pointer to slider that was changed w/ address of our slider
    if (slider == &toneDial)
    {
        // get a pointer to the first param in the processor
        juce::AudioParameterFloat* zToneParam = (juce::AudioParameterFloat*)params.getUnchecked(1);
        
        // use value from slider to set param in processor
        float sliderValue = toneDial.getValue();
        *zToneParam = sliderValue;     // set the param
        
        
        // we can use DBG() for simple print debugging
        DBG("Tone Slider Changed to " << sliderValue);
    }
    // compare pointer to slider that was changed w/ address of our slider
    if (slider == &mixDial)
    {
        // get a pointer to the first param in the processor
        juce::AudioParameterFloat* zMixParam = (juce::AudioParameterFloat*)params.getUnchecked(2);
        
        // use value from slider to set param in processor
        float sliderValue = mixDial.getValue();
        *zMixParam = sliderValue;     // set the param
        
        
        // we can use DBG() for simple print debugging
        DBG("Mix Slider Changed to " << sliderValue);
    }
    // compare pointer to slider that was changed w/ address of our slider
    if (slider == &levelDial)
    {
        // get a pointer to the first param in the processor
        juce::AudioParameterFloat* zVolParam = (juce::AudioParameterFloat*)params.getUnchecked(3);
        
        // use value from slider to set param in processor
        float sliderValue = levelDial.getValue();
        *zVolParam = sliderValue;     // set the param
        
        
        // we can use DBG() for simple print debugging
        DBG("Volume Slider Changed to " << sliderValue);
    }
}

void ZacharyWFinalProjectDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
