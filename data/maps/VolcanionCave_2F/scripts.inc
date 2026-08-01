VolcanionCave_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_2F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_2F_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, VolcanionCave_2F_OnLoad
	.byte 0

VolcanionCave_2F_OnLoad::
	call_if_ne VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100, VolcanionCave_2F_EventScript_SetRockBarrier1
	call_if_ne VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 100, VolcanionCave_2F_EventScript_SetRockBarrier2
	end

VolcanionCave_2F_EventScript_SetRockBarrier1::
	setmetatile 36, 45, METATILE_Cave_RockBarrier_Left, 1
	setmetatile 37, 45, METATILE_Cave_RockBarrier_MiddleHorizontal, 1
	setmetatile 38, 45, METATILE_Cave_RockBarrier_Right, 1
	return

VolcanionCave_2F_EventScript_SetRockBarrier2::
	setmetatile 10, 34, METATILE_Cave_RockBarrier_Top, 1
	setmetatile 10, 35, METATILE_Cave_RockBarrier_MiddleVertical, 1
	setmetatile 10, 36, METATILE_Cave_RockBarrier_MiddleVertical, 1
	setmetatile 10, 37, METATILE_Cave_RockBarrier_MiddleVertical, 1
	setmetatile 10, 18, METATILE_Cave_RockBarrier_Bottom, 1
	return

VolcanionCave_2F_OnTransition:
	callnative UpdateStrengthBoulderPositions
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
	getplayerxy VAR_0x8000, VAR_0x8001
	getobjectxy LOCALID_2F_DIGLETT, CURRENT_POSITION, VAR_0x8002, VAR_0x8003
	goto_if_ne VAR_0x8001, VAR_0x8003, VolcanionCave_2F_EventScript_DiglettDoNothing
	applymovement LOCALID_2F_DIGLETT, Common_Movement_FacePlayer
	waitmovement
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_2F_EventScript_DiglettMagma
	goto VolcanionCave_2F_EventScript_DiglettAqua
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	release
	end

VolcanionCave_2F_EventScript_DiglettDoNothing::
	release
	end

VolcanionCave_2F_EventScript_DiglettMagma::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	msgbox VolcanionCave_2F_Text_DiglettCry
	waitmoncry
	closemessage
	delay 20
	msgbox VolcanionCave_2F_Text_DiglettSecretAgent
	closemessage
	release
	end

VolcanionCave_2F_EventScript_DiglettAqua::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	msgbox VolcanionCave_2F_Text_AgentDiggsCry, 
	waitmoncry
	closemessage
	delay 20
	msgbox VolcanionCave_2F_Text_GoodWorkDiggs
	closemessage
	delay 20
	release
	end

VolcanionCave_2F_Text_DiglettCry::
	.string "{SPEAKER NAME_DIGLETT COLOR_AQUA}Pipipi wowow!$"

VolcanionCave_2F_Text_AgentDiggsCry::
	.string "{SPEAKER NAME_AGENT_DIGGS COLOR_AQUA}Pipipi wowow!$"

VolcanionCave_2F_Text_DiglettSecretAgent::
	.string "(The DIGLETT seems to be an\n"
	.string "agent working for TEAM AQUA.)\p"
	.string "(You decide not to ruin the MAGMA\n"
	.string "GRUNT'S day with this information.)$"

VolcanionCave_2F_Text_GoodWorkDiggs::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Keep up the good work, AGENT DIGGS!$"

VolcanionCave_2F_EventScript_AquaMemberMFishingRod::
	lock
	giveitem ITEM_OLD_ROD
	release
	end

VolcanionCave_2F_EventScript_FloorSwitch1::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 36, 45, METATILE_Cave_Floor, 0
	setmetatile 37, 45, METATILE_Cave_Floor, 0
	setmetatile 38, 45, METATILE_Cave_Floor, 0
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setobjectmovementtype LOCALID_VOLCANION_CAVE_2F_BOULDER_1, MOVEMENT_TYPE_NONE
	copyobjectxytoperm LOCALID_VOLCANION_CAVE_2F_BOULDER_1
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitch2::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 10, 34, METATILE_Cave_Floor, 0
	setmetatile 10, 35, METATILE_Cave_Floor, 0
	setmetatile 10, 36, METATILE_Cave_Floor, 0
	setmetatile 10, 37, METATILE_Cave_Floor, 0
	setmetatile 10, 18, METATILE_Cave_Floor, 0
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setobjectmovementtype LOCALID_VOLCANION_CAVE_2F_BOULDER_2, MOVEMENT_TYPE_NONE
	copyobjectxytoperm LOCALID_VOLCANION_CAVE_2F_BOULDER_2
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed::
	release
	end

VolcanionCave_2F_EventScript_Exeggutor::
	playmoncry SPECIES_EXEGGUTOR_ALOLA, CRY_MODE_NORMAL
	msgbox VolcanionCave_2F_Text_Exeggutor
	waitmoncry
	release
	end

VolcanionCave_2F_Text_Exeggutor::
	.string "Tall.$"

