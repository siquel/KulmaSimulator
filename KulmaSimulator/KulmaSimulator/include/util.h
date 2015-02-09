#ifndef UTIL_H
#define UTIL_H

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

#define glAssert() assert(glGetError() == GL_NO_ERROR)


#endif