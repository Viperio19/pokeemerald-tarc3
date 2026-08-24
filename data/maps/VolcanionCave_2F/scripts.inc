VolcanionCave_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_2F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_2F_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, VolcanionCave_2F_OnLoad
	.byte 0

VolcanionCave_2F_OnLoad::
	call_if_ne VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100, VolcanionCave_2F_EventScript_SetRockBarrier1
	call_if_ne VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 100, VolcanionCave_2F_EventScript_SetRockBarrier2
	call_if_ne VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_3, 100, VolcanionCave_2F_EventScript_SetRockBarrier3
	call_if_ne VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_4, 100, VolcanionCave_2F_EventScript_SetRockBarrier4
	call_if_eq VAR_TEMP_F, 1, VolcanionCave_2F_EventScript_SetMetatilesBlueButtonPressed
	end

VolcanionCave_2F_EventScript_SetRockBarrier1::
	setmetatile 26, 64, METATILE_Cave_RockBarrier_Left, TRUE
	setmetatile 27, 64, METATILE_Cave_RockBarrier_MiddleHorizontal, TRUE
	setmetatile 28, 64, METATILE_Cave_RockBarrier_Right, TRUE
	return

VolcanionCave_2F_EventScript_SetRockBarrier2::
	setmetatile 18, 40, METATILE_Cave_RockBarrier_Top, TRUE
	setmetatile 18, 41, METATILE_Cave_RockBarrier_MiddleVertical, TRUE
	setmetatile 18, 42, METATILE_Cave_RockBarrier_Bottom, TRUE
	return

VolcanionCave_2F_EventScript_SetRockBarrier3::
	setmetatile 20, 8, METATILE_Cave_RockBarrier_TopEdge, TRUE
	setmetatile 20, 9, METATILE_Cave_RockBarrier_Bottom, TRUE
	return

VolcanionCave_2F_EventScript_SetRockBarrier4::
	setmetatile 23, 4, METATILE_Cave_RockBarrier_Top, TRUE
	setmetatile 23, 5, METATILE_Cave_RockBarrier_MiddleVertical, TRUE
	setmetatile 23, 6, METATILE_Cave_RockBarrier_Bottom, TRUE
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
	call_if_ne VAR_OLD_ROD_STATE, 2, VolcanionCave_2F_EventScript_RemoveOldRod
	call_if_eq VAR_OLD_ROD_STATE, 2, VolcanionCave_2F_EventScript_SetOldRodPosition
	end

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

#define LOCALID_PLAYER_AQUA  VAR_0x800A
#define LOCALID_PLAYER_MAGMA VAR_0x800B

VolcanionCave_2F_EventScript_EnterCave::
	lock
	setvar VAR_VOLCANION_CAVE_2F_STATE, 1
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, TRUE, VolcanionCave_2F_EventScript_PlayersEnter
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_2F_EventScript_PlayersEnter2
VolcanionCave_2F_EventScript_Intro::
	delay 30
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceRight
	message VolcanionCave_1F_Text_IntroOhNo
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceLeft
	message VolcanionCave_1F_Text_IntroWeirdo
	waitmovement 0
	waitmessage
	callnative UpdatePlayer2Pos
	release
	end

VolcanionCave_2F_EventScript_PlayersEnter::
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_PlayerAquaEnterCave
	waitmovement 0
	callnative SpawnPlayer2For2FIntro
	applymovement LOCALID_PLAYER_2, VolcanionCave_2F_Movement_Player2Enter
	waitmovement 0
	applymovement LOCALID_PLAYER_2, VolcanionCave_2F_Movement_PlayerMagmaEnterCave
	waitmovement 0
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER_2
	goto VolcanionCave_2F_EventScript_Intro
	end

VolcanionCave_2F_EventScript_PlayersEnter2::
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_PlayerMagmaEnterCave
	waitmovement 0
	callnative SpawnPlayer2For2FIntro
	applymovement LOCALID_PLAYER_2, VolcanionCave_2F_Movement_Player2Enter
	waitmovement 0
	applymovement LOCALID_PLAYER_2, VolcanionCave_2F_Movement_PlayerAquaEnterCave
	waitmovement 0
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER_2
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER
	goto VolcanionCave_2F_EventScript_Intro
	end

