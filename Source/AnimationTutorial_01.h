/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             AnimationTutorial
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Animates a fish.

 dependencies:     juce_core, juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2019, linux_make, xcode_iphone, androidstudio

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once

//==============================================================================
class MainContentComponent   : public juce::AnimatedAppComponent
{
public:

    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 400;

    //==============================================================================
    MainContentComponent()
    {
        setSize (SCREEN_WIDTH, SCREEN_HEIGHT);
        setFramesPerSecond (60);  
        
        initPosition();        
        move_count = 0;
        setLineColor();
    }

    void update() override
    {
        // This function is called at the frequency specified by the setFramesPerSecond() call
        // in the constructor. You can use it to update counters, animate values, etc.
    }

    void paint (juce::Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)

        g.fillAll (juce::Colours::black);
 
        g.setColour (lineColor);
        g.setFont (14.0f);
        g.drawText ("Hello, World!", getLocalBounds(), juce::Justification::centred, true);
        
        initPosition();
        const int MOVE = 5;
        const int LINE_WIDTH=1;
        
        for(int i = 0;i < move_count; ++i){
            g.drawLine (x0, y0, x1, y1, LINE_WIDTH);
            g.drawLine (x1, y1, x2, y2, LINE_WIDTH);
            g.drawLine (x2, y2, x3, y3, LINE_WIDTH);
            g.drawLine (x3, y3, x0, y0, LINE_WIDTH);

            x0 += MOVE;
            y1 += MOVE;
            x2 -= MOVE;
            y3 -= MOVE;
        }
        
        ++move_count;
        
        if(x0 >= SCREEN_WIDTH){
            move_count = 0;
            setLineColor();
        }

    
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)

    void initPosition()
    {
        x0 = 0; y0 = 0;
        x1 = SCREEN_WIDTH; y1 = 0;
        x2 = SCREEN_WIDTH; y2 = SCREEN_HEIGHT;
        x3 = 0; y3 = SCREEN_HEIGHT;
    }
    
    void setLineColor()
    {
        lineColor = juce::Colour(random.nextInt(255), random.nextInt(255), random.nextInt(255));
    }
    
    int x0, y0;
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int move_count;

    juce::Random random;
    juce::Colour lineColor;
    
};
