#!/bin/bash

for c in {a..z}
do
	./omni_spray_glyph "$c"
done

for c in {0..9}
do
	./omni_spray_glyph "$c"
done
