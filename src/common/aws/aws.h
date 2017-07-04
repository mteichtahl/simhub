#ifndef __AWS_H
#define __AWS_H

#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <string.h>

/**
 *  @brief Class allowing for logging to various targets based on zlog.
 */
class AWS
{
public:
    // Default constructor
    AWS();
    // Destructor
    ~AWS();
    bool init();

protected:
};

extern AWS awsHelper; ///< allow externals to access logger

#endif // __AWS_H