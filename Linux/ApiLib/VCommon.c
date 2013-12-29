/*========================================================
  VCommon.c
  all routine is running with Platform non-related,
  simulated the common use function in Palm OS.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0507, 2001 by Jerry Chu
					 0528, 2001 by Jerry Chu, add 6 preference
									routines
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#define noPreferenceFound	-1
#define preferenceDataVersion	2

Char	*sysPassword = NULL;
SystemPreferencesType	sysPrefs;
SystemPreferencesType	appPrefs;

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PwdExists
//
// DESCRIPTION: This routine return true if the system password is set.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns true if the system password is set.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean PwdExists ()
{
	if ( sysPassword == NULL ) {
		return	false;
	} else {
		return	true;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PwdRemove
//
// DESCRIPTION: This routine remove the encrypted password string and
//					 recover data hidden in databases.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void PwdRemove (void)
{
	Vfree (sysPassword);
	sysPassword = NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PwdSet
//
// DESCRIPTION: This routine use a passed string as the new password. The
//					 password is stored in an encrypted form.
//
// PARAMETERS:  (Char *) oldPassword - The old password must be successfully
//									verified or the new password isn't accepted.
//					 (Char *) newPassword - Char *to a string to use as the
//									password. NULL means no password.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void PwdSet (Char *oldPassword, Char *newPassword)
{
	if ( sysPassword == NULL ) {
		if ( oldPassword == NULL ) {
			sysPassword = (Char *) Vmalloc ( sizeof (newPassword));
			Vstrcpy ( sysPassword, newPassword ) ;
		}
	} else if ( Vstrcmp (sysPassword, oldPassword) == 0 ) {
		sysPassword = (Char *) Vrealloc ( sysPassword, sizeof (newPassword));
		Vstrcpy ( sysPassword, newPassword ) ;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PwdVerify
//
// DESCRIPTION: This routine verify that the string passed matches the
//					 system password.
//
// PARAMETERS:  (Char *) string - String to compare to the system password.
//									NULL means no current password.
//
// RETURNED:    Returns true if the string matches the system password.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean PwdVerify (Char *string)
{
	if ( (string == NULL) && (sysPassword == NULL) ) {
		return	true;
	}

	if( Vstrcmp (string, sysPassword) == 0 ) {
		return	true;
	} else {
		return	false;
	}
}



// below is preference relative routines
////////////////////////////////////////////////////////////////////////
// FUNCTION:    PrefGetAppPreferences
//
// DESCRIPTION: This routine return a copy of an application's preference.
//
// PARAMETERS:  (UInt32) creator - Application creator.
//					 (UInt16) id - ID number.
//					 (void *) prefs - Pointer to a buffer to hold preference.
//					 (UInt16 *) prefsSize - Pointer to size the buffer passed.
//					 (Boolean) saved - If true, retrieve the saved preferences.
//										If false, retrieve the current preferences.
//
// RETURNED:    Returns the constant noPreferenceFound if the preference
//					 resource wasn't found, else return the size of preference.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 PrefGetAppPreferences (UInt32 creator, UInt16 id, void *prefs,
									  UInt16 *prefsSize, Boolean saved)
{
/*
	if ( saved ) {
		Vmemcpy (prefs, &appPrefs, sizeof (SystemPreferencesType));
		*prefsSize = sizeof (appPrefs);

		return	sizeof (appPrefs);
	} else {
		Vmemcpy (prefs, &sysPrefs, sizeof (SystemPreferencesType));
		*prefsSize = sizeof (sysPrefs);

		return	sizeof (sysPrefs);
	}
*/
	return	noPreferenceFound;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PrefGetAppPreferencesV10
//
// DESCRIPTION: This routine return a copy of an application's preference.
//
// PARAMETERS:  (UInt32) type - Application creator type.
//					 (Int16) version - Version number of the application.
//					 (void *) prefs - Pointer to a buffer to hold preference.
//					 (UInt16) prefsSize - Size the buffer passed.
//
// RETURNED:    Returns false if the preference resource was not found
//					 or the preference resoure contains the wrong version 
//					 number.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/23/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean PrefGetAppPreferencesV10 (UInt32 type, Int16 version, 
											void *prefs, UInt16 prefsSize)
{
	return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PrefGetPreference
//
// DESCRIPTION: This routine return a system preference.
//
// PARAMETERS:  (SystemPreferencesChoice) choice - System preference
//																	choice.
//
// RETURNED:    Returns the system preference.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 PrefGetPreference (SystemPreferencesChoice choice)
{
	switch (choice) {
		case prefVersion:
			return	sysPrefs.version;
			break;
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PrefGetPreferences
//
// DESCRIPTION: This routine return a copy of the system preference.
//
// PARAMETERS:  (SystemPreferencesPtr) p - Pointer to system preferences.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void PrefGetPreferences (SystemPreferencesPtr p)
{
	Vmemcpy (p, &sysPrefs, sizeof (SystemPreferencesType));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PrefSetAppPreferences
//
// DESCRIPTION: This routine set an application's preference in the
//					 preferences database.
//
// PARAMETERS:  (UInt32) creator - Application creator type.
//					 (UInt16) id - Resource ID.
//					 (UInt16) version - Version numer of the application.
//					 (void *) prefs - Pointer to a buffer that holds preference.
//					 (UInt16) prefsSize - Size of the buffer passed.
//					 (Boolean) saved - If true, set the saved preferences.
//										If false, set the current preferences.
//
// RETURNED:    Returns the constant noPreferenceFound if the preference
//					 resource wasn't found, else return the size of preference.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void PrefSetAppPreferences (UInt32 creator, UInt16 id, UInt16 version, 
									 void *prefs, UInt16 prefsSize, Boolean saved)
{
	if ( saved ) {
		Vmemcpy (&appPrefs, prefs, prefsSize);
	} else {
		Vmemcpy (&sysPrefs, prefs, prefsSize);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PrefSetAppPreferencesV10
//
// DESCRIPTION: This routine set an application's preferences in the
//					 preferences database.
//
// PARAMETERS:  (UInt32) creator - Application creator type.
//					 (Int16) version - Version number of the application.
//					 (void *) prefs - Pointer to a buffer to hold preference.
//					 (UInt16) prefsSize - Size the buffer passed.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/23/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void PrefSetAppPreferencesV10 (UInt32 creator, Int16 version, 
											void *prefs, UInt16 prefsSize)
{
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PrefSetPreference
//
// DESCRIPTION: This routine set a system preference.
//
// PARAMETERS:  (SystemPreferencesChoice) choice - A System preference
//																	choice.
//					 (UInt32) value - Value to assign to the item in 
//											SystemPreferenceChoice.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void PrefSetPreference (SystemPreferencesChoice choice, UInt32 value)
{
	switch (choice) {
		case prefVersion:
			sysPrefs.version = (UInt16) value;
			break;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PrefSetPreferences
//
// DESCRIPTION: This routine set the system preferences
//
// PARAMETERS:  (SystemPreferencesPtr) p - Pointer to system preferences.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void PrefSetPreferences (SystemPreferencesPtr p)
{
	Vmemcpy (&sysPrefs, p, sizeof(SystemPreferencesType));
}
