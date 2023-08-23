/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQChain2AudioProcessor::EQChain2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), treestate(*this, nullptr, "PARMETERS", createParameterLayout()), leftchain(), rightchain()
#endif
{
    treestate.addParameterListener("input gain", this);

    treestate.addParameterListener("first filter type", this);
    treestate.addParameterListener("first bypass", this);
    treestate.addParameterListener("first freq", this);
    treestate.addParameterListener("first gain", this);
    treestate.addParameterListener("first q", this);

    treestate.addParameterListener("second filter type", this);
    treestate.addParameterListener("second bypass", this);
    treestate.addParameterListener("second freq", this);
    treestate.addParameterListener("second gain", this);
    treestate.addParameterListener("second q", this);

    treestate.addParameterListener("third filter type", this);
    treestate.addParameterListener("third bypass", this);
    treestate.addParameterListener("third freq", this);
    treestate.addParameterListener("third gain", this);
    treestate.addParameterListener("third q", this);

    treestate.addParameterListener("fourth filter type", this);
    treestate.addParameterListener("fourth bypass", this);
    treestate.addParameterListener("fourth freq", this);
    treestate.addParameterListener("fourth gain", this);
    treestate.addParameterListener("fourth q", this);

    treestate.addParameterListener("fifth filter type", this);
    treestate.addParameterListener("fifth bypass", this);
    treestate.addParameterListener("fifth freq", this);
    treestate.addParameterListener("fifth gain", this);
    treestate.addParameterListener("fifth q", this);

    treestate.addParameterListener("sixth filter type", this);
    treestate.addParameterListener("sixth bypass", this);
    treestate.addParameterListener("sixth freq", this);
    treestate.addParameterListener("sixth gain", this);
    treestate.addParameterListener("sixth q", this);

    treestate.addParameterListener("seventh filter type", this);
    treestate.addParameterListener("seventh bypass", this);
    treestate.addParameterListener("seventh freq", this);
    treestate.addParameterListener("seventh gain", this);
    treestate.addParameterListener("seventh q", this);

    treestate.addParameterListener("eighth filter type", this);
    treestate.addParameterListener("eighth bypass", this);
    treestate.addParameterListener("eighth freq", this);
    treestate.addParameterListener("eighth gain", this);
    treestate.addParameterListener("eighth q", this);

    treestate.addParameterListener("output gain", this);
}

