/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQChain2AudioProcessorEditor::EQChain2AudioProcessorEditor (EQChain2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    f1gKnobAttachment(audioProcessor.treestate, "first gain", f1gKnob),
    f1ToggleAttachment(audioProcessor.treestate, "first bypass", f1Toggle),
    f1fKnobAttachment(audioProcessor.treestate, "first freq", f1fKnob),
    f1qKnobAttachment(audioProcessor.treestate, "first q", f1qKnob),
    f2gKnobAttachment(audioProcessor.treestate, "second gain", f2gKnob),
    f2ToggleAttachment(audioProcessor.treestate, "second bypass", f2Toggle),
    f2fKnobAttachment(audioProcessor.treestate, "second freq", f2fKnob),
    f2qKnobAttachment(audioProcessor.treestate, "second q", f2qKnob),
    f3gKnobAttachment(audioProcessor.treestate, "third gain", f3gKnob),
    f3ToggleAttachment(audioProcessor.treestate, "third bypass", f3Toggle),
    f3fKnobAttachment(audioProcessor.treestate, "third freq", f3fKnob),
    f3qKnobAttachment(audioProcessor.treestate, "third q", f3qKnob),
    f4gKnobAttachment(audioProcessor.treestate, "fourth gain", f4gKnob),
    f4ToggleAttachment(audioProcessor.treestate, "fourth bypass", f4Toggle),
    f4fKnobAttachment(audioProcessor.treestate, "fourth freq", f4fKnob),
    f4qKnobAttachment(audioProcessor.treestate, "fourth q", f4qKnob),
    f5gKnobAttachment(audioProcessor.treestate, "fifth gain", f5gKnob),
    f5ToggleAttachment(audioProcessor.treestate, "fifth bypass", f5Toggle),
    f5fKnobAttachment(audioProcessor.treestate, "fifth freq", f5fKnob),
    f5qKnobAttachment(audioProcessor.treestate, "fifth q", f5qKnob),
    f6gKnobAttachment(audioProcessor.treestate, "sixth gain", f6gKnob),
    f6ToggleAttachment(audioProcessor.treestate, "sixth bypass", f6Toggle),
    f6fKnobAttachment(audioProcessor.treestate, "sixth freq", f6fKnob),
    f6qKnobAttachment(audioProcessor.treestate, "sixth q", f6qKnob),
    f7gKnobAttachment(audioProcessor.treestate, "seventh gain", f7gKnob),
    f7ToggleAttachment(audioProcessor.treestate, "seventh bypass", f7Toggle),
    f7fKnobAttachment(audioProcessor.treestate, "seventh freq", f7fKnob),
    f7qKnobAttachment(audioProcessor.treestate, "seventh q", f7qKnob),
    f8gKnobAttachment(audioProcessor.treestate, "eighth gain", f8gKnob),
    f8ToggleAttachment(audioProcessor.treestate, "eighth bypass", f8Toggle),
    f8fKnobAttachment(audioProcessor.treestate, "eighth freq", f8fKnob),
    f8qKnobAttachment(audioProcessor.treestate, "eighth q", f8qKnob),
    outgainSliderAttachment(audioProcessor.treestate, "output gain", outgainSlider)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    initializeKnob(f1fKnob, " Hz");
    initializeKnob(f2fKnob, " Hz");
    initializeKnob(f3fKnob, " Hz");
    initializeKnob(f4fKnob, " Hz");
    initializeKnob(f5fKnob, " Hz");
    initializeKnob(f6fKnob, " Hz");
    initializeKnob(f7fKnob, " Hz");
    initializeKnob(f8fKnob, " Hz");

    

    initializeKnob(f1gKnob, " dB");
    initializeKnob(f2gKnob, " dB");
    initializeKnob(f3gKnob, " dB");
    initializeKnob(f4gKnob, " dB");
    initializeKnob(f5gKnob, " dB");
    initializeKnob(f6gKnob, " dB");
    initializeKnob(f7gKnob, " dB");
    initializeKnob(f8gKnob, " dB");
    
    initializeKnob(f1qKnob);
    initializeKnob(f2qKnob);
    initializeKnob(f3qKnob);
    initializeKnob(f4qKnob);
    initializeKnob(f5qKnob);
    initializeKnob(f6qKnob);
    initializeKnob(f7qKnob);
    initializeKnob(f8qKnob);
    
    addAndMakeVisible(f1Toggle);
    f1Toggle.setButtonText("1");
    f1Toggle.addMouseListener(this, true);
    addAndMakeVisible(f2Toggle);
    f2Toggle.setButtonText("2");
    f2Toggle.addMouseListener(this, true);
    addAndMakeVisible(f3Toggle);
    f3Toggle.setButtonText("3");
    f3Toggle.addMouseListener(this, true);
    addAndMakeVisible(f4Toggle);
    f4Toggle.setButtonText("4");
    f4Toggle.addMouseListener(this, true);
    addAndMakeVisible(f5Toggle);
    f5Toggle.setButtonText("5");
    f5Toggle.addMouseListener(this, true);
    addAndMakeVisible(f6Toggle);
    f6Toggle.setButtonText("6");
    f6Toggle.addMouseListener(this, true);
    addAndMakeVisible(f7Toggle);
    f7Toggle.setButtonText("7");
    f7Toggle.addMouseListener(this, true);
    addAndMakeVisible(f8Toggle);
    f8Toggle.setButtonText("8");
    f8Toggle.addMouseListener(this, true);

    f1fKnob.setVisible(true);
    f1gKnob.setVisible(true);
    f1qKnob.setVisible(true);

    initializeMenu(f1typeMenu);
    f1typeMenu.addMouseListener(this, true);
    f1MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "first filter type", f1typeMenu);
    initializeMenu(f2typeMenu);
    f2typeMenu.addMouseListener(this, true);
    f2MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "second filter type", f2typeMenu);
    initializeMenu(f3typeMenu);
    f3typeMenu.addMouseListener(this, true);
    f3MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "third filter type", f3typeMenu);
    initializeMenu(f4typeMenu);
    f4typeMenu.addMouseListener(this, true);
    f4MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "fourth filter type", f4typeMenu);
    initializeMenu(f5typeMenu);
    f5typeMenu.addMouseListener(this, true);
    f5MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "fifth filter type", f5typeMenu);
    initializeMenu(f6typeMenu);
    f6typeMenu.addMouseListener(this, true);
    f6MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "sixth filter type", f6typeMenu);
    initializeMenu(f7typeMenu);
    f7typeMenu.addMouseListener(this, true);
    f7MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "seventh filter type", f7typeMenu);
    initializeMenu(f8typeMenu);
    f8typeMenu.addMouseListener(this, true);
    f8MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "eighth filter type", f8typeMenu);
    

    // resizing
    setResizable(true, true);
    setResizeLimits(650, 260, 750, 300);
    getConstrainer()->setFixedAspectRatio(2.5);
    setSize(650, 260);
}