VolcanionCave_2F_Movement_Player2Enter::
	set_visible
	walk_up
	step_end

VolcanionCave_2F_Movement_PlayerMagmaEnterCave::
	walk_right
	walk_up
	step_end

VolcanionCave_2F_Movement_PlayerAquaEnterCave::
	walk_left
	walk_up
	step_end

VolcanionCave_2F_EventScript_DropOldRod::
	lock
	clearflag FLAG_DISABLE_OLD_ROD_BOB
    clearflag FLAG_HIDE_VOLCANION_CAVE_2F_OLD_ROD
    setflag FLAG_DROPPED_VOLCANION_CAVE_2F_OLD_ROD
	addobject LOCALID_2F_OLD_ROD
	callnative SetOldRodBob
	removeitem ITEM_OLD_ROD
	setvar VAR_OLD_ROD_STATE, 2
	getplayerxy VAR_0x8000, VAR_0x8001
	goto_if_ne VAR_0x8000, 29, VolcanionCave_2F_EventScript_MessageDroppedRod
	goto_if_eq VAR_0x8001, 24, VolcanionCave_2F_EventScript_OldRodCurrentsY24
	goto_if_eq VAR_0x8001, 26, VolcanionCave_2F_EventScript_OldRodCurrentsY26
	goto_if_eq VAR_0x8001, 27, VolcanionCave_2F_EventScript_OldRodCurrentsY27
VolcanionCave_2F_EventScript_MessageDroppedRod::
	playfanfare MUS_TOO_BAD
	msgbox VolcanionCave_2F_Text_DroppedRod
	closemessage
	release
	end

VolcanionCave_2F_EventScript_OldRodCurrentsY24::
	special SpawnCameraObject
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodFloatY24
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_OldRodFloatY24
	waitmovement 0
	callnative StopOldRodBob
	playse SE_LEDGE
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodJumpY24
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	setvar VAR_OLD_ROD_X, 29
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

VolcanionCave_2F_Movement_OldRodJumpY24::
	jump_right
	step_end

VolcanionCave_2F_Movement_CameraMoveBackY24::
	walk_up
	step_end

VolcanionCave_2F_EventScript_OldRodCurrentsY26::
	special SpawnCameraObject
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodFloatY26
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_OldRodFloatY26
	waitmovement 0
	callnative StopOldRodBob
	playse SE_LEDGE
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodJumpY26
	waitmovement 0
	setvar VAR_OLD_ROD_X, 17
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

VolcanionCave_2F_Movement_OldRodJumpY26::
	jump_left
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
	applymovement LOCALID_2F_DIGLETT, Common_Movement_FacePlayer
	waitmovement
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_2F_EventScript_DiglettMagma
	goto VolcanionCave_2F_EventScript_DiglettAqua
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
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
	faceplayer
	goto_if_set FLAG_DEFEATED_VOLCANION_CAVE_2F_TOXAPEX, VolcanionCave_2F_EventScript_AquaGruntReceivedOldRod
	msgbox VolcanionCave_2F_Text_AquaGruntWantToBattle, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, VolcanionCave_2F_EventScript_AquaGruntRejected
	trainerbattle_single TRAINER_GRUNT_VC_2F_TOXAPEX, VolcanionCave_2F_Text_AquaGruntIntro, VolcanionCave_2F_Text_AquaGruntDefeat, VolcanionCave_2F_EventScript_AquaGruntGiveOldRod
	msgbox VolcanionCave_2F_Text_AquaGruntPostBattle, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_AquaGruntRejected::
	msgbox VolcanionCave_2F_Text_AquaGruntRejected, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_AquaGruntGiveOldRod::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, VolcanionCave_2F_EventScript_AquaGruntVictory
	setflag FLAG_DEFEATED_VOLCANION_CAVE_2F_TOXAPEX
	msgbox VolcanionCave_2F_Text_AquaGruntPostBattle, MSGBOX_DEFAULT
	closemessage
	delay 10
	giveitem ITEM_OLD_ROD
	release
	end

VolcanionCave_2F_EventScript_AquaGruntReceivedOldRod::
	msgbox VolcanionCave_2F_Text_AquaGruntPostBattle, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_AquaGruntVictory::
	msgbox VolcanionCave_2F_Text_AquaGruntVictory, MSGBOX_NPC
	end

