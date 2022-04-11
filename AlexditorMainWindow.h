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
#ifndef ALEXDITORMAINWINDOW_H
#define ALEXDITORMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AlexditorMainWindow; }
QT_END_NAMESPACE

/// La fenêtre principale de l'application
class AlexditorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    AlexditorMainWindow(QWidget *parent = nullptr);
    ~AlexditorMainWindow();

protected:
    /// Intercepte l'évènement de fermeture de l'application afin de proposer à l'utilisateur
    /// de sauvegarder son document au préalable si nécessaire.
    void closeEvent( QCloseEvent * event ) override;

private slots:
    /**
     * @brief Propose à l'utilisateur de choisir un fichier texte et ouvre celui-ci
     *
     *  Si un document modifié et non sauvé est déjà chargé, la fonction propose à
     *  l'utilisateur de le sauvergarder avant.
     */
    void ouvrir();

    /**
     * @brief Sauve le document en cours
     *
     * Si le document est nouveau et n'a pas encore été sauvé, ou si @p copie vaut true,
     * la fonction propose à l'utilisateur de choisir un nom de fichier pour y sauvegarder
     * le document.
     */
    void sauver( bool copie = false );

    /**
     * @brief Propose à l'utilisateur de choisir nom de fichier et sauve le document en cours dedans.
     */
    void sauverSous();

    /**
     * @brief Crée un nouveau document qui remplace le document en cours
     *
     *  Si un document modifié et non sauvé est déjà chargé, la fonction propose à
     *  l'utilisateur de le sauvergarder avant.
     */
    void nouveau();

    /// gère le statut modifié du document en cours
    void gérerTextChanged();

    /// Affiche une fenêtre présentant Alexditor
    void aPropos();

private:
    typedef enum {
        CONTINUER = 0,  ///< Continuer d'exécuter l'action quel que soit l'état du document en cours (et l'abandonner s'il n'est pas sauvé)
        ANNULER         ///< Annuler l'action. Le document en cours est conservé
    } ActionSauvegarde;

    /// Vérifie si un document a besoin d'être sauvegardé et demande à l'utilisateur s'il veut le faire le cas échéant.
    ActionSauvegarde vérifierSauvergarde();

    /// Met à jour le titre de la fenêtre avec le nom du document en cours
    void mettreTitreFenêtre();

private:
    Ui::AlexditorMainWindow *ui;

    /// Nom du fichier dans lequel le document en cours est stocké
    QString mNomFichier;

    /// format du titre de la fenêtre
    QString const mFormatNomFenêtre;
};
#endif // ALEXDITORMAINWINDOW_H
