#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QErrorMessage>
#include <QDebug>
#include "sanealsa.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), hctl(NULL)
{
    // Create a new element_value object, use thorugh this class to write to ALSA mixer
    assert(!snd_ctl_elem_value_malloc(&value));
    qDebug("Setting up UI...");
    // Qt creator magic
    ui->setupUi(this);
    QComboBox * cardsBox = this->findChild<QComboBox*>("card");
    // Hide "setup" (that is, extended settings, frame)
    this->findChild<QWidget*>("setupWidget")->setVisible(false);
    // Look for soundcards
    qDebug("Checking soundcards...");
    int i = 0;
    char * name;
    do {
        assert(!snd_card_get_name(i, &name));
        qDebug() << "Found soundcard #" << i << ": " << name;
        if (QString(name).startsWith(QLatin1String("E-mu 1010"))) // Simple check, may not be enough to see if card is compatible
            cardsBox->addItem(QString().number(i) + " - " + name, i); // I only have one card, so haven't seen if this works
    } while (snd_card_next(&i));

    if (cardsBox->count() == 0)
    {
        showError(tr("Sorry! No EMU 1010 based cards found."));
        return;
    }
    cardsBox->setCurrentIndex(0); // Calls code to initialize first card.

    qDebug("Setting start defaults...");
    // Set "sane" values, mostly to elements not controllable from within the program
    for (int i = 0; sanealsa_0[i] != ""; i++)
        writeStereoInt(sanealsa_0[i], 0);
    for (int i = 0; sanealsa_100[i] != ""; i++)
        writeStereoInt(sanealsa_100[i], 100);
    for (int i = 0; sanealsa_false[i] != ""; i++)
        writeBool(sanealsa_false[i], false);

    qDebug("Registering callbacks with ALSA");
    assert(!elements.empty());
    // Setup ALSA callbacks
    setAlsaCallback("Master Playback Volume", (snd_hctl_elem_callback_t)&MainWindow::alsaMasterChanged);
    startTimer(0);
}

MainWindow::~MainWindow()
{
    qDebug("Cleaning up...");
    delete  callbackTimer;
    snd_ctl_elem_value_free(value);
    if (hctl)
      snd_hctl_free(hctl);
    delete ui;
}

////////// ERROR HANDLING
void MainWindow::showError(const QString & msg)
{
      qDebug() << "Error: " << msg;
      QErrorMessage * err = new QErrorMessage(this);
      err->showMessage(msg);
}

//// RANDOM HELPER FUNCTIONS
void MainWindow::setButtonGroupVisible(const QButtonGroup * bg, bool visible)
{
    /*for (QList<QWidget*>::iterator it = bg->buttons().begin();
        it != bg->buttons().end(); ++it)
        (*it)->setVisible(visible);*/
}

void MainWindow::timerEvent(QTimerEvent *)
{
    // qDebug("Timer click!");
    // Handle ALSA callbacks.
    if (snd_hctl_wait(hctl, 10))
        snd_hctl_handle_events(hctl);
}

void MainWindow::setAlsaCallback(const char * eln, snd_hctl_elem_callback_t cb)
{
    qDebug() << "Setting up " << eln << " callback...";
    snd_hctl_elem_t * el = elements.find(eln).value();
    snd_hctl_elem_set_callback_private(el, this);
    snd_hctl_elem_set_callback(el, cb);
}

///// GENERIC ALSA WRITERS
void MainWindow::writeValue(const QString &el)
{
        qDebug() << "Writing to "<< el << " ALSA element.";
        assert(elements.contains(el));
        assert(snd_hctl_elem_write(elements.find(el).value(), value) >= 0);
}

void MainWindow::writeStereoInt(const QString & el, int v)
{
    /* Allmost all E-mu faders are stereo, exceptions are [PCM] {Center|LFE} Playback Volume and Master Playback Volume (mono),
    and of course all those pesky Multichannel Routing/Volume thingies, with witch we don't bother right now. Mono faders
    work with this, too. */
    //TODO check if the element is the right type
    qDebug() << "Going to write stereo faders " << el << " to " << v;
    snd_ctl_elem_value_set_integer(value, 0, v);
    snd_ctl_elem_value_set_integer(value, 1, v);
    writeValue(el);
}

