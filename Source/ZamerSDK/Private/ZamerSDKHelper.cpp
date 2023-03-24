#include "ZamerSDKHelper.h"
#include <time.h>
#include <objbase.h>
#include "CoreGlobals.h"
#include "Misc/ConfigCacheIni.h"
#include <string>
//SDK接口
//SDKAPI
typedef char* (*StartBillingThread)(char *, char *, char *);
typedef char* (*GetDeviceSNDLL)(void);
typedef int   (*GetUserIdDLL)(void);
typedef int   (*GetMerchantIdDLL)(void);
typedef char* (*GetMerchantNameDLL)(void);
typedef bool(*TransferCommonParmsFunc)(const PTCHAR, const PTCHAR);
typedef PTCHAR(*UploadGameProgressFunc)(UINT, const PTCHAR, UINT, UINT, const PTCHAR, const PTCHAR);
typedef bool(*DownloadGameProgressFunc)(const PTCHAR, const PTCHAR);
typedef PTCHAR(*QueryGameProgressFunc)(UINT);
typedef PTCHAR(*SaveGamePropertyFunc)(UINT, UINT, const PTCHAR, const PTCHAR);
typedef PTCHAR(*QueryGamePropertyFunc)(UINT);
typedef PTCHAR(*GetOpenIdFunc)();
typedef PTCHAR(*GetNicknameFunc)();
typedef PTCHAR(*GetAvatarUrlFunc)();

static void* wDllHandle;
#pragma endregion


//调用实现函数
//Implementation function for calling procedure.
void ZamerSDKHelper::CallStartBillingThread(char *DEVELOP_ID, char *CONTENT_ID, char *TOKEN, char * CHECKCODE)
{
	UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::CallStartBillingThread::StartBillingThread."));


	/*步骤1：检查文件是否存在,不存在则退出游戏！
	* STEP1:Check if the file exists and exit the game if it does not exist!
	*/
	FString filePath = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("Studio/ZamerSDK/ThirdParty/ZamerSDK/Win64"), TEXT("ZMVR.dll"));
	UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::CallStartBillingThread: filePath:%s"), *(filePath));

	if (!FPaths::FileExists(filePath))
	{
		UE_LOG(LogTemp, Error, TEXT("ZMVRSDKHelper::CallStartBillingThread: CheckToken.dll not found!!!"));
		//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("ZMSDK Failed CallStartBillingThread: ZMVR.dll not found!!!"));
		//TODO 友好提示后退出游戏
		//TODO Exit the game after the friendly prompts.
		FGenericPlatformMisc::RequestExit(false);
	}
	UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::CallStartBillingThread: CheckToken.dll was found."));


	/*步骤2：加载dll，加载失败则退出游戏！
	* STEP2: Load dll, exit the game if load faied!
	*/
	void* pDllHandle = FPlatformProcess::GetDllHandle(*filePath);
	if (!pDllHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("ZMVRSDKHelper::CallStartBillingThread: Failed to load CheckToken.dll!!!"));
		//TODO 友好提示后退出游戏
		//TODO Exit the game after the friendly prompts.
		FGenericPlatformMisc::RequestExit(false);
	}
	UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::CallStartBillingThread: CheckToken.dll loaded successfully."));


	/*步骤3：调用"CheckToken"接口,并比对返回的校验码，若检验码不匹配，则退出游戏！
	* STEP3: Call the API-"CheckToken" and compare the returned checksums. If the checksums do not match, exit the game!
	*/
	StartBillingThread func = NULL;
	FString apiName = "StartBillingThread";
	func = (StartBillingThread)FPlatformProcess::GetDllExport(pDllHandle, *apiName);
	FString checkcodeReturn = func(DEVELOP_ID, CONTENT_ID, TOKEN);
	//UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::CallStartBillingThread: return checkcode:%s"), *(checkcodeReturn));
	if (!checkcodeReturn.Equals(CHECKCODE)) {
		UE_LOG(LogTemp, Error, TEXT("ZMVRSDKHelper::CallStartBillingThread: Verification failed!!!"));

		//TODO 友好提示后退出游戏
		//TODO Exit the game after the friendly prompts.

		FGenericPlatformMisc::RequestExit(false);
	}
}

