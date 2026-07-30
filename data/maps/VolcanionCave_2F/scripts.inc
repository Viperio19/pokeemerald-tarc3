VolcanionCave_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_2F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_2F_OnFrame
	.byte 0

VolcanionCave_2F_OnTransition:
	end

VolcanionCave_2F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_2F_EventScript_TrySpawnPlayer2
	.2byte 0

VolcanionCave_2F_EventScript_TrySpawnPlayer2::
	callnative TrySpawnPlayer2
	setvar VAR_TEMP_1, 1
	call_if_eq VAR_VOLCANION_CAVE_2F_STATE, 0, VolcanionCave_2F_EventScript_HidePlayers
	end

VolcanionCave_2F_EventScript_HidePlayers::
	hideobjectat LOCALID_PLAYER_2, MAP_VOLCANION_CAVE_1F
	hideplayer
	return

VolcanionCave_2F_OnFrame:
	map_script_2 VAR_VOLCANION_CAVE_2F_STATE, 0, VolcanionCave_2F_EventScript_EnterCave
	.2byte 0

VolcanionCave_2F_EventScript_EnterCave::
	lock
	setvar VAR_VOLCANION_CAVE_2F_STATE, 1
	showplayer
	release
	end

VolcanionCave_2F_EventScript_Diglett::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	release
	end
