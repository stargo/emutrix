/********************************************************************************
** Form generated from reading UI file 'setup.ui'
**
** Created: Fri Aug 27 05:31:36 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUP_H
#define UI_SETUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_setup
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QGroupBox *connections;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_3;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QPushButton *pushButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *setup)
    {
        if (setup->objectName().isEmpty())
            setup->setObjectName(QString::fromUtf8("setup"));
        setup->setWindowModality(Qt::WindowModal);
        setup->resize(477, 225);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(setup->sizePolicy().hasHeightForWidth());
        setup->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/action/device"), QSize(), QIcon::Normal, QIcon::Off);
        setup->setWindowIcon(icon);
        setup->setModal(true);
        verticalLayout_4 = new QVBoxLayout(setup);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(setup);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        comboBox = new QComboBox(setup);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_3->addWidget(comboBox);

        horizontalLayout_3->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_3);

        connections = new QGroupBox(setup);
        connections->setObjectName(QString::fromUtf8("connections"));
        sizePolicy1.setHeightForWidth(connections->sizePolicy().hasHeightForWidth());
        connections->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(connections);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 1);
        checkBox_2 = new QCheckBox(connections);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setChecked(true);

        verticalLayout->addWidget(checkBox_2);

        checkBox = new QCheckBox(connections);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setChecked(true);

        verticalLayout->addWidget(checkBox);

        checkBox_3 = new QCheckBox(connections);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setChecked(true);

        verticalLayout->addWidget(checkBox_3);

        spinBox_2 = new QSpinBox(connections);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setMaximum(16);
        spinBox_2->setValue(16);

        verticalLayout->addWidget(spinBox_2);

        spinBox_3 = new QSpinBox(connections);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setMaximum(6);
        spinBox_3->setValue(6);

        verticalLayout->addWidget(spinBox_3);


        verticalLayout_3->addWidget(connections);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(setup);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(setup);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(44100);
        spinBox->setMaximum(48000);
        spinBox->setSingleStep(3900);
        spinBox->setValue(48000);

        horizontalLayout->addWidget(spinBox);

        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        groupBox = new QGroupBox(setup);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy2);
        pushButton_6->setCheckable(true);

        gridLayout->addWidget(pushButton_6, 1, 1, 1, 1);

        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy3);
        pushButton_5->setCheckable(true);

        gridLayout->addWidget(pushButton_5, 1, 0, 1, 1);

        pushButton_8 = new QPushButton(groupBox);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        sizePolicy2.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy2);
        pushButton_8->setCheckable(true);

        gridLayout->addWidget(pushButton_8, 2, 1, 1, 1);

        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy2.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy2);
        pushButton_7->setCheckable(true);

        gridLayout->addWidget(pushButton_7, 2, 0, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setCheckable(true);

        gridLayout->addWidget(pushButton, 0, 0, 1, 2);


        verticalLayout_2->addWidget(groupBox);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(setup);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(comboBox);
        label->setBuddy(spinBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(setup);
        QObject::connect(buttonBox, SIGNAL(accepted()), setup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), setup, SLOT(reject()));

        QMetaObject::connectSlotsByName(setup);
    } // setupUi

    void retranslateUi(QDialog *setup)
    {
        setup->setWindowTitle(QApplication::translate("setup", "Setup", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("setup", "&Sound Card: ", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("setup", "EMU 1010 (1)", 0, QApplication::UnicodeUTF8)
        );
        connections->setTitle(QApplication::translate("setup", "Show:", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("setup", "&1010 Connections", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("setup", "0&202 Connections", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("setup", "&Dock Connections", 0, QApplication::UnicodeUTF8));
        spinBox_2->setSuffix(QApplication::translate("setup", " Jack Playback Connections", 0, QApplication::UnicodeUTF8));
        spinBox_3->setSuffix(QApplication::translate("setup", " Jack Capture Connections", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("setup", "Clock &Rate: ", 0, QApplication::UnicodeUTF8));
        spinBox->setSuffix(QApplication::translate("setup", " Hz", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("setup", "Output Attenuation:", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("setup", "Dock 2 -14dB", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("setup", "Dock 1 -14dB", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("setup", "Dock 4 -14dB", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("setup", "Dock 3 -14dB", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("setup", "0202 DAC -14dB", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class setup: public Ui_setup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_H
