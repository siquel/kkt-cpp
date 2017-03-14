solution "kkt-cpp"
	configurations {
		"Debug",
		"Release"
	}

	platforms {
		"x64"
	}

	language "C++"


KKT_DIR = path.getabsolute("..")
local KKT_BUILD_DIR = path.join(KKT_DIR, ".build")
local KKT_THIRD_PARTY_DIR = path.join(KKT_DIR, "3rdparty")

dofile("toolchain.lua")
if not toolchain(KKT_BUILD_DIR, KKT_THIRD_PARTY_DIR) then
    return
end

--if os.is("windows") then
--	if not os.getenv("SDL2_DIR") then
--		print("Set SDL2_DIR enviroment variable.")
--	end
--end

project "kkt"
	kind "WindowedApp"
	
	configuration {}

	files {
		path.join(KKT_DIR, "src/**.cpp"),
		path.join(KKT_DIR, "src/**.h")
	}

	configuration { "asmjs" }
		kind "ConsoleApp"
		targetextension ".bc"


	configuration {}

	strip()