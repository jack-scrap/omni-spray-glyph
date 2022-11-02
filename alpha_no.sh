#!/bin/bash

for C in {a..z}
do
	./omni_spray_glyph "$C"
done

for C in {0..9}
do
	./omni_spray_glyph "$C"
done