VolcanionCave_2F_Text_AquaGruntWantToBattle:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Want to battle for my OLD ROD?$"

VolcanionCave_2F_Text_AquaGruntRejected:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Booooooooooo!!!$"

VolcanionCave_2F_Text_AquaGruntIntro:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Let's battle for my OLD ROD!$"

VolcanionCave_2F_Text_AquaGruntDefeat:
	.string "Awwww man there goes my OLD ROD...$"

VolcanionCave_2F_Text_AquaGruntPostBattle:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Go throw this OLD ROD in the water\n"
	.string "or something...$"

VolcanionCave_2F_Text_AquaGruntVictory:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Heh you're not getting my OLD ROD\n"
	.string "if you battle that way!$"

VolcanionCave_2F_EventScript_FloorSwitch1::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 26, 64, METATILE_Cave_Floor, FALSE
	setmetatile 27, 64, METATILE_Cave_Floor, FALSE
	setmetatile 28, 64, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitch2::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 18, 40, METATILE_Cave_Floor, FALSE
	setmetatile 18, 41, METATILE_Cave_Floor, FALSE
	setmetatile 18, 42, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitch3::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_3, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 20, 8, METATILE_Cave_Floor_Smooth_Top, FALSE
	setmetatile 20, 9, METATILE_Cave_Floor_Smooth, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_3, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitch4::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_4, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 23, 4, METATILE_Cave_Floor, FALSE
	setmetatile 23, 5, METATILE_Cave_Floor, FALSE
	setmetatile 23, 6, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_4, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed::
	release
	end

VolcanionCave_2F_EventScript_Exeggutor::
	playmoncry SPECIES_EXEGGUTOR_ALOLA, CRY_MODE_NORMAL
	msgbox VolcanionCave_2F_Text_Exeggutor, MSGBOX_DEFAULT
	waitmoncry
	setwildbattle SPECIES_EXEGGUTOR_ALOLA, 25, TRUE, ITEM_SITRUS_BERRY
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_2F_EventScript_DefeatedExeggutor
	release
	end

VolcanionCave_2F_EventScript_DefeatedExeggutor::
	playmoncry SPECIES_EXEGGUTOR_ALOLA, CRY_MODE_NORMAL
	msgbox VolcanionCave_2F_Text_Exeggutor, MSGBOX_DEFAULT
	waitmoncry
	setflag FLAG_DEFEATED_VOLCANION_CAVE_2F_EXEGGUTOR
	removeobject LOCALID_2F_EXEGGUTOR_1
	removeobject LOCALID_2F_EXEGGUTOR_2
	release
	end

VolcanionCave_2F_Text_Exeggutor::
	.string "(exeggutor cry)$"

VolcanionCave_2F_EventScript_Toxapex::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TOXAPEX, CRY_MODE_NORMAL
	call_if_unset FLAG_DEFEATED_VOLCANION_CAVE_2F_TOXAPEX, VolcanionCave_2F_EventScript_ToxapexHappy
	call_if_set FLAG_DEFEATED_VOLCANION_CAVE_2F_TOXAPEX, VolcanionCave_2F_EventScript_ToxapexSad
	waitmoncry
	release
	end

VolcanionCave_2F_EventScript_ToxapexHappy:
	msgbox VolcanionCave_2F_Text_ToxapexHappy, MSGBOX_DEFAULT
	return

VolcanionCave_2F_EventScript_ToxapexSad:
	msgbox VolcanionCave_2F_Text_ToxapexSad, MSGBOX_DEFAULT
	return

VolcanionCave_2F_Text_ToxapexHappy::
	.string "TOXAPEX: Toxaaaaa!$"

VolcanionCave_2F_Text_ToxapexSad::
	.string "TOXAPEX: Pex...$"

VolcanionCave_2F_EventScript_OldRod::
	lock
	removeobject VAR_LAST_TALKED
	giveitem ITEM_OLD_ROD
	clearflag FLAG_DROPPED_VOLCANION_CAVE_2F_OLD_ROD
	setflag FLAG_HIDE_VOLCANION_CAVE_2F_OLD_ROD
	setvar VAR_OLD_ROD_STATE, 0
	release
	end

