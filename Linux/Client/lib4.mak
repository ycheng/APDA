# Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
# This file is part of the Linux-8086 C library and is distributed
# under the GNU Library General Public License.


CLIENTLIBDIR    =       ../ClientLib/

LIBC=$(CLIENTLIBDIR)libclient4.a

include ./make.rules

LIB4SRC=lib4.c
LIB4OBJ=FntAverageCharWidth.o		\
FntBaseLine.o				\
FntCharHeight.o			\
FntCharsInWidth.o		\
FntCharsWidth.o			\
FntCharWidth.o			\
FntDefineFont.o			\
FntGetFont.o			\
FntGetFontPtr.o			\
FntGetScrollValues.o		\
FntLineHeight.o			\
FntLineWidth.o			\
FntSetFont.o			\
FntWidthToOffset.o		\
FntWordWrap.o			\
FntWordWrapReverseNLines.o	\
FontSelect.o			\
FrmAlert.o      \
FrmCloseAllForms.o              \
FrmCopyLabel.o                   \
FrmCopyTitle.o                          \
FrmCustomAlert.o                \
FrmCustomResponseAlert.o      \
FrmDeleteForm.o      \
FrmDispatchEvent.o      \
FrmDoDialog.o                    \
FrmDrawForm.o      \
FrmEraseForm.o      \
FrmGetActiveForm.o      \
FrmGetActiveFormID.o      \
FrmGetControlGroupSelection.o      \
FrmGetControlValue.o      \
FrmGetFirstForm.o      \
FrmGetFocus.o      \
FrmGetFormBounds.o      \
FrmGetFormId.o      \
FrmGetFormPtr.o      \
FrmGetGadgetData.o      \
FrmGetLabel.o      \
FrmGetNumberOfObjects.o      \
FrmGetObjectBounds.o      \
FrmGetObjectId.o      \
FrmGetObjectIndex.o      \
FrmGetObjectPosition.o      \
FrmGetObjectPtr.o      \
FrmGetObjectType.o      \
FrmGetTitle.o      \
FrmGetWindowHandle.o      \
FrmGotoForm.o      \
FrmHandleEvent.o      \
FrmHelp.o      \
FrmHideObject.o      \
FrmInitForm.o      \
FrmNewBitmap.o      \
FrmNewForm.o      \
FrmNewGadget.o      \
FrmNewGsi.o      \
FrmNewLabel.o      \
FrmPointInTitle.o      \
FrmPopupForm.o      \
FrmRemoveObject.o      \
FrmRestoreActiveState.o      \
FrmReturnToForm.o      \
FrmSaveActiveState.o      \
FrmSaveAllForms.o      \
FrmSetActiveForm.o      \
FrmSetCategoryLabel.o      \
FrmSetControlGroupSelection.o      \
FrmSetControlValue.o      \
FrmSetEventHandler.o      \
FrmSetFocus.o      \
FrmSetGadgetData.o      \
FrmSetGadgetHandler.o      \
FrmSetMenu.o      \
FrmSetObjectBounds.o      \
FrmSetObjectPosition.o      \
FrmSetTitle.o      \
FrmShowObject.o      \
FrmUpdateForm.o      \
FrmUpdateScrollers.o      \
FrmValidatePtr.o      \
FrmVisible.o





OBJ= $(LIB4OBJ)

#CFLAGS=$(ARCH) $(CCFLAGS) $(DEFS)

all: $(LIBC)
	@$(RM) $(OBJ)


$(LIBC): $(LIBC)($(OBJ))

$(LIBC)($(LIB4OBJ)): $(LIB4SRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o



transfer:
	-@rm -f ../include/stdio.h
	cp -p stdio.h ../include/.

transfer2:
	cp -p ../include/stdio.h .

clean:
	rm -f *.o $(CLIENTLIBDIR)libclient4.a

#$(LIBC)($(OBJ)): transfer2 stdio.h

