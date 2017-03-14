function copyLib()
end

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
BGFX_DIR = path.join(KKT_DIR, "3rdparty/bgfx/")
BX_DIR = path.join(KKT_DIR, "3rdparty/bx/")

dofile("toolchain.lua")
if not toolchain(KKT_BUILD_DIR, KKT_THIRD_PARTY_DIR) then
    return
end

dofile (path.join(BGFX_DIR, "scripts/bgfx.lua"))

group "libs"
bgfxProject("", "StaticLib", {})

--if os.is("windows") then
--	if not os.getenv("SDL2_DIR") then
--		print("Set SDL2_DIR enviroment variable.")
--	end
--end

project "kkt"
	kind "WindowedApp"
	
	configuration {}

	links {
		"bgfx"
	}

	files {
		path.join(KKT_DIR, "src/**.cpp"),
		path.join(KKT_DIR, "src/**.h")
	}

	includedirs {
		path.join(KKT_DIR, "src"),
		path.join(KKT_DIR, "3rdparty/bgfx/include"),
		path.join(KKT_DIR, "3rdparty/bx/include")
	}

	configuration { "asmjs" }
		kind "ConsoleApp"
		targetextension ".bc"
		buildoptions {
			"-s USE_SDL=2"
		}


	configuration {}

	strip()