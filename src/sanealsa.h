/*
 * Copyright 2010 Camilo Polymeris
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SANEALSA_H
#define SANEALSA_H

#include <QString>

/// ALSA elements to zero-out at start
const QString sanealsa_0[] = {
    //this is so that setting other faders to 100 won't blow the users ears
    "Master Playback Volume",
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
    // Empty string needed, acts as end marker.
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
    // Empty string needed, acts as end marker.
    ""
};

/// ALSA switches turned off at start
const QString sanealsa_false[] = {
    "Tone Control - Switch",
    "IEC958 Optical Raw Playback Switch",
    // Empty string needed, acts as end marker.
    ""
};



#endif // SANEALSA_H
