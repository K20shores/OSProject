#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -s -S -m 512M -cdrom $OSNAME.iso