// Set or unsets generic alsa switches
void MainWindow::writeBool(QString s, bool a)
{
    snd_ctl_elem_value_set_boolean(value, 0, a);
    writeValue(s);
}

void MainWindow::matrixWriteEnum(const QString & e, int i)
{
    // Translate QButtonGroup indices to alsa enumeration indices. Let's only hope both are constant across environments.
    int alsai = -(i+2);
    // Write them and cross fingers.
    snd_ctl_elem_value_set_enumerated(value, 0, alsai);
    writeValue(e);
}

////// ALSA CALLBACKS

int MainWindow::alsaMasterChanged(snd_hctl_elem_t * elem, unsigned int mask)
{
    qDebug("Master Volume changed outside.");
    assert(mask == SND_CTL_EVENT_MASK_VALUE);
    MainWindow * w = (MainWindow * )snd_hctl_elem_get_callback_private(elem);
    assert(w);
    snd_hctl_elem_read(elem, w->value);
    int value = snd_ctl_elem_value_get_integer(w->value, 0);
    qDebug() << "Changed to " << value;
    w->ui->master->setValue(value);
    return 0;
}

//// GENERAL SIGNALS
void MainWindow::on_panic_pressed()
{
    // TODO: Basic implementation. I want the Panic button to silence all channels in the future.
    this->findChild<QSlider*>("master")->setValue(0);
}

void MainWindow::on_card_currentIndexChanged(int index)
{
    qDebug() << "Selecting card #" << index;
    // ALSA control handles
    if (hctl)
      snd_hctl_free(hctl);
    // Initialize card
    qDebug("Opening card...");
    QString name = QString("hw:") + QString().number(index);
    if (snd_hctl_open(&hctl, name.toLatin1().data(), SND_CTL_NONBLOCK))
    {
        showError(tr("Oops. Couldn't access sound card."));
        return;
    }
    qDebug("Loading card elements...");
    assert(!snd_hctl_load(hctl));
    // Populate elements map to make stuff easier in the future
    elements.clear();
    for (snd_hctl_elem_t * el = snd_hctl_first_elem(hctl);
      el != snd_hctl_last_elem(hctl);
      el = snd_hctl_elem_next(el))
        elements.insert(snd_hctl_elem_get_name(el), el);
    qDebug() << elements.size() << " elements loaded.";
}

void MainWindow::on_master_valueChanged(int v)
{
    writeStereoInt("Master Playback Volume", v);
}

void MainWindow::on_rate_currentIndexChanged(int index)
{
    //TODO check if the element is the right type
    snd_ctl_elem_value_set_enumerated(value, 0, index);
    writeValue("Clock Internal Rate");
}

//// PAD SIGNALS
// Output Pad switches, labeled 14dB, when I think it's actually 12 (+4dBu/-10dBV)
void MainWindow::on_dacpad_toggled(bool checked)
{
    writeBool("DAC1 0202 14dB PAD Playback Switch", checked);
}

void MainWindow::on_d1pad_toggled(bool checked)
{
    writeBool("DAC1 Audio Dock 14dB PAD Playback Switch", checked);
}

void MainWindow::on_d2pad_toggled(bool checked)
{
    writeBool("DAC2 Audio Dock 14dB PAD Playback Switch", checked);
}

void MainWindow::on_d3pad_toggled(bool checked)
{
    writeBool("DAC3 Audio Dock 14dB PAD Playback Switch", checked);
}

void MainWindow::on_d4pad_toggled(bool checked)
{
    writeBool("DAC4 Audio Dock 14dB PAD Playback Switch", checked);
}

// TODO The input switches don't work, but crash the app, not sure why.
void MainWindow::on_adcpadin_toggled(bool checked)
{
    writeBool("DAC1 0202 14dB PAD Capture Switch", checked);
}

void MainWindow::on_d1padin_toggled(bool checked)
{
    writeBool("DAC1 Audio Dock 14dB PAD Capture Switch", checked);
}

void MainWindow::on_d2padin_toggled(bool checked)
{
    writeBool("DAC2 Audio Dock 14dB PAD Capture Switch", checked);
}

void MainWindow::on_d3padin_toggled(bool checked)
{
    writeBool("DAC3 Audio Dock 14dB PAD Capture Switch", checked);
}

