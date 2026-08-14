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
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_2F_EventScript_InitObjects
	.2byte 0

VolcanionCave_2F_EventScript_InitObjects::
	callnative TrySpawnPlayer2
	setvar VAR_TEMP_1, 1
	call_if_eq VAR_VOLCANION_CAVE_2F_STATE, 0, VolcanionCave_2F_EventScript_HidePlayers
	call_if_ne VAR_OLD_ROD_STATE, 2, VolcanionCave_2F_EventScript_RemoveOldRod
	call_if_eq VAR_OLD_ROD_STATE, 2, VolcanionCave_2F_EventScript_SetOldRodPosition
	end

VolcanionCave_2F_EventScript_HidePlayers::
	hideobjectat LOCALID_PLAYER_2, MAP_VOLCANION_CAVE_1F
	hideplayer
	return

VolcanionCave_2F_EventScript_RemoveOldRod::
	removeobject LOCALID_2F_OLD_ROD
	return

VolcanionCave_2F_EventScript_SetOldRodPosition::
	setobjectxyperm LOCALID_2F_OLD_ROD, VAR_OLD_ROD_X, VAR_OLD_ROD_Y
	addobject LOCALID_2F_OLD_ROD
	callnative SetOldRodBob
	return

VolcanionCave_2F_OnFrame:
	map_script_2 VAR_VOLCANION_CAVE_2F_STATE, 0, VolcanionCave_2F_EventScript_EnterCave
	map_script_2 VAR_OLD_ROD_STATE, 10, VolcanionCave_2F_EventScript_DropOldRod
	map_script_2 VAR_OLD_ROD_STATE, 15, VolcanionCave_1F_EventScript_MagmaWarning
	.2byte 0

VolcanionCave_2F_EventScript_EnterCave::
	lock
	setvar VAR_VOLCANION_CAVE_2F_STATE, 1
	showplayer
	release
	end

VolcanionCave_2F_EventScript_DropOldRod::
	lock
    clearflag FLAG_HIDE_VOLCANION_CAVE_2F_OLD_ROD
    setflag FLAG_DROPPED_VOLCANION_CAVE_2F_OLD_ROD
	addobject LOCALID_2F_OLD_ROD
	callnative SetOldRodBob
	removeitem ITEM_OLD_ROD
	setvar VAR_OLD_ROD_STATE, 2
	delay 20
	getplayerxy VAR_0x8000, VAR_0x8001
	goto_if_ne VAR_0x8000, 29, VolcanionCave_2F_EventScript_MessageDroppedRod
	goto_if_eq VAR_0x8001, 24, VolcanionCave_2F_EventScript_OldRodCurrentsY24
	goto_if_eq VAR_0x8001, 26, VolcanionCave_2F_EventScript_OldRodCurrentsY26
	goto_if_eq VAR_0x8001, 27, VolcanionCave_2F_EventScript_OldRodCurrentsY27
VolcanionCave_2F_EventScript_MessageDroppedRod::
	msgbox VolcanionCave_2F_Text_DroppedRod
	closemessage
	release
	end

VolcanionCave_2F_EventScript_OldRodCurrentsY24::
	special SpawnCameraObject
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodFloatY24
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_OldRodFloatY24
	waitmovement 0
	setvar VAR_OLD_ROD_X, 28
	setvar VAR_OLD_ROD_Y, 25
	setobjectxyperm LOCALID_2F_OLD_ROD, VAR_OLD_ROD_X, VAR_OLD_ROD_Y
	delay 20
	applymovement LOCALID_CAMERA, Common_Movement_WalkUp
	waitmovement 0
	special RemoveCameraObject
	msgbox VolcanionCave_2F_Text_DroppedRodFloated
	closemessage
	release
	end

VolcanionCave_2F_Movement_OldRodFloatY24::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

VolcanionCave_2F_Movement_CameraMoveBackY24::
	walk_up
	step_end

VolcanionCave_2F_EventScript_OldRodCurrentsY26::
	special SpawnCameraObject
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodFloatY26
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_OldRodFloatY26
	waitmovement 0
	setvar VAR_OLD_ROD_X, 18
	setvar VAR_OLD_ROD_Y, 31
	setobjectxyperm LOCALID_2F_OLD_ROD, VAR_OLD_ROD_X, VAR_OLD_ROD_Y
	delay 20
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_CameraMoveBackY26
	waitmovement 0
	special RemoveCameraObject
	msgbox VolcanionCave_2F_Text_DroppedRodFloated
	closemessage
	release
	end

VolcanionCave_2F_Movement_OldRodFloatY26::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

VolcanionCave_2F_Movement_CameraMoveBackY26::
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

VolcanionCave_2F_EventScript_OldRodCurrentsY27::
	special SpawnCameraObject
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodFloatY27
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_OldRodFloatY27
	waitmovement 0
	setvar VAR_OLD_ROD_X, 27
	setvar VAR_OLD_ROD_Y, 30
	setobjectxyperm LOCALID_2F_OLD_ROD, VAR_OLD_ROD_X, VAR_OLD_ROD_Y
	delay 20
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_CameraMoveBackY27
	waitmovement 0
	special RemoveCameraObject
	msgbox VolcanionCave_2F_Text_DroppedRodFloated
	closemessage
	release
	end

VolcanionCave_2F_Movement_OldRodFloatY27::
	walk_left
	walk_down
	walk_fast_down
	walk_fast_down
	step_end

VolcanionCave_2F_Movement_CameraMoveBackY27::
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

VolcanionCave_2F_Text_DroppedRod::
	.string "Dropped rod...$"

VolcanionCave_2F_Text_DroppedRodFloated::
	.string "Dropped rod...\p"
	.string "It floated...$"

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

VolcanionCave_2F_EventScript_Toxapex::
	playmoncry SPECIES_TOXAPEX, CRY_MODE_NORMAL
	msgbox VolcanionCave_2F_Text_Toxapex
	waitmoncry
	release
	end

VolcanionCave_2F_Text_Toxapex::
	.string "Not tall.$"

VolcanionCave_2F_EventScript_OldRod::
	lock
	removeobject VAR_LAST_TALKED
	giveitem ITEM_OLD_ROD
	clearflag FLAG_DROPPED_VOLCANION_CAVE_2F_OLD_ROD
	setflag FLAG_HIDE_VOLCANION_CAVE_2F_OLD_ROD
	setvar VAR_OLD_ROD_STATE, 0
	release
	end
