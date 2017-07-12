-- Clean Function --
newaction {
   trigger     = "clean",
   description = "clean the software",
   execute     = function ()
      print("clean the build...")
      os.rmdir("./build")
      print("done.")
   end
}

-- A solution contains projects, and defines the available configurations
solution "simhub"
    configurations { "Debug", "Release" }
    
    configuration "Debug"
        defines { "DEBUG" }
        symbols "On"

    configuration "Debug_AWS"
        defines { "DEBUG", "_AWS_SDK" }
        symbols "On"
        links { "aws-cpp-sdk-core",
                "aws-cpp-sdk-polly",
                "aws-cpp-sdk-text-to-speech" }

    configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }
 
    -- A project defines one build target
    project "simhub"
        kind "ConsoleApp"
        language "C++"
        files { "src/app/**.cpp", "src/app/**.h", 
                "src/common/**.h", "src/common/**.cpp" }

        filter { "configurations:Debug" }
            excludes {"src/common/aws/**"}
        filter {} 
        
        includedirs { "src",
					  "src/common",
					  "src/libs",
					  "src/libs/variant/include",
					  "src/libs/variant/include/mpark",
					  "src/libs/queue" }

        links { "zlog", 
                "pthread", 
                "config++" }

        targetdir ("bin")
    
        buildoptions { "--std=c++14" }
    
        configuration { "macosx", "Debug" }
            postbuildcommands { "dsymutil bin/simhub", "gtags" }
                
    project "simhub_tests"
        kind "ConsoleApp"
	    language "C++"
        files { "src/common/**.h", 
                "src/common/**.cpp", 
                "src/test/**.h", 
                "src/test/**.cpp", 
                "src/libs/googletest/src/gtest-all.cc" }

        filter { "configurations:Debug" }
            excludes {"src/common/aws/**"}
        filter {} 

        includedirs { "src/libs/googletest/include", 
                      "src/libs/googletest", 
                      "src", 
                      "src/common", 
                      "src/libs/variant/include", 
                      "src/libs",
                      "src/libs/variant/include/mpark",
					  "src/libs/queue" }
        links { "dl", 
                "zlog", 
                "pthread", 
                "config++" ,
                "aws-cpp-sdk-core",
                "aws-cpp-sdk-polly",  
                "aws-cpp-sdk-text-to-speech"}
        targetdir ("bin")
        buildoptions { "--std=c++14" }

    project "simplug_simsource"
	    kind "SharedLib"
		language "C++"
        targetname "prepare3d"
        targetdir ("bin/plugins")
		files { "src/libs/plugins/simsource/**.h",
                "src/libs/plugins/common/**.cpp",
			    "src/libs/plugins/simsource/**.cpp" }
        includedirs { "src/libs/googletest/include", 
                      "src/libs/googletest", 
                      "src/common",
                      "src/libs/plugins",
                      "src/libs/variant/include", 
                      "src/libs",
                      "src/libs/variant/include/mpark",
					  "src/libs/queue" }
        buildoptions { "--std=c++14" }

project "simplug_devicesource"
	    kind "SharedLib"
		language "C++"
        targetname "pokey"
        targetdir ("bin/plugins")
		files { "src/libs/plugins/pokey/**.h",
                "src/libs/plugins/common/**.cpp",
			    "src/libs/plugins/pokey/**.cpp" }
        includedirs { "src/libs/googletest/include", 
                      "src/libs/googletest", 
                      "src/common",
                      "src/libs/plugins",
                      "src/libs/variant/include", 
                      "src/libs",
                      "src/libs/variant/include/mpark",
					  "src/libs/queue" }
        buildoptions { "--std=c++14" }
		
