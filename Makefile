GXX = g++
SOURCE = source/*.cpp
OUTPUT = RSGL-static

RSGL-static:
	$(GXX) $(SOURCE) -o $(OUTPUT)

install:
	mv $(OUTPUT) /usr/bin