EQChain2AudioProcessor::~EQChain2AudioProcessor()
{
    treestate.removeParameterListener("input gain", this);

    treestate.removeParameterListener("first filter type", this);
    treestate.removeParameterListener("first bypass", this);
    treestate.removeParameterListener("first freq", this);
    treestate.removeParameterListener("first gain", this);
    treestate.removeParameterListener("first q", this);

    treestate.removeParameterListener("second filter type", this);
    treestate.removeParameterListener("second bypass", this);
    treestate.removeParameterListener("second freq", this);
    treestate.removeParameterListener("second gain", this);
    treestate.removeParameterListener("second q", this);

    treestate.removeParameterListener("third filter type", this);
    treestate.removeParameterListener("third bypass", this);
    treestate.removeParameterListener("third freq", this);
    treestate.removeParameterListener("third gain", this);
    treestate.removeParameterListener("third q", this);

    treestate.removeParameterListener("fourth filter type", this);
    treestate.removeParameterListener("fourth bypass", this);
    treestate.removeParameterListener("fourth freq", this);
    treestate.removeParameterListener("fourth gain", this);
    treestate.removeParameterListener("fourth q", this);

    treestate.removeParameterListener("fifth filter type", this);
    treestate.removeParameterListener("fifth bypass", this);
    treestate.removeParameterListener("fifth freq", this);
    treestate.removeParameterListener("fifth gain", this);
    treestate.removeParameterListener("fifth q", this);

    treestate.removeParameterListener("sixth filter type", this);
    treestate.removeParameterListener("sixth bypass", this);
    treestate.removeParameterListener("sixth freq", this);
    treestate.removeParameterListener("sixth gain", this);
    treestate.removeParameterListener("sixth q", this);

    treestate.removeParameterListener("seventh filter type", this);
    treestate.removeParameterListener("seventh bypass", this);
    treestate.removeParameterListener("seventh freq", this);
    treestate.removeParameterListener("seventh gain", this);
    treestate.removeParameterListener("seventh q", this);

    treestate.removeParameterListener("eighth filter type", this);
    treestate.removeParameterListener("eighth bypass", this);
    treestate.removeParameterListener("eighth freq", this);
    treestate.removeParameterListener("eighth gain", this);
    treestate.removeParameterListener("eighth q", this);

    treestate.removeParameterListener("output gain", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout EQChain2AudioProcessor::createParameterLayout()
{
    std::vector < std::unique_ptr<juce::RangedAudioParameter >> params;

    
    juce::StringArray filterchoice = { "Peak", "Low Shelf", "High Shelf", "Low Cut", "Low Cut x4", "High Cut", "High Cut x4"};
    
    auto pInputGain = std::make_unique<juce::AudioParameterFloat>("input gain", "Input Gain", -36.0f, 6.0f, 0.0f);

    auto pFirstBypass = std::make_unique<juce::AudioParameterBool>("first bypass", "First Bypass", 0);
    auto pFirstFilter = std::make_unique<juce::AudioParameterChoice>("first filter type", "First Filter Type", filterchoice, 0);
    auto pFirstFreq = std::make_unique<juce::AudioParameterFloat>("first freq", "First Freq", 20.0f, 20000.0f, 20.0f);
    auto pFirstGain = std::make_unique<juce::AudioParameterFloat>("first gain", "First Gain", -48.0f, 12.0f, 0.0f);
    auto pFirstQ = std::make_unique<juce::AudioParameterFloat>("first q", "First Q", 0.5f, 18.0f, 0.5f);

    
    auto pSecondBypass = std::make_unique<juce::AudioParameterBool>("second bypass", "Second Bypass", 0);
    auto pSecondFilter = std::make_unique<juce::AudioParameterChoice>("second filter type", "Second Filter Type", filterchoice, 0);
    auto pSecondFreq = std::make_unique<juce::AudioParameterFloat>("second freq", "Second Freq", 20.0f, 20000.0f, 60.0f);
    auto pSecondGain = std::make_unique<juce::AudioParameterFloat>("second gain", "Second Gain", -48.0f, 12.0f, 0.0f);
    auto pSecondQ = std::make_unique<juce::AudioParameterFloat>("second q", "Second Q", 0.5f, 18.0f, 0.5f);

    auto pThirdBypass = std::make_unique<juce::AudioParameterBool>("third bypass", "Third Bypass", 1);
    auto pThirdFilter = std::make_unique<juce::AudioParameterChoice>("third filter type", "Third Filter Type", filterchoice, 0);
    auto pThirdFreq = std::make_unique<juce::AudioParameterFloat>("third freq", "Third Freq", 20.0f, 20000.0f, 300.0f);
    auto pThirdGain = std::make_unique<juce::AudioParameterFloat>("third gain", "Third Gain", -48.0f, 12.0f, 0.0f);
    auto pThirdQ = std::make_unique<juce::AudioParameterFloat>("third q", "Third Q", 0.5f, 18.0f, 0.5f);

    auto pFourthBypass = std::make_unique<juce::AudioParameterBool>("fourth bypass", "Fourth Bypass", 1);
    auto pFourthFilter = std::make_unique<juce::AudioParameterChoice>("fourth filter type", "Fourth Filter Type", filterchoice, 0);
    auto pFourthFreq = std::make_unique<juce::AudioParameterFloat>("fourth freq", "Fourth Freq", 20.0f, 20000.0, 1100.0f);
    auto pFourthGain = std::make_unique<juce::AudioParameterFloat>("fourth gain", "Fourth Gain", -48.0f, 12.0f, 0.0f);
    auto pFourthQ = std::make_unique<juce::AudioParameterFloat>("fourth q", "Fourth Q", 0.5f, 18.0f, 0.5f);

    auto pFifthBypass = std::make_unique<juce::AudioParameterBool>("fifth bypass", "Fifth Bypass", 1);
    auto pFifthFilter = std::make_unique<juce::AudioParameterChoice>("fifth filter type", "Fifth Filter Type", filterchoice, 0);
    auto pFifthFreq = std::make_unique<juce::AudioParameterFloat>("fifth freq", "Fifth Freq", 20.0f, 20000.0f, 2000.0f);
    auto pFifthGain = std::make_unique<juce::AudioParameterFloat>("fifth gain", "Fifth Gain", -48.0f, 12.0f, 0.0f);
    auto pFifthQ = std::make_unique<juce::AudioParameterFloat>("fifth q", "Fifth Q", 0.5f, 18.0f, 0.5f);

    auto pSixthBypass = std::make_unique<juce::AudioParameterBool>("sixth bypass", "Sixth Bypass", 1);
    auto pSixthFilter = std::make_unique<juce::AudioParameterChoice>("sixth filter type", "Sixth Filter Type", filterchoice, 0);
    auto pSixthFreq = std::make_unique<juce::AudioParameterFloat>("sixth freq", "Sixth Freq", 20.0f, 20000.0f, 4000.0f);
    auto pSixthGain = std::make_unique<juce::AudioParameterFloat>("sixth gain", "Sixth Gain", -48.0f, 12.0f, 0.0f);
    auto pSixthQ = std::make_unique<juce::AudioParameterFloat>("sixth q", "Sixth Q", 0.5f, 18.0f, 0.5f);

    auto pSeventhBypass = std::make_unique<juce::AudioParameterBool>("seventh bypass", "Seventh Bypass", 0);
    auto pSeventhFilter = std::make_unique<juce::AudioParameterChoice>("seventh filter type", "Seventh Filter Type", filterchoice, 0);
    auto pSeventhFreq = std::make_unique<juce::AudioParameterFloat>("seventh freq", "Seventh Freq", 20.0f, 20000.0f, 6000.0f);
    auto pSeventhGain = std::make_unique<juce::AudioParameterFloat>("seventh gain", "Seventh Gain", -48.0f, 12.0f, 0.0f);
    auto pSeventhQ = std::make_unique<juce::AudioParameterFloat>("seventh q", "Seventh Q", 0.5f, 18.0f, 0.5f);

    auto pEighthBypass = std::make_unique<juce::AudioParameterBool>("eighth bypass", "Eighth Bypass", 0);
    auto pEighthFilter = std::make_unique<juce::AudioParameterChoice>("eighth filter type", "Eighth Filter Type", filterchoice, 0);
    auto pEighthFreq = std::make_unique<juce::AudioParameterFloat>("eighth freq", "Eighth Freq", 20.0f, 20000.0f, 10000.0f);
    auto pEighthGain = std::make_unique<juce::AudioParameterFloat>("eighth gain", "Eighth Gain", -48.0f, 12.0f, 0.0f);
    auto pEighthQ = std::make_unique<juce::AudioParameterFloat>("eighth q", "Eighth Q", 0.5f, 18.0f, 0.5f);
    

    auto pOutputGain = std::make_unique<juce::AudioParameterFloat>("output gain", "Output Gain", -36.0f, 6.0f, 0.0f);

    params.push_back(std::move(pInputGain));

    params.push_back(std::move(pFirstBypass));
    params.push_back(std::move(pFirstFilter));
    params.push_back(std::move(pFirstFreq));
    params.push_back(std::move(pFirstGain));
    params.push_back(std::move(pFirstQ));

    
    params.push_back(std::move(pSecondBypass));
    params.push_back(std::move(pSecondFilter));
    params.push_back(std::move(pSecondFreq));
    params.push_back(std::move(pSecondGain));
    params.push_back(std::move(pSecondQ));

    params.push_back(std::move(pThirdBypass));
    params.push_back(std::move(pThirdFilter));
    params.push_back(std::move(pThirdFreq));
    params.push_back(std::move(pThirdGain));
    params.push_back(std::move(pThirdQ));

    params.push_back(std::move(pFourthBypass));
    params.push_back(std::move(pFourthFilter));
    params.push_back(std::move(pFourthFreq));
    params.push_back(std::move(pFourthGain));
    params.push_back(std::move(pFourthQ));

    params.push_back(std::move(pFifthBypass));
    params.push_back(std::move(pFifthFilter));
    params.push_back(std::move(pFifthFreq));
    params.push_back(std::move(pFifthGain));
    params.push_back(std::move(pFifthQ));

    params.push_back(std::move(pSixthBypass));
    params.push_back(std::move(pSixthFilter));
    params.push_back(std::move(pSixthFreq));
    params.push_back(std::move(pSixthGain));
    params.push_back(std::move(pSixthQ));

    params.push_back(std::move(pSeventhBypass));
    params.push_back(std::move(pSeventhFilter));
    params.push_back(std::move(pSeventhFreq));
    params.push_back(std::move(pSeventhGain));
    params.push_back(std::move(pSeventhQ));

    params.push_back(std::move(pEighthBypass));
    params.push_back(std::move(pEighthFilter));
    params.push_back(std::move(pEighthFreq));
    params.push_back(std::move(pEighthGain));
    params.push_back(std::move(pEighthQ));
    
    params.push_back(std::move(pOutputGain));

    return { params.begin(), params.end() };
}

void EQChain2AudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "input gain")
    {
        ingain = (newValue);
    }
    if (parameterID == "first bypass")
    {
        filterParams[0].bypass = newValue;
    }
    if (parameterID == "first filter type")
    {
        filterParams[0].type = newValue;
    }
    if (parameterID == "first freq")
    {
        filterParams[0].frequency = newValue;
    }
    if (parameterID == "first gain")
    {
        filterParams[0].gain = newValue;
    }
    if (parameterID == "first q")
    {
        filterParams[0].q = newValue;
    }
    
    if (parameterID == "second bypass")
    {
        filterParams[1].bypass = newValue;
    }
    if (parameterID == "second filter type")
    {
        filterParams[1].type = newValue;
    }
    if (parameterID == "second freq")
    {
        filterParams[1].frequency = newValue;
    }
    if (parameterID == "second gain")
    {
        filterParams[1].gain = newValue;
    }
    if (parameterID == "second q")
    {
        filterParams[1].q = newValue;
    }
    if (parameterID == "third bypass")
    {
        filterParams[2].bypass = newValue;
    }
    if (parameterID == "third filter type")
    {
        filterParams[2].type = newValue;
    }
    if (parameterID == "third freq")
    {
        filterParams[2].frequency = newValue;
    }
    if (parameterID == "third gain")
    {
        filterParams[2].gain = newValue;
    }
    if (parameterID == "third q")
    {
        filterParams[2].q = newValue;
    }
    if (parameterID == "fourth bypass")
    {
        filterParams[3].bypass = newValue;
    }
    if (parameterID == "fourth filter type")
    {
        filterParams[3].type = newValue;
    }
    if (parameterID == "fourth freq")
    {
        filterParams[3].frequency = newValue;
    }
    if (parameterID == "fourth gain")
    {
        filterParams[3].gain = newValue;
    }
    if (parameterID == "fourth q")
    {
        filterParams[3].q = newValue;
    }
    if (parameterID == "fifth bypass")
    {
        filterParams[4].bypass = newValue;
    }
    if (parameterID == "fifth filter type")
    {
        filterParams[4].type = newValue;
    }
    if (parameterID == "fifth freq")
    {
        filterParams[4].frequency = newValue;
    }
    if (parameterID == "fifth gain")
    {
        filterParams[4].gain = newValue;
    }
    if (parameterID == "fifth q")
    {
        filterParams[4].q = newValue;
    }
    if (parameterID == "sixth bypass")
    {
        filterParams[5].bypass = newValue;
    }
    if (parameterID == "sixth filter type")
    {
        filterParams[5].type = newValue;
    }
    if (parameterID == "sixth freq")
    {
        filterParams[5].frequency = newValue;
    }
    if (parameterID == "sixth gain")
    {
        filterParams[5].gain = newValue;
    }
    if (parameterID == "sixth q")
    {
        filterParams[5].q = newValue;
    }
    if (parameterID == "seventh bypass")
    {
        filterParams[6].bypass = newValue;
    }
    if (parameterID == "seventh filter type")
    {
        filterParams[6].type = newValue;
    }
    if (parameterID == "seventh freq")
    {
        filterParams[6].frequency = newValue;
    }
    if (parameterID == "seventh gain")
    {
        filterParams[6].gain = newValue;
    }
    if (parameterID == "seventh q")
    {
        filterParams[6].q = newValue;
    }
    if (parameterID == "eighth bypass")
    {
        filterParams[7].bypass = newValue;
    }
    if (parameterID == "eighth filter type")
    {
        filterParams[7].type = newValue;
    }
    if (parameterID == "eighth freq")
    {
        filterParams[7].frequency = newValue;
    }
    if (parameterID == "eighth gain")
    {
        filterParams[7].gain = newValue;
    }
    if (parameterID == "eighth q")
    {
        filterParams[7].q = newValue;
    }
    
    if (parameterID == "output gain")
    {
        outgain = (newValue);
    }
}

