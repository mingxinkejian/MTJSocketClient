//
//  MTJSocketPlatformConfig.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef MTJSocketClient_MTJSocketPlatformConfig_h
#define MTJSocketClient_MTJSocketPlatformConfig_h

#define PLATFORM_UNKNOW             0
#define PLATFORM_IOS                1
#define PLATFORM_ANDROID            2
#define PLATFORM_WIN32              3
#define PLATFORM_MAC                4
// Determine target platform by compile environment macro.
#define TARGET_PLATFORM             PLATFORM_UNKNOWN

//Mac
#if defined(TARGET_OS_MAC)
#undef TARGET_PLATFORM
#define TARGET_PLATFORM             PLATFORM_MAC
#endif

//IOS
#if defined(TARGET_OS_IOS)
#undef TARGET_PLATFORM
#define TARGET_PLATFORM             PLATFORM_IOS
#endif

//Android
#if defined(ANDROID)
#undef TARGET_PLATFORM
#define TARGET_PLATFORM             PLATFORM_ANDROID
#endif

//Win32
#if defined(WIN32) && defined(_WINDOWS)
#undef TARGET_PLATFORM
#define TARGET_PLATFORM             PLATFORM_WIN32
#endif

//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! TARGET_PLATFORM
#error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif

#if (TARGET_PLATFORM == PLATFORM_WIN32)
#pragma warning (disable:4127)
#endif  // CC_PLATFORM_WIN32


#endif
