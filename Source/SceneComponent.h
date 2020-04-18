/*
  ==============================================================================

    SceneComponent.h
    Created: 15 Mar 2019 5:39:56pm
    Author:  Matteo Scerbo (matteo.scerbo@mail.polimi.it)
    Author:  Luca Bondi (luca.bondi@polimi.it)

  ==============================================================================
*/

#pragma once

#define PLANAR_MODE

#define PERSPECTIVE_RATIO 5

#define TILE_ROW_COUNT 7
#define TILE_COL_COUNT 25

#define SCENE_WIDTH 460

#ifdef PLANAR_MODE
#define GUI_HEIGHT 830
#define SCENE_HEIGHT 230
#else
#define GUI_HEIGHT 980
#define SCENE_HEIGHT 460
#endif

#define GRID_REFRESH_TIMER 50

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "AudioComponents.h"
#include "DOAthread.h"

//==============================================================================

class TileComponent    : public Component
{
public:
    
    juce::Point<float> corners[2][2];
    Colour tileColour;
    
    TileComponent();
    ~TileComponent();
    
    void paint(Graphics&) override;
    void resized() override;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TileComponent)
};

//==============================================================================

class GridComponent    : public Component, public Timer
{
public:
    GridComponent();
    ~GridComponent();
    
    void resized() override;
    
    void setSource(std::shared_ptr<DOAthread> d){doaThread = d;};
    
private:
    
    TileComponent tiles[TILE_ROW_COUNT][TILE_COL_COUNT];
    juce::Point<float> vertices[TILE_ROW_COUNT+1][TILE_COL_COUNT+1];
    
    std::shared_ptr<DOAthread> doaThread;
    
    std::vector<float> th;
    
    void computeVertices();
    void timerCallback() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridComponent)
};

//==============================================================================

class BeamComponent    : public Component
{
public:
    BeamComponent();
    ~BeamComponent();
    
    void paint(Graphics&) override;
    void resized() override;
    
    void move(float);
    void scale(float);
    void setStatus(bool);
    
    void setBaseColor(Colour colour){baseColour = colour;}
    
private:
    
    float position;
    float width;
    bool status;
    
    Colour baseColour = Colours::lightblue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeamComponent)
};

//==============================================================================

class SceneComponent    : public Component
{
public:
    SceneComponent();
    ~SceneComponent();
    
    void setBeamColors(const std::vector<Colour> &colours);
    
    void paint(Graphics&) override;
    void resized() override;
    
    GridComponent grid;
    BeamComponent beams[EbeamerAudioProcessor::numBeams];
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SceneComponent)
};