FString ZamerSDKHelper::GetDeviceSN()
{
	UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::::GetDeviceSN."));
	FString filePath = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("Studio/ZamerSDK/ThirdParty/ZamerSDK/Win64"), TEXT("ZMVR.dll"));
	void* pDllHandle = FPlatformProcess::GetDllHandle(*filePath);
	if (!pDllHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("ZMVRSDKHelper::GetDeviceSN: Failed to load CheckToken.dll!!!"));
		//TODO 友好提示后退出游戏
		//TODO Exit the game after the friendly prompts.
		//FGenericPlatformMisc::RequestExit(false);
	}

	GetDeviceSNDLL fundev = NULL;
	FString apiName = "GetDeviceSN";
	fundev = (GetDeviceSNDLL)FPlatformProcess::GetDllExport(pDllHandle, *apiName);
	FString devReturn = fundev();

	return devReturn;
}

int ZamerSDKHelper::GetUserId()
{
	FString filePath = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("Studio/ZamerSDK/ThirdParty/ZamerSDK/Win64"), TEXT("ZMVR.dll"));
	void* pDllHandle = FPlatformProcess::GetDllHandle(*filePath);
	if (!pDllHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("ZMVRSDKHelper::GetDeviceSN: Failed to load CheckToken.dll!!!"));
	}

	GetUserIdDLL funuid = NULL;
	FString apiName = "GetUserId";
	funuid = (GetUserIdDLL)FPlatformProcess::GetDllExport(pDllHandle, *apiName);
	int32 uid = funuid();

	return uid;
}

int ZamerSDKHelper::GetMerchantId()
{
	FString filePath = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("Studio/ZamerSDK/ThirdParty/ZamerSDK/Win64"), TEXT("ZMVR.dll"));
	void* pDllHandle = FPlatformProcess::GetDllHandle(*filePath);
	if (!pDllHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("ZMVRSDKHelper::GetMerchantId: Failed to load ZMVR.dll!!!"));

		//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("ZMSDK Failed to load  GetMerchantId"));
		//TODO 友好提示后退出游戏
		//TODO Exit the game after the friendly prompts.
		//FGenericPlatformMisc::RequestExit(false);
	}

	GetMerchantIdDLL funmid = NULL;
	FString apiName = "GetMerchantId";
	funmid = (GetMerchantIdDLL)FPlatformProcess::GetDllExport(pDllHandle, *apiName);
	int mid = funmid();

	return mid;
}

//获取文件md5值
FString ZamerSDKHelper::FileDigest(FString file)
{
	const char *cfile = TCHAR_TO_ANSI(*file);
	ifstream in(cfile, ios::binary);
	if (!in) return "";
	MD5 md5;
	std::streamsize length;
	char buffer[1024];
	while (!in.eof()) {
		in.read(buffer, 1024);
		length = in.gcount();
		if (length > 0)
			md5.update(buffer, length);
	}
	in.close();
	string filemd5= md5.toString();
	FString FileMD5(filemd5.c_str());
	return FileMD5;
}

//md5加密字符串
FString ZamerSDKHelper::MD5StringDigest(FString str)
{
	std::string MyStdString(TCHAR_TO_UTF8(*str));
	string md5 = MD5(MyStdString).toString();
	FString strmd5(md5.c_str());
	return strmd5;
}

//时间戳
FString ZamerSDKHelper::Timestamp()
{
	char s[100];
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	//localtime_s(timeinfo, &rawtime);
	timeinfo = localtime(&rawtime);
	strftime(s, sizeof(s), "%Y%m%d%H%M%S", timeinfo);
	string time = s;
	FString timestamp(time.c_str());
	return timestamp;
}
//32位随机数
FString ZamerSDKHelper::GetRandomNumber()
{
	time_t t;
	srand((unsigned)time(&t));
	FString random = "";
	for (int i = 0; i < 32; ++i)
		random = random + FString::FromInt((rand() % 9 + 1));
	return random;
}

