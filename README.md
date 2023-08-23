# EQChain2

This project is an update to my previous EQChain plugin I made that was inspired by Ableton Live's EQ Eight. The EQ controls eight bands with non-linear phase. The update was focused on making the GUI and processing closer to the user experience of using EQ Eight. 

# Updates

The "High Cut x4" and "Low Cut x4" filter types have been added, which involves a slope change from 12dB/oct to 48dB/oct. When operating a filter using the x4 filter types, the Q is not adjustable. If you are trying to create a resonance bump within your high/low cut filter, please use the normal high/low pass filter type from which you can adjust the Q.

Each band has the whole range of filter type options ("Peak", "Low Shelf", "High Shelf", "Low Cut", "Low Cut x4", "High Cut", "High Cut x4"), and each band is initialized with a specific frequency, but each filter has 20 - 20k Hz frequency ranges.

The GUI now consists of a singular frequency, gain, and Q knob that switches between the selected filter at the time. The "Bypass" buttons for each filter are flipped in logic and now act more as a "On/Off" button where when the button is checked, the filter is not bypassed, and when the button is unchecked, the filter is bypassed. You can switch between filters by toggling the button, or clicking the drop down arrow of the filter type menu of the desired filter.

Multiple functions and objects were created to clean up the code which makes it easier to read.

# Requirements

To use this audio plugin, you will need a Digital Audio Workstation (DAW) that supports VST, VST3, or AU plugin formats. The plugin was built and tested on Windows, but should also work on Mac and Linux systems.

# Installation

To install the plugin, simply take the source files and replace them in your own project. Build the VST or AU version of the project, then copy the plugin file to your DAW's plugin folder. The plugin file will have the appropriate extension depending on the format you choose. Once the plugin is in the correct plugin folder, you can use it in your DAW like any other audio effect plugin.
