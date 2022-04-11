/*
 * Alexditor - Un petit éditeur tout simple pour commencer à apprendre Qt.
 *   Copyright (C) 2022  Frédéric Virot
 *
 * Ce fichier fait partie d'Alexditor.
 *
 * Alexditor est un logiciel libre ; vous pouvez le redistribuer ou le modifier suivant les termes
 * de la GNU General Public License telle que publiée par la Free Software Foundation ; soit la
 * version 3 de la licence, soit (à votre gré) toute version ultérieure.
 *
 * Alexditor est distribué dans l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE ; sans même
 * la garantie tacite de QUALITÉ MARCHANDE ou d'ADÉQUATION à UN BUT PARTICULIER. Consultez la
 * GNU General Public License pour plus de détails.
 *
 * Vous devez avoir reçu une copie de la GNU General Public License en même temps que Alexditor ;
 * si ce n'est pas le cas, consultez <http://www.gnu.org/licenses>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "AlexditorMainWindow.h"
#include "ui_AlexditorMainWindow.h"

#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QFileInfo>
#include <QMessageBox>
#include <QAction>
#include <QCloseEvent>
#include <QUrl>

AlexditorMainWindow::AlexditorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AlexditorMainWindow)
    , mNomFichier()
    , mFormatNomFenêtre( "Alexditor -- %1 [*]" )
{
    ui->setupUi(this);

    QAction * raccourciClavier;

    raccourciClavier = new QAction( "Ouvrir", this );
    raccourciClavier->setShortcut( QKeySequence::Open );
    addAction( raccourciClavier );
    connect( raccourciClavier, &QAction::triggered, this, & AlexditorMainWindow::ouvrir );

    raccourciClavier = new QAction( "Ouvrir", this );
    raccourciClavier->setShortcut( QKeySequence::Save );
    addAction( raccourciClavier );
    connect( raccourciClavier, &QAction::triggered, this, & AlexditorMainWindow::sauver );

    raccourciClavier = new QAction( "Ouvrir", this );
    raccourciClavier->setShortcut( QKeySequence::SaveAs );
    addAction( raccourciClavier );
    connect( raccourciClavier, &QAction::triggered, this, & AlexditorMainWindow::sauverSous );

    raccourciClavier = new QAction( "Nouveau", this );
    raccourciClavier->setShortcut( QKeySequence::New );
    addAction( raccourciClavier );
    connect( raccourciClavier, &QAction::triggered, this, & AlexditorMainWindow::nouveau );

    raccourciClavier = new QAction( "A propos", this );
    raccourciClavier->setShortcut( QKeySequence( "Ctrl+?" ) );
    addAction( raccourciClavier );
    connect( raccourciClavier, &QAction::triggered, this, & AlexditorMainWindow::aPropos );

    connect( ui->ouvrir_pushButton, &QPushButton::clicked, this, & AlexditorMainWindow::ouvrir );
    connect( ui->sauver_pushButton, &QPushButton::clicked, this, & AlexditorMainWindow::sauver );
    connect( ui->sauverSous_pushButton, &QPushButton::clicked, this, & AlexditorMainWindow::sauverSous );
    connect( ui->nouveau_pushButton, &QPushButton::clicked, this, & AlexditorMainWindow::nouveau );
    connect( ui->textEdit, &QTextEdit::textChanged, this, &AlexditorMainWindow::gérerTextChanged );

    // Donner un titre à la fenêtre, même si aucun document n'est chargé
    mettreTitreFenêtre();

    // S'assure que la zone de texte reçoit les appuis de touches du clavier au démarrage
    ui->textEdit->setFocus();
}

AlexditorMainWindow::~AlexditorMainWindow()
{
    delete ui;
}

void AlexditorMainWindow::ouvrir()
{
    if ( vérifierSauvergarde() == CONTINUER ) {
        QString nomFichier = QFileDialog::getOpenFileName( this,
                                                           "Sélectionne un fichier texte à ouvrir",
                                                           QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation),
                                                           "textes markdown (*.md);; textes bruts (*.txt)");

        if ( ! nomFichier.isEmpty() ) {
            QFile fichier( nomFichier );

            if ( fichier.open( QIODevice::ReadOnly ) ) {
                ui->textEdit->clear();
                ui->textEdit->setMarkdown( QTextStream( & fichier ).readAll() );
                fichier.close();

                mNomFichier = nomFichier;
                setWindowModified( false );
                mettreTitreFenêtre();
            }
        }
    }
}

void AlexditorMainWindow::closeEvent( QCloseEvent * event )
{
    if ( vérifierSauvergarde() == CONTINUER ) {
        event->accept();
    } else {
        event->ignore();
    }
}

void AlexditorMainWindow::sauver( bool copie )
{
    QString loc = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
    QString nomFichier;

    if ( ! mNomFichier.isEmpty() ) {
        QFileInfo fi( mNomFichier );

        if ( ! fi.absolutePath().isEmpty() ) {
            loc = fi.absolutePath();
        }
    } else
        copie = true;

    if ( copie ) {
        nomFichier = QFileDialog::getSaveFileName( this,
                                                   "Sélectionne un emplacement et un nom de fichier pour sauver",
                                                   loc,
                                                   "textes markdown (*.md);; textes bruts (*.txt)" );
    } else
        nomFichier = mNomFichier;

    if ( ! nomFichier.isEmpty() ) {
        QFile fichier( nomFichier );

        if ( fichier.open( QIODevice::WriteOnly ) ) {
            QTextStream stream( & fichier );

            stream << ui->textEdit->toMarkdown();
            stream.flush();

            fichier.close();

            setWindowModified( false );
            mNomFichier = nomFichier;
            mettreTitreFenêtre();
        }
    }
}

void AlexditorMainWindow::sauverSous()
{
    sauver( true );
}

void  AlexditorMainWindow::nouveau()
{
    if ( vérifierSauvergarde() == CONTINUER ) {
        ui->textEdit->clear();

        setWindowModified( false );
        mNomFichier.clear();
        mettreTitreFenêtre();
    }
}

void AlexditorMainWindow::gérerTextChanged()
{
    setWindowModified( true );
}


AlexditorMainWindow::ActionSauvegarde AlexditorMainWindow::vérifierSauvergarde()
{
    ActionSauvegarde valeurRetour = CONTINUER;

    if ( isWindowModified() ) {
        QMessageBox::StandardButton but = QMessageBox::question( this,
                                                                 "Sauver?",
                                                                 "Veux-tu sauver le fichier en cours avant?",
                                                                 QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel) );
        if ( but == QMessageBox::Yes ) {
            sauver();
        } else if ( but == QMessageBox::Cancel ) valeurRetour = ANNULER;
    }

    return valeurRetour;
}

void AlexditorMainWindow::mettreTitreFenêtre()
{
    QString nomDocument = mNomFichier;

    if ( nomDocument.isEmpty() ) nomDocument = "Document Sans Titre.md";

    setWindowTitle( QString( mFormatNomFenêtre ).arg( nomDocument ) );
    ui->textEdit->document()->setBaseUrl( QUrl( mNomFichier ) );
}

void AlexditorMainWindow::aPropos()
{
    QMessageBox::about( this, "Alexditor -- l'éditeur d'Alex", "Alexditor - Un petit éditeur tout simple pour commencer à apprendre Qt.\n"
                                                               "Copyright (C) 2022 Frédéric Virot\n\n"

                                                               "This program is free software: you can redistribute it and/or modify\n"
                                                               "it under the terms of the GNU General Public License as published by\n"
                                                               "the Free Software Foundation, either version 3 of the License, or\n"
                                                               "(at your option) any later version.\n\n"

                                                               "This program is distributed in the hope that it will be useful,\n"
                                                               "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                                                               "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                                                               "GNU General Public License for more details.\n\n"

                                                               "You should have received a copy of the GNU General Public License\n"
                                                               "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n"
                        );
}
