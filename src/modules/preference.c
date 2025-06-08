/**
    -----------------------------------------------------------

 	easyVGL
 	modules/preference.h    2025/6/8

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#include "preference.h"

#define EMPTY_STR ""
#define DEFAULT_SCREEN_LIGHTEN 50
#define DEFAULT_VOLUME 50

reflect_item_t standardJson_ref_tbl[] = {
        _property_string(StandardJSON, name),
        _property_string(StandardJSON, description),
        _property_string(StandardJSON, version),
        _property_int(StandardJSON, createtime),
        _property_int(StandardJSON, lasttime),
        _property_end()
};

#define PreferenceReflectDef( ID, PropReflects... ) \
reflect_item_t PreferenceReflect##ID[] = \
{\
        _property_string(Preference##ID, name),\
        _property_string(Preference##ID, description),\
        _property_string(Preference##ID, version),\
        _property_int(Preference##ID, createtime),\
        _property_int(Preference##ID, lasttime),\
        PropReflects,\
        _property_end() \
};


PreferenceReflectDef( User,
    _property_int(PreferenceUser,screenLighten),
    _property_int(PreferenceUser,volume),
    _property_bool(PreferenceUser,wifi_enabled),
    _property_bool(PreferenceUser,audio_enabled),
    _property_string(PreferenceUser ,wifissid),
    _property_string(PreferenceUser ,wifipass)
);

PreferenceReflectDef( Factory,
    _property_string(PreferenceFactory ,wifissid),
    _property_string(PreferenceFactory ,wifipass)
);

static PreferenceManager * cManagerGl;


/**

PlayList playList;

Decode
csonJsonStr2Struct(jStr, &playList, play_list_ref_tbl);

Encode
char* jstrOutput;
csonStruct2JsonStr(&jstrOutput, &playList, play_list_ref_tbl);

 */

static PreferenceUser * userPreference = NULL;
static PreferenceFactory * factoryPreference = NULL;

static void syncUserPreference()
{

    char * buf;
    csonStruct2JsonStr( &buf, userPreference, PreferenceReflectUser);

    printf("UserJson Sting %s \n", buf);

    write_file( USER_PREFERENCE_FILE, (uint8_t*)buf, strlen(buf));

    free(buf);
}

static void syncFactoryPreference()
{

    char * buf;
    csonStruct2JsonStr( &buf, factoryPreference, PreferenceReflectFactory);

    printf("FactoryJson Sting %s \n", buf);

    write_file( USER_PREFERENCE_FILE, (uint8_t*)buf, strlen(buf));

    free(buf);
}

static void checkUserPreference()
{
    if (!userPreference->name)
        userPreference->name = "User.json";

    if (!userPreference->description)
        userPreference->description = "File saved user's preferences.";

    if (!userPreference->wifi_enabled)
        userPreference->wifi_enabled = false;

    if (!userPreference->wifissid)
        userPreference->wifissid = EMPTY_STR;

    if (!userPreference->wifipass)
        userPreference->wifipass = EMPTY_STR;

    if (!userPreference->volume)
        userPreference->volume = DEFAULT_VOLUME;

    if (!userPreference->audio_enabled)
        userPreference->audio_enabled = true;

    if (!userPreference->screenLighten)
        userPreference->screenLighten = DEFAULT_SCREEN_LIGHTEN;

}

static void initUserPreference()
{

    long file_len = 0;

    char * jsonStr = read_file( USER_PREFERENCE_FILE, &file_len );

    CNewAt( userPreference, PreferenceUser);

    csonJsonStr2Struct(jsonStr, userPreference, PreferenceReflectUser);

    checkUserPreference();

    free(jsonStr);

    syncUserPreference();
}

static void initFactoryPreference()
{

    long file_len = 0;

    char * jsonStr = read_file( FACTORY_PREFERENCE_FILE, &file_len );

    CNewAt( factoryPreference, PreferenceFactory);

    csonJsonStr2Struct(jsonStr, factoryPreference, PreferenceReflectFactory);

    free(jsonStr);

}

void setUserPreferenceInt( PreferenceUserKey key, int value )
{
    switch (key) {
        case UserPrefKey_volume:
            userPreference->volume = value;
            break;
        case UserPrefKey_screenLighten:
            userPreference->screenLighten = value;
            break;
        default:
            break;
    }
    syncUserPreference();
}

void setUserPreferenceBool( PreferenceUserKey key, bool value )
{
    switch (key) {
        case UserPrefKey_wifi_enabled:
            userPreference->wifienabled = value;
            break;
        case UserPrefKey_audio_enabled:
            userPreference->audioenabled = value;
            break;
        default:
            break;
    }
    syncUserPreference();
}

void setUserPreferenceStr( PreferenceUserKey key, const char * str )
{
    char * buf = malloc(strlen(str)+1);
    memset(buf,0,strlen(str)+1);
    memcpy(buf,str, strlen(str));

    switch (key) {
        case UserPrefKey_name:
            free(userPreference->name);
            userPreference->name = buf;
            break;
        case UserPrefKey_description:
            free(userPreference->description);
            userPreference->description = buf;
            break;
        case UserPrefKey_wifissid:
            free(userPreference->wifissid);
            userPreference->wifissid = buf;
            break;
        case UserPrefKey_wifipass:
            free(userPreference->wifipass);
            userPreference->wifipass = buf;
            break;
        default:
            break;
    }
    syncUserPreference();
}

void setFactoryPreferenceStr( enum PreferenceFactoryKey_e key, const char * str )
{
    char * buf = malloc(strlen(str)+1);
    memset(buf,0,strlen(str)+1);
    memcpy(buf,str, strlen(str));

    switch (key) {
        case FactoryPrefKey_name:
            free(factoryPreference->name);
            factoryPreference->name = buf;
            break;
        case FactoryPrefKey_wifissid:
            free(factoryPreference->wifissid);
            factoryPreference->wifissid = buf;
            break;
        case FactoryPrefKey_wifipass:
            free(factoryPreference->wifipass);
            factoryPreference->wifipass = buf;
            break;
        default:
            break;
    }
    syncFactoryPreference();
}

void setFactoryPreferenceBool( PreferenceFactoryKey key, bool value )
{
    switch (key) {
        default:
            break;
    }
    syncFactoryPreference();
}

const PreferenceUser * getUserPreference()
{
    if (userPreference==NULL) initUserPreference();

    return userPreference;
}

const PreferenceFactory * getFactoryPreference()
{
    if (factoryPreference==NULL) initFactoryPreference();

    return factoryPreference;
}

const PreferenceManager * preferenceManagerCreate()
{
    CNewAt(cManagerGl, PreferenceManager);

    initUserPreference();

    initFactoryPreference();

    return cManagerGl;

}
