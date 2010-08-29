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
