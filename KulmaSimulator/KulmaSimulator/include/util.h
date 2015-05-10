#ifndef UTIL_H
#define UTIL_H
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
class ITrigger;
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------
template<typename TDerived>
struct AlignedNew
{
	// Allocate aligned memory.
	static void* operator new (size_t size)
	{
		const size_t alignment = __alignof(TDerived);

		static_assert(alignment > 8, "AlignedNew is only useful for types with > 8 byte alignment. Did you forget a __declspec(align) on TDerived?");

		void* ptr = _aligned_malloc(size, alignment);

		if (!ptr)
			throw std::bad_alloc();

		return ptr;
	}


	// Free aligned memory.
	static void operator delete (void* ptr)
	{
		_aligned_free(ptr);
	}


	// Array overloads.
	static void* operator new[](size_t size) {
		return operator new(size);
	}


	static void operator delete[](void* ptr) {
		operator delete(ptr);
	}
};

void __log(const char* severity, const char* fmt, ...);

#define glAssert() assert(glGetError() == GL_NO_ERROR)
#define LOG_INFO(format,...) __log("<INFO> ", format, ##__VA_ARGS__)
#define KULMA_BIND_1(__selector__, __target__) std::bind(&__selector__, __target__, std::placeholders::_1)
#define KULMA_INPUT_BIND_1(__selector__, __target__, ...) KULMA_BIND_1(__selector__, __target__), 1, __VA_ARGS__
#define KULMA_INPUT_BIND_2(__selector__, __target__, ...) KULMA_BIND_1(__selector__, __target__), 2, __VA_ARGS__
#define KULMA_INPUT_BIND_3(__selector__, __target__, ...) KULMA_BIND_1(__selector__, __target__), 3, __VA_ARGS__

#endif