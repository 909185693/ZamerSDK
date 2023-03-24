#pragma once
#include <algorithm> 
#include "MD5.h"
#include "Http.h"
#include "Json.h"

using namespace std;



#define INTERFACEADDR	TEXT("https://sdk.zamertech.com/api/gamesdk/checkdll.aspx")//正式
#define MAX_RES_LEN	1024*10
#define MAX_CMD_LEN 1024
#define REGMSG_LEN	1024*10


class ZAMERSDK_API  ZamerSDKHelper
{
public:
	//在GameInstance初始化的时候调用SDK；也可在其它地方调用，但要确保在游戏正常运行前调用检验。
	//The SDK is called when GameInstance is initialized; it can also be called elsewhere, but be sure to call and check before the game runs normally.
	//void CallStartBillingThread();
	void CallStartBillingThread(char * DEVELOP_ID, char * CONTENT_ID, char * TOKEN, char * CHECKCODE);
	FString GetDeviceSN();
	int	GetUserId();
	int	GetMerchantId();
	//bool	ZHttpPost(FString JsonStr);
	//void	HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	int ZMVRCheckDll(FString TOKEN, FString CHECKCODE, FString DEVELOP_ID, FString CONTENT_ID);

	bool ZHttpPost(FString postData);

	void HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//时间戳
	FString Timestamp();

	//随机数
	FString GetRandomNumber();
	//md5
	FString FileDigest(FString file);
	FString MD5StringDigest(FString str);

	static bool InitAPI();

	static PTCHAR UpDataZM(UINT Score);

	static FString GetZMPlayerData();

	static bool TransferCommonParms(const PTCHAR AppKey, const PTCHAR Secret);

	static PTCHAR UploadGameProgress(UINT GameId, const PTCHAR GameName, UINT Barrier, UINT Score, const PTCHAR GameStoreDt = NULL, const PTCHAR ProgressFile = NULL);

	static bool DownloadGameProgress(const PTCHAR Url, const PTCHAR Filename);

	static PTCHAR QueryGameProgress(UINT GameId);

	static PTCHAR SaveGameProperty(UINT GameId, UINT ItemSpecId, const PTCHAR ItemVal, const PTCHAR ActionType);

	static PTCHAR QueryGameProperty(UINT GameId);

	static PTCHAR GetOpenId();

	static PTCHAR GetNickname();

	static PTCHAR GetAvatarUrl();

private:
	bool HttpCompleteCallbackfalg = false;

	FString d_id;
	FString c_id;	
	FString bcheckcode ;
	FString btoken;
};

