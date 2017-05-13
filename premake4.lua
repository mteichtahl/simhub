-- A solution contains projects, and defines the available configurations
solution "simhub"
    configurations { "Debug", "Release" }
    
    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

    configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }    
 
   -- A project defines one build target
    project "simhub"
        kind "ConsoleApp"
        language "C++"
        files { "src/app/**.cpp", "src/app/**.h", 
                "src/common/**.h", "src/common/**.cpp",
                "src/libs/common/plugins/**.cpp","src/libs/common/plugins/**.h"}
        includedirs {   "src", 
                        "src/common", 
                        "src/libs/variant/include", 
                        "src/libs/variant/include/mpark",
                        "src/libs/plugins/simsource",
                        "src/libs/queue"
                        }
        links { "dl","zlog", "pthread", "config++" }
        targetdir ("bin")
        buildoptions { "--std=c++14" }
        configuration { "macosx" }
            postbuildcommands { "dsymutil bin/simhub", "gtags" }

    project "simhub_tests"
        kind "ConsoleApp"
	    language "C++"
        files { "src/common/**.h", "src/common/**.cpp", 
                "src/test/**.h", "src/test/**.cpp", 
                "src/libs/googletest/src/gtest-all.cc" }
        includedirs {   "src/libs/googletest/include", 
                        "src/libs/googletest", 
                        "src", 
                        "src/common", 
                        "src/libs/variant/include", 
                        "src/libs/variant/include/mpark" ,
                        "src/libs/plugins/simsource",
                        "src/libs/queue"
                    }
        links { "dl","zlog", "pthread", "config++" }
        targetdir ("bin")
        buildoptions { "--std=c++14" }

 project "simplug_simsource"
	    kind "SharedLib"
		language "C++"
        targetdir ("bin/plugins")
        targetname "prepare3d"
		files { "src/libs/plugins/simsource/**.h",
			    "src/libs/plugins/simsource/**.cpp" }
        includedirs { "src/libs/googletest/include", 
                      "src/libs/googletest", 
                      "src/common", 
                      "src/libs/variant/include", 
                      "src/libs",
                      "src/libs/variant/include/mpark",
					  "src/libs/queue" }
        buildoptions { "--std=c++14" }