EQChain2AudioProcessorEditor::~EQChain2AudioProcessorEditor()
{
    f1Toggle.removeMouseListener(this);
    f2Toggle.removeMouseListener(this);
    f3Toggle.removeMouseListener(this);
    f4Toggle.removeMouseListener(this);
    f5Toggle.removeMouseListener(this);
    f6Toggle.removeMouseListener(this);
    f7Toggle.removeMouseListener(this);
    f8Toggle.removeMouseListener(this);

    f1typeMenu.removeMouseListener(this);
    f2typeMenu.removeMouseListener(this);
    f3typeMenu.removeMouseListener(this);
    f4typeMenu.removeMouseListener(this);
    f5typeMenu.removeMouseListener(this);
    f6typeMenu.removeMouseListener(this);
    f7typeMenu.removeMouseListener(this);
    f8typeMenu.removeMouseListener(this);
}

//==============================================================================
void EQChain2AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // g.setColour (juce::Colours::white);
    // g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EQChain2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();
    auto filterSection = bounds.removeFromLeft(bounds.getWidth() / 6);
    
    f1fKnob.setBounds(filterSection.getX(), filterSection.getY(), filterSection.getWidth(), filterSection.getHeight() / 3);
    f1gKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f1qKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() * 2 / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f2fKnob.setBounds(filterSection.getX(), filterSection.getY(), filterSection.getWidth(), filterSection.getHeight() / 3);
    f2gKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f2qKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() * 2 / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f3fKnob.setBounds(filterSection.getX(), filterSection.getY(), filterSection.getWidth(), filterSection.getHeight() / 3);
    f3gKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f3qKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() * 2 / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f4fKnob.setBounds(filterSection.getX(), filterSection.getY(), filterSection.getWidth(), filterSection.getHeight() / 3);
    f4gKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f4qKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() * 2 / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f5fKnob.setBounds(filterSection.getX(), filterSection.getY(), filterSection.getWidth(), filterSection.getHeight() / 3);
    f5gKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f5qKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() * 2 / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f6fKnob.setBounds(filterSection.getX(), filterSection.getY(), filterSection.getWidth(), filterSection.getHeight() / 3);
    f6gKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f6qKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() * 2 / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f7fKnob.setBounds(filterSection.getX(), filterSection.getY(), filterSection.getWidth(), filterSection.getHeight() / 3);
    f7gKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f7qKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() * 2 / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f8fKnob.setBounds(filterSection.getX(), filterSection.getY(), filterSection.getWidth(), filterSection.getHeight() / 3);
    f8gKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() / 3, filterSection.getWidth(), filterSection.getHeight() / 3);
    f8qKnob.setBounds(filterSection.getX(), filterSection.getY() + filterSection.getHeight() * 2 / 3, filterSection.getWidth(), filterSection.getHeight() / 3);


    auto toggleLane = bounds.getWidth() / 8;
    f1typeMenu.setBounds(bounds.getX(), bounds.getY() + bounds.getHeight() / 4, toggleLane, bounds.getHeight() / 4);
    f2typeMenu.setBounds(bounds.getX() + toggleLane, bounds.getY() + bounds.getHeight() / 4, toggleLane, bounds.getHeight() / 4);
    f3typeMenu.setBounds(bounds.getX() + toggleLane * 2, bounds.getY() + bounds.getHeight() / 4, toggleLane, bounds.getHeight() / 4);
    f4typeMenu.setBounds(bounds.getX() + toggleLane * 3, bounds.getY() + bounds.getHeight() / 4, toggleLane, bounds.getHeight() / 4);
    f5typeMenu.setBounds(bounds.getX() + toggleLane * 4, bounds.getY() + bounds.getHeight() / 4, toggleLane, bounds.getHeight() / 4);
    f6typeMenu.setBounds(bounds.getX() + toggleLane * 5, bounds.getY() + bounds.getHeight() / 4, toggleLane, bounds.getHeight() / 4);
    f7typeMenu.setBounds(bounds.getX() + toggleLane * 6, bounds.getY() + bounds.getHeight() / 4, toggleLane, bounds.getHeight() / 4);
    f8typeMenu.setBounds(bounds.getX() + toggleLane * 7, bounds.getY() + bounds.getHeight() / 4, toggleLane, bounds.getHeight() / 4);

    f1Toggle.setBounds(bounds.getX(), bounds.getY() + bounds.getHeight() / 2, toggleLane, bounds.getHeight() / 4);
    f2Toggle.setBounds(bounds.getX() + toggleLane, bounds.getY() + bounds.getHeight() / 2, toggleLane, bounds.getHeight() / 4);
    f3Toggle.setBounds(bounds.getX() + toggleLane * 2, bounds.getY() + bounds.getHeight() / 2, toggleLane, bounds.getHeight() / 4);
    f4Toggle.setBounds(bounds.getX() + toggleLane * 3, bounds.getY() + bounds.getHeight() / 2, toggleLane, bounds.getHeight() / 4);
    f5Toggle.setBounds(bounds.getX() + toggleLane * 4, bounds.getY() + bounds.getHeight() / 2, toggleLane, bounds.getHeight() / 4);
    f6Toggle.setBounds(bounds.getX() + toggleLane * 5, bounds.getY() + bounds.getHeight() / 2, toggleLane, bounds.getHeight() / 4);
    f7Toggle.setBounds(bounds.getX() + toggleLane * 6, bounds.getY() + bounds.getHeight() / 2, toggleLane, bounds.getHeight() / 4);
    f8Toggle.setBounds(bounds.getX() + toggleLane * 7, bounds.getY() + bounds.getHeight() / 2, toggleLane, bounds.getHeight() / 4);
    
}

