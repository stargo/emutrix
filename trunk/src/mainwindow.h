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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <QButtonGroup>
#include <QMap>
#include "alsa/asoundlib.h"

namespace Ui
{
    // Actual class definition generated automagically by qmake
    class MainWindow;
}

/** Program main window.
    Contains a hiddeable upper portion with general sound card controls.
    Below the matrix per se, and to the right a vertical bar with most
    frequently used buttons, and faders.
    Building the ui is handled by the ui element, defined in a file
    generated by qmake from mainwindow.ui
    */
class MainWindow : public QMainWindow
{
    /// This macro provides for Qt meta object handling and permits defining slots and signals
    Q_OBJECT

public:
    /** Overloaded default constructor.
        Setup happens here.
        Cards get loaded, timer started, functions to set defaults, etc.
        */
    MainWindow(QWidget *parent = 0);
    /** Destructor.
        Clean up here.
        */
    ~MainWindow();

private:
    /** Contains actual UI widgets.
        It is no neccesary to interacte directly with this.
        */
    Ui::MainWindow *ui;
    ///// ALSA HANDLES
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

    ///// GUI METHODS
    /** Displays error message popup.
        @param msg Message to display.
    */
    void showError(const QString & msg);
    /// Show or hide button groups (matrix columns), not implemented
    void setButtonGroupVisible(const QButtonGroup * bg, bool visible);

    /** Intialize ALSA card.
        Initialize card, load elements and register ALSA callbacks.
        @param index ALSA index for card.
    */
    void initCard(int index);
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
    void matrixWriteEnum(const QString & el, int i);
    /** Does ALSA element writing
        Writes whatever is in the value private member to ALSA.
        @param el Element name
        Does no sanity checks, right now.
        */
    void writeValue(const QString &el);

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
    static MainWindow * readCallbackValue(snd_hctl_elem_t * el, unsigned int mask);
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

    /** Timer event
        Timer event for this class. Set to timeout when GUI stuff is idle. Updates
        ALSA status and polls any pending events, calling callbacks.
        Argument ignored.
        */
    void timerEvent(QTimerEvent *);

private slots:
    /// Should set visible connectors
    void on_con0202_toggled(bool checked);
    /// Signaled by pad togglebuttons
    void on_dacpad_toggled(bool checked);
    void on_d1pad_toggled(bool checked);
    void on_d2pad_toggled(bool checked);
    void on_d3pad_toggled(bool checked);
    void on_d4pad_toggled(bool checked);
    void on_adcpadin_toggled(bool checked);
    void on_d1padin_toggled(bool checked);
    void on_d2padin_toggled(bool checked);
    void on_d3padin_toggled(bool checked);
    /// Signals from various widgets:
    /// Clock rate ComboBox
    void on_rate_currentIndexChanged(int index);
    /// Master fader
    void on_master_valueChanged(int value);
    /// Card switcher ComboBox
    void on_card_currentIndexChanged(int index);
    /// Panic button
    void on_panic_pressed();

    /// These are signaled by clicks on the matrix, each for one column (output)
    ///  b11 - b16: Alsa capture channels
    void on_b11_buttonClicked(int);
    void on_b12_buttonClicked(int);
    void on_b13_buttonClicked(int);
    void on_b14_buttonClicked(int);
    void on_b15_buttonClicked(int);
    void on_b16_buttonClicked(int);
    /// b0l, b0r: 0202 left & right DACs
    void on_b0l_buttonClicked(int);
    void on_b0r_buttonClicked(int);
    /// ba0 - ba7: 1010 ADAT ouput channels
    void on_ba0_buttonClicked(int);
    void on_ba1_buttonClicked(int);
    void on_ba2_buttonClicked(int);
    void on_ba3_buttonClicked(int);
    void on_ba4_buttonClicked(int);
    void on_ba5_buttonClicked(int);
    void on_ba6_buttonClicked(int);
    void on_ba7_buttonClicked(int);
    /// bsl, bsr: 1010 S/PDIF left & right
    void on_bsl_buttonClicked(int);
    void on_bsr_buttonClicked(int);
    /// b1l, b1r - b4l, b4r: Dock DACs 1-4, left & right
    void on_b1l_buttonClicked(int);
    void on_b1r_buttonClicked(int);
    void on_b2l_buttonClicked(int);
    void on_b2r_buttonClicked(int);
    void on_b3l_buttonClicked(int);
    void on_b3r_buttonClicked(int);
    void on_b4l_buttonClicked(int);
    void on_b4r_buttonClicked(int);
    /// bpl, bpr: Dock phones DAC, left & right
    void on_bpl_buttonClicked(int);
    void on_bpr_buttonClicked(int);
    /// bdsl, bsdr: Dock S/PDIF outputs, left & right
    void on_bdsl_buttonClicked(int);
    void on_bdsr_buttonClicked(int);
};

#endif // MAINWINDOW_H
