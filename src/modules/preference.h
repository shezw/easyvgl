/**
    -----------------------------------------------------------

 	easyVGL
 	modules/preference.h    2025/6/8

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_MODULE_PREFERENCE_H
#define EVG_MODULE_PREFERENCE_H

#include "modules.h"

#ifdef __cplusplus
extern "C" {
#endif

#define USER_PREFERENCE_FILE        Preference_default_path"User.json"
#define OTA_PREFERENCE_FILE         Preference_default_path"OTA.json"
#define MACHINE_PREFERENCE_FILE     Preference_default_path"Machine.json"
#define FACTORY_PREFERENCE_FILE     Preference_default_path"Factory.json"
#define RECENT_USE_FILE             Preference_default_path"RecentUse.json"


/* Used by some code below as an example datatype. */
typedef struct StandardJSON_t
{
    char *name;
    char *description;
    char *version;
    u32  createtime;
    u32  lasttime;
} StandardJSON;


#define PreferenceDef( ID, Props ) \
typedef struct Preference##ID##_t\
{\
char *name;\
char *description;\
char *version;\
u32  createtime;\
u32  lasttime;\
Props \
} Preference##ID;


PreferenceDef(User,
    u32 screenLighten;
    u32 volume;
    bool wifi_enabled;
    bool audio_enabled;
    char * wifissid;
    char * wifipass;
);

PreferenceDef(Factory,
    char * wifissid;
    char * wifipass;
);

#define PreferenceKeyDef( ID, keys... ) \
typedef enum Preference##ID##Key_e \
{\
    ID##PrefKey_name,\
    ID##PrefKey_description,\
    ID##PrefKey_version,\
    ID##PrefKey_createtime,\
    ID##PrefKey_lasttime,\
    keys \
} Preference##ID##Key;

PreferenceKeyDef(User,
    UserPrefKey_screenLighten,
    UserPrefKey_volume,
    UserPrefKey_wifi_enabled,
    UserPrefKey_audio_enabled,
    UserPrefKey_wifissid,
    UserPrefKey_wifipass
);

PreferenceKeyDef(Factory,
    FactoryPrefKey_wifissid,
    FactoryPrefKey_wifipass
);

const PreferenceUser * getUserPreference();
void setUserPreferenceInt( PreferenceUserKey key, int value );
void setUserPreferenceBool( PreferenceUserKey key, bool value );
void setUserPreferenceStr( PreferenceUserKey key, const char * str );

#define UserPreference( id ) \
getUserPreference()->id

#define SetUserPreference( id, value )

const PreferenceFactory * getFactoryPreference();
void setFactoryPreferenceInt( PreferenceFactoryKey key, int value );
void setFactoryPreferenceBool( PreferenceFactoryKey key, bool value );
void setFactoryPreferenceStr( PreferenceFactoryKey key, const char * str );

#define FactoryPreference( id ) \
getFactoryPreference()->id

#define SetFactoryPreference( id, value )


typedef struct PreferenceManager_t
{

    void ( * init ) ( void );
    void ( * deinit) ( void );

} PreferenceManager;

const PreferenceManager * preferenceManagerCreate();

#ifdef __cplusplus
}
#endif

#endif //EVG_MODULE_PREFERENCE_H
