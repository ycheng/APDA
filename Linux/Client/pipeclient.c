//#include <linux/sched.h>
//#include <linux/fcntl.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>          4
#include <errno.h>

#include <linux/mman.h>
#include <linux/fb.h>
#include <sys/ipc.h>
#include <sys/sem.h>
//#include <unistd.h>

#include <Common.h>
#include "wisapi.h"


#define	WTransFunction(type)		(funcCount[(type/100-100)].count+(type%100))

#define	false		FALSE
#define	true		TRUE

struct FuncCount {
	int	index;
	int	count;
} funcCount[] = {
	{ 100, 0 },
   { 101, 4 },
   { 102, 13 },
   { 103, 29 },
   { 104, 35 },
   { 105, 38 },
   { 106, 42 },
   { 107, 62 },
   { 108, 68 },
   { 109, 136 },
   { 110, 142 },
   { 111, 151 },
   { 112, 158 },
   { 113, 210 },
   { 114, 226 },
   { 115, 230 },
   { 116, 242 },
   { 117, 259 },
   { 118, 324 },
   { 119, 343 },
   { 120, 348 },
   { 121, 354 },
   { 122, 357 },
   { 123, 379 },
   { 124, 393 },
   { 125, 410 },
   { 126, 454 },
   { 127, 468 },
   { 128, 471 },
   { 129, 473 },
   { 130, 514 },
   { 131, 517 },
   { 132, 538 },
   { 133, 542 },
   { 134, 549 },
   { 135, 553 },
   { 136, 555 },
   { 137, 564 },
   { 138, 566 },
   { 139, 572 },
   { 140, 578 },
   { 141, 579 },
   { 142, 583 },
   { 143, 591 },
   { 144, 601 },
   { 145, 618 },
   { 146, 622 },
   { 147, 628 },
   { 148, 633 },
   { 149, 652 },
   { 150, 655 },
   { 151, 680 },
   { 152, 713 },
   { 153, 771 },
   { 154, 809 },
   { 155, 826 },
   { 156, 829 },
   { 157, 832 },
   { 158, 836 },
   { 159, 842 },
	{ 160, 922 }
};


int		DisplayDev;	// the Display and touch pad device
unsigned char* pipe_ram;
FormType	*ActiveForm;
int	 sem_callid;

Boolean GetParameter (void *ptr, int length, int offset)
{
//if ((offset != 15011)&&(offset != 15117)&&(offset != 12608)&&((offset<11700)||(offset>=11800)) )
//printf ("Call Function [%d][%d]\n", offset,WTransFunction(offset));
	memcpy (ptr, &(pipe_ram[APIADDRESSOFFSET+WTransFunction(offset)*sizeof(void *)]), length);
	return	true;
}

Char *StrIToA(Char *s, Int32 i)
{
	int	count=0;
	int	dec, num;
	char	buffer[10];

	if ( !s )	return NULL;

	do {
		dec = i%10;
		i = i/10;
		buffer[count] = dec + '0';
		count++;
	} while (i != 0);

	if ( count > 10 )
		count = 10;
	for ( num = 0; num < count; num++ ) {
		s[num] = buffer[count-num-1];
	}
	s[num] = 0;

	return	s;
}



Boolean VSetRCPFile(char *filename)
{
	Boolean (*VSetRCPFileP) (char *filename);

	GetParameter (&VSetRCPFileP, sizeof(void *), pVSetRCPFile);
	return	(*VSetRCPFileP) (filename);
}


int GetPipeMemory ()
{
	char	*env;
	int	size;
	unsigned char* video_ram;
	struct fb_fix_screeninfo fb_fix;
	struct fb_var_screeninfo fb_var;

	if (!(env = (char *)getenv("FRAMEBUFFER")))
		env = "/dev/fb0";
	if ((DisplayDev = open(env,O_RDWR)) < 0) {
		printf("Error opening %s:. Check kernel config\n",env);
		return -1;
	}
	if (ioctl(DisplayDev,FBIOGET_FSCREENINFO,&fb_fix) == -1 ||
       ioctl(DisplayDev,FBIOGET_VSCREENINFO,&fb_var) == -1) {
		printf("Error reading screen info.\n");
		close(DisplayDev);
		return -1;
	}
	size = fb_fix.line_length * fb_var.yres+4096;
	if ((video_ram = (char *)mmap(NULL,size,PROT_READ | PROT_WRITE,0,DisplayDev,0)) == NULL) {
		printf("Error mmaping %s:\n",env);
		close(DisplayDev);
		return -1;
	}
//	printf("%s: allocated %d bytes @ 0x%p from %s (%dx%d)\n",env,size,video_ram,fb_fix.id,fb_var.xres,fb_var.yres);

	pipe_ram = video_ram+fb_fix.line_length * fb_var.yres;

	return	0;
}

int Initialize_System ()
{

	if ( GetPipeMemory () != errNone ) {
		printf ("Screen initialize error\n");
		return	-1;
	}

	if( (sem_callid = semget( sem_callkey, 1, IPC_CREAT )) == -1 ) {
		perror( "SERVER: semget" );
	}

	return	0;
}

//
// This is the main server loop which initialises the server, services
// the clients, and shuts the server down when there are no more clients.
//
int
main(int argc, char *argv[])
{
//	int	address = 0xd0c02580;
//	pipe_ram = argv[1];
//	memcpy (&pipe_ram, address, sizeof(unsigned char *));
//	printf ("pipe[%x]", pipe_ram);
	struct sembuf lock_sembuf[1];

	if ( Initialize_System () > 0 )
		printf ("Client Initialize system\n");

	if ( VSetRCPFile (argv[1]) ) {
		PilotMain( 0, NULL, 0 );
	}

	// close pipe when exit program
	close (DisplayDev);

	// finished client application, wake up server
	lock_sembuf[0].sem_num   =  0;
	lock_sembuf[0].sem_op    =  -1;
	lock_sembuf[0].sem_flg   =  0;

	if( semctl( sem_callid, 0, SETVAL, 1) != 0 ) {
		perror( "CLIENT: semctl" );
	}

	return 0;
}

