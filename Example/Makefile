# C/C++ project Makefile

# Parameters to be changed may be found in this file or in Makefile.prj
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# + Parameter  + Meaning                                           + Default value         +
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# + TARGET:    + a name of the output ELF file                     + name of "." directory +
# + DIRS:      + directories that contain source files             + current directory     +
# + CFLAGS:    + C compiler flags                                  + empty                 +
# + CXXFLAGS:  + C++ compiler flags                                + empty                 +
# + LDFLAGS:   + linker flags                                      + empty                 +
# + PARAM:     + program executing parameters                      + empty                 +
# + TTY:       + file or terminal to send program output to        + empty                 +
# + PRJ:       + the temporary project directory                   + .prj                  +
# + BIN_DIR:   + a directory to place output executable            + /usr/local/bin        +
# + LIB_DIR:   + a directory to place lib files                    + /usr/local/lib        +
# + LIB_FILES  + files and directories to place to $LIB_DIR        + empty                 +
# + ARC:       + additional files to be added to archive           + empty                 +
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

-include Makefile.prj

ifeq ($(TARGET),)
    TARGET := $(notdir $(PWD))
endif
ifeq ($(PRJ),)
    PRJ = .prj
endif
ifeq ($(DIRS),)
    DIRS = .
endif
ifneq ($(TTY),)
    TTY:= > $(TTY)
endif

ifeq ($(BIN_DIR),)
    BIN_DIR = "/usr/local/bin"
endif
ifeq ($(LIB_DIR),)
    LIB_DIR="/usr/local/lib"
endif


ifneq ($(MAKECMDGOALS),"clean") 
MAKE_PRJ_DIR := $(shell mkdir $(PRJ) > /dev/null 2>&1)
endif

CC=gcc

vpath
vpath $(TARGET) .
vpath %.c   $(DIRS)
vpath %.cxx $(DIRS)
vpath %.C   $(DIRS)
vpath %.cc  $(DIRS)
vpath %.cpp $(DIRS)
vpath %.o $(PRJ)

MARK = $(TARGET)":"  
SHELL = /bin/sh

HDR := $(foreach suffix, h hxx H hh hpp, $(foreach dir, $(DIRS), $(wildcard $(dir)/*.$(suffix))))
SRC := $(foreach suffix, c cxx C cc cpp, $(foreach dir, $(DIRS), $(wildcard $(dir)/*.$(suffix))))
OBJ := $(foreach suffix, c cxx C cc cpp, $(patsubst %.$(suffix), $(PRJ)/%.o, $(notdir $(filter %.$(suffix), $(SRC)))))


.PHONY: nodeps clean tar gz bz2  nlines nbytes get_files get_headers get_sources

$(TARGET): Makefile* $(notdir $(OBJ))
	@echo $(MARK) linking "($(words $(OBJ)) .o files total):" $(notdir $(OBJ))
	@$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJ) $(LIBS)
	@echo $(MARK) done

nodeps: $(notdir $(OBJ))
	$(MAKE) $(TARGET)

ifeq ($(MAKECMDGOALS),)
-include $(OBJ:%.o=%.d) 
endif

# dependencies
$(PRJ)/%.d: %.c 
	@echo $(MARK) dependence \`$(notdir $@)\'
	@$(CC) $(CFLAGS) $(DEFINES) $(INCPATH) -MM $< > $@ 
$(PRJ)/%.d: %.cxx
	@echo $(MARK) dependence \`$(notdir $@)\'
	@$(CXX) $(CXXFLAGS) $(DEFINES) $(INCPATH) -MM $< > $@ 
$(PRJ)/%.d: %.C
	@echo $(MARK) dependence \`$(notdir $@)\'
	@$(CXX) $(CFLAGS) $(DEFINES) $(INCPATH) -MM $< > $@ 
$(PRJ)/%.d: %.cc
	@echo $(MARK) dependence \`$(notdir $@)\'
	@$(CXX) $(CXXFLAGS) $(DEFINES) $(INCPATH) -MM $< > $@ 
$(PRJ)/%.d: %.cpp
	@echo $(MARK) dependence \`$(notdir $@)\'
	@$(CXX) $(CXXFLAGS) $(DEFINES) $(INCPATH) -MM $< > $@ 

# compiling
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(DEFINES) $(INCPATH) -o $(PRJ)/$@ $<
%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(DEFINES) $(INCPATH) -o $(PRJ)/$@ $<
%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $(DEFINES) $(INCPATH) -o $(PRJ)/$@ $<
%.o: %.C
	$(CXX) -c $(CFLAGS) $(DEFINES) $(INCPATH) -o $(PRJ)/$@ $<
%.o: %.c 
	$(CC) -c $(CFLAGS) $(DEFINES) $(INCPATH) -o $(PRJ)/$@ $<


clean:
	@echo $(MARK) making clean
	@rm -R $(PRJ); rm -f $(TARGET) core

tar:
	@echo $(MARK) storing to tar
	@tar cf  $(TARGET)-`date +%y%m%d`.tar     Makefile* $(ARC) $(HDR) $(SRC)
gz:
	@echo $(MARK) storing to tar.gz
	@tar czf $(TARGET)-`date +%y%m%d`.tar.gz  Makefile* $(ARC) $(HDR) $(SRC)
bz2:
	@echo $(MARK) storing to tar.bz2
	@tar cjf $(TARGET)-`date +%y%m%d`.tar.bz2 Makefile* $(ARC) $(HDR) $(SRC)

nlines:
	@wc $(SRC) $(HDR) -l
nbytes:
	@wc $(SRC) $(HDR) -c

sync:
	@echo $(MARK) syncing project files with system time
	@touch -m $(TARGET) Makefile* `$(MAKE) -s get_files` $(PRJ)/* 

install: $(TARGET)
	@echo $(MARK) installing 
	@mkdir -p $(BIN_DIR) 
	@cp  $(TARGET) $(BIN_DIR)
	@strip $(BIN_DIR)/$(TARGET)
ifneq (LIB_DIR,)
	@mkdir -p $(LIB_DIR)
	@cp -r $(LIB_FILES) $(LIB_DIR)  
endif

get_name:
	@echo $(TARGET)
get_prj:
	@echo $(PRJ)
get_files:
	@echo $(HDR) $(SRC)
get_param:
	@echo $(PARAM)
get_sources:
	@echo $(SRC)
get_headers:
	@echo $(HDR)
