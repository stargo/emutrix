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
#include <QComboBox>
#include "soundcard.h"
#include "matrix_visibility.h"

//// GENERAL SIGNALS
void MainWindow::on_panic_pressed()
{
    // TODO: Basic implementation. I want the Panic button to silence all channels in the future.
    this->findChild<QSlider*>("master")->setValue(0);
}

void MainWindow::on_card_currentIndexChanged(int index)
{
    int aix = findChild<QComboBox*>("card")->itemData(index).toInt();
    qDebug() << "Selecting card #" << aix;
    // ALSA control handles
    if (card)
      delete card;
    // Initialize card .. TODO ALSA index isn't necessarly equal to cb index, if
    // user has non-emu cards! fixed -- works now?
    card = new SoundCard(aix);
    card->setupCallbacks(this);
}

void MainWindow::on_master_valueChanged(int v)
{
    card->writeStereoInt("Master Playback Volume", v);
}

void MainWindow::on_rate_currentIndexChanged(int index)
{
    card->writeEnum("Clock Internal Rate", index);
}

//// PAD SIGNALS
// Output Pad switches, labeled 14dB, when I think it's actually 12 (+4dBu/-10dBV)
void MainWindow::on_dacpad_toggled(bool checked)
{
    card->writeBool("DAC1 0202 14dB PAD Playback Switch", checked);
}

void MainWindow::on_d1pad_toggled(bool checked)
{
    card->writeBool("DAC1 Audio Dock 14dB PAD Playback Switch", checked);
}

void MainWindow::on_d2pad_toggled(bool checked)
{
    card->writeBool("DAC2 Audio Dock 14dB PAD Playback Switch", checked);
}

void MainWindow::on_d3pad_toggled(bool checked)
{
    card->writeBool("DAC3 Audio Dock 14dB PAD Playback Switch", checked);
}

void MainWindow::on_d4pad_toggled(bool checked)
{
    card->writeBool("DAC4 Audio Dock 14dB PAD Playback Switch", checked);
}

// TODO The input switches don't work, but crash the app, not sure why.
void MainWindow::on_adcpadin_toggled(bool checked)
{
    card->writeBool("ADC1 14dB PAD 0202 Capture Switch", checked);
}

void MainWindow::on_d1padin_toggled(bool checked)
{
    card->writeBool("ADC1 14dB PAD Audio Dock Capture Switch", checked);
}

void MainWindow::on_d2padin_toggled(bool checked)
{
    card->writeBool("ADC2 14dB PAD Audio Dock Capture Switch", checked);
}

void MainWindow::on_d3padin_toggled(bool checked)
{
    card->writeBool("ADC3 14dB PAD Audio Dock Capture Switch", checked);
}

///// VIEW SIGNALS
//Hide unnecessary channels when user clicks on the appropiate checkboxes
void MainWindow::on_con0202_toggled(bool checked)
{
    // actually not 0202, but 1212
    if (!checked)
            return;
    // 1010 is always visible
    // matrixSetVisible(matrix1010rows, matrix1010cols, true);
    matrixSetVisible(matrix0202rows, matrix0202cols, true);
    matrixSetVisible(matrixDockRows, matrixDockCols, false);
}

void MainWindow::on_con1010_toggled(bool checked)
{
    // 1010 only
    if (!checked)
            return;
    // 1010 is always visible
    // matrixSetVisible(matrix1010rows, matrix1010cols, true);
    matrixSetVisible(matrixDockRows, matrixDockCols, false);
    matrixSetVisible(matrix0202rows, matrix0202cols, false);
}

void MainWindow::on_condock_toggled(bool checked)
{
    if (checked)
    {
        ui->labelspdifl->setText("Dock S/PDIF L");
        ui->labelspdifr->setText("Dock S/PDIF R");
    }
    else
    {
        ui->labelspdifl->setText("1010 S/PDIF L");
        ui->labelspdifr->setText("1010 S/PDIF R");
    }
    // 1010 + Dock
    if (!checked)
            return;
    // 1010 is always visible
    // matrixSetVisible(matrix1010rows, matrix1010cols, true);
    matrixSetVisible(matrixDockRows, matrixDockCols, true);
    matrixSetVisible(matrix0202rows, matrix0202cols, false);
}

/////// MATRIX SIGNALS
// Ugly way to do this. These are signaled by QButtonGroups of each column of the matrix, representing one card output.
// The stuff below is simple, but does the "real work".
// TODO implement stereo linking.

void MainWindow::on_b11_buttonClicked(int i)
{
    card->matrixWriteEnum("DSP A Capture Enum", i);
    checkLinked(ui->b11, ui->b12);
}

void MainWindow::on_b12_buttonClicked(int i)
{
    card->matrixWriteEnum("DSP B Capture Enum", i);
    checkLinked(ui->b12, ui->b13, ui->b11);
}

