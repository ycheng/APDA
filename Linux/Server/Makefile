LIBDIR          =       ../ApiLib

LIBRARY0	=	$(LIBDIR)/Control.o $(LIBDIR)/Database.o $(LIBDIR)/EventLib.o $(LIBDIR)/Field.o
LIBRARY1	=	$(LIBDIR)/Font.o $(LIBDIR)/FrmDDK.o $(LIBDIR)/File.o $(LIBDIR)/Text.o $(LIBDIR)/VSysSDK.o
LIBRARY2	=	$(LIBDIR)/List.o $(LIBDIR)/Menu.o $(LIBDIR)/Memory.o $(LIBDIR)/Category.o
LIBRARY3	=	$(LIBDIR)/Parser.o $(LIBDIR)/Rectangle.o $(LIBDIR)/String.o $(LIBDIR)/SysManager.o
LIBRARY4	=	$(LIBDIR)/Table.o $(LIBDIR)/Time.o $(LIBDIR)/VCommon.o $(LIBDIR)/VPdaSDK.o $(LIBDIR)/Window.o
LIBRARY5	=	$(LIBDIR)/WisSDK.o $(LIBDIR)/VxDDK.o $(LIBDIR)/Graffiti.o $(LIBDIR)/HandWriting.o $(LIBDIR)/HWUtility.o
LIBRARY		=	$(LIBRARY0) $(LIBRARY1) $(LIBRARY2) $(LIBRARY3) $(LIBRARY4) $(LIBRARY5)
APILIB		=	servapi1.o servapi2.o servapi3.o servapi4.o servapi5.o servapi6.o servapi7.o servapi8.o servapi9.o
TARGET		=	servmain
OBJECTS 	=	$(LIBRARY) $(APILIB) $(TARGET).o
LOCAL_CFLAGS	=	-g
OUTDIR		=	../bin/

include 	../App.mk

CFLAGS		+=	-DLINUX -I../include