int ZamerSDKHelper::ZMVRCheckDll(FString TOKEN, FString CHECKCODE, FString DEVELOP_ID, FString CONTENT_ID)
{
	UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::ZMVRCheckDll."));
	FString filePath = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("Studio/ZamerSDK/ThirdParty/ZamerSDK/Win64"), TEXT("ZMVR.dll"));
	//判断文件是否存在
	IPlatformFile& fileManager = FPlatformFileManager::Get().GetPlatformFile();
	if (!fileManager.FileExists(*filePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::ZMVRCheckDll, ZMVR.dll file  not exist"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("error ZMVR.dll file  not exist")));
		FGenericPlatformMisc::RequestExit(false);
	}
	FString filemd5 = FileDigest(filePath);
	//UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::ZMVRCheckDll, filemd5=%s"), *filemd5);
	//时间戳
	FString timestamp = Timestamp();
	//UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::ZMVRCheckDll, timestamp=%s"), *timestamp);
	//32位随机数
	FString reqId = GetRandomNumber();
	//UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::ZMVRCheckDll, reqId=%s"), *reqId);
	//设备码
	FString dn = GetDeviceSN();
	//UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::ZMVRCheckDll, dn=%s"), *dn);
	//签名
	d_id= DEVELOP_ID;
	c_id= CONTENT_ID;
	btoken= TOKEN;
	bcheckcode = CHECKCODE;
	FString sig = bcheckcode + "btoken" + TOKEN + "dn" + dn + "filemd5" + filemd5 + "reqId" + reqId + "timestamp" + timestamp + bcheckcode;
	FString sign = MD5StringDigest(sig);
	//UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::ZMVRCheckDll, sign=%s"), *sign);

	FString postData = "filemd5=" + filemd5 + "&timestamp=" + timestamp + "&btoken=" + TOKEN + "&reqId=" + reqId + "&dn=" + dn + "&sign=" + sign;

	ZHttpPost(postData);

	return 0;
}

bool ZamerSDKHelper::ZHttpPost(FString postData)
{
	bool  ret = false;
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded;charset=GBK"));
	HttpRequest->SetURL(INTERFACEADDR);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetContentAsString(postData);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ZamerSDKHelper::HttpCompleteCallback);
	HttpRequest->ProcessRequest();
	return true;
}

void ZamerSDKHelper::HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	int32 ZM_code = -1;
	FString MessageBody = "";
	FString resmsg;
	UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::HttpCompleteCallback."));

	if (!Response.IsValid())
	{
		MessageBody = "{\"rescode\":\"-1\",\"resmsg\":\"Error: Unable to process HTTP Request!\"}";
	}
	else if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		MessageBody = Response->GetContentAsString();
	}
	else
	{
		MessageBody = FString::Printf(TEXT("{\"rescode\":\"-1\",\"resmsg\":\"HTTP Error: %d\"}"), Response->GetResponseCode());
	}

	UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::HttpCompleteCallback, MessageBody:%s"), *MessageBody);
	HttpCompleteCallbackfalg = true;

	//json 解析
	TSharedPtr<FJsonValue> JsonParsed;
	const TSharedRef< TJsonReader<TCHAR> > JsonReader = TJsonReaderFactory<TCHAR>::Create(MessageBody);
	bool BFlag = FJsonSerializer::Deserialize(JsonReader, JsonParsed);
	if (BFlag)
	{

		ZM_code = JsonParsed->AsObject()->GetIntegerField("rescode");
		resmsg = JsonParsed->AsObject()->GetStringField("resmsg");
		if (ZM_code == 0)
		{//success		
			FString ZM_reqId = JsonParsed->AsObject()->GetStringField("reqId");
			FString ZM_timestamp = JsonParsed->AsObject()->GetStringField("timestamp");
			FString ZM_sign = JsonParsed->AsObject()->GetStringField("sign").ToLower();
			if (ZM_reqId != ""&&ZM_timestamp != ""&&ZM_sign != "")
			{
				FString sig = bcheckcode + "reqId" + ZM_reqId + "timestamp" + ZM_timestamp + bcheckcode;
				FString sign = MD5StringDigest(sig);
				UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper, sign=%s"), *sign);
				if (sign.Equals(ZM_sign))
				{
					UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper,HttpCompleteCallback success "));
					CallStartBillingThread(TCHAR_TO_ANSI(*d_id), TCHAR_TO_ANSI(*c_id), TCHAR_TO_ANSI(*btoken), TCHAR_TO_ANSI(*bcheckcode));
					return;
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ZMVRSDKHelper::HttpCompleteCallback, fail:%d"), ZM_code);
		}
	}

	FString tip = "ZMVRSDK Failed ERROR :"+ FString::FromInt(ZM_code)+"\n"+ resmsg;
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(tip));
	FGenericPlatformMisc::RequestExit(false);
}

