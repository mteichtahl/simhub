# Logging

In **simhub** logging is handled by a global [singleton](https://en.wikipedia.org/wiki/Singleton_pattern), and is available to **all** classes, functions etc via that global scope.

This global singleton is created once ```CLog.h``` is included and is accessable via ```logger.log(LOG_LEVEL, fmt, param)```. One may think of interacting with ```logger.log(...)``` in the same way as interacting with [printf](http://www.cplusplus.com/reference/cstdio/printf/).

### Example implmentation
```c++
#include "CLog.h"

// initialise the logger and provide the config file
logger.init("config/zlog.conf);

// log to the LOG_INFO category
logger.log(LOG_INFO, "This is a sample INFO log message - %d", "some char*");

```

## Configuration

Logging is based on the great [zlog](http://hardysimpson.github.io/zlog/UsersGuide-EN.html) library.

Sane defaults are provided

* All [global](http://hardysimpson.github.io/zlog/UsersGuide-EN.html#htoc14) options are supported
* All [patterns](http://hardysimpson.github.io/zlog/UsersGuide-EN.html#htoc14) are supported
* Some [rules](http://hardysimpson.github.io/zlog/UsersGuide-EN.html#htoc22) are support. Though there should be **no need** to modify these.

## Logging Levels

### INFO

As the name suggests, these are purely informational messages; they should not be used to indicate a fault or error state in the application. To use this log level effectively, try to think about what general information would be useful for diagnosing an application error when the primary interface is not accessible.

#### Example
```
logger.log(LOG_INFO, "This is a sample INFO log message - %d", "some char*");
```

##### Output
```
2017-04-27 13:40:49 INFO [43427:src/log/CLog.cpp:91] This is a sample INFO log message - some char *
```

This is the first level which indicates some form of simhub failure.

### ERROR

This is the second level of failure, and by its very name, it should indicate that something more critical has occurred. ERROR messages should be used to indicate that the application faced a significant problem and that, as a result, the user experience was affected in some way. For example, a database connection could have failed, resulting in parts of the application being rendered unusable.

#### Example
```
logger.log(LOG_ERROR, "This is a sample ERROR log message - %d", 123);
```

##### Output
```
2017-04-27 13:40:49 ERROR [43427:src/log/CLog.cpp:91] This is a sample INFO log message - 123
```

### DEBUG

This log level is used to indicate that the logged message is to be used for debugging purposes - in other words, these messages are aimed squarely at the developer. What you use this for really depends on the application you are developing. Many problems can be resolved via the debugger, making the use of DEBUG messages redundant; however, there are a few situations where DEBUG messages are quite useful, for example:

#### Example
```
logger.log(LOG_DEBUG, "This is a sample DEBUG log message - 0x%.2x", 5);
```

##### Output
```
2017-04-27 13:40:49 DEBUG [43427:src/log/CLog.cpp:91] This is a sample INFO log message - 0x05
```

