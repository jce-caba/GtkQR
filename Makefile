

CC=gcc
CCFLAGS= -Wall -O2
LDFLAGS= -shared



# FOLDERS

INCLUDE= include

SRC= src
UTILITIES=$(SRC)/utilities
GTK=$(SRC)/Gtk
UI=$(SRC)/UI
ENCODINGS=$(SRC)/encodings

OUTPUT=build
OBJECTS=$(OUTPUT)/obj
OBJECTS_GTK=$(OUTPUT)/objGtk




ifeq ($(PREFIX),)
    PREFIX := /usr
endif



#VERSION
VERSION= 3
VERSION_GTK_4=4.0
VERSION_GTK_3=3.0
VERSION_GTK_2=2.0


ifneq ("$(wildcard $(OUTPUT)/version)","")
$(eval VERSION=$(shell cat $(OUTPUT)/version));
endif

ifeq ($(VERSION),4)
VERSION_GTK=$(VERSION_GTK_4)
PKG_CONFIG_INCLUDE= `pkg-config gtk4 --cflags`
PKG_CONFIG_LIBS= `pkg-config gtk4 --libs`	
else ifeq ($(VERSION),3)
VERSION_GTK=$(VERSION_GTK_3)
PKG_CONFIG_INCLUDE=`pkg-config gtk+-3.0 --cflags`	
PKG_CONFIG_LIBS=`pkg-config gtk+-3.0 --libs`
else ifeq ($(VERSION),2)
VERSION_GTK=$(VERSION_GTK_2)
PKG_CONFIG_INCLUDE= `pkg-config gtk+-2.0 --cflags`	
PKG_CONFIG_LIBS= `pkg-config gtk+-2.0 --libs`
else	
$(error ERROR: Invalid version,only VERSION=2,VERSION=3 or VERSION=4)
endif

TARGET=$(OUTPUT)/libgtkqr$(VERSION_GTK).so
TARGET_NON_GUI=$(OUTPUT)/libqrutils.so
TARGET_NON_GUI_LIB=lqrutils
PKG_CONFIG_FILE=gtkqr+-$(VERSION_GTK).pc
PKG_CONFIG_FILE_NO_UI=qrutils.pc
TARGET_LIB=lgtkqr$(VERSION_GTK)



