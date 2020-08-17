#include "functions.h"
#include <vector>
#include <map>


unsigned long convert(string val) {
	
	unsigned long result = 0;

	sscanf_s(val.c_str(), "%x", &result);

	return result;
}
