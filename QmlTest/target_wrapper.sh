#!/bin/sh
LD_LIBRARY_PATH=/home/tomoyuki/Qt5.9.2/5.9.2/gcc_64/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}
export LD_LIBRARY_PATH
QT_PLUGIN_PATH=/home/tomoyuki/Qt5.9.2/5.9.2/gcc_64/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}
export QT_PLUGIN_PATH
exec "$@"
