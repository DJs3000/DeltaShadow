all: main

clean:
	rm -f *.o main

.PHONY: all clean

OBJS := \
	AnimTile.o \
	DeltaShadow.Program.o \
	DeltaShadow.SetupForm.o \
	ObjectData.o \
	Program.o \
	program_main.o \
	RoomLayers.o \
	Properties/AssemblyInfo.o \
	Properties/Resources.Designer.o \

PROGRAM_H_HEADERS := \
	AnimTile.h \
	RoomLayers.h \
	Program.h \
	DeltaShadow.SetupForm.h \
	rectangularvectors.h \
	stringhelper.h

main: $(OBJS)

DeltaShadow.SetupForm.o: DeltaShadow.SetupForm.cpp Properties/Resources.Designer.h DeltaShadow.Program.h DeltaShadow.SetupForm.h

program_main.o: DeltaShadow.Program.h $(PROGRAM_H_HEADERS)

DeltaShadow.Program.o: DeltaShadow.Program.h $(PROGRAM_H_HEADERS) Properties/Resources.Designer.h

RoomLayers.o: RoomLayers.h

Properties/AssemblyInfo.o: Properties/AssemblyInfo.h

ObjectData.o: ObjectData.h

AnimTile.o: AnimTile.h