VolcanionCave_2F_EventScript_MagmaMemberFGoldeen::
	lock
	faceplayer
	goto_if_set FLAG_TALKED_TO_GOLDEEN_GRUNT, VolcanionCave_2F_EventScript_PleaseShowGoldeen
	setflag FLAG_TALKED_TO_GOLDEEN_GRUNT
	msgbox VolcanionCave_2F_Text_IDroppedGoldeen, MSGBOX_DEFAULT
	goto VolcanionCave_2F_EventScript_ChoosePartyMonGoldeen
	end

VolcanionCave_2F_EventScript_PleaseShowGoldeen::
	msgbox VolcanionCave_2F_Text_PleaseShowGoldeen, MSGBOX_DEFAULT
VolcanionCave_2F_EventScript_ChoosePartyMonGoldeen::
	setvar VAR_0x8009, SPECIES_CHI_YU
	special ChoosePartyMon
	specialvar VAR_RESULT, GetTradeSpecies
	goto_if_eq VAR_RESULT, SPECIES_NONE, VolcanionCave_2F_EventScript_PleaseKeepLooking
	goto_if_ne VAR_RESULT, VAR_0x8009, VolcanionCave_2F_EventScript_ThatsNotGoldeen
	msgbox VolcanionCave_2F_Text_ThatsIt, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_GOLDEEN_GRUNT
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

VolcanionCave_2F_EventScript_ThatsNotGoldeen::
	msgbox VolcanionCave_2F_Text_ThatsNotGoldeen, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_PleaseKeepLooking::
	closemessage
	delay 5
	msgbox VolcanionCave_2F_Text_PleaseKeepLooking, MSGBOX_NPC
	end

VolcanionCave_2F_Text_IDroppedGoldeen::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}I found a GOLDEEN and ditched it\n"
	.string "in the lava over there.\p"
	.string "I feel a bit bad though...\p"
	.string "Can you fish it up and\n"
	.string "show it to me?\p"
	.string "Please show it to me!$"

VolcanionCave_2F_Text_PleaseShowGoldeen::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}Please show GOLDEEN to me!$"

VolcanionCave_2F_Text_ThatsNotGoldeen::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}That's not it...\p"
	.string "Please keep looking for GOLDEEN!$"

VolcanionCave_2F_Text_PleaseKeepLooking::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}Please keep looking for GOLDEEN!$"

VolcanionCave_2F_Text_ThatsIt::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}That's it!{PAUSE 40}\n"
	.string ".{PAUSE 20} .{PAUSE 20} .{PAUSE 40} that's GOLDEEN right?\p"
	.string "Regardless, thanks for looking!\p"
	.string "I'm gonna do... something else now!\p"
	.string "Byeeeeeeeeeeeeeeeeeeee!$"

VolcanionCave_2F_EventScript_BlueButton::
	lockall
	setvar VAR_TEMP_F, 1
	playse SE_PIN
	call VolcanionCave_2F_EventScript_SetMetatilesBlueButtonPressed
	special DrawWholeMapView
	releaseall
	end

VolcanionCave_2F_EventScript_RedButton::
	lockall
	setvar VAR_TEMP_F, 0
	playse SE_PIN
	call VolcanionCave_2F_EventScript_SetMetatilesRedButtonPressed
	special DrawWholeMapView
	releaseall
	end

VolcanionCave_2F_EventScript_SetMetatilesBlueButtonPressed::
	setmetatile 7, 48, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 17, 11, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 11, 46, METATILE_Cave_CoolButton_Red, FALSE
	setmetatile 10, 46, METATILE_Cave_CoolGem_Blue_Ground_Empty, FALSE
	setmetatile 33, 58, METATILE_Cave_CoolGem_Blue_Mud_Empty, FALSE
	setmetatile 35, 50, METATILE_Cave_CoolGem_Blue_Mud_Empty, FALSE
	setmetatile 21, 11, METATILE_Cave_CoolGem_Blue_Ground_Empty, FALSE
	setmetatile 8, 50, METATILE_Cave_CoolGem_Red_Ground_Full, TRUE
	setmetatile 17, 9, METATILE_Cave_CoolGem_Red_Ground_Full, TRUE
	return

