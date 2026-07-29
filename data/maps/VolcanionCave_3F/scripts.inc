VolcanionCave_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_3F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_3F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_3F_OnFrame
	.byte 0

VolcanionCave_3F_OnTransition:
	end

VolcanionCave_3F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_3F_EventScript_TrySpawnPlayer2
	.2byte 0

VolcanionCave_3F_EventScript_TrySpawnPlayer2::
	callnative TrySpawnPlayer2
	setvar VAR_TEMP_1, 1
	call_if_eq VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_HidePlayers
	end

VolcanionCave_3F_EventScript_HidePlayers::
	hideobjectat LOCALID_PLAYER_2, MAP_VOLCANION_CAVE_1F
	hideplayer
	return

VolcanionCave_3F_OnFrame:
	map_script_2 VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_EnterCave
	.2byte 0

VolcanionCave_3F_EventScript_EnterCave::
	lock
	setvar VAR_VOLCANION_CAVE_3F_STATE, 1
	showplayer
	release
	end
