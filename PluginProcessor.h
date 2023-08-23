/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class EQChain2AudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    EQChain2AudioProcessor();
    ~EQChain2AudioProcessor() override;

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

    void updateChain();

    // juce::Decibels::dBtoGain wasnt working so I created my own math equation for it
    float dBtoGainFactor(float dB);

    struct FilterParameters
    {
        bool bypass;
        int type;
        float frequency;   // Frequency at which the filter operates
        float gain;              // Gain applied by the filter (if applicable)
        float q;         // Resonance or Q-factor of the filter
        // Add more parameters as needed for your specific filters

        // Constructor to initialize parameters to default values
        FilterParameters() :
            bypass(false),               // Default bypassed
            type(0),                    // Default filter type
            frequency(20.0f),   // Default cutoff frequency
            gain(0.0f),                  // Default gain
            q(0.5f)                    // Default resonance
            
        {
            // You can add more default initializations here
        }
    };

    //==============================================================================
    // Value Trees
    juce::AudioProcessorValueTreeState treestate;

private:

    using Filter = juce::dsp::IIR::Filter<float>;
    enum
    {
        slope12,
        slope24,
        slope36,
        slope48
    };
    using fourFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;
    enum
    {
        f1,
        f2,
        f3,
        f4
    };
    
    using FilterChain = juce::dsp::ProcessorChain<fourFilter, fourFilter, fourFilter, fourFilter>;
    using Gain = juce::dsp::Gain<float>;

    enum
    {
        ingainIndex,
        f1Index,
        f2Index,
        outgainIndex
    };
    using Monochain = juce::dsp::ProcessorChain<Gain, FilterChain, FilterChain, Gain>;
    Monochain leftchain, rightchain;
    // left and right chain for stereo ability

    //Parameters
    float ingain = 0.0;
    FilterParameters filterParams[8];
    float outgain = 0.0;

    

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQChain2AudioProcessor)
};
