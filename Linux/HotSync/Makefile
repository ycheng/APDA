# makefile for hotsync
#
# Copyright (C) 2001 by William Liang @ Wiscore Inc.
#
# Date: $Date: 2001/12/06 07:14:10 $
# Version: $Revision: 1.8 $

TARGET		=	hotsync
OBJECTS		=	$(TARGET).o 
ExtraTARGET	=	master slave

OPT		=	-O
DEBUG		=	# -DDEBUG
ACK		=	-DACK
EXPR		=	# -DRAWDATA # -DTIMEOUT 

include ../common/Makefile

CFLAGS		+=	$(OPT) -DSLAVE -DOPENTTY $(ACK) $(DEBUG) $(EXPR)
FLTFLAGS	+=	-z

# other rules
slave:		hotsync.c hotsync.h Makefile
	gcc $(OPT) -Wall -DSLAVE  -DOPENTTY -o $@ $< $(ACK) $(DEBUG) $(EXPR)
                                                                 
master:		hotsync.c hotsync.h Makefile
	gcc $(OPT) -Wall -DMASTER -DOPENTTY -DUSETTYS1 -o $@ $< $(ACK) $(DEBUG) $(EXPR)


# other dependency declaration 
hotsync.o:	hotsync.h Makefile
