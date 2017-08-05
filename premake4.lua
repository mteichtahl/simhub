
-- Clean Function --
newaction {
   trigger     = "clean",
   description = "clean the software",
   execute     = function ()
      print("clean the build...")
      os.rmdir("./obj")
      os.remove("./*.make")
      os.remove("./Makefile")
      print("done.")
   end
}

-- A solution contains projects, and defines the available configurations
solution "simhub"
    configurations { "Debug", "Release", "Debug_AWS" }
    
    -- pass in platform helper #defines
    configuration {"macosx"}
        defines {"build_macosx"}
    configuration {""}    
    configuration {"linux"}
        defines {"build_linux"}
    configuration {""}
    
    defines {"__PLATFORM"}
    configuration "Debug"
        defines { "DEBUG" }
        symbols "On"

    configuration "Debug_AWS"
        defines { "DEBUG" , "_AWS_SDK" }
        symbols "On"
        links { "aws-cpp-sdk-core",
                "aws-cpp-sdk-polly",
                "aws-cpp-sdk-text-to-speech" }

    configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }
        links { "aws-cpp-sdk-core",
                "aws-cpp-sdk-polly",
                "aws-cpp-sdk-text-to-speech" }
 
    -- A project defines one build target
    project "simhub"
        kind "ConsoleApp"
        language "C++"
        files { "src/app/**.cpp", "src/app/**.h", 
                "src/common/**.h", "src/common/**.cpp" }

        configuration {"Debug"}
            excludes {"src/common/aws/**"}
        configuration {}

        includedirs { "src",
                      "src/app",
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
        configuration {}
		
        configuration {"linux"}
            links {"dl"}
        configuration {""}
                
    project "simhub_tests"
        kind "ConsoleApp"
	    language "C++"
        files { "src/common/**.h", 
                "src/common/**.cpp", 
                "src/test/**.h", 
                "src/test/**.cpp", 
                "src/app/simhub.cpp",
                "src/libs/googletest/src/gtest-all.cc" }

        configuration {"Debug"}
            excludes {"src/common/aws/**"}
        configuration {}

        includedirs { "src/libs/googletest/include", 
                      "src/libs/googletest", 
                      "src",
                      "src/app", 
                      "src/common", 
                      "src/libs/variant/include", 
                      "src/libs",
                      "src/libs/variant/include/mpark",
					  "src/libs/queue" }
        links { "dl", 
                "zlog", 
                "pthread", 
                "config++"}

        targetdir ("bin")
        buildoptions { "--std=c++14" }

    project "prepare3d_plugin"
	    kind "SharedLib"
		language "C++"
        targetname "prepare3d"
        targetdir ("bin/plugins")
        links { 'uv',
                'config++',
                'pthread'}
		files { "src/libs/plugins/prepare3d/**.h",
                "src/libs/plugins/common/**.cpp",
			    "src/libs/plugins/prepare3d/**.cpp" }
        includedirs { "src/libs/googletest/include", 
                      "src/libs/googletest", 
                      "src/common",
                      "src/libs/plugins",
                      "src/libs/variant/include", 
                      "src/libs",
                      "src/libs/variant/include/mpark",
					  "src/libs/queue" }
        buildoptions { "--std=c++14" }

    project "pokey_dev_support"
        kind "Makefile"
        basedir ("lib/pokey")

        configuration { "macosx" }
        buildcommands {
            "cd lib/pokey && make -j12 -f Makefile.noqmake.osx && cp libPoKeys.so ../../bin"
        }
        rebuildcommands {
            "cd lib/pokey && make -f Makefile.noqmake.osx clean ; make -j12 -f Makefile.noqmake.osx && cp libPoKeys.so ../../bin"
        }
        cleancommands {
            "cd lib/pokey && make -f Makefile.noqmake.osx clean ; make -j12 -f Makefile.noqmake.osx && cp libPoKeys.so ../../bin"
        }
        configuration {}

        configuration { "linux" }
        buildcommands {
            "cd lib/pokey && make -j12 -f Makefile.noqmake && cp libPoKeys.so ../../bin"
        }
        rebuildcommands {
            "cd lib/pokey && make -f Makefile.noqmake clean ; make -j12 -f Makefile.noqmake && cp libPoKeys.so ../../bin"
        }
        cleancommands {
            "cd lib/pokey && make -f Makefile.noqmake clean ; make -j12 -f Makefile.noqmake && cp libPoKeys.so ../../bin"
        }
        configuration {}

    project "pokey_plugin"
        kind "SharedLib"
        language "C++"
        targetname "pokey"
        targetdir ("bin/plugins")
        libdirs { "lib/pokey" }
        links {
            "PoKeys",
            "usb-1.0"
        }
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
                    "lib/pokey",
                    "src/libs/queue" }
        links { 'config++',
                'pthread'}
        buildoptions { "--std=c++14" }
            
