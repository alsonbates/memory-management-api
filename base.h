#ifndef HBASE
#define HBASE

#include <stdio.h>
#include <nmmintrin.h>

typedef unsigned long long	u64;
typedef signed long long	s64;

typedef unsigned int		u32;
typedef signed int			s32;

typedef unsigned short		u16;
typedef signed short		s16;

typedef unsigned char		u8;
typedef signed char			s8;

typedef float				f32;

typedef u64					quant64;
typedef u32					quant32;
typedef u16					quant16;
typedef u8					quant8;

typedef u64					index64;
typedef u32					index32;

typedef u64					mask64;
typedef u32					mask32;
typedef	u8					mask8;

typedef u64					hash64;
typedef u32					hash32;

typedef u32					bool32;
typedef u8					bool8;

typedef u32					ret32;

#define reg register

#define KB *1024
#define MB *1024*1024
#define GB *1024*1024*1024

#define CHECKDO(condition, action) if((condition)){action}
#define CHECKLOGDO(condition, action, logFile, message, ...) if((condition)){fprintf(logFile, message, __VA_ARGS__); action}
#define LOG(logFile, message, ...) fprintf(logFile, message, __VA_ARGS__);

#ifdef DEBUG

#define DCHECKLOGDO(condition, action, logFile, message, ...) if((condition)){fprintf(logFile, message, __VA_ARGS__); action}
#define DEXPR(debug_expression) debug_expression
#define DLOG(logFile, message, ...) fprintf(logFile, message, __VA_ARGS__);

FILE* traceFile = 0;
#define STARTTRACE(file) {traceFile = fopen(file, "w"); fprintf(traceFile, "[\n{");}
#define ENDTRACE() {fprintf(traceFile, "}\n]\0"); fclose(traceFile);}
#define TRACEEVENT(name, cat, thread_index, time0, time1) {fprintf(traceFile, "\"name\":\"%s\",\"ph\":\"B\",\"pid\":\"0\",\"tid\":\"%u\",\"ts\":\"%llu\"},{\"name\":\"%s\",\"ph\":\"E\",\"pid\":\"0\",\"tid\":\"%u\",\"ts\":\"%llu\"},{", name, thread_index, time0, name, thread_index, time1);};

#else

#define DCHECKLOGDO(condition, action, logFile, message, ...)
#define DEXPR(debug_expression)
#define DLOG(logFile, message, ...)

#define STARTTRACE(file)
#define ENDTRACE()
#define TRACEEVENT(type, task_name, cat, thread_index, timestamp)

#endif

#define ASM __asm__
#define PACKED __attribute__((packed))
#define PADDING(bytes) u8 padding[bytes]
#define STRUCT(...) struct{__VA_ARGS__}


// PLATFORM
#include <windows.h>

typedef enum
THREAD_PRIORITES {
	PRIORITY_LOW,
	PRIORITY_NORMAL,
	PRIORITY_HIGH,
	nTHREAD_PRIORITIEs
} ThreadPriority;

typedef struct
THREAD_ABSTR {
	HANDLE handle;
} Thread;

Thread pCreateThread(reg void*(*aRoutine)(), reg void* aParams)
{
	HANDLE handle = CreateThread(0, 0, aRoutine, aParams, 0, 0);
	return (Thread){handle};
}

void pSetThreadPriority(Thread thread, ThreadPriority threadPriority)
{
	switch(threadPriority)
	{
		case PRIORITY_LOW:
		{
			SetThreadPriority(thread.handle, THREAD_PRIORITY_BELOW_NORMAL);
			break;
		}
		case PRIORITY_NORMAL:
		{
			SetThreadPriority(thread.handle, THREAD_PRIORITY_NORMAL);
			break;
		}
		case PRIORITY_HIGH:
		{
			SetThreadPriority(thread.handle, THREAD_PRIORITY_ABOVE_NORMAL);
			break;
		}
		default:
		{
			SetThreadPriority(thread.handle, THREAD_PRIORITY_NORMAL);
			break;
		}
	}
	return;
}

#define pPopCount(bits) _Generic((bits), default: 0, u32: _mm_popcnt_u32(bits), u64: _mm_popcnt_u64(bits))(bits)

#endif