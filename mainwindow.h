#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_setup.h"
#include "alsa/asoundlib.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    /// ALSA control handle
    snd_hctl_t * hctl;
    /// ALSA element value reused in this class for all writes and reads
    snd_ctl_elem_value_t * value;
    QMap<QString, snd_hctl_elem_t *> elements;
    /// Displays error message
    void showError(const QString &);
    /// Writes ALSA elements consisting of one or two integer values ("faders")
    void writeStereoInt(const QString & el, int value);
    /// Toggles ALSA switches
    void writeBool(QString, bool);
    /// Show or hide button groups (matrix columns), not implemented
    void setButtonGroupVisible(const QButtonGroup * bg, bool visible);
    /// Selects index from ALSA enumerated element
    void matrixWriteEnum(const QString & e, int i);
    /// Writes whatever is in the value private member to ALSA
    void writeValue(const QString &el);

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
    void on_b11_buttonClicked(int);
    void on_b12_buttonClicked(int);
    void on_b13_buttonClicked(int);
    void on_b14_buttonClicked(int);
    void on_b15_buttonClicked(int);
    void on_b16_buttonClicked(int);
    void on_b0l_buttonClicked(int);
    void on_b0r_buttonClicked(int);
    void on_ba0_buttonClicked(int);
    void on_ba1_buttonClicked(int);
    void on_ba2_buttonClicked(int);
    void on_ba3_buttonClicked(int);
    void on_ba4_buttonClicked(int);
    void on_ba5_buttonClicked(int);
    void on_ba6_buttonClicked(int);
    void on_ba7_buttonClicked(int);
    void on_bsl_buttonClicked(int);
    void on_bsr_buttonClicked(int);
    void on_b1l_buttonClicked(int);
    void on_b1r_buttonClicked(int);
    void on_b2l_buttonClicked(int);
    void on_b2r_buttonClicked(int);
    void on_b3l_buttonClicked(int);
    void on_b3r_buttonClicked(int);
    void on_b4l_buttonClicked(int);
    void on_b4r_buttonClicked(int);
    void on_bpl_buttonClicked(int);
    void on_bpr_buttonClicked(int);
    void on_bdsl_buttonClicked(int);
    void on_bdsr_buttonClicked(int);

};

#endif // MAINWINDOW_H
