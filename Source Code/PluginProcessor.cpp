/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ZacharyWFinalProjectDistortionAudioProcessor::ZacharyWFinalProjectDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
    
    
    // Instantiating AudioParameters
    
    // Drive Parameter
    addParameter(zDriveParam = new juce::AudioParameterFloat("Drive (dB)", // parameter ID,
                                                                "Drive", // parameter name,
                                                                0.0f, // minValue,
                                                                1.0f, // maxValue,
                                                                0.3f // defaultValue
                                                                ));
    // Tone Parameter
    addParameter(zToneParam = new juce::AudioParameterFloat("Tone (Hz)", // parameter ID,
                                                                "Tone", // parameter name,
                                                                0.1f, // minValue,
                                                                300.0f, // maxValue,
                                                                10.0f // defaultValue
                                                                ));
    // Mix Parameter
    addParameter(zMixParam = new juce::AudioParameterFloat("Wet and Dry Mix", // parameter ID,
                                                                "Mix", // parameter name,
                                                                0.1f, // minValue,
                                                                1.0f, // maxValue,
                                                                0.5f // defaultValue
                                                                ));
    // Volume Parameter
    addParameter(zVolParam = new juce::AudioParameterFloat("Volume(dB)", // parameter ID,
                                                                "Volume", // parameter name,
                                                                0.0f, // minValue,
                                                                2.0f, // maxValue,
                                                                1.0f // defaultValue
                                                                ));
    /*
    
    // Low Pass Filter Cutoff parameter
    addParameter(LPFFcParam = new juce::AudioParameterFloat("LPF Cutoff (Hz)", // parameter ID,
                                                                "LPFFc", // parameter name,
                                                                40.0f, // minValue,
                                                                10000.0f, // maxValue,
                                                                500.0f // defaultValue
                                                                ));
    // Low Pass Filter Q Parameter
    addParameter(LPFQParam = new juce::AudioParameterFloat("LPF Q", // parameter ID,
                                                               "LPFQ", // parameter name,
                                                               1.0f, // minValue,
                                                               10.0f, // maxValue,
                                                               3.0f // defaultValue
                                                               ));
    // Low Shelf Gain Parameter
    addParameter(LSGainParam = new juce::AudioParameterFloat("Low Shelf Gain", // parameter ID,
                                                               "LSGain", // parameter name,
                                                               -20.0f, // minValue,
                                                               20.0f, // maxValue,
                                                               0.0f // defaultValue
                                                               ));
    
    // Low Shelf Fc Parameter
    addParameter(LSFcParam = new juce::AudioParameterFloat("Low Shelf Fc (transition)", // parameter ID,
                                                               "LSFc", // parameter name,
                                                               50.0f, // minValue,
                                                               400.0f, // maxValue,
                                                               200.0f // defaultValue
                                                               ));
    
    // High Shelf Gain Parameter
    addParameter(HSGainParam = new juce::AudioParameterFloat("High Shelf Gain", // parameter ID,
                                                               "HSGain", // parameter name,
                                                               -20.0f, // minValue,
                                                               20.0f, // maxValue,
                                                               0.0f // defaultValue
                                                               ));
    
    // High Shelf Fc Parameter
    addParameter(HSFcParam = new juce::AudioParameterFloat("High Shelf Fc (transition)", // parameter ID,
                                                               "HSFc", // parameter name,
                                                               1000.0f, // minValue,
                                                               15000.0f, // maxValue,
                                                               10000.0f // defaultValue
                                                               ));
     */
}

ZacharyWFinalProjectDistortionAudioProcessor::~ZacharyWFinalProjectDistortionAudioProcessor()
{
}

//==============================================================================
const juce::String ZacharyWFinalProjectDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ZacharyWFinalProjectDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ZacharyWFinalProjectDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ZacharyWFinalProjectDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ZacharyWFinalProjectDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ZacharyWFinalProjectDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ZacharyWFinalProjectDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ZacharyWFinalProjectDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ZacharyWFinalProjectDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void ZacharyWFinalProjectDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ZacharyWFinalProjectDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    zFs = sampleRate;
}

void ZacharyWFinalProjectDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ZacharyWFinalProjectDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void ZacharyWFinalProjectDistortionAudioProcessor::calcAlgorithmParams()
{
    
    // drive
    Drive = zDriveParam->get();
    
    
    // tone
    Tone = zToneParam->get();

    /*
    // calculating Drive and Tone
    LDT = (2.f / PI) * atan(DriveL * ToneL);
    RDT = (2.f / PI) * atan(DriveR * ToneR);
     */
    
    /*
    // Wet and Dry gains
    zWetGain = zMixParam->get()/100.0;
    zDryGain = 1.0 - zWetGain;
     */
    
    zMix = zMixParam->get();
    
    /*
    
    // User Parameters for Low Shelf Filter
    float fc = LSFcParam->get();
    float gainDb = LSGainParam->get();
    
    // Calculate Filter Coefficients
    float coeffs[5]; // an array of 5 floats for filter coeffs: [b0, b1, b2, a1, a2]
    Mu45FilterCalc::calcCoeffsLowShelf(coeffs, fc, gainDb, zFs);
    
    // setting coefficients for each filter
    LSFilter.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    
    // User Parameters for High Shelf Filter
    fc = HSFcParam->get();
    gainDb = HSGainParam->get();
    
    // Calculate Filter Coefficients
    Mu45FilterCalc::calcCoeffsHighShelf(coeffs, fc, gainDb, zFs);
    
    // setting coefficients for each filter
    HSFilter.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    
    // Get User Parameter Values
    fc = LPFFcParam->get();
    float Q  = LPFQParam->get();
    
    
    
    // Calculate Filter Coefficients
    Mu45FilterCalc::calcCoeffsLPF(coeffs, fc, Q, zFs);

    
    // setting coefficients for each filter
    LPFilter.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    LPFilter.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    
    DBG("Fc = "<<fc);       // debugging
     
     */
    
    // set Volume
    //zGainLin = powf(10.0, zVolParam->get() / 20.0);
    zGainLin = zVolParam->get();
    
}

void ZacharyWFinalProjectDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // Update Param Values
    calcAlgorithmParams();
    
    /*
    // get left and right audio buffers
    auto* channelDataLeft = buffer.getWritePointer(0);
    auto* channelDataRight = buffer.getWritePointer(1);
     */

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    /*
    for (int channel = 0; channel < getNumInputChannels(); ++channel) {
            float* channelData = buffer.getWritePointer (channel);

            for (int i = 0; i < buffer.getNumSamples(); ++i) {
                channelData[i] = processor->processSample(channelData[i]);
            }
        }
     */
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
                for (int sample = 0; sample < buffer.getNumSamples(); sample++){
                    float cleanSig = *channelData;
                    *channelData *= Drive*Tone;
                    *channelData = (((((2.0f/PI) * atan(*channelData))*zMix)+(cleanSig * (1.0f / zMix))) / 2)*zGainLin;
                    // LPFilter.tick(*channelData);
                    channelData++;
                }
    }
    /*
    for (int samp = 0; samp < buffer.getNumSamples(); samp++)
    {
        /*
        float cleanL = zDryGain * channelDataLeft[samp];
        float cleanR = zDryGain * channelDataRight[samp];
        
        channelDataLeft[samp] = (2.f / PI) * atan(DriveL*channelDataLeft[samp]);
        channelDataRight[samp] = (2.f / PI) * atan(DriveR*channelDataRight[samp]);
        
        channelDataLeft[samp] = zWetGain * channelDataLeft[samp] * zGainLin;
        channelDataRight[samp] = zWetGain * channelDataRight[samp] * zGainLin;
        
        channelDataLeft[samp] = LSFilterL.tick(channelDataLeft[samp]);
        channelDataRight[samp] = LSFilterR.tick(channelDataRight[samp]);
        
        channelDataLeft[samp] = HSFilterL.tick(channelDataLeft[samp]);
        channelDataRight[samp] = HSFilterR.tick(channelDataRight[samp]);
        
        channelDataLeft[samp] = cleanL + zWetGain;
        channelDataRight[samp] = cleanR + zWetGain;
        */
        
        
        /*
        float cleanL = zDryGain*channelDataLeft[samp];
        float cleanR = zDryGain*channelDataLeft[samp];
        
        channelDataLeft[samp] = DriveL * ToneL;
        channelDataRight[samp] = DriveR * ToneR;
        
        channelDataLeft[samp] = (((((2.f / PI) * atan(channelDataLeft[samp])) * zWetGain) + cleanL) / 2) * zGainLin;
        channelDataRight[samp] = (((((2.f / PI) * atan(channelDataRight[samp])) * zWetGain) + cleanL) / 2) * zGainLin;
            
        */
            
        // channelDataLeft[samp] = (LDT*channelDataLeft[samp]*zWetGain + zDryGain) * zGainLin;
            
    //}

    
    
}

//==============================================================================
bool ZacharyWFinalProjectDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ZacharyWFinalProjectDistortionAudioProcessor::createEditor()
{
    return new ZacharyWFinalProjectDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void ZacharyWFinalProjectDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ZacharyWFinalProjectDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ZacharyWFinalProjectDistortionAudioProcessor();
}
