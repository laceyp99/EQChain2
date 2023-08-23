/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    {
    }
};

struct CustomHorizontalSlider : juce::Slider
{
    CustomHorizontalSlider() : juce::Slider(juce::Slider::SliderStyle::LinearHorizontal, juce::Slider::TextEntryBoxPosition::TextBoxAbove)
    {
    }
};



//==============================================================================
/**
*/
class EQChain2AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::MouseListener
{
public:
    EQChain2AudioProcessorEditor (EQChain2AudioProcessor&);
    ~EQChain2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event);
    
    void EQChain2AudioProcessorEditor::toggleKnobsVisibility(bool f1Visible, bool f2Visible, bool f3Visible, bool f4Visible, bool f5Visible, bool f6Visible, bool f7Visible, bool f8Visible)
    {
        f1fKnob.setVisible(f1Visible);
        f1gKnob.setVisible(f1Visible);
        f1qKnob.setVisible(f1Visible);

        f2fKnob.setVisible(f2Visible);
        f2gKnob.setVisible(f2Visible);
        f2qKnob.setVisible(f2Visible);

        f3fKnob.setVisible(f3Visible);
        f3gKnob.setVisible(f3Visible);
        f3qKnob.setVisible(f3Visible);

        f4fKnob.setVisible(f4Visible);
        f4gKnob.setVisible(f4Visible);
        f4qKnob.setVisible(f4Visible);

        f5fKnob.setVisible(f5Visible);
        f5gKnob.setVisible(f5Visible);
        f5qKnob.setVisible(f5Visible);

        f6fKnob.setVisible(f6Visible);
        f6gKnob.setVisible(f6Visible);
        f6qKnob.setVisible(f6Visible);

        f7fKnob.setVisible(f7Visible);
        f7gKnob.setVisible(f7Visible);
        f7qKnob.setVisible(f7Visible);

        f8fKnob.setVisible(f8Visible);
        f8gKnob.setVisible(f8Visible);
        f8qKnob.setVisible(f8Visible);
    }


    void initializeKnob(CustomRotarySlider& knob, juce::String suffix = "")
    {
        addChildComponent(knob);
        knob.setTextValueSuffix(suffix);
        knob.setTextBoxIsEditable(true);
        knob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    };

    void initializeMenu(juce::ComboBox& menu)
    {
		addAndMakeVisible(menu);
		menu.addItem("Peak", 1);
        menu.addItem("Low Shelf", 2);
        menu.addItem("High Shelf", 3);
        menu.addItem("Low Cut", 4);
        menu.addItem("Low Cut x4", 5);
        menu.addItem("High Cut", 6);
        menu.addItem("High Cut x4", 7);
		menu.setSelectedId(1);
	};

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EQChain2AudioProcessor& audioProcessor;

    //vertical fader
    //CustomVerticalSlider f1gSlider, f2gSlider, f3gSlider, f4gSlider, f5gSlider, f6gSlider, f7gSlider, f8gSlider;
    CustomHorizontalSlider outgainSlider;

    //rotary knob
    CustomRotarySlider f1fKnob, f2fKnob, f3fKnob, f4fKnob, f5fKnob, f6fKnob, f7fKnob, f8fKnob,
        f1qKnob, f2qKnob, f3qKnob, f4qKnob, f5qKnob, f6qKnob, f7qKnob, f8qKnob,
        f1gKnob, f2gKnob, f3gKnob, f4gKnob, f5gKnob, f6gKnob, f7gKnob, f8gKnob;

    // drop down menus
    juce::ComboBox f1typeMenu, f2typeMenu, f3typeMenu, f4typeMenu, f5typeMenu, f6typeMenu, f7typeMenu, f8typeMenu;

    //bypass buttons
    juce::ToggleButton f1Toggle, f2Toggle, f3Toggle, f4Toggle, f5Toggle, f6Toggle, f7Toggle, f8Toggle;

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;
    using ToggleAttachment = APVTS::ButtonAttachment;
    using MenuAttachment = APVTS::ComboBoxAttachment;
    // using Border = juce::GroupComponent;

    // building attachments to audio processor
    Attachment f1gKnobAttachment, f1fKnobAttachment, f1qKnobAttachment, f2gKnobAttachment, f2fKnobAttachment, f2qKnobAttachment,
        f3gKnobAttachment, f3fKnobAttachment, f3qKnobAttachment, f4gKnobAttachment, f4fKnobAttachment, f4qKnobAttachment,
        f5gKnobAttachment, f5fKnobAttachment, f5qKnobAttachment, f6gKnobAttachment, f6fKnobAttachment, f6qKnobAttachment,
        f7gKnobAttachment, f7fKnobAttachment, f7qKnobAttachment, f8gKnobAttachment, f8fKnobAttachment, f8qKnobAttachment,
        outgainSliderAttachment;
    ToggleAttachment f1ToggleAttachment, f2ToggleAttachment, f3ToggleAttachment, f4ToggleAttachment,
        f5ToggleAttachment, f6ToggleAttachment, f7ToggleAttachment, f8ToggleAttachment;

    // Border gainBorder, freqBorder, qBorder, outgainBorder;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> f1MenuAttachment, f2MenuAttachment, f3MenuAttachment, f4MenuAttachment,
        f5MenuAttachment, f6MenuAttachment, f7MenuAttachment, f8MenuAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQChain2AudioProcessorEditor)
};
