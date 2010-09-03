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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSlider>

//// HELPER FUNCTIONS

void MainWindow::checkLinked(QButtonGroup * bg, QButtonGroup * linked)
{
    if (!ui->link->isChecked())
        return;
    int ix = bg->checkedId();
    if (ix == -2);
    else if (linked->objectName().endsWith('l'))
        ix++;
    else if(linked->objectName().endsWith('r'))
        ix--;
    /// TODO make this work for input channels.
    /*else if (-ix >= 5 && -ix <= 14 && ix % 2 == 0) // checked an even id => right channel
        ix++; // change left
    else if (-ix >= 5 && -ix <= 14 && ix % 2 == 1) // checked an odd id => left channel
        ix--; // change right
        */
    else
        return;
    if (linked->checkedId() != ix)
        // Using click() because it fires the appropiate signals
        linked->button(ix)->click();
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
    initCard(index);
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
    writeBool("ADC1 14dB PAD 0202 Capture Switch", checked);
}

void MainWindow::on_d1padin_toggled(bool checked)
{
    writeBool("ADC1 14dB PAD Audio Dock Capture Switch", checked);
}

void MainWindow::on_d2padin_toggled(bool checked)
{
    writeBool("ADC2 14dB PAD Audio Dock Capture Switch", checked);
}

void MainWindow::on_d3padin_toggled(bool checked)
{
    writeBool("ADC3 14dB PAD Audio Dock Capture Switch", checked);
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
    checkLinked(ui->b0l, ui->b0r);
}

void MainWindow::on_b0r_buttonClicked(int i)
{
    matrixWriteEnum("0202 DAC Right Playback Enum", i);
    checkLinked(ui->b0r, ui->b0l);
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
    checkLinked(ui->bsl, ui->bsr);
}

void MainWindow::on_bsr_buttonClicked(int i)
{
    matrixWriteEnum("1010 SPDIF Right Playback Enum", i);
    checkLinked(ui->bsr, ui->bsl);
}

void MainWindow::on_b1l_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC1 Left Playback Enum", i);
    checkLinked(ui->b1l, ui->b1r);
}

void MainWindow::on_b1r_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC1 Right Playback Enum", i);
    checkLinked(ui->b1r, ui->b1l);
}

void MainWindow::on_b2l_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC2 Left Playback Enum", i);
    checkLinked(ui->b2l, ui->b2r);
}

void MainWindow::on_b2r_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC2 Right Playback Enum", i);
    checkLinked(ui->b2r, ui->b2l);
}

void MainWindow::on_b3l_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC3 Left Playback Enum", i);
    checkLinked(ui->b3l, ui->b3r);
}

void MainWindow::on_b3r_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC3 Right Playback Enum", i);
    checkLinked(ui->b3r, ui->b3l);
}

void MainWindow::on_b4l_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC4 Left Playback Enum", i);
    checkLinked(ui->b4l, ui->b4r);
}

void MainWindow::on_b4r_buttonClicked(int i)
{
    matrixWriteEnum("Dock DAC4 Right Playback Enum", i);
    checkLinked(ui->b4r, ui->b4l);
}

void MainWindow::on_bpl_buttonClicked(int i)
{
    matrixWriteEnum("Dock Phones Left Playback Enum", i);
    checkLinked(ui->bpl, ui->bpr);
}

void MainWindow::on_bpr_buttonClicked(int i)
{
    matrixWriteEnum("Dock Phones Right Playback Enum", i);
    checkLinked(ui->bpr, ui->bpl);
}

void MainWindow::on_bdsl_buttonClicked(int i)
{
    matrixWriteEnum("Dock SPDIF Left Playback Enum", i);
    checkLinked(ui->bdsl, ui->bdsr);
}

void MainWindow::on_bdsr_buttonClicked(int i)
{
    matrixWriteEnum("Dock SPDIF Right Playback Enum", i);
    checkLinked(ui->bdsr, ui->bdsl);
}
