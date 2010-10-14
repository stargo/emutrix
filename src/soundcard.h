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

#ifndef SOUNDCARD_H
#define SOUNDCARD_H

#include <QString>
#include <QMap>
#include "alsa/asoundlib.h"
#include "mainwindow.h"

/** This class is a wrapper around ALSA functions.
  It is targeted at handling EMU cards only. Deals with initialization in constructor and
  offers reading and writing functionality.
  Callbacks are also handled by this class when requested through updateCallbacks()
  */
class SoundCard
{
public:
    /** Constructor.
      Initializes ALSA card. Pass as pointer to avoid creating and destroying ALSA handles.
      @param index is the ALSA card index
      */
    SoundCard(int index);
    /** Destructor.
      Frees ALSA card handles.
      */
    ~SoundCard();

    /** Setup ALSA callbacks.
      @param w is the mainwindow that should be modified with callbacks.
      Should this be moved to updateCallbacks()?
    */
    void setupCallbacks(MainWindow * w);

    /** Returns a list of card names & ALSA indices
      Ordered acording to ALSA index
      */
    static QList<QPair<QString, int> > getCardList();

    QString getName();

    /** Update ALSA callbacks
        Set to timeout when GUI stuff is idle. Updates
        ALSA status and polls any pending events, calling callbacks.
        Argument ignored.
        */
    void updateCallbacks();

    ///// VARIOUS ALSA WRITER FUNCTIONS
    /** Writes ALSA elements consisting of one or two integer values ("faders").
        Most elements we bother with right now are stereo, a few mono.
        This function handles both. Writes the same value to both channels.
        @param el Element name
        @param value Value to use for both channels
        Calls writeValue to do actual writing.
        */
    void writeStereoInt(const QString & el, int value);
    /** Toggles ALSA switches (single index)
        AKA boolean elements.
        @param el Element name
        Calls writeValue to do actual writing.
        */
    void writeBool(const QString & el, bool);
    /** Selects index from ALSA enumerated element
        Selects an item from a (mono) enumeration.
        Mostly for routing, but also used in clock rate selection.
        @param el Element to write to
        @i Index of enumerated selection
        Calls writeValue to do actual writing.
        */
    void writeEnum(const QString &el, int i);
    /** Same as writeEnum, but converting icon to alsa indices.*/
    void matrixWriteEnum(const QString & el, int i);

private:
    /** Does ALSA element writing
        Writes whatever is in the value private member to ALSA.
        @param el Element name
        Does no sanity checks, right now.
        */
    void writeValue(const QString &el);

private:
    //// ALSA CALLBACKS
    /** Set callback function for a given element
        This function takes an element name and a function which should
        be called each time the element value changes (Inside or outside
        emutrix.
        */
    void setAlsaCallback(const char * eln, snd_hctl_elem_callback_t cb);
    /** Read callback value.
        Reads the changed value from element el (if mask is proper),
        stored in value member. Returns MainWindow that changed, or NULL on
        error.
        */
    static SoundCard * readCallbackValue(snd_hctl_elem_t * el, unsigned int mask);
    /** Master change.
        This callback function gets called when master playback volume changes
        @see setAlsaCallback
        */
    static int alsaMasterChanged(snd_hctl_elem_t *elem, unsigned int mask);
    /** Clock rate change
        This callback function gets called when ALSA "Internal Clock Rate" element changes
        @see setAlsaCallback
        */
    static int alsaRateChanged(snd_hctl_elem_t *elem, unsigned int mask);
    /** Pad change.
        This callback function gets called when any pad changes state.
        @see setAlsaCallback
        */
    static int alsaPadChanged(snd_hctl_elem_t *elem, unsigned int mask);
    /** Routing changed
        This callback function gets called when an ALSA routing enumeration changes value.
        @see setAlsaCallback
        */
    static int alsaRoutingChanged(snd_hctl_elem_t *elem, unsigned int mask);

private:
    ///// ALSA HANDLES
    /** ALSA card index. */
    int index;
    /** Handle to ALSA High level control interface.
      Using this frees us from having to load an sort elements.
      Also has some caching features */
    snd_hctl_t * hctl;
    /** String to ALSA elements map.
        Makes accesing elements easier.
        Each element contains info about the type of the element
        (integer, boolean, int64, etc.), its "interface" (card, midi, timer, etc.),
        if it is locked, etc.
        This is loaded at start andwhenever switching cards, although it should
        not change.
        Several functions defined in this class allow for writing elements by QString
        */
    QMap<QString, snd_hctl_elem_t *> elements;
    /** ALSA element value.
        Reused in this class for all writes and reads.
        Contains one or more indexed values of whatever type the element understands.
        */
    snd_ctl_elem_value_t * value;
    /** Window that contains UI elements.
      Is modified on callbacks.
      */
    MainWindow * window;
};

#endif // SOUNDCARD_H
