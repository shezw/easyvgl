/**
    -----------------------------------------------------------

 	easyVGL
 	porting/wasm/wifi.h  2025/6/7

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_PORTING_API_WLAN_H
#define EVG_PORTING_API_WLAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"

void EVG_Debug(const char* format, ...);

#define EVG_WLAN_MAX_RETRY 3

typedef enum {

    EVG_AP_StatusIdle,
    EVG_AP_StatusReady,
    EVG_AP_StatusWaitingConnect,
    EVG_AP_StatusConnecting,
    EVG_AP_StatusBroadcast,
    EVG_AP_StatusConnected,
    EVG_AP_StatusFailed

} EVG_AP_WorkingStatus;

typedef enum {

    EVG_STA_StatusIdle,
    EVG_STA_StatusReady,
    EVG_STA_StatusWaitingConnect,
    EVG_STA_StatusDhcp,
    EVG_STA_StatusConnecting,
    EVG_STA_StatusConnected,
    EVG_STA_StatusFailed

} EVG_STA_WorkingStatus;

typedef struct EVG_STA_ConnectionStatus_t{
    char ssid[128];
    int ssidLen;
    char ip[16];
    int ipLen;
    int rssi;
    int signalStr;
    int channel;
    EVG_STA_WorkingStatus status;
} EVG_STA_ConnectionStatus;

typedef void (*EVG_STA_StatusNotifier)( EVG_STA_ConnectionStatus * status );

void EVG_Wlan_Reset();
void EVG_Wlan_Init();
void EVG_Wlan_Destroy();
int  EVG_Wlan_Open();

void EVG_Wlan_ChangeMode( int mode );
void EVG_Wlan_UseAPMode();
void EVG_Wlan_UseSTAMode();

bool EVG_Wlan_IsAP();
bool EVG_Wlan_IsSTA();

void EVG_Wlan_PrintInfo();

bool EVG_Set_APConfig( const char *, const char * );

bool EVG_AP_IsConnected();

typedef struct RouterInfo_t
{
    char ssid[64];
    char mac[20];
    bool enc;
    int  str; //  0-5

} RouterInfo;

typedef void (*EVG_STA_ScanResultNotifier)( RouterInfo ** routerList, int routerCount );

void EVG_STA_SetScanNotifier( EVG_STA_ScanResultNotifier callback );

void EVG_STA_Scan( EVG_STA_ScanResultNotifier callback );

void EVG_AP_Start( const char * apssid, const char * appsw );
void EVG_AP_Connect( const char * ssid, int ssid_len, const char * psw, int psw_len);
void EVG_AP_Disconnect();
void EVG_AP_PrintInfo();

void EVG_STA_SetStatusNotifier( EVG_STA_StatusNotifier callback );

void EVG_STA_FakeConnect();
void EVG_STA_Connect( const char * ssid, int ssid_len, const char * psw, int psw_len);
void EVG_STA_Disconnect();
void EVG_STA_PrintInfo();
bool EVG_STA_IsConnected();
void EVG_STA_StatusToData( const EVG_STA_ConnectionStatus * status, char * data, int * dataLen );
void EVG_STA_WorkingStatusEnumString( EVG_STA_WorkingStatus stEnum, char * string, int * strLen );

void EVG_STA_DisconnectNotify();

bool ipAddressValid( char * ip );


#ifdef __cplusplus
}
#endif

#endif //EVG_PORTING_API_WLAN_H
