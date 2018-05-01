#ifndef POPEN1_HH
#define POPEN1_HH

#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include <iostream>
#include <string>
#include <vector>

bool popen_cplusplus (
	const std::string &command_i, std::vector<std::string> &result_o);

#endif

