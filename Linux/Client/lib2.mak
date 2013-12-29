# Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
# This file is part of the Linux-8086 C library and is distributed
# under the GNU Library General Public License.

CLIENTLIBDIR    =       ../ClientLib/

LIBC= $(CLIENTLIBDIR)libclient2.a

include ./make.rules


LIB2SRC=lib2.c
LIB2OBJ=DmArchiveRecord.o      \
DmAttachRecord.o      \
DmAttachResource.o      \
DmCloseDatabase.o      \
DmCreateDatabase.o      \
DmCreateDatabaseFromImage.o      \
DmDatabaseInfo.o      \
DmDatabaseProtect.o      \
DmDatabaseSize.o      \
DmDeleteCategory.o      \
DmDeleteDatabase.o      \
DmDeleteRecord.o      \
DmDetachRecord.o      \
DmDetachResource.o      \
DmFindDatabase.o      \
DmFindRecordByID.o      \
DmFindResource.o      \
DmFindResourceType.o      \
DmFindSortPosition.o      \
DmGetAppInfoID.o      \
DmGetDatabase.o      \
DmGetDatabaseLocaState.o      \
DmGetLastErr.o      \
DmGetNextDatabaseByTypeCreator.o      \
DmGetRecord.o      \
DmGetResource.o      \
DmGetResourceIndex.o      \
DmGet1Resource.o      \
DmInsertionSort.o      \
DmMoveCategory.o      \
DmMoveRecord.o      \
DmNewHandle.o      \
DmNewRecord.o      \
DmNewReresource.o      \
DmNextOpenDatabase.o      \
DmNumDatabases.o      \
DmNumRecords.o      \
DmNumRecordsInCategory.o      \
DmNumResources.o      \
DmOpenDatabase.o      \
DmOpenDatabaseByTypeCreator.o      \
DmOpenDatabaseInfo.o      \
DmOpenDBNoOvelay.o      \
DmPositionInCategory.o      \
DmQueryNextInCategory.o      \
DmQueryRecord.o      \
DmQuickSort.o      \
DmRecordInfo.o      \
DmReleaseRecord.o      \
DmReleaseResource.o      \
DmRemoveRecord.o      \
DmRemoveResource.o      \
DmRemoveSecretRecord.o      \
DmResizeRecord.o      \
DmResizeResource.o      \
DmResourceInfo.o      \
DmResetRecordStates.o      \
DmSearchRecord.o      \
DmSearchResource.o      \
DmSeekRecordInCategory.o      \
DmSet.o      \
DmSetDatabaseInfo.o      \
DmSetRecordInfo.o      \
DmSetResourceInfo.o      \
DmStrCopy.o      \
DmWrite.o      \
DmWriteCheck.o		\
ErrAlert.o		\
ErrFatalDisplayIf.o		\
ErrDisplayFileLineMsg.o		\
ErrFatalDisplay.o		\
ErrNonFatalDisplayIf.o		\
ErrThrow.o			\
ExgAccept.o			\
ExgDBRead.o			\
ExgDBWrite.o			\
ExgDisconnect.o			\
ExgDoDialog.o			\
ExgPut.o				\
ExgReceive.o			\
ExgRegisterData.o			\
ExgSend.o				\
FtrGet.o					\
FtrGetByIndex.o				\
FtrPtrFree.o				\
FtrPtrNew.o				\
FtrPtrResize.o				\
FtrSet.o					\
FtrUnregister.o






OBJ= $(LIB2OBJ)

#CFLAGS=$(ARCH) $(CCFLAGS) $(DEFS)

all: $(LIBC)
	@$(RM) $(OBJ)
	

$(LIBC): $(LIBC)($(OBJ))

$(LIBC)($(LIB2OBJ)): $(LIB2SRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o



transfer:
	-@rm -f ../include/stdio.h
	cp -p stdio.h ../include/.

transfer2:
	cp -p ../include/stdio.h .

clean:
	rm -f *.o $(CLIENTLIBDIR)libclient2.a

#$(LIBC)($(OBJ)): transfer2 stdio.h

