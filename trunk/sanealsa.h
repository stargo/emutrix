#ifndef SANEALSA_H
#define SANEALSA_H

/// ALSA elements to zero-out at start
const QString sanealsa_0[] = {
    "Master Playback Volume", //this is so that setting other faders to 100 won't blow the users ears
    "PCM Capture Volume",
    "Synth Playback Volume",
    "Synth Capture Volume",
    "Line Playback Volume",
    "Line Capture Volume",
    "CD Playback Volume",
    "CD Capture Volume",
    "Mic Playback Volume",
    "Mic Capture Volume",
    "Aux Playback Volume",
    "Aux Capture Volume",
    "IEC958 Optical Capture Volume",
    "IEC958 Optical Playback Volume",
    "Analog Mix Capture Volume",
    "Analog Mix Playback Volume",
    ""
};

/// ALSA levels set at 100 during start
const QString sanealsa_100[] = {
    "PCM Center Playback Volume",
    "PCM Front Playback Volume",
    "PCM LFE Playback Volume",
    "PCM Side Playback Volume",
    "PCM Surround Playback Volume",
    "PCM Playback Volume",
    "Front Playback Volume",
    "Surround Playback Volume",
    "Center Playback Volume",
    "LFE Playback Volume",
    ""
};

/// ALSA switches turned off at start
const QString sanealsa_false[] = {
    "Tone Control - Switch",
    "IEC958 Optical Raw Playback Switch",
    ""
};



#endif // SANEALSA_H
