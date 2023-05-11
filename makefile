CXX = g++
BIN = main
FOLDER = Build

ALL_LIB = . SourceFiles
ALL_INCLUDE = -I. -IHeaderFiles
ALL_SOURCE = $(foreach D, $(ALL_LIB), $(wildcard $(D)/*.cpp))

SDL_LINKER = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
SDL_INCLUDE = -I "C:/C++/SDL2 - Template/SDL/include"
SDL_LIBRARY = -L "C:/C++/SDL2 - Template/SDL/lib"

JDM_INCLUDE = -I "C:/C++/SDL2 - Template/JDM"
JDM_LIB = "C:/C++/SDL2 - Template/JDM/Source"
JDM_SOURCE = $(foreach D, $(JDM_LIB), $(wildcard $(D)/*.cpp))
ALL_EXECUTABLE = $(foreach D, $(FOLDER), $(wildcard $(D)/*.exe))

.PHONY: default all debug release dexec rexec clean

default: debug
all: debug release
debug: $(FOLDER)/$(BIN)-Debug
release: $(FOLDER)/$(BIN)-Release

$(FOLDER)/$(BIN)-Debug: $(ALL_SOURCE) $(JDM_SOURCE)
	@cls
	@echo JDM - SDL2 ($(BIN)): Started Building (Debug Mode)
	@echo JDM - SDL2 ($(BIN)): Compilation started.
	@$(CXX) $(SDL_INCLUDE) $(ALL_INCLUDE) $(JDM_INCLUDE) $(SDL_LIBRARY) $^ -o $@ $(SDL_LINKER)
	@echo JDM - SDL2 ($(BIN)): Compilation completed successfully!
	@echo JDM - SDL2 ($(BIN)): Build successfully!

$(FOLDER)/$(BIN)-Release: $(ALL_SOURCE) $(JDM_SOURCE)
	@cls
	@echo JDM - SDL2 ($(BIN)): Started Building (Release Mode)
	@echo JDM - SDL2 ($(BIN)): Compilation started.
	@$(CXX) -O3 -DNDEBUG $(SDL_INCLUDE) $(ALL_INCLUDE) $(JDM_INCLUDE) $(SDL_LIBRARY) $^ -o $@ $(SDL_LINKER) -mwindows
	@echo JDM - SDL2 ($(BIN)): Compilation completed successfully!
	@echo JDM - SDL2 ($(BIN)): Build successfully!

dexec:
	@cls
	@$(FOLDER)/$(BIN)-Debug.exe

rexec:
	@cls
	@$(FOLDER)/$(BIN)-Release.exe

clean:
	@$(foreach D, $(wildcard $(FOLDER)/*.exe), del $(FOLDER)\$(notdir $(D)))
