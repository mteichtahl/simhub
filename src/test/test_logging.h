#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../common/configmanager/configmanager.h"
#include "../common/elements/sources/source.h"
#include "libs/commandLine.h" // https://github.com/tanakh/cmdline
#include "log/clog.h"

TEST(LoggerTest, InvalidConfigFile)
{
    EXPECT_EQ(false, logger.init());
    EXPECT_EQ(false, logger.canLog());

    EXPECT_EQ(false, logger.init(""));
    EXPECT_EQ(false, logger.canLog());

    EXPECT_EQ(false, logger.init("invalid"));
    EXPECT_EQ(false, logger.canLog());
}

TEST(LoggerTest, validConfigFile)
{
    EXPECT_EQ(true, logger.init("config/zlog.conf"));
    EXPECT_STREQ("config/zlog.conf", logger.configFilename().c_str());
    EXPECT_EQ(true, logger.canLog());
}