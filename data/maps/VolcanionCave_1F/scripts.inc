VolcanionCave_1F_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_1F_OnWarp
	.byte 0

VolcanionCave_1F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_1F_EventScript_TrySpawnPlayer2
	.2byte 0

VolcanionCave_1F_EventScript_TrySpawnPlayer2::
	callnative TrySpawnPlayer2
	setvar VAR_TEMP_1, 1
	end