bool ZamerSDKHelper::InitAPI()
{
	FString AppKeyString = TEXT("");

	if (!GConfig->GetString(TEXT("ZamerSDK"), TEXT("AppKey"), AppKeyString, GEngineIni))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to obtain bEnabled from [ZMAPI] engine config."));
	}

	const TCHAR* AppKeyChar = *AppKeyString;

	PTCHAR AppKey = const_cast<TCHAR*>(AppKeyChar);

	FString SecretString = TEXT("");

	if (!GConfig->GetString(TEXT("ZamerSDK"), TEXT("Secret"), SecretString, GEngineIni))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to obtain bEnabled from [ZMAPI] engine config."));
	}

	const TCHAR* SecretChar = *SecretString;

	PTCHAR Secret = const_cast<TCHAR*>(SecretChar);


	return TransferCommonParms(AppKey, Secret);
}

PTCHAR ZamerSDKHelper::UpDataZM(UINT Score)
{
	FString GameIDString = TEXT("");

	if (!GConfig->GetString(TEXT("ZamerSDK"), TEXT("ContentID"), GameIDString, GEngineIni))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to obtain bEnabled from [ZMVRSDK] engine config."));
	}

	int32 GameIDInt = FCString::Atoi(*GameIDString);

	UINT GameID = GameIDInt;

	FString GameNameString = TEXT("");

	if (!GConfig->GetString(TEXT("ZamerSDK"), TEXT("GameName"), GameNameString, GEngineIni))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to obtain bEnabled from [ZMAPI] engine config."));
	}

	const TCHAR* GameNameChar = *GameNameString;

	PTCHAR GameName = const_cast<TCHAR*>(GameNameChar);

	UINT barrier = 0;

	PTCHAR ReturnData = UploadGameProgress(GameID, GameName, barrier, Score);

	return ReturnData;
}

FString ZamerSDKHelper::GetZMPlayerData()
{
	PTCHAR UserName = GetNickname();

	return UserName;
}

