#include "util.h"
#include <cstdarg>
#include <string>
#include <windows.h>
void __log(const char* severity, const char* fmt, ...) {
	va_list vl;
	va_start(vl, fmt);
	char buf[512];
	size_t i = vsprintf(buf, fmt, vl);
	strcpy(buf + i, "\n");
	va_end(vl);
	OutputDebugString(std::string(std::string(severity) + buf).c_str());
}