float EQChain2AudioProcessor::dBtoGainFactor(float dB)
{
    return std::pow(10, dB / 20);
}

//==============================================================================
const juce::String EQChain2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EQChain2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EQChain2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EQChain2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EQChain2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EQChain2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EQChain2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void EQChain2AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EQChain2AudioProcessor::getProgramName (int index)
{
    return {};
}

void EQChain2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EQChain2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1; // one channel per chain
    spec.sampleRate = sampleRate;

    leftchain.reset();
    rightchain.reset();
    leftchain.prepare(spec);
    rightchain.prepare(spec);

    updateChain();
}

void EQChain2AudioProcessor::updateChain()
{
    //input gain connection
    leftchain.get<ingainIndex>().setGainDecibels(*treestate.getRawParameterValue("input gain"));
    rightchain.get<ingainIndex>().setGainDecibels(*treestate.getRawParameterValue("input gain"));
    leftchain.get<ingainIndex>().setRampDurationSeconds(0.005);
    rightchain.get<ingainIndex>().setRampDurationSeconds(0.005);

    //filter parameter connection
    filterParams[0].frequency = *treestate.getRawParameterValue("first freq");
    filterParams[0].q = *treestate.getRawParameterValue("first q");
    filterParams[0].gain = *treestate.getRawParameterValue("first gain");
    filterParams[0].type = *treestate.getRawParameterValue("first filter type");
    filterParams[0].bypass = *treestate.getRawParameterValue("first bypass");
    
    filterParams[1].frequency = *treestate.getRawParameterValue("second freq");
    filterParams[1].q = *treestate.getRawParameterValue("second q");
    filterParams[1].gain = *treestate.getRawParameterValue("second gain");
    filterParams[1].type = *treestate.getRawParameterValue("second filter type");
    filterParams[1].bypass = *treestate.getRawParameterValue("second bypass");

    filterParams[2].frequency = *treestate.getRawParameterValue("third freq");
    filterParams[2].q = *treestate.getRawParameterValue("third q");
    filterParams[2].gain = *treestate.getRawParameterValue("third gain");
    filterParams[2].type = *treestate.getRawParameterValue("third filter type");
    filterParams[2].bypass = *treestate.getRawParameterValue("third bypass");

    filterParams[3].frequency = *treestate.getRawParameterValue("fourth freq");
    filterParams[3].q = *treestate.getRawParameterValue("fourth q");
    filterParams[3].gain = *treestate.getRawParameterValue("fourth gain");
    filterParams[3].type = *treestate.getRawParameterValue("fourth filter type");
    filterParams[3].bypass = *treestate.getRawParameterValue("fourth bypass");

    filterParams[4].frequency = *treestate.getRawParameterValue("fifth freq");
    filterParams[4].q = *treestate.getRawParameterValue("fifth q");
    filterParams[4].gain = *treestate.getRawParameterValue("fifth gain");
    filterParams[4].type = *treestate.getRawParameterValue("fifth filter type");
    filterParams[4].bypass = *treestate.getRawParameterValue("fifth bypass");

    filterParams[5].frequency = *treestate.getRawParameterValue("sixth freq");
    filterParams[5].q = *treestate.getRawParameterValue("sixth q");
    filterParams[5].gain = *treestate.getRawParameterValue("sixth gain");
    filterParams[5].type = *treestate.getRawParameterValue("sixth filter type");
    filterParams[5].bypass = *treestate.getRawParameterValue("sixth bypass");

    filterParams[6].frequency = *treestate.getRawParameterValue("seventh freq");
    filterParams[6].q = *treestate.getRawParameterValue("seventh q");
    filterParams[6].gain = *treestate.getRawParameterValue("seventh gain");
    filterParams[6].type = *treestate.getRawParameterValue("seventh filter type");
    filterParams[6].bypass = *treestate.getRawParameterValue("seventh bypass");

    filterParams[7].frequency = *treestate.getRawParameterValue("eighth freq");
    filterParams[7].q = *treestate.getRawParameterValue("eighth q");
    filterParams[7].gain = *treestate.getRawParameterValue("eighth gain");
    filterParams[7].type = *treestate.getRawParameterValue("eighth filter type");
    filterParams[7].bypass = *treestate.getRawParameterValue("eighth bypass");

    //builds filters based off the filter type choices and taking from parameters above
    if (filterParams[0].bypass == 0)
    {
        leftchain.get<f1Index>().setBypassed<f1>(1);
        rightchain.get<f1Index>().setBypassed<f1>(1);
    }
    else
    {
        leftchain.get<f1Index>().setBypassed<f1>(0); // "Peak", "Low Shelf", "High Shelf", "Low Cut", "Low Cut x4", "High Cut", "High Cut x4"
        rightchain.get<f1Index>().setBypassed<f1>(0);

        if (filterParams[0].type == 0)
        {
            leftchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[0].frequency, filterParams[0].q, dBtoGainFactor(filterParams[0].gain));
            rightchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[0].frequency, filterParams[0].q, dBtoGainFactor(filterParams[0].gain));
            leftchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);

        }
        if (filterParams[0].type == 1)
        {
            leftchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[0].frequency, filterParams[0].q, dBtoGainFactor(filterParams[0].gain));
            rightchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[0].frequency, filterParams[0].q, dBtoGainFactor(filterParams[0].gain));
            leftchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);
        }
        if (filterParams[0].type == 2)
        {
            leftchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[0].frequency, filterParams[0].q, dBtoGainFactor(filterParams[0].gain));
            rightchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[0].frequency, filterParams[0].q, dBtoGainFactor(filterParams[0].gain));
            leftchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);
        }
        if (filterParams[0].type == 3)
        {
            leftchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, filterParams[0].q);
            rightchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, filterParams[0].q);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);
        }
        if (filterParams[0].type == 4)
        {
            // make another 4x filter high pass chain
            leftchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            rightchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope24>(0);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope24>(0);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope36>(0);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope36>(0);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope48>(0);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope48>(0);
            leftchain.get<f1Index>().get<f1>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            rightchain.get<f1Index>().get<f1>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            leftchain.get<f1Index>().get<f1>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            rightchain.get<f1Index>().get<f1>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            leftchain.get<f1Index>().get<f1>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            rightchain.get<f1Index>().get<f1>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[0].frequency, 0.707f);
        }
        if (filterParams[0].type == 5)
        {
            leftchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, filterParams[0].q);
            rightchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, filterParams[0].q);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope48>(1);
        }
        if (filterParams[0].type == 6)
        {
            // make 4x filter low pass chain
            leftchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            rightchain.get<f1Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope24>(0);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope24>(0);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope36>(0);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope36>(0);
            leftchain.get<f1Index>().get<f1>().setBypassed<slope48>(0);
            rightchain.get<f1Index>().get<f1>().setBypassed<slope48>(0);
            leftchain.get<f1Index>().get<f1>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            rightchain.get<f1Index>().get<f1>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            leftchain.get<f1Index>().get<f1>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            rightchain.get<f1Index>().get<f1>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            leftchain.get<f1Index>().get<f1>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, 0.707f);
            rightchain.get<f1Index>().get<f1>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[0].frequency, 0.707f);
        }
    }

    if (filterParams[1].bypass == 0)  // "Peak", "Low Shelf", "High Shelf", "Low Cut", "Low Cut x4", "High Cut", "High Cut x4"
    {
        leftchain.get<f1Index>().setBypassed<f2>(1);
        rightchain.get<f1Index>().setBypassed<f2>(1);
    }
    else
    {
        leftchain.get<f1Index>().setBypassed<f2>(0);
        rightchain.get<f1Index>().setBypassed<f2>(0);

        if (filterParams[1].type == 0)
        {
            leftchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[1].frequency, filterParams[1].q, dBtoGainFactor(filterParams[1].gain));
            rightchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[1].frequency, filterParams[1].q, dBtoGainFactor(filterParams[1].gain));
            leftchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
        }
        if (filterParams[1].type == 1)
        {
            leftchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[1].frequency, filterParams[1].q, dBtoGainFactor(filterParams[1].gain));
            rightchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[1].frequency, filterParams[1].q, dBtoGainFactor(filterParams[1].gain));
            leftchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
        }
        if (filterParams[1].type == 2)
        {
            leftchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[1].frequency, filterParams[1].q, dBtoGainFactor(filterParams[1].gain));
            rightchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[1].frequency, filterParams[1].q, dBtoGainFactor(filterParams[1].gain));
            leftchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
        }
        if (filterParams[1].type == 3)
        {
            leftchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, filterParams[1].q);
            rightchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, filterParams[1].q);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
        }
        
        if (filterParams[1].type == 4)
        {
            // make another 4x filter chain
            leftchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            rightchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope24>(0);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope24>(0);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope36>(0);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope36>(0);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope48>(0);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope48>(0);
            leftchain.get<f1Index>().get<f2>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            rightchain.get<f1Index>().get<f2>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            leftchain.get<f1Index>().get<f2>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            rightchain.get<f1Index>().get<f2>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            leftchain.get<f1Index>().get<f2>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            rightchain.get<f1Index>().get<f2>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[1].frequency, 0.707f);
        }
        
        if (filterParams[1].type == 5)
        {
            leftchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, filterParams[1].q);
            rightchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, filterParams[1].q);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope48>(1);
        }
        if (filterParams[1].type == 6)
		{
			// make another 4x filter chain
			leftchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, 0.707f);
			rightchain.get<f1Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope24>(0);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope24>(0);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope36>(0);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope36>(0);
            leftchain.get<f1Index>().get<f2>().setBypassed<slope48>(0);
            rightchain.get<f1Index>().get<f2>().setBypassed<slope48>(0);
            leftchain.get<f1Index>().get<f2>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            rightchain.get<f1Index>().get<f2>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            leftchain.get<f1Index>().get<f2>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            rightchain.get<f1Index>().get<f2>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            leftchain.get<f1Index>().get<f2>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, 0.707f);
            rightchain.get<f1Index>().get<f2>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[1].frequency, 0.707f);
		}
    }

    if (filterParams[2].bypass == 0)
    {
        leftchain.get<f1Index>().setBypassed<f3>(1);
        rightchain.get<f1Index>().setBypassed<f3>(1);
    }
    else
    {
        leftchain.get<f1Index>().setBypassed<f3>(0);
        rightchain.get<f1Index>().setBypassed<f3>(0);

        if (filterParams[2].type == 0)
        {
            leftchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[2].frequency, filterParams[2].q, dBtoGainFactor(filterParams[2].gain));
            rightchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[2].frequency, filterParams[2].q, dBtoGainFactor(filterParams[2].gain));
            leftchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
        }
        if (filterParams[2].type == 1)
        {
            leftchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[2].frequency, filterParams[2].q, dBtoGainFactor(filterParams[2].gain));
            rightchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[2].frequency, filterParams[2].q, dBtoGainFactor(filterParams[2].gain));
            leftchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
        }
        if (filterParams[2].type == 2)
        {
            leftchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[2].frequency, filterParams[2].q, dBtoGainFactor(filterParams[2].gain));
            rightchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[2].frequency, filterParams[2].q, dBtoGainFactor(filterParams[2].gain));
            leftchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
        }
        if (filterParams[2].type == 3)
        {
            leftchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, filterParams[2].q);
            rightchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, filterParams[2].q);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
        }
        if (filterParams[2].type == 4)
        {
            // make another 4x filter chain
            leftchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            rightchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope24>(0);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope24>(0);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope36>(0);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope36>(0);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope48>(0);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope48>(0);
            leftchain.get<f1Index>().get<f3>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            rightchain.get<f1Index>().get<f3>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            leftchain.get<f1Index>().get<f3>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            rightchain.get<f1Index>().get<f3>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            leftchain.get<f1Index>().get<f3>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            rightchain.get<f1Index>().get<f3>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[2].frequency, 0.707f);
        }
        if (filterParams[2].type == 5)
        {
            leftchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, filterParams[2].q);
            rightchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, filterParams[2].q);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope48>(1);
        }
        if (filterParams[2].type == 6)
		{
			// make another 4x filter chain
			leftchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, 0.707f);
			rightchain.get<f1Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope24>(0);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope24>(0);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope36>(0);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope36>(0);
            leftchain.get<f1Index>().get<f3>().setBypassed<slope48>(0);
            rightchain.get<f1Index>().get<f3>().setBypassed<slope48>(0);
            leftchain.get<f1Index>().get<f3>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            rightchain.get<f1Index>().get<f3>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            leftchain.get<f1Index>().get<f3>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            rightchain.get<f1Index>().get<f3>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            leftchain.get<f1Index>().get<f3>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, 0.707f);
            rightchain.get<f1Index>().get<f3>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[2].frequency, 0.707f);
		}
    }

    if (filterParams[3].bypass == 0)
    {
        leftchain.get<f1Index>().setBypassed<f4>(1);
        rightchain.get<f1Index>().setBypassed<f4>(1);
    }
    else
    {
        leftchain.get<f1Index>().setBypassed<f4>(0);
        rightchain.get<f1Index>().setBypassed<f4>(0);

        if (filterParams[3].type == 0)
        {
            leftchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[3].frequency, filterParams[3].q, dBtoGainFactor(filterParams[3].gain));
            rightchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[3].frequency, filterParams[3].q, dBtoGainFactor(filterParams[3].gain));
            leftchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[3].type == 1)
        {
            leftchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[3].frequency, filterParams[3].q, dBtoGainFactor(filterParams[3].gain));
            rightchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[3].frequency, filterParams[3].q, dBtoGainFactor(filterParams[3].gain));
            leftchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[3].type == 2)
        {
            leftchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[3].frequency, filterParams[3].q, dBtoGainFactor(filterParams[3].gain));
            rightchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[3].frequency, filterParams[3].q, dBtoGainFactor(filterParams[3].gain));
            leftchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[3].type == 3)
        {
            leftchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, filterParams[3].q);
            rightchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, filterParams[3].q);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[3].type == 4)
        {
            // make another 4x filter chain
            leftchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            rightchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope24>(0);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope24>(0);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope36>(0);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope36>(0);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope48>(0);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope48>(0);
            leftchain.get<f1Index>().get<f4>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            rightchain.get<f1Index>().get<f4>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            leftchain.get<f1Index>().get<f4>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            rightchain.get<f1Index>().get<f4>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            leftchain.get<f1Index>().get<f4>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            rightchain.get<f1Index>().get<f4>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[3].frequency, 0.707f);
        }
        if (filterParams[3].type == 5)
        {
            leftchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, filterParams[3].q);
            rightchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, filterParams[3].q);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[3].type == 6)
		{
			// make another 4x filter chain
			leftchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, 0.707f);
			rightchain.get<f1Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope24>(0);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope24>(0);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope36>(0);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope36>(0);
            leftchain.get<f1Index>().get<f4>().setBypassed<slope48>(0);
            rightchain.get<f1Index>().get<f4>().setBypassed<slope48>(0);
            leftchain.get<f1Index>().get<f4>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            rightchain.get<f1Index>().get<f4>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            leftchain.get<f1Index>().get<f4>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            rightchain.get<f1Index>().get<f4>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            leftchain.get<f1Index>().get<f4>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, 0.707f);
            rightchain.get<f1Index>().get<f4>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[3].frequency, 0.707f);
		}
    }

    if (filterParams[4].bypass == 0)
    {
        leftchain.get<f2Index>().setBypassed<f1>(1);
        rightchain.get<f2Index>().setBypassed<f1>(1);
    }
    else
    {
        leftchain.get<f2Index>().setBypassed<f1>(0);
        rightchain.get<f2Index>().setBypassed<f1>(0);

        if (filterParams[4].type == 0)
        {
            leftchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[4].frequency, filterParams[4].q, dBtoGainFactor(filterParams[4].gain));
            rightchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[4].frequency, filterParams[4].q, dBtoGainFactor(filterParams[4].gain));
            leftchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
        }
        if (filterParams[4].type == 1)
        {
            leftchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[4].frequency, filterParams[4].q, dBtoGainFactor(filterParams[4].gain));
            rightchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[4].frequency, filterParams[4].q, dBtoGainFactor(filterParams[4].gain));
            leftchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
        }
        if (filterParams[4].type == 2)
        {
            leftchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[4].frequency, filterParams[4].q, dBtoGainFactor(filterParams[4].gain));
            rightchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[4].frequency, filterParams[4].q, dBtoGainFactor(filterParams[4].gain));
            leftchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
        }
        if (filterParams[4].type == 3)
        {
            leftchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, filterParams[4].q);
            rightchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, filterParams[4].q);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
        }
        if (filterParams[4].type == 4)
        {
            // make another 4x filter chain
            leftchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            rightchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope24>(0);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope24>(0);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope36>(0);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope36>(0);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope48>(0);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope48>(0);
            leftchain.get<f2Index>().get<f1>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            rightchain.get<f2Index>().get<f1>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            leftchain.get<f2Index>().get<f1>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            rightchain.get<f2Index>().get<f1>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            leftchain.get<f2Index>().get<f1>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            rightchain.get<f2Index>().get<f1>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[4].frequency, 0.707f);
        }
        if (filterParams[4].type == 5)
        {
            leftchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, filterParams[4].q);
            rightchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, filterParams[4].q);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope48>(1);
        }
        if (filterParams[4].type == 6)
        {
            leftchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            rightchain.get<f2Index>().get<f1>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope24>(0);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope24>(0);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope36>(0);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope36>(0);
            leftchain.get<f2Index>().get<f1>().setBypassed<slope48>(0);
            rightchain.get<f2Index>().get<f1>().setBypassed<slope48>(0);
            leftchain.get<f2Index>().get<f1>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            rightchain.get<f2Index>().get<f1>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            leftchain.get<f2Index>().get<f1>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            rightchain.get<f2Index>().get<f1>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            leftchain.get<f2Index>().get<f1>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, 0.707f);
            rightchain.get<f2Index>().get<f1>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[4].frequency, 0.707f);
        }
    }

    if (filterParams[5].bypass == 0)
    {
        leftchain.get<f2Index>().setBypassed<f2>(1);
        rightchain.get<f2Index>().setBypassed<f2>(1);
    }
    else
    {
        leftchain.get<f2Index>().setBypassed<f2>(0);
        rightchain.get<f2Index>().setBypassed<f2>(0);

        if (filterParams[5].type == 0)
        {
            leftchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[5].frequency, filterParams[5].q, dBtoGainFactor(filterParams[5].gain));
            rightchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[5].frequency, filterParams[5].q, dBtoGainFactor(filterParams[5].gain));
            leftchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
        }
        if (filterParams[5].type == 1)
        {
            leftchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[5].frequency, filterParams[5].q, dBtoGainFactor(filterParams[5].gain));
            rightchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[5].frequency, filterParams[5].q, dBtoGainFactor(filterParams[5].gain));
            leftchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
        }
        if (filterParams[5].type == 2)
        {
            leftchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[5].frequency, filterParams[5].q, dBtoGainFactor(filterParams[5].gain));
            rightchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[5].frequency, filterParams[5].q, dBtoGainFactor(filterParams[5].gain));
            leftchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
        }
        if (filterParams[5].type == 3)
        {
            leftchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, filterParams[5].q);
            rightchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, filterParams[5].q);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
        }
        if (filterParams[5].type == 4)
        {
            // make another 4x filter chain
            leftchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            rightchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope24>(0);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope24>(0);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope36>(0);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope36>(0);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope48>(0);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope48>(0);
            leftchain.get<f2Index>().get<f2>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            rightchain.get<f2Index>().get<f2>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            leftchain.get<f2Index>().get<f2>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            rightchain.get<f2Index>().get<f2>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            leftchain.get<f2Index>().get<f2>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            rightchain.get<f2Index>().get<f2>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[5].frequency, 0.707f);
        }
        if (filterParams[5].type == 5)
        {
            leftchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, filterParams[5].q);
            rightchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, filterParams[5].q);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope48>(1);
        }
        if (filterParams[5].type == 6)
		{
			// make another 4x filter chain
			leftchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, 0.707f);
			rightchain.get<f2Index>().get<f2>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope24>(0);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope24>(0);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope36>(0);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope36>(0);
            leftchain.get<f2Index>().get<f2>().setBypassed<slope48>(0);
            rightchain.get<f2Index>().get<f2>().setBypassed<slope48>(0);
            leftchain.get<f2Index>().get<f2>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            rightchain.get<f2Index>().get<f2>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            leftchain.get<f2Index>().get<f2>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            rightchain.get<f2Index>().get<f2>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            leftchain.get<f2Index>().get<f2>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, 0.707f);
            rightchain.get<f2Index>().get<f2>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[5].frequency, 0.707f);
		}
    }

    if (filterParams[6].bypass == 0)
    {
        leftchain.get<f2Index>().setBypassed<f3>(1);
        rightchain.get<f2Index>().setBypassed<f3>(1);
    }
    else
    {
        leftchain.get<f2Index>().setBypassed<f3>(0);
        rightchain.get<f2Index>().setBypassed<f3>(0);

        if (filterParams[6].type == 0)
        {
            leftchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[6].frequency, filterParams[6].q, dBtoGainFactor(filterParams[6].gain));
            rightchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[6].frequency, filterParams[6].q, dBtoGainFactor(filterParams[6].gain));
            leftchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
        }
        if (filterParams[6].type == 1)
        {
            leftchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[6].frequency, filterParams[6].q, dBtoGainFactor(filterParams[6].gain));
            rightchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[6].frequency, filterParams[6].q, dBtoGainFactor(filterParams[6].gain));
            leftchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
        }
        if (filterParams[6].type == 2)
        {
            leftchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[6].frequency, filterParams[6].q, dBtoGainFactor(filterParams[6].gain));
            rightchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[6].frequency, filterParams[6].q, dBtoGainFactor(filterParams[6].gain));
            leftchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
            
        }
        if (filterParams[6].type == 3)
        {
            leftchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, filterParams[6].q);
            rightchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, filterParams[6].q);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
        }
        if (filterParams[6].type == 4)
        {
            // make another 4x filter chain
            leftchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            rightchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope24>(0);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope24>(0);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope36>(0);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope36>(0);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope48>(0);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope48>(0);
            leftchain.get<f2Index>().get<f3>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            rightchain.get<f2Index>().get<f3>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            leftchain.get<f2Index>().get<f3>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            rightchain.get<f2Index>().get<f3>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            leftchain.get<f2Index>().get<f3>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            rightchain.get<f2Index>().get<f3>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[6].frequency, 0.707f);
        }
        if (filterParams[6].type == 5)
        {
            leftchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, filterParams[6].q);
            rightchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, filterParams[6].q);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope48>(1);
        }
        if (filterParams[6].type == 6)
		{
			// make another 4x filter chain
			leftchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, 0.707f);
			rightchain.get<f2Index>().get<f3>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope24>(0);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope24>(0);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope36>(0);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope36>(0);
            leftchain.get<f2Index>().get<f3>().setBypassed<slope48>(0);
            rightchain.get<f2Index>().get<f3>().setBypassed<slope48>(0);
            leftchain.get<f2Index>().get<f3>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            rightchain.get<f2Index>().get<f3>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            leftchain.get<f2Index>().get<f3>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            rightchain.get<f2Index>().get<f3>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            leftchain.get<f2Index>().get<f3>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, 0.707f);
            rightchain.get<f2Index>().get<f3>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[6].frequency, 0.707f);
		}
    }

    if (filterParams[7].bypass == 0)
    {
        leftchain.get<f2Index>().setBypassed<f4>(1);
        rightchain.get<f2Index>().setBypassed<f4>(1);
    }
    else
    {
        leftchain.get<f2Index>().setBypassed<f4>(0);
        rightchain.get<f2Index>().setBypassed<f4>(0);

        if (filterParams[7].type == 0)
        {
            leftchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[7].frequency, filterParams[7].q, dBtoGainFactor(filterParams[7].gain));
            rightchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), filterParams[7].frequency, filterParams[7].q, dBtoGainFactor(filterParams[7].gain));
            leftchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[7].type == 1)
        {
            leftchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[7].frequency, filterParams[7].q, dBtoGainFactor(filterParams[7].gain));
            rightchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), filterParams[7].frequency, filterParams[7].q, dBtoGainFactor(filterParams[7].gain));
            leftchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[7].type == 2)
        {
            leftchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[7].frequency, filterParams[7].q, dBtoGainFactor(filterParams[7].gain));
            rightchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), filterParams[7].frequency, filterParams[7].q, dBtoGainFactor(filterParams[7].gain));
            leftchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[7].type == 3)
        {
            leftchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, filterParams[7].q);
            rightchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, filterParams[7].q);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[7].type == 4)
        {
            // make another 4x filter chain
            leftchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            rightchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope24>(0);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope24>(0);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope36>(0);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope36>(0);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope48>(0);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope48>(0);
            leftchain.get<f2Index>().get<f4>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            rightchain.get<f2Index>().get<f4>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            leftchain.get<f2Index>().get<f4>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            rightchain.get<f2Index>().get<f4>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            leftchain.get<f2Index>().get<f4>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            rightchain.get<f2Index>().get<f4>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), filterParams[7].frequency, 0.707f);
        }
        if (filterParams[7].type == 5)
        {
            leftchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, filterParams[7].q);
            rightchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, filterParams[7].q);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope24>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope36>(1);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope48>(1);
        }
        if (filterParams[7].type == 6)
		{
			// make another 4x filter chain
			leftchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, 0.707f);
			rightchain.get<f2Index>().get<f4>().get<slope12>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope24>(0);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope24>(0);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope36>(0);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope36>(0);
            leftchain.get<f2Index>().get<f4>().setBypassed<slope48>(0);
            rightchain.get<f2Index>().get<f4>().setBypassed<slope48>(0);
            leftchain.get<f2Index>().get<f4>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            rightchain.get<f2Index>().get<f4>().get<slope24>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            leftchain.get<f2Index>().get<f4>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            rightchain.get<f2Index>().get<f4>().get<slope36>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            leftchain.get<f2Index>().get<f4>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, 0.707f);
            rightchain.get<f2Index>().get<f4>().get<slope48>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), filterParams[7].frequency, 0.707f);
		}
    }

    //output gain connected
    leftchain.get<outgainIndex>().setGainDecibels(*treestate.getRawParameterValue("output gain"));
    rightchain.get<outgainIndex>().setGainDecibels(*treestate.getRawParameterValue("output gain"));
    leftchain.get<outgainIndex>().setRampDurationSeconds(0.005);
    rightchain.get<outgainIndex>().setRampDurationSeconds(0.005);
}