void EQChain2AudioProcessorEditor::mouseDown(const juce::MouseEvent& event)
{
    if (event.eventComponent == &f1Toggle || event.eventComponent == &f1typeMenu)
    {
        toggleKnobsVisibility(1, 0, 0, 0, 0, 0, 0, 0);
    }
    if (event.eventComponent == &f2Toggle || event.eventComponent == &f2typeMenu)
    {
        toggleKnobsVisibility(0, 1, 0, 0, 0, 0, 0, 0);
    }
    if (event.eventComponent == &f3Toggle || event.eventComponent == &f3typeMenu)
    {
        toggleKnobsVisibility(0, 0, 1, 0, 0, 0, 0, 0);
    }
    if (event.eventComponent == &f4Toggle || event.eventComponent == &f4typeMenu)
    {
        toggleKnobsVisibility(0, 0, 0, 1, 0, 0, 0, 0);
    }
    if (event.eventComponent == &f5Toggle || event.eventComponent == &f5typeMenu)
    {
        toggleKnobsVisibility(0, 0, 0, 0, 1, 0, 0, 0);
    }
    if (event.eventComponent == &f6Toggle || event.eventComponent == &f6typeMenu)
    {
        toggleKnobsVisibility(0, 0, 0, 0, 0, 1, 0, 0);
    }
    if (event.eventComponent == &f7Toggle || event.eventComponent == &f7typeMenu)
    {
        toggleKnobsVisibility(0, 0, 0, 0, 0, 0, 1, 0);
    }
    if (event.eventComponent == &f8Toggle || event.eventComponent == &f8typeMenu)
    {
        toggleKnobsVisibility(0, 0, 0, 0, 0, 0, 0, 1);
    }
}