SRCS    := $(wildcard $(UTILITIES)/*.c)
OBJS    := $(patsubst $(UTILITIES)/%.c,$(OBJECTS)/%.o,$(SRCS))
SRCS    := $(wildcard $(UI)/*.c)
OBJS2    := $(patsubst $(UI)/%.c,$(OBJECTS)/%.o,$(SRCS))
SRCS    := $(wildcard $(ENCODINGS)/*.c)
OBJS3    := $(patsubst $(ENCODINGS)/%.c,$(OBJECTS)/%.o,$(SRCS))


#FUNCTIONS
define create_folder
	@if [ ! -d $(1) ]; then mkdir $(1); fi
	@if [ ! -d $(2) ]; then mkdir $(2); fi
	@if [ ! -d $(3) ]; then mkdir $(3); fi
endef


define create_pkg_file	
	@echo "prefix=" $(2)  >> $(1);
	@echo "exec_prefix=${2}" >> $(1);
        @echo "libdir=${2}/lib" >> $(1);
	@echo "includedir=${2}/include/gtkQR\n" >> $(1);
	@echo "Name: gtkqr" >> $(1);
	@echo "Description: QR widget for gtk" >> $(1);
	@echo "Version: 1.0.0\n" >> $(1);
	@echo "Requires:" >> $(1);
        @echo "Libs: -L${2}/lib -$(3) -$(4)" >> $(1);
        @echo "Cflags: -I${2}/include/gtkQR" >> $(1);

endef

define create_pkg_file_non_gui 	
	@echo "prefix=" $(2)  >> $(1);
	@echo "exec_prefix=${2}" >> $(1);
        @echo "libdir=${2}/lib" >> $(1);
	@echo "includedir=${2}/include/gtkQR\n" >> $(1);
	@echo "Name: qrutils" >> $(1);
	@echo "Description: QR without widget" >> $(1);
	@echo "Version: 1.0.0\n" >> $(1);
	@echo "Requires:" >> $(1);
        @echo "Libs: -L${2}/lib -$(3)" >> $(1);
        @echo "Cflags: -I${2}/include/gtkQR" >> $(1);

endef


all: $(TARGET)
	
$(TARGET): $(TARGET_NON_GUI) $(OBJECTS_GTK)/QrDrawData.o $(OBJECTS_GTK)/gtkQR.o
	$(CC) $(LDFLAGS) $(OBJECTS_GTK)/QrDrawData.o $(OBJECTS_GTK)/gtkQR.o -L$(OUTPUT) -$(TARGET_NON_GUI_LIB)  -o $@
	@if [ ! -f $(OUTPUT)/version ]; then echo $(VERSION)  >> $(OUTPUT)/version; fi  
	
$(OBJECTS_GTK)/%.o:$(wildcard $(GTK)/*.c)
	$(call create_folder,$(OUTPUT),$(OBJECTS),$(OBJECTS_GTK))
	$(CC) $(CCFLAGS)  -I$(INCLUDE) $(PKG_CONFIG_INCLUDE) -c $(patsubst $(OBJECTS_GTK)/%.o,$(GTK)/%.c,$@) -o $@	
	
	
$(TARGET_NON_GUI): $(OBJS) $(OBJS2) $(OBJS3)	
	$(CC) $(LDFLAGS) $(PKG_CONFIG_LIBS) $(wildcard $(OBJECTS)/*.o)  -o $@
	

$(OBJS):$(wildcard $(UTILITIES)/*.c)
	$(call create_folder,$(OUTPUT),$(OBJECTS),$(OBJECTS_GTK))
	$(CC) $(CCFLAGS)  -I$(INCLUDE)  -c $(patsubst $(OBJECTS)/%.o,$(UTILITIES)/%.c,$@) -o $@ 
	
$(OBJS2):$(wildcard $(UI)/*.c)
	$(call create_folder,$(OUTPUT),$(OBJECTS),$(OBJECTS_GTK))
	$(CC) $(CCFLAGS)   -I$(INCLUDE)  -c $(patsubst $(OBJECTS)/%.o,$(UI)/%.c,$@) -o $@ 

$(OBJS3):$(wildcard $(ENCODINGS)/*.c)
	$(call create_folder,$(OUTPUT),$(OBJECTS),$(OBJECTS_GTK))	
	$(CC) $(CCFLAGS)  -I$(INCLUDE)  -c $(patsubst $(OBJECTS)/%.o,$(ENCODINGS)/%.c,$@) -o $@ 

	
doxygen:
	@echo Generate Doxygen documentation
	@if [ ! -d DOC ]; then mkdir DOC; fi
	doxygen Doxyfile	
	@echo '<meta http-equiv="REFRESH" content="0;URL=DOC/html/index.html">'  >> Documentation.html;	
	
	
.PHONY: clean

clean :
	@rm -r $(OBJECTS)/*.o
	@rm -r $(OBJECTS_GTK)/*.o
	@if [ -f $(OUTPUT)/version ]; then rm  $(OUTPUT)/version; fi
	
.PHONY: install	
	
install: $(TARGET) $(TARGET_NON_GUI)
	
	@if [ -f $(PKG_CONFIG_FILE) ]; then rm  $(PKG_CONFIG_FILE); fi
	@if [ -f $(PKG_CONFIG_FILE_NO_UI) ]; then rm  $(PKG_CONFIG_FILE_NO_UI); fi
	install -d $(DESTDIR)$(PREFIX)/lib/              
	install -m 644 $(TARGET) $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(TARGET_NON_GUI) $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/gtkQR
	install -m 644 $(INCLUDE)/QrUtils.h $(DESTDIR)$(PREFIX)/include/gtkQR
	install -m 644 $(INCLUDE)/QrDefinitions.h $(DESTDIR)$(PREFIX)/include/gtkQR
	install -m 644 $(INCLUDE)/gtkQR.h $(DESTDIR)$(PREFIX)/include/gtkQR
	$(call create_pkg_file,$(PKG_CONFIG_FILE),$(DESTDIR)$(PREFIX),$(TARGET_NON_GUI_LIB),$(TARGET_LIB))    
	$(call create_pkg_file_non_gui,$(PKG_CONFIG_FILE_NO_UI),$(DESTDIR)$(PREFIX),$(TARGET_NON_GUI_LIB))
	$(eval IN=$(shell pkg-config --variable pc_path pkg-config))
	$(eval IN=$(word 1, $(subst :, ,${IN})))
	install -d ${IN} 
	install -m 644 $(PKG_CONFIG_FILE) ${IN}
	install -m 644 $(PKG_CONFIG_FILE_NO_UI) ${IN}
	@if [ -f $(PKG_CONFIG_FILE) ]; then rm  $(PKG_CONFIG_FILE); fi
	@if [ -f $(PKG_CONFIG_FILE_NO_UI) ]; then rm  $(PKG_CONFIG_FILE_NO_UI); fi
	@echo "\n\n"
	@echo "*********************************************************"
	@echo "*                                                       *"
	@echo "*  finished process, use:                               *"
	@echo "*  pkg-config gtkqr+-$(VERSION_GTK) --cflags  --libs               *"
	@echo "*  in non UI, use:                                      *"
	@echo "*  pkg-config qrutils --cflags  --libs                  *"
	@echo "*                                                       *"
	@echo "*********************************************************"
	