VolcanionCave_2F_EventScript_SetMetatilesRedButtonPressed::
	setmetatile 7, 48, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 17, 11, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 11, 46, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 10, 46, METATILE_Cave_CoolGem_Blue_Ground_Full, TRUE
	setmetatile 33, 58, METATILE_Cave_CoolGem_Blue_Mud_Full, TRUE
	setmetatile 35, 50, METATILE_Cave_CoolGem_Blue_Mud_Full, TRUE
	setmetatile 21, 11, METATILE_Cave_CoolGem_Blue_Ground_Full, TRUE
	setmetatile 8, 50, METATILE_Cave_CoolGem_Red_Ground_Empty, FALSE
	setmetatile 17, 9, METATILE_Cave_CoolGem_Red_Ground_Empty, FALSE
	return

VolcanionCave_2F_EventScript_Hole1A::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole1AToB
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleSouth
	waitmovement 0
	release
	end

VolcanionCave_2F_EventScript_Hole1B::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole1BToA
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleEast
	waitmovement 0
	release
	end

VolcanionCave_2F_Movement_Hole1AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole1BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_2F_EventScript_Hole2A::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole2AToB
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleNorth
	waitmovement 0
	release
	end

VolcanionCave_2F_EventScript_Hole2B::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole2BToA
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleWest
	waitmovement 0
	release
	end

VolcanionCave_2F_Movement_Hole2AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole2BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_2F_EventScript_Hole3A::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole3AToB
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleNorth
	waitmovement 0
	release
	end

VolcanionCave_2F_EventScript_Hole3B::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole3BToA
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleSouth
	waitmovement 0
	release
	end

VolcanionCave_2F_Movement_Hole3AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole3BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_2F_EventScript_Hole4A::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole4AToB
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleSouth
	waitmovement 0
	release
	end

VolcanionCave_2F_EventScript_Hole4B::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole4BToA
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleNorth
	waitmovement 0
	release
	end

VolcanionCave_2F_Movement_Hole4AToB::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole4BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

VolcanionCave_2F_EventScript_Hole5A::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole5AToB
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleSouth
	waitmovement 0
	release
	end

VolcanionCave_2F_EventScript_Hole5B::
	lock
	hideplayer
	playse SE_FALL
	waitse
	delay 16
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_Hole5BToA
	waitmovement 0
	delay 16
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_ExitHoleSouth
	waitmovement 0
	release
	end

VolcanionCave_2F_Movement_Hole5AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole5BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_2F_Movement_ExitHoleSouth::
	face_down
	set_visible
	jump_down
	step_end

VolcanionCave_2F_Movement_ExitHoleNorth::
	face_up
	set_visible
	jump_up
	step_end

VolcanionCave_2F_Movement_ExitHoleEast::
	face_right
	set_visible
	jump_right
	step_end

VolcanionCave_2F_Movement_ExitHoleWest::
	face_left
	set_visible
	jump_left
	step_end

VolcanionCave_2F_EventScript_RockSmash::
	lockall
	checkfieldmove FIELD_MOVE_ROCK_SMASH, TRUE
	goto_if_eq VAR_RESULT, PARTY_SIZE, VolcanionCave_2F_EventScript_CantSmashRock
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH
	msgbox Text_WantToSmash, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VolcanionCave_2F_EventScript_CancelSmash
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
VolcanionCave_2F_EventScript_RockSmashCommon:
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
VolcanionCave_2F_EventScript_SmashRock:: @ fallthrough
	applymovement VAR_LAST_TALKED, Movement_SmashRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	delay 10
	setflag FLAG_ANIMATE_MUD_UNDER_BOULDER
	playse SE_FALL
	applymovement LOCALID_2F_BOULDER_ON_MUD, VolcanionCave_2F_Movement_BoulderSlideDown
	waitmovement 0
	setobjectxyperm LOCALID_2F_BOULDER_ON_MUD, 26, 13
	playse SE_M_STRENGTH
	clearflag FLAG_ANIMATE_MUD_UNDER_BOULDER
	callnative UpdateBoulderOnMudPosition
	delay 10
	msgbox VolcanionCave_2F_Text_BoulderSlidDown, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_2F_EventScript_CantSmashRock::
	msgbox Text_CantSmash, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_2F_EventScript_CancelSmash::
	closemessage
	releaseall
	end

VolcanionCave_2F_Text_BoulderSlidDown::
	.string "The boulder slid down!$"

VolcanionCave_2F_Movement_BoulderSlideDown::
	walk_down
	walk_down
	walk_fast_down
	jump_down
	step_end
