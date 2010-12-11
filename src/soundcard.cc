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

#include "soundcard.h"
#include "sanealsa.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>

/// call ALSA function or die trying.
void tryAlsa(int err)
{
    if (err)
        throw QString("ALSA Error: ") + snd_strerror(err);
}

QList<QPair<QString, int> > SoundCard::getCardList()
{

    QList<QPair<QString, int> > list;

    // Look for soundcards
    qDebug("Checking soundcards...");
    int i = 0;
    char * name;
    do {
        snd_card_get_name(i, &name);
        qDebug() << "Found soundcard #" << i << ": " << name;
         // Simple check, may not be enough to see if card is compatible
        if (QString(name).startsWith(QLatin1String("E-mu 1010"))
            || QString(name).startsWith(QLatin1String("E-mu 0404")))
            list.append(QPair<QString, int>(name, i)); // I only have one card, so haven't seen if this works
        tryAlsa(snd_card_next(&i)); // hendryx pointed out a bug with the previous implementation, hope this works
    } while (i >= 0);

    return list;
}

SoundCard::SoundCard(int index) : index(index), hctl(NULL), window(NULL)
{
    // Create a new element_value object, use thorugh this class to write to ALSA mixer
    tryAlsa(snd_ctl_elem_value_malloc(&value));
    qDebug("Opening card...");
    QString name = QString("hw:") + QString().number(index);
    if (snd_hctl_open(&hctl, name.toLatin1().data(), SND_CTL_NONBLOCK))
        throw "Oops. Couldn't access sound card.";
    qDebug("Loading card elements...");
    tryAlsa(snd_hctl_load(hctl));
    // Populate elements map to make stuff easier in the future
    elements.clear();
    for (snd_hctl_elem_t * el = snd_hctl_first_elem(hctl);
      el != snd_hctl_last_elem(hctl);
      el = snd_hctl_elem_next(el))
        elements.insert(snd_hctl_elem_get_name(el), el);
    qDebug() << elements.size() << " elements loaded. Setting start defaults...;";
    // Set "sane" values, mostly to elements not controllable from within the program
    for (int i = 0; sanealsa_0[i] != ""; i++)
        writeStereoInt(sanealsa_0[i], 0);
    for (int i = 0; sanealsa_100[i] != ""; i++)
        writeStereoInt(sanealsa_100[i], 100);
    for (int i = 0; sanealsa_false[i] != ""; i++)
        writeBool(sanealsa_false[i], false);
}

SoundCard::~SoundCard()
{
    snd_ctl_elem_value_free(value);
    if (hctl)
      snd_hctl_free(hctl);
}

QString SoundCard::getName()
{
    char * name;
    assert(!snd_card_get_name(index, &name));
    return QString(name);
}

void SoundCard::setupCallbacks(MainWindow * w)
{
    window = w;
    qDebug("Registering callbacks with ALSA");
    assert(!elements.empty());
    // Setup ALSA callbacks for two special controls... Also sets initial values with a fake callback
    setAlsaCallback("Master Playback Volume", (snd_hctl_elem_callback_t)&SoundCard::alsaMasterChanged);
    setAlsaCallback("Clock Internal Rate", &SoundCard::alsaRateChanged);
    // ..and for all those pads and routing enums.
    for (QMap<QString, snd_hctl_elem_t *>::iterator it = elements.begin();
        it != elements.end();
        ++it)
        if (it.key().contains("PAD"))
            setAlsaCallback(it.key().toLatin1().data(), &SoundCard::alsaPadChanged);
        else if (it.key().endsWith("Enum"))
            setAlsaCallback(it.key().toLatin1().data(), &SoundCard::alsaRoutingChanged);
}

void SoundCard::updateCallbacks()
{
    // qDebug("Timer click!");
    // Handle ALSA callbacks.
    if (snd_hctl_wait(hctl, 10))
        snd_hctl_handle_events(hctl);
    // Workaround for driver bug: The driver doesn't report pad changes.
    // Poll manually.
    for (QMap<QString, snd_hctl_elem_t *>::iterator it = elements.begin();
        it != elements.end();
        ++it)
        if (it.key().contains("PAD"))
            alsaPadChanged(it.value(), SND_CTL_EVENT_MASK_VALUE);
}

