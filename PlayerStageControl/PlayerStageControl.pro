#
# SCC0712 - Programação de Robôs Móveis
# Universidade de São Paulo (USP) - São Carlos
# Instituto de Ciências Matemáticas e de Computação (ICMC)
# Autor: Guilherme Caixeta de Oliveira (gcaixetaoliveira@gmail.com) - nUSP 8504368
#
# This file is part of PlayerStageControl project.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# Application info
TEMPLATE = app
DESTDIR = bin
TARGET = PlayerStageControl
VERSION = 1.0

# Qt config
CONFIG += c++11
CONFIG += console
CONFIG -= qt app_bundle

# Libs
LIBS += -lplayerc -L/usr/local/lib64 -pthread
#INCLUDEPATH += /usr/local/include/player-3.0
INCLUDEPATH += /usr/include/player-3.0

# Temporary dirs
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/moc
RCC_DIR = tmp/rc

# Source files
INCLUDEPATH *= . src

SOURCES += \
    src/main.cc \
    src/PlayerStageControl/player/behavior/basics/behavior_goto.cc \
    src/PlayerStageControl/player/behavior/behavior.cc \
    src/PlayerStageControl/player/player.cc \
    src/PlayerStageControl/utils/position/position.cc \
    src/PlayerStageControl/utils/thread/thread.cc \
    src/exithandler.cc \
    src/PlayerStageControl/utils/utils.cc \
    src/PlayerStageControl/player/navigation/navigationalgorithm/PF/pf.cc \
    src/PlayerStageControl/player/navigation/navigationalgorithm/navigationalgorithm.cc \
    src/PlayerStageControl/player/navigation/navigation.cc \
    src/PlayerStageControl/player/device/laser/laser.cc \
    src/PlayerStageControl/player/device/odometer/odometer.cc \
    src/PlayerStageControl/player/device/device.cc \
    src/PlayerStageControl/player/device/gripper/gripper.cc \
    src/PlayerStageControl/player/device/basedevices.cc \
    src/PlayerStageControl/player/device/devices.cc \
    src/PlayerStageControl/player/device/blobfinder/blobfinder.cc \
    src/PlayerStageControl/player/device/blobfinder/blob.cc \
    src/PlayerStageControl/utils/color/color.cc \
    src/PlayerStageControl/utils/vector/vector.cc \
    src/PlayerStageControl/utils/scanpoint/scanpoint.cc \
    src/PlayerStageControl/player/behavior/basics/behavior_gripper.cc

# Header files
HEADERS += \
    src/exithandler.hh \
    src/PlayerStageControl/player/behavior/basics/behavior_goto.hh \
    src/PlayerStageControl/player/behavior/behavior.hh \
    src/PlayerStageControl/player/behavior/behaviors.hh \
    src/PlayerStageControl/player/baseplayer.hh \
    src/PlayerStageControl/player/player.hh \
    src/PlayerStageControl/utils/position/position.hh \
    src/PlayerStageControl/utils/thread/thread.hh \
    src/PlayerStageControl/utils/utils.hh \
    src/PlayerStageControl/player/navigation/navigationalgorithm/PF/pf.hh \
    src/PlayerStageControl/player/navigation/navigationalgorithm/navigationalgorithm.hh \
    src/PlayerStageControl/player/navigation/navigation.hh \
    src/PlayerStageControl/player/device/laser/laser.hh \
    src/PlayerStageControl/player/device/odometer/odometer.hh \
    src/PlayerStageControl/player/device/device.hh \
    src/PlayerStageControl/player/device/devices.hh \
    src/PlayerStageControl/player/device/basedevices.hh \
    src/PlayerStageControl/player/device/gripper/gripper.hh \
    src/PlayerStageControl/player/device/blobfinder/blobfinder.hh \
    src/PlayerStageControl/player/device/blobfinder/blob.hh \
    src/PlayerStageControl/utils/color/color.hh \
    src/PlayerStageControl/utils/vector/vector.hh \
    src/PlayerStageControl/utils/scanpoint/scanpoint.hh \
    src/PlayerStageControl/player/behavior/basics/behavior_gripper.hh

# Other files
DISTFILES += \
    LICENSE
