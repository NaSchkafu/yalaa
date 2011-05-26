#!/bin/sh

# MOC_MK=build-files/moc_files.mk
# UIC_MK=build-files/uic_files.mk
SRC_MK=build-files/src_files.mk
INC_MK=../build-files/extra_inc.mk
# GUI_MK=build-files/gui_files.mk
# SWG_MK=build-files/swg_files.mk

mkdir -p src/.moc
mkdir -p src/.ui
mkdir -p src/.swig-obj

# set `find src -regex ".*\.h\\(pp\\)?$" | xargs -n 1 grep -l -i Q_OBJECT`
# echo -n "MOC_FILES=" > $MOC_MK
# for f; do
#   echo -n $f | xargs basename | sed -e "s/^./.moc\/moc_&/;s/\.h\(pp\)\?$/.cpp\ /" | tr -d '\n' >> $MOC_MK
# done
# echo >> $MOC_MK

# set `find src -regex ".*\.ui$" -type f | xargs -n 1 echo`
# echo -n "UIC_FILES=" > $UIC_MK
# for f; do
# #  echo -n $f | sed -e "s/[[:alnum:]]\+\.ui$/ui_&/;s/\.ui$/\.h\ /;s/\//&.ui&/" >> $UIC_MK
#   echo -n $f | xargs basename | sed -e "s/^./.ui\/ui_&/;s/\.ui$/\.h\ /" | tr -d '\n' >> $UIC_MK
# done
# echo >> $UIC_MK

set `find src -regex ".*\.cpp$" -not -regex ".*/ui/.*" -not -name "main.cpp" -type f -not -iname "moc_*" | xargs -n 1 echo`
echo -n "SRC_FILES=" > $SRC_MK
for f; do
  echo -n $f | tr -d '\n' | xargs -I "%%" echo -n "%% " >> $SRC_MK
done
echo >> $SRC_MK

# set `find src -regex ".*\.cpp$" -regex ".*/ui/.*" -type f -not -iname "moc_*" | xargs -n 1 echo`
# echo -n "GUI_FILES=" > $GUI_MK
# for f; do
#   echo -n $f | tr -d '\n' | xargs -I "%%" echo -n "%% " >> $GUI_MK
# done
# echo -n "src/main.cpp" >> $GUI_MK
# echo >> $GUI_MK

cd src
set `find . -type d -regex "\.[^.]*" -printf "%P\n" | xargs -n 1 echo`
echo -n "EXTRA_INC=" > $INC_MK
for f; do
  echo -n "-Isrc/"$f" " >> $INC_MK
done
echo >> $INC_MK
cd ..

# set `find . -regex ".*\.i$" -type f | xargs -n 1 echo`
# echo -n "SWIG_INTERFACES=" > $SWG_MK
# for f; do
#   echo -n $f" " | sed -e "s/^.\///" | tr -d '\n' >> $SWG_MK
# done
# echo >> $SWG_MK