void EQChain2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EQChain2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void EQChain2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // audio block
    juce::dsp::AudioBlock<float> block(buffer);

    updateChain();

    //splitting block into left and right
    auto leftblock = block.getSingleChannelBlock(0);
    auto rightblock = block.getSingleChannelBlock(1);

    //wrapping blocks into context
    juce::dsp::ProcessContextReplacing<float> leftContext(leftblock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightblock);

    //process the context
    leftchain.process(leftContext);
    rightchain.process(rightContext);
   
}

//==============================================================================
bool EQChain2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EQChain2AudioProcessor::createEditor()
{
    return new EQChain2AudioProcessorEditor (*this);
    // return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void EQChain2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::MemoryOutputStream stream(destData, false);
    treestate.state.writeToStream(stream);
}

void EQChain2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));

    if (tree.isValid())
    {
        treestate.state = tree;
        ingain = *treestate.getRawParameterValue("input gain");
        filterParams[0].bypass = *treestate.getRawParameterValue("first bypass");
        filterParams[0].type = *treestate.getRawParameterValue("first filter type");
        filterParams[0].frequency = *treestate.getRawParameterValue("first freq");
        filterParams[0].gain = *treestate.getRawParameterValue("first gain");
        filterParams[0].q = *treestate.getRawParameterValue("first q");
        filterParams[1].bypass = *treestate.getRawParameterValue("second bypass");
        filterParams[1].type = *treestate.getRawParameterValue("second filter type");
        filterParams[1].frequency = *treestate.getRawParameterValue("second freq");
        filterParams[1].gain = *treestate.getRawParameterValue("second gain");
        filterParams[1].q = *treestate.getRawParameterValue("second q");
        filterParams[2].bypass = *treestate.getRawParameterValue("third bypass");
        filterParams[2].type = *treestate.getRawParameterValue("third filter type");
        filterParams[2].frequency = *treestate.getRawParameterValue("third freq");
        filterParams[2].gain = *treestate.getRawParameterValue("third gain");
        filterParams[2].q = *treestate.getRawParameterValue("third q");
        filterParams[3].bypass = *treestate.getRawParameterValue("fourth bypass");
        filterParams[3].type = *treestate.getRawParameterValue("fourth filter type");
        filterParams[3].frequency = *treestate.getRawParameterValue("fourth freq");
        filterParams[3].gain = *treestate.getRawParameterValue("fourth gain");
        filterParams[3].q = *treestate.getRawParameterValue("fourth q");

        filterParams[4].bypass = *treestate.getRawParameterValue("fifth bypass");
        filterParams[4].type = *treestate.getRawParameterValue("fifth filter type");
        filterParams[4].frequency = *treestate.getRawParameterValue("fifth freq");
        filterParams[4].gain = *treestate.getRawParameterValue("fifth gain");
        filterParams[4].q = *treestate.getRawParameterValue("fifth q");
        filterParams[5].bypass = *treestate.getRawParameterValue("sixth bypass");
        filterParams[5].type = *treestate.getRawParameterValue("sixth filter type");
        filterParams[5].frequency = *treestate.getRawParameterValue("sixth freq");
        filterParams[5].gain = *treestate.getRawParameterValue("sixth gain");
        filterParams[5].q = *treestate.getRawParameterValue("sixth q");
        filterParams[6].bypass = *treestate.getRawParameterValue("seventh bypass");
        filterParams[6].type = *treestate.getRawParameterValue("seventh filter type");
        filterParams[6].frequency = *treestate.getRawParameterValue("seventh freq");
        filterParams[6].gain = *treestate.getRawParameterValue("seventh gain");
        filterParams[6].q = *treestate.getRawParameterValue("seventh q");
        filterParams[7].bypass = *treestate.getRawParameterValue("eighth bypass");
        filterParams[7].type = *treestate.getRawParameterValue("eighth filter type");
        filterParams[7].frequency = *treestate.getRawParameterValue("eighth freq");
        filterParams[7].gain = *treestate.getRawParameterValue("eighth gain");
        filterParams[7].q = *treestate.getRawParameterValue("eighth q");
        outgain = *treestate.getRawParameterValue("output gain");
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EQChain2AudioProcessor();
}