///// VIEW SIGNALS
//TODO Hide unnecessary channels when user clicks on the appropiate checkboxes
void MainWindow::on_con0202_toggled(bool checked)
{
   /* QList<QButtonGroup*> cols = this->findChildren<QButtonGroup*>(QRegExp("b0[r,l]"));
    for (QList<QButtonGroup*>::iterator it = cols.begin();
        it != cols.end(); ++it)
        setButtonGroupVisible(*it, checked);*/
}

/////// MATRIX SIGNALS
// Ugly way to do this. These are signaled by QButtonGroups of each column of the matrix, representing one card output.
// The stuff below is simple, but does the "real work".
// TODO implement stereo linking.

void MainWindow::on_b11_buttonClicked(int i)
{
    matrixWriteEnum("DSP A Capture Enum", i);
}

void MainWindow::on_b12_buttonClicked(int i)
{
    matrixWriteEnum("DSP B Capture Enum", i);
}

void MainWindow::on_b13_buttonClicked(int i)
{
    matrixWriteEnum("DSP C Capture Enum", i);
}

void MainWindow::on_b14_buttonClicked(int i)
{
    matrixWriteEnum("DSP D Capture Enum", i);
}

void MainWindow::on_b15_buttonClicked(int i)
{
    matrixWriteEnum("DSP E Capture Enum", i);
}

void MainWindow::on_b16_buttonClicked(int i)
{
    matrixWriteEnum("DSP F Capture Enum", i);
}

void MainWindow::on_b0l_buttonClicked(int i)
{
    matrixWriteEnum("0202 DAC Left Playback Enum", i);
}

void MainWindow::on_b0r_buttonClicked(int i)
{
    matrixWriteEnum("0202 DAC Right Playback Enum", i);
}

void MainWindow::on_ba0_buttonClicked(int i)
{
    matrixWriteEnum("1010 ADAT 0 Playback Enum", i);
}

void MainWindow::on_ba1_buttonClicked(int i)
{
    matrixWriteEnum("1010 ADAT 1 Playback Enum", i);
}

void MainWindow::on_ba2_buttonClicked(int i)
{
    matrixWriteEnum("1010 ADAT 2 Playback Enum", i);
}

void MainWindow::on_ba3_buttonClicked(int i)
{
    matrixWriteEnum("1010 ADAT 3 Playback Enum", i);
}

void MainWindow::on_ba4_buttonClicked(int i)
{
    matrixWriteEnum("1010 ADAT 4 Playback Enum", i);
}

void MainWindow::on_ba5_buttonClicked(int i)
{
    matrixWriteEnum("1010 ADAT 5 Playback Enum", i);
}

void MainWindow::on_ba6_buttonClicked(int i)
{
    matrixWriteEnum("1010 ADAT 6 Playback Enum", i);
}

void MainWindow::on_ba7_buttonClicked(int i)
{
    matrixWriteEnum("1010 ADAT 7 Playback Enum", i);
}

void MainWindow::on_bsl_buttonClicked(int i)
{
    matrixWriteEnum("1010 SPDIF Left Playback Enum", i);
}

void MainWindow::on_bsr_buttonClicked(int i)
{
    matrixWriteEnum("1010 SPDIF Right Playback Enum", i);
}

void MainWindow::on_b1l_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC1 Left Playback Enum", i);
}

void MainWindow::on_b1r_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC1 Right Playback Enum", i);
}

void MainWindow::on_b2l_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC2 Left Playback Enum", i);
}

void MainWindow::on_b2r_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC2 Right Playback Enum", i);
}

void MainWindow::on_b3l_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC3 Left Playback Enum", i);
}

void MainWindow::on_b3r_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC3 Right Playback Enum", i);
}

void MainWindow::on_b4l_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC4 Left Playback Enum", i);
}

void MainWindow::on_b4r_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC4 Right Playback Enum", i);
}

void MainWindow::on_bpl_buttonClicked(int i)
{
    matrixWriteEnum("Dock Phones Left Playback Enum", i);
}

void MainWindow::on_bpr_buttonClicked(int i)
{
    matrixWriteEnum("Dock Phones Right Playback Enum", i);
}

void MainWindow::on_bdsl_buttonClicked(int i)
{
    matrixWriteEnum("Dock SPDIF Left Playback Enum", i);
}

void MainWindow::on_bdsr_buttonClicked(int i)
{
    matrixWriteEnum("Dock SPDIF Right Playback Enum", i);
}
