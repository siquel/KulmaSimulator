#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
class NotImplementedException : public std::logic_error {
public:
	NotImplementedException() : std::logic_error("Not implemented") {}
	~NotImplementedException() {}
	virtual char const* what() const { return "Not implemented"; }
};

#endif