void MainWindow::on_b13_buttonClicked(int i)
{
    card->matrixWriteEnum("DSP C Capture Enum", i);
    checkLinked(ui->b13, ui->b14, ui->b12);
}

void MainWindow::on_b14_buttonClicked(int i)
{
    card->matrixWriteEnum("DSP D Capture Enum", i);
    checkLinked(ui->b14, ui->b15, ui->b13);
}

void MainWindow::on_b15_buttonClicked(int i)
{
    card->matrixWriteEnum("DSP E Capture Enum", i);
    checkLinked(ui->b15, ui->b16, ui->b14);
}

void MainWindow::on_b16_buttonClicked(int i)
{
    card->matrixWriteEnum("DSP F Capture Enum", i);
    checkLinked(ui->b16, NULL, ui->b15);
}

void MainWindow::on_b0l_buttonClicked(int i)
{
    card->matrixWriteEnum("0202 DAC Left Playback Enum", i);
    checkLinked(ui->b0l, ui->b0r);
}

void MainWindow::on_b0r_buttonClicked(int i)
{
    card->matrixWriteEnum("0202 DAC Right Playback Enum", i);
    checkLinked(ui->b0r, ui->b0l);
}

void MainWindow::on_ba0_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 ADAT 0 Playback Enum", i);
    checkLinked(ui->ba0, ui->ba1);
}

void MainWindow::on_ba1_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 ADAT 1 Playback Enum", i);
    checkLinked(ui->ba1, ui->ba2, ui->ba0);
}

void MainWindow::on_ba2_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 ADAT 2 Playback Enum", i);
    checkLinked(ui->ba2, ui->ba3, ui->ba1);
}

void MainWindow::on_ba3_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 ADAT 3 Playback Enum", i);
    checkLinked(ui->ba3, ui->ba4, ui->ba2);
}

void MainWindow::on_ba4_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 ADAT 4 Playback Enum", i);
    checkLinked(ui->ba4, ui->ba5, ui->ba3);
}

void MainWindow::on_ba5_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 ADAT 5 Playback Enum", i);
    checkLinked(ui->ba5, ui->ba6, ui->ba4);
}

void MainWindow::on_ba6_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 ADAT 6 Playback Enum", i);
    checkLinked(ui->ba6, ui->ba7, ui->ba5);
}

void MainWindow::on_ba7_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 ADAT 7 Playback Enum", i);
    checkLinked(ui->ba7, NULL, ui->ba6);
}

void MainWindow::on_bsl_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 SPDIF Left Playback Enum", i);
    checkLinked(ui->bsl, ui->bsr);
}

void MainWindow::on_bsr_buttonClicked(int i)
{
    card->matrixWriteEnum("1010 SPDIF Right Playback Enum", i);
    checkLinked(ui->bsr, ui->bsl);
}

void MainWindow::on_b1l_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock DAC1 Left Playback Enum", i);
    checkLinked(ui->b1l, ui->b1r);
}

void MainWindow::on_b1r_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock DAC1 Right Playback Enum", i);
    checkLinked(ui->b1r, ui->b1l);
}

void MainWindow::on_b2l_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock DAC2 Left Playback Enum", i);
    checkLinked(ui->b2l, ui->b2r);
}

void MainWindow::on_b2r_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock DAC2 Right Playback Enum", i);
    checkLinked(ui->b2r, ui->b2l);
}

void MainWindow::on_b3l_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock DAC3 Left Playback Enum", i);
    checkLinked(ui->b3l, ui->b3r);
}

void MainWindow::on_b3r_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock DAC3 Right Playback Enum", i);
    checkLinked(ui->b3r, ui->b3l);
}

void MainWindow::on_b4l_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock DAC4 Left Playback Enum", i);
    checkLinked(ui->b4l, ui->b4r);
}

void MainWindow::on_b4r_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock DAC4 Right Playback Enum", i);
    checkLinked(ui->b4r, ui->b4l);
}

void MainWindow::on_bpl_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock Phones Left Playback Enum", i);
    checkLinked(ui->bpl, ui->bpr);
}

void MainWindow::on_bpr_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock Phones Right Playback Enum", i);
    checkLinked(ui->bpr, ui->bpl);
}

void MainWindow::on_bdsl_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock SPDIF Left Playback Enum", i);
    checkLinked(ui->bdsl, ui->bdsr);
}

void MainWindow::on_bdsr_buttonClicked(int i)
{
    card->matrixWriteEnum("Dock SPDIF Right Playback Enum", i);
    checkLinked(ui->bdsr, ui->bdsl);
}

void MainWindow::on_conplay_valueChanged(int)
{

}

void MainWindow::on_concapture_valueChanged(int)
{

}
