HOMEDIR         =       ../../Linux/

TARGET		=	pmail
OBJECTS 	=	$(HOMEDIR)Client/pipeclient.o $(TARGET).o
LOCAL_CFLAGS	=	-g
OUTDIR		=	../bin/mail/

include 	../../Linux/App.mk

LDFLAGS		+=	-L$(HOMEDIR)ClientLib
lFLAGS		:=	-lclient1 -lclient2 -lclient3 -lclient4 -lclient5 -lclient6 -lclient7 -lclient8 -lclient9 $(lFLAGS)
CFLAGS		:=	-DLINUX -I$(HOMEDIR)include $(CFLAGS)