bool ZamerSDKHelper::TransferCommonParms(const PTCHAR AppKey, const PTCHAR Secret)
{
	FString filePath = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("Studio/ZamerSDK/ThirdParty/ZamerSDK/Win64"), TEXT("ZamerOpenAPI.dll"));
	wDllHandle = FPlatformProcess::GetDllHandle(*filePath);
	if (wDllHandle != nullptr)
	{
		FString apiName = "TransferCommonParms";
		TransferCommonParmsFunc ZMSDKAPIFunc = (TransferCommonParmsFunc)FPlatformProcess::GetDllExport(wDllHandle, *apiName);
		if (ZMSDKAPIFunc)
		{
			bool IsWin = ZMSDKAPIFunc(AppKey, Secret);
			if (!IsWin)
			{
				UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:TransferCommonParms:function failed!!!"));
				return IsWin;
			}

			return IsWin;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:Failed to load ZamerOpenAPI.dll!!!"));

	return false;
}

PTCHAR ZamerSDKHelper::UploadGameProgress(UINT GameId, const PTCHAR GameName, UINT Barrier, UINT Score, const PTCHAR GameStoreDt, const PTCHAR ProgressFile)
{
	if (wDllHandle != nullptr)
	{
		FString apiName = "UploadGameProgress";
		UploadGameProgressFunc ZMSDKAPIFunc = (UploadGameProgressFunc)FPlatformProcess::GetDllExport(wDllHandle, *apiName);
		if (ZMSDKAPIFunc)
		{
			PTCHAR UpData = ZMSDKAPIFunc(GameId, GameName, Barrier, Score, GameStoreDt, ProgressFile);
			if (!UpData)
			{
				UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:function failed!!!"));
				return nullptr;
			}

			return UpData;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:Failed to load ZamerOpenAPI.dll!!!"));

	return NULL;
}

bool ZamerSDKHelper::DownloadGameProgress(const PTCHAR Url, const PTCHAR Filename)
{
	if (wDllHandle != nullptr)
	{
		FString apiName = "DownloadGameProgress";
		DownloadGameProgressFunc ZMSDKAPIFunc = (DownloadGameProgressFunc)FPlatformProcess::GetDllExport(wDllHandle, *apiName);
		if (ZMSDKAPIFunc != nullptr)
		{
			bool IsWin = ZMSDKAPIFunc(Url, Filename);
			if (!IsWin)
			{
				UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:DownloadGameProgress:function failed!!!"));
				return false;
			}

			return IsWin;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:Failed to load ZamerOpenAPI.dll!!!"));
	return false;
}

PTCHAR ZamerSDKHelper::QueryGameProgress(UINT GameId)
{
	if (wDllHandle != nullptr)
	{
		FString apiName = "QueryGameProgress";
		QueryGameProgressFunc ZMSDKAPIFunc = (QueryGameProgressFunc)FPlatformProcess::GetDllExport(wDllHandle, *apiName);
		if (ZMSDKAPIFunc != nullptr)
		{
			PTCHAR GameData = TEXT("");
			GameData = ZMSDKAPIFunc(GameId);
			//PTCHAR GameData = ZMSDKAPIFunc(GameId);
			//if (!GameData)
			if (!GameData)
			{
				UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:QueryGameProgress:function failed!!!"));
				return TEXT("");
			}

			return GameData;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:Failed to load ZamerOpenAPI.dll!!!"));
	return TEXT("");
}

PTCHAR ZamerSDKHelper::SaveGameProperty(UINT GameId, UINT ItemSpecId, const PTCHAR ItemVal, const PTCHAR ActionType)
{
	if (wDllHandle != nullptr)
	{
		FString apiName = "SaveGameProperty";
		SaveGamePropertyFunc ZMSDKAPIFunc = (SaveGamePropertyFunc)FPlatformProcess::GetDllExport(wDllHandle, *apiName);
		if (ZMSDKAPIFunc != nullptr)
		{
			PTCHAR GameData = ZMSDKAPIFunc(GameId, ItemSpecId, ItemVal, ActionType);
			if (!GameData)
			{
				UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:SaveGameProperty:function failed!!!"));
				return NULL;
			}

			return GameData;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:Failed to load ZamerOpenAPI.dll!!!"));
	return NULL;
}

PTCHAR ZamerSDKHelper::QueryGameProperty(UINT GameId)
{
	if (wDllHandle != nullptr)
	{
		FString apiName = "QueryGameProperty";
		QueryGamePropertyFunc ZMSDKAPIFunc = (QueryGamePropertyFunc)FPlatformProcess::GetDllExport(wDllHandle, *apiName);
		if (ZMSDKAPIFunc != nullptr)
		{
			PTCHAR GameData = ZMSDKAPIFunc(GameId);
			if (!GameData)
			{
				UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:QueryGameProperty:function failed!!!"));
				return NULL;
			}

			return GameData;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:Failed to load ZamerOpenAPI.dll!!!"));

	return NULL;
}

PTCHAR ZamerSDKHelper::GetOpenId()
{
	if (wDllHandle != nullptr)
	{
		FString apiName = "GetOpenId";
		GetOpenIdFunc ZMSDKAPIFunc = (GetOpenIdFunc)FPlatformProcess::GetDllExport(wDllHandle, *apiName);
		if (ZMSDKAPIFunc != nullptr)
		{
			PTCHAR GameData = ZMSDKAPIFunc();
			if (!GameData)
			{
				UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:GetOpenId:function failed!!!"));
				return NULL;
			}

			return GameData;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:Failed to load ZamerOpenAPI.dll!!!"));

	return NULL;
}

PTCHAR ZamerSDKHelper::GetNickname()
{
	if (wDllHandle != nullptr)
	{
		FString apiName = "GetNickname";
		GetNicknameFunc ZMSDKAPIFunc = (GetNicknameFunc)FPlatformProcess::GetDllExport(wDllHandle, *apiName);
		if (ZMSDKAPIFunc != nullptr)
		{
			PTCHAR GameData = ZMSDKAPIFunc();
			if (!GameData)
			{
				UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:GetNickname:function failed!!!"));
				return NULL;
			}

			return GameData;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:Failed to load ZamerOpenAPI.dll!!!"));

	return NULL;
}

PTCHAR ZamerSDKHelper::GetAvatarUrl()
{
	// dll未实现获取头像函数
	//if (wDllHandle != nullptr)
	//{
	//	FString apiName = "GetAvatarurl";
	//	GetAvatarUrlFunc ZMSDKAPIFunc = (GetAvatarUrlFunc)FPlatformProcess::GetDllExport(wDllHandle, *apiName);
	//	if (ZMSDKAPIFunc != nullptr)
	//	{
	//		PTCHAR GameData = ZMSDKAPIFunc();
	//		if (!GameData)
	//		{
	//			UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:GetAvatarUrl:function failed!!!"));
	//			return NULL;
	//		}

	//		return GameData;
	//	}

	//}
	//UE_LOG(LogTemp, Error, TEXT("ZamerSDKHelper:UploadGameProgress:Failed to load ZamerOpenAPI.dll!!!"));

	return NULL;
}