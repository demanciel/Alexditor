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

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlexditorMainWindow w;
    w.show();
    return a.exec();
}
