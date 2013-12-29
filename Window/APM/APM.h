#ifndef __APPLICATION_MANAGET_H__
#define __APPLICATION_MANAGET_H__

#define	PrefFORM					1000

#define	PrefHELP					1900

#define	PrefMENU					1800

#define	MAINFORM					1001
#define	DELETEFORM				1002

#define	MenuApp					1
#define	ItemInstall				11
#define	ItemDelete				12
#define	ItemBeam					13
#define	ItemCategory			14
#define	ItemInfo					15

#define	MenuOptions				2
#define	ItemPreference			21
#define	ItemAbout				22


typedef struct {
	Char	appName[30];
	Char	appFileName[256];
	Char	rscName[256];
	int	appSize;
} AppList;

AppList					appList[50];

#endif	// __APPLICATION_MANAGET_H__
