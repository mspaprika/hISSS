
local m = {}

function m.UsePCH()

end

function m.AddFiles()
	filter {}
    
	includedirs { ".", "../" }

	files {
		"premake5.lua",
		"**.cpp",
		"**.h",
		"**.natvis"
	}

	filter {}
end

function m.AddMainProjectSettings()
	-- links 
	-- {
	-- 	"Play3D",
	-- 	"HSHeaderLib",
	-- 	"HSSystemLib"
	-- }

	local workspace_root = path.getabsolute("..")
    includedirs {
        path.join(workspace_root, "hiSSS/include/hiSSS/HSHeaderLib"),
        path.join(workspace_root, "hiSSS/include/hiSSS/HSSystemLib"),
        path.join(workspace_root, "hiSSS/include/ext/Play3D")
    }

	debugdir "."
end


return m