void SoundCard::setAlsaCallback(const char * eln, snd_hctl_elem_callback_t cb)
{
  //  qDebug() << "Setting up " << eln << " callback...";
    snd_hctl_elem_t * el = elements.find(eln).value();
    // SoundCard is passed as private to static callbacks.
    snd_hctl_elem_set_callback_private(el, this);
    snd_hctl_elem_set_callback(el, cb);
    // Fake callback to read initial values
   // qDebug() << "Reading initial status";
    cb(el, SND_CTL_EVENT_MASK_VALUE);
}

///// GENERIC ALSA WRITERS
void SoundCard::writeValue(const QString &el)
{
        //qDebug() << "Writing to "<< el << " ALSA element.";
        if (elements.contains(el))
            assert(snd_hctl_elem_write(elements.find(el).value(), value) >= 0);
        else
            qDebug() << "Warning: Element " << el << " not available!";
}

void SoundCard::writeStereoInt(const QString & el, int v)
{
    /* Allmost all E-mu faders are stereo, exceptions are [PCM] {Center|LFE} Playback Volume and Master Playback Volume (mono),
    and of course all those pesky Multichannel Routing/Volume thingies, with witch we don't bother right now. Mono faders
    work with this, too. */
    //TODO check if the element is the right type
    //qDebug() << "Stereo faders " << el << " to " << v;
    snd_ctl_elem_value_set_integer(value, 0, v);
    snd_ctl_elem_value_set_integer(value, 1, v);
    writeValue(el);
}

// Set or unsets generic alsa switches
void SoundCard::writeBool(const QString & s, bool a)
{
    snd_ctl_elem_value_set_boolean(value, 0, a);
    writeValue(s);
}

void SoundCard::writeEnum(const QString & e, int i)
{
    snd_ctl_elem_value_set_enumerated(value, 0, i);
    writeValue(e);
}

void SoundCard::matrixWriteEnum(const QString & e, int i)
{
    // Translate QButtonGroup indices to alsa enumeration indices. Let's only hope both are constant across environments.
    int alsai = -(i+2);
    // Write them and cross fingers.
    writeEnum(e, alsai);
}

////// ALSA CALLBACKS

SoundCard * SoundCard::readCallbackValue(snd_hctl_elem_t * el, unsigned int mask)
{
    if (mask != SND_CTL_EVENT_MASK_VALUE)
        return NULL;
    SoundCard * c = (SoundCard * )snd_hctl_elem_get_callback_private(el);
    assert(c);
    tryAlsa(snd_hctl_elem_read(el, c->value));
    return c;
}

int SoundCard::alsaMasterChanged(snd_hctl_elem_t * elem, unsigned int mask)
{
    SoundCard * c = readCallbackValue(elem, mask);
    if (!c)
        return 0;
    int value = snd_ctl_elem_value_get_integer(c->value, 0);
   // qDebug() << "Master volume changed to " << value;
    c->window->ui->master->setValue(value);
    return 0;
}

int SoundCard::alsaRateChanged(snd_hctl_elem_t *elem, unsigned int mask)
{
    SoundCard * c = readCallbackValue(elem, mask);
    if (!c)
        return 0;
    qDebug("Clock rate changed.");
    int ix = snd_ctl_elem_value_get_enumerated(c->value, 0);
    // Set Index, unless it is S/PDIF or ADAT!
    // FIXME
    if (ix <= c->window->ui->rate->count() - 1)
        c->window->ui->rate->setCurrentIndex(ix);
    return 0;
}

int SoundCard::alsaPadChanged(snd_hctl_elem_t *elem, unsigned int mask)
{
    // FIXME this dosen't work. Neither way: emutrix->alsamixer or
    // alsamixer->emutrix. Function never gets called, unless
    // explicitely. Why?
    SoundCard * c = readCallbackValue(elem, mask);
    QString ename = snd_hctl_elem_get_name(elem);
    QAbstractButton * button = NULL;
    if (!c)
        return 0;
    bool pad = snd_ctl_elem_value_get_boolean(c->value, 0);
    MainWindow * w = c->window;
    // Commenting this out, too many calls to this function because of
    // driver bug workaround polute stdout.
    // qDebug() << ename << " changed to " << pad;
    if (ename == "ADC1 14dB PAD Audio Dock Capture Switch")
        button = w->ui->d1padin;
    else if (ename == "ADC2 14dB PAD Audio Dock Capture Switch")
        button = w->ui->d2padin;
    else if (ename == "ADC3 14dB PAD Audio Dock Capture Switch")
        button = w->ui->d3padin;
    else if (ename == "ADC1 14dB PAD 0202 Capture Switch")
        button = w->ui->adcpadin;
    else if (ename == "DAC1 Audio Dock 14dB PAD Playback Switch")
        button = w->ui->d1pad;
    else if (ename == "DAC2 Audio Dock 14dB PAD Playback Switch")
        button = w->ui->d2pad;
    else if (ename == "DAC3 Audio Dock 14dB PAD Playback Switch")
        button = w->ui->d3pad;
    else if (ename == "DAC4 Audio Dock 14dB PAD Playback Switch")
        button = w->ui->d4pad;
    else if (ename == "DAC1 0202 14dB PAD Playback Switch")
        button = w->ui->dacpad;
    else
        qDebug() << "No pad callback for element " << snd_hctl_elem_get_name(elem);

    if (button)
        button->setChecked(pad);
    return 0;
}

int SoundCard::alsaRoutingChanged(snd_hctl_elem_t *elem, unsigned int mask)
{
    SoundCard * c = readCallbackValue(elem, mask);
    if (!c)
        return 0;
    MainWindow * w = c->window;
    QButtonGroup * bg = NULL;
    QString ename = snd_hctl_elem_get_name(elem);
    int ix = snd_ctl_elem_value_get_enumerated(c->value, 0);
    // Convert ALSA index to button index
    ix = -(ix + 2);
    qDebug() << ename << " routing to " << ix;
    if (ename == "DSP A Capture Enum")
        bg = w->ui->b11;
    else if (ename == "DSP B Capture Enum")
        bg = w->ui->b12;
    else if (ename == "DSP C Capture Enum")
        bg = w->ui->b13;
    else if (ename == "DSP D Capture Enum")
        bg = w->ui->b14;
    else if (ename == "DSP E Capture Enum")
        bg = w->ui->b15;
    else if (ename == "DSP F Capture Enum")
        bg = w->ui->b16;
    else if (ename == "0202 DAC Left Playback Enum")
        bg = w->ui->b0l;
    else if (ename == "0202 DAC Right Playback Enum")
        bg = w->ui->b0r;
    else if (ename == "1010 ADAT 0 Playback Enum")
        bg = w->ui->ba0;
    else if (ename == "1010 ADAT 1 Playback Enum")
        bg = w->ui->ba1;
    else if (ename == "1010 ADAT 2 Playback Enum")
        bg = w->ui->ba2;
    else if (ename == "1010 ADAT 3 Playback Enum")
        bg = w->ui->ba3;
    else if (ename == "1010 ADAT 4 Playback Enum")
        bg = w->ui->ba4;
    else if (ename == "1010 ADAT 5 Playback Enum")
        bg = w->ui->ba5;
    else if (ename == "1010 ADAT 6 Playback Enum")
        bg = w->ui->ba6;
    else if (ename == "1010 ADAT 7 Playback Enum")
        bg = w->ui->ba7;
    else if (ename == "1010 SPDIF Left Playback Enum")
        bg = w->ui->bsl;
    else if (ename == "1010 SPDIF Right Playback Enum")
        bg = w->ui->bsr;
    else if (ename == "Dock DAC1 Left Playback Enum")
        bg = w->ui->b1l;
    else if (ename == "Dock DAC1 Right Playback Enum")
        bg = w->ui->b1r;
    else if (ename == "Dock DAC2 Left Playback Enum")
        bg = w->ui->b2l;
    else if (ename == "Dock DAC2 Right Playback Enum")
        bg = w->ui->b2r;
    else if (ename == "Dock DAC3 Left Playback Enum")
        bg = w->ui->b3l;
    else if (ename == "Dock DAC3 Right Playback Enum")
        bg = w->ui->b3r;
    else if (ename == "Dock DAC4 Left Playback Enum")
        bg = w->ui->b4l;
    else if (ename == "Dock DAC4 Right Playback Enum")
        bg = w->ui->b4r;
    else if (ename == "Dock Phones Left Playback Enum")
        bg = w->ui->bpl;
    else if (ename == "Dock Phones Right Playback Enum")
        bg = w->ui->bpr;
    else if (ename == "Dock SPDIF Left Playback Enum")
        bg = w->ui->bdsl;
    else if (ename == "Dock SPDIF Right Playback Enum")
        bg = w->ui->bdsr;
    else
    {
        qDebug() << "No routing callback for element " << ename;
        return 0;
    }

    // Make sure ix does make reference to an available button
    if (bg->button(ix))
        bg->button(ix)->setChecked(true);
    // or else uncheck all buttons.
    else
        bg->checkedButton()->setChecked(false);
    return 0;
}
