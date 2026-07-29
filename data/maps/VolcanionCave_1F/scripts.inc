VolcanionCave_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_1F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_1F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_1F_OnFrame
	.byte 0

VolcanionCave_1F_OnTransition:
	callnative UpdateStrengthBoulderPositions
	call_if_set FLAG_VOLCANION_CAVE_1F_DIGLETT_LEFT_SPOT, VolcanionCave_1F_EventScript_UpdateMagmaMGruntAndDiglett
	end

VolcanionCave_1F_EventScript_UpdateMagmaMGruntAndDiglett::
	setobjectxyperm LOCALID_DIGLETT, 34, 17
	turnobject LOCALID_MAGMA_GRUNT_M, DIR_EAST
	return

VolcanionCave_1F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_1F_EventScript_TrySpawnPlayer2
	.2byte 0

VolcanionCave_1F_EventScript_TrySpawnPlayer2::
	callnative TrySpawnPlayer2
	setvar VAR_TEMP_1, 1
	call_if_eq VAR_VOLCANION_CAVE_1F_STATE, 0, VolcanionCave_1F_EventScript_HidePlayers
	end

VolcanionCave_1F_EventScript_HidePlayers::
	hideobjectat LOCALID_PLAYER_2, MAP_VOLCANION_CAVE_1F
	hideplayer
	return

VolcanionCave_1F_OnFrame:
	map_script_2 VAR_VOLCANION_CAVE_1F_STATE, 0, VolcanionCave_1F_EventScript_EnterCave
	.2byte 0

VolcanionCave_1F_EventScript_EnterCave::
	lock
	applymovement LOCALID_PLAYER_2, VolcanionCave_1F_Movement_Player2EnterCave
	waitmovement 0
	applymovement LOCALID_PLAYER, VolcanionCave_1F_Movement_PlayerEnterCave
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	setvar VAR_VOLCANION_CAVE_1F_STATE, 1
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	message VolcanionCave_1F_Text_IntroOhNo
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	message VolcanionCave_1F_Text_IntroWeirdo
	waitmessage
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	message VolcanionCave_1F_Text_IntroDontStare
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	message VolcanionCave_1F_Text_IntroLookTheSame
	waitmessage
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	message VolcanionCave_1F_Text_IntroBeatPoochyena
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	message VolcanionCave_1F_Text_IntroHowDoYouKnow
	waitmessage
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	message VolcanionCave_1F_Text_IntroSmellLikeEggs
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	message VolcanionCave_1F_Text_IntroJobToDo
	waitmessage
	callnative UpdatePlayer2Pos
	release
	end

VolcanionCave_1F_Movement_Player2EnterCave::
	set_visible
	walk_up
	walk_left
	walk_up
	step_end

VolcanionCave_1F_Movement_PlayerEnterCave::
	set_visible
	walk_up
	walk_right
	walk_up
	step_end

VolcanionCave_1F_Text_IntroOhNo::
	.string "{SPEAKER NAME_RIVAL COLOR_AQUA}Oh no…\p"
	.string "Of all of the people to run into\n"
	.string "on this job, it HAD to be you???\p$"

VolcanionCave_1F_Text_IntroWeirdo::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}(What is this TEAM AQUA\n"
	.string "weirdo yelling at me for?)\p$"

VolcanionCave_1F_Text_IntroDontStare::
	.string "{SPEAKER NAME_RIVAL COLOR_AQUA}Don't just stare at me like that!!\n"
	.string "…You do remember who I am, right?\p$"

VolcanionCave_1F_Text_IntroLookTheSame::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}I've seen hundreds of AQUA GRUNTS over\n"
	.string "the years and you all either look like\l"
	.string "pirates or pirates with orange hair.\p"
	.string "You'll have to forgive me for\n"
	.string "having zero clue who you are.\p$"

VolcanionCave_1F_Text_IntroBeatPoochyena::
	.string "{SPEAKER NAME_RIVAL COLOR_AQUA}hrRrrRRNGH-YOU BEAT MY POOCHYENA ON\n"
	.string "TOP OF MT. CHIMNEY AND YOU KNOW IT!!\p$"

VolcanionCave_1F_Text_IntroHowDoYouKnow::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}How do you know that was me?\p$"

VolcanionCave_1F_Text_IntroSmellLikeEggs::
	.string "{SPEAKER NAME_RIVAL COLOR_AQUA}YOU SMELL LIKE EGGS!!!!!\p$"

VolcanionCave_1F_Text_IntroJobToDo::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}{FONT 5}oh for the love of- {PAUSE 20}{FONT_NORMAL}Don't bring my\n"
	.string "sister's TOGEPI into this...\p"
	.string "Look, unlike you ARAQUA-NERDS,\n"
	.string "I have an important job to do.\p"
	.string "I'd appreciate it if you\n"
	.string "stayed out of my way.\p$"

VolcanionCave_1F_EventScript_MagmaGruntF::
	random 3
	goto_if_eq VAR_RESULT, 1, VolcanionCave_1F_EventScript_MagmaGruntFMsg1
	goto_if_eq VAR_RESULT, 2, VolcanionCave_1F_EventScript_MagmaGruntFMsg2
	msgbox VolcanionCave_1F_Text_HowDidIGetHere, MSGBOX_NPC
	end

VolcanionCave_1F_EventScript_MagmaGruntFMsg1::
	msgbox VolcanionCave_1F_Text_Help, MSGBOX_NPC
	end

VolcanionCave_1F_EventScript_MagmaGruntFMsg2::
	msgbox VolcanionCave_1F_Text_HELP, MSGBOX_NPC
	end

VolcanionCave_1F_Text_HowDidIGetHere::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}How did I get here…$"

VolcanionCave_1F_Text_Help::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}… … …\p"
	.string "Help.$"

VolcanionCave_1F_Text_HELP::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}HELP$"

VolcanionCave_1F_EventScript_MagmaGruntM::
	lock
	goto_if_set FLAG_VOLCANION_CAVE_1F_GRUNT_DROPPED_BADGE, VolcanionCave_1F_EventScript_MagmaGruntMDroppedBadge
	setflag FLAG_VOLCANION_CAVE_1F_GRUNT_DROPPED_BADGE
	setflag FLAG_VOLCANION_CAVE_1F_DIGLETT_LEFT_SPOT
	faceplayer
	message VolcanionCave_1F_Text_MagmaGruntMLoveDiglett
	waitmessage
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_M, Common_Movement_WalkInPlaceRight
	waitmovement 0
	message VolcanionCave_1F_Text_MagmaGruntMLookAtDiglett
	waitmessage
	closemessage
	applymovement LOCALID_DIGLETT, VolcanionCave_1F_Movement_DiglettDigDown
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_M, VolcanionCave_1F_Movement_MagmaGruntMConfused
	waitmovement 0
	delay 20
	applymovement LOCALID_DIGLETT, VolcanionCave_1F_Movement_DiglettDigUp
	waitmovement 0
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	applymovement LOCALID_MAGMA_GRUNT_M, VolcanionCave_1F_Movement_MagmaGruntMSurprised
	waitmovement 0
	delay 20
	setobjectxyperm LOCALID_DIGLETT, 34, 17
	addobject LOCALID_HEAT_BADGE
	setobjectxy LOCALID_HEAT_BADGE, 33, 17
	clearflag FLAG_HIDE_VOLCANION_CAVE_1F_HEAT_BADGE
	applymovement LOCALID_MAGMA_GRUNT_M, VolcanionCave_1F_Movement_MagmaGruntMWatchBadgeFallDown
	applymovement LOCALID_HEAT_BADGE, VolcanionCave_1F_Movement_BadgeFallDown
	waitmovement 0
	delay 20
	msgbox VolcanionCave_1F_Text_MagmaGruntMDroppedBadge
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_M, Common_Movement_WalkInPlaceRight
	waitmovement 0
	release
	end

VolcanionCave_1F_EventScript_MagmaGruntMDroppedBadge::
	goto_if_set FLAG_HIDE_VOLCANION_CAVE_1F_HEAT_BADGE, VolcanionCave_1F_EventScript_MagmaGruntMBadgeStolen
	faceplayer
	msgbox VolcanionCave_1F_Text_MagmaGruntMCoolDiglett
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_M, Common_Movement_WalkInPlaceRight
	waitmovement 0
	release
	end

VolcanionCave_1F_EventScript_MagmaGruntMBadgeStolen::
	msgbox VolcanionCave_1F_Text_MagmaGruntMHideoutPassword
	faceplayer
	msgbox VolcanionCave_1F_Text_MagmaGruntMGetALoadOfDiglett
	closemessage
	waitse
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	applymovement LOCALID_DIGLETT, VolcanionCave_1F_Movement_DiglettSurprised
	waitmoncry
	applymovement LOCALID_MAGMA_GRUNT_M, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox VolcanionCave_1F_Text_MagmaGruntMWoahThereDiglett
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_M, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VolcanionCave_1F_Movement_DiglettDigDown::
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	set_invisible
	walk_faster_left
	walk_faster_left
	face_left
	step_end

VolcanionCave_1F_Movement_DiglettDigUp::
	face_left
	set_visible
	walk_in_place_fast_left
	step_end

VolcanionCave_1F_Movement_MagmaGruntMConfused::
	emote_question_mark
	walk_in_place_left
	delay_16
	walk_in_place_down
	delay_16
	walk_in_place_right
	delay_16
	step_end

VolcanionCave_1F_Movement_MagmaGruntMSurprised::
	emote_exclamation_mark
	jump_in_place_right
	step_end

VolcanionCave_1F_Movement_MagmaGruntMWatchBadgeFallDown::
	delay_16
	emote_exclamation_mark
	walk_in_place_down
	step_end

VolcanionCave_1F_Movement_BadgeFallDown::
	set_visible
	slide_down
	jump_down
	jump_left
	jump_down
	step_end

VolcanionCave_1F_Movement_DiglettSurprised::
	emote_exclamation_mark
	step_end

VolcanionCave_1F_Text_MagmaGruntMLoveDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}I love DIGLETT.\p"
	.string "Their funny little bald heads\n"
	.string "always crack me up.\p$"

VolcanionCave_1F_Text_MagmaGruntMLookAtDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}I've been trying to get a closer look\n"
	.string "at this little guy for an hour now,\l"
	.string "but it doesn't seem like it's inter-{PAUSE 40}$"

VolcanionCave_1F_Text_MagmaGruntMDroppedBadge::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}Aw DIGLETTS!{PAUSE 20} That was my HEAT BADGE…\p"
	.string "And after COURTNEY went through the\n"
	.string "trouble of stealing BADGES from the\l"
	.string "POKéMON League so we could use HMs…\p"
	.string "I am in BIG trouble.$"

VolcanionCave_1F_Text_MagmaGruntMCoolDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}I guess on the bright side, being this\n"
	.string "close to a DIGLETT has been pretty rad.$"

VolcanionCave_1F_Text_MagmaGruntMHideoutPassword::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}…The PASSWORD to MAGMA HIDEOUT?\p"
	.string "Why would a DIGLETT want to know that?$"

VolcanionCave_1F_Text_MagmaGruntMGetALoadOfDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}Oh hey, get a load of this DIGLETT!!\p"
	.string "Little fella has been trying to\n"
	.string "get all sorts of confidential\l"
	.string "information out of me for a while.\p"
	.string "I'm pretty sure my little boy\n"
	.string "sent him to check up on me.\p"
	.string "I haven't been home much recently.\n"
	.string "He must be so worried about me…\p"
	.string "Don't worry TOMMY, I'll be home soon!$"

VolcanionCave_1F_Text_MagmaGruntMWoahThereDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}No, I don't know MAXIE's\n"
	.string "POKENAV number!$"

VolcanionCave_1F_EventScript_HeatBadge::
	removeobject VAR_LAST_TALKED
	msgbox VolcanionCave_1F_Text_ObtainedHeatBadge
	closemessage
	setflag FLAG_BADGE04_GET
	end

VolcanionCave_1F_Text_ObtainedHeatBadge::
	.string "{PLAYER} obtained the HEAT BADGE!$"

VolcanionCave_1F_EventScript_Diglett::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	msgbox VolcanionCave_1F_Text_DiglettCry
	waitmoncry
	closemessage
	delay 20
	msgbox VolcanionCave_1F_Text_DiglettSecretAgent
	closemessage
	release
	end

VolcanionCave_1F_Text_DiglettCry::
	.string "{SPEAKER NAME_DIGLETT COLOR_AQUA}Pipipi wowow!$"

VolcanionCave_1F_Text_DiglettSecretAgent::
	.string "(The DIGLETT seems to be an\n"
	.string "agent working for TEAM AQUA.)\p"
	.string "(You decide not to ruin the MAGMA\n"
	.string "GRUNT'S day with this information.)$"

VolcanionCave_1F_Movement_DiglettDigDown2::
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	set_invisible
	walk_faster_right
	walk_faster_right
	face_left
	step_end

VolcanionCave_1F_Movement_DiglettDigUp2::
	face_left
	set_visible
	walk_in_place_fast_left
	step_end

VolcanionCave_1F_EventScript_AquaGruntF::
	applymovement LOCALID_AQUA_GRUNT_F, Common_Movement_FacePlayer
	waitmovement 0
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_1F_EventScript_AquaGruntFPlayer2
	msgbox VolcanionCave_1F_Text_Repels, MSGBOX_NPC
	end

VolcanionCave_1F_EventScript_AquaGruntFPlayer2::
	msgbox VolcanionCave_1F_Text_NoRepels, MSGBOX_NPC
	end

VolcanionCave_1F_Text_Repels::
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}REPELS!!!!$"

VolcanionCave_1F_Text_NoRepels::
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}NO REPELS!!!!$"

VolcanionCave_1F_EventScript_RemoveLastTalked::
	removeobject VAR_LAST_TALKED
	return

VolcanionCave_1F_EventScript_Tirtouga::
	lock
	faceplayer
	playmoncry SPECIES_TIRTOUGA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_TIRTOUGA, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, VolcanionCave_1F_EventScript_RemoveLastTalked
	release
	end

VolcanionCave_1F_EventScript_Cubone::
	lock
	faceplayer
	playmoncry SPECIES_CUBONE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_CUBONE, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, VolcanionCave_1F_EventScript_RemoveLastTalked
	release
	end

VolcanionCave_1F_EventScript_RockSmash::
	lockall
	checkfieldmove FIELD_MOVE_ROCK_SMASH, TRUE
	goto_if_eq VAR_RESULT, PARTY_SIZE, VolcanionCave_1F_EventScript_CantSmashRock
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH
	msgbox Text_WantToSmash, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VolcanionCave_1F_EventScript_CancelSmash
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
VolcanionCave_1F_EventScript_RockSmashCommon:
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
VolcanionCave_1F_EventScript_SmashRock:: @ fallthrough
	applymovement VAR_LAST_TALKED, Movement_SmashRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	delay 10
	applymovement LOCALID_PLAYER, Common_Movement_FacePlayer2
	waitmovement 0
	callnative UpdateVarFacing
	call_if_eq VAR_FACING, DIR_NORTH, VolcanionCave_1F_EventScript_PlayerWalkInPlaceNorth
	call_if_eq VAR_FACING, DIR_SOUTH, VolcanionCave_1F_EventScript_PlayerWalkInPlaceSouth
	call_if_eq VAR_FACING, DIR_EAST, VolcanionCave_1F_EventScript_PlayerWalkInPlaceEast
	call_if_eq VAR_FACING, DIR_WEST, VolcanionCave_1F_EventScript_PlayerWalkInPlaceWest
	msgbox VolcanionCave_1F_Text_RockIsGone, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_1F_EventScript_CantSmashRock::
	msgbox Text_CantSmash, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_1F_EventScript_CancelSmash::
	closemessage
	releaseall
	end

VolcanionCave_1F_EventScript_PlayerWalkInPlaceNorth::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceUp
	waitmovement 0
	return

VolcanionCave_1F_EventScript_PlayerWalkInPlaceSouth::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	return

VolcanionCave_1F_EventScript_PlayerWalkInPlaceEast::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceRight
	waitmovement 0
	return

VolcanionCave_1F_EventScript_PlayerWalkInPlaceWest::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	return

VolcanionCave_1F_Text_RockIsGone::
	.string "{PLAYER}: Hey, {RIVAL}!\p"
	.string "Rock is gone, be useful \n"
	.string "and battle with me!$"

VolcanionCave_1F_EventScript_Golem::
	lock
	faceplayer
	playmoncry SPECIES_GOLEM_ALOLA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	goto_if_set FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER, VolcanionCave_1F_EventScript_DoGolemMultiBattle
	goto_if_unset FLAG_HIDE_VOLCANION_CAVE_1F_BREAKABLE_ROCK, VolcanionCave_1F_EventScript_DoGolemSingleBattle
VolcanionCave_1F_EventScript_AskGolemMultiBattle::
	msgbox VolcanionCave_1F_Text_BattleTogether, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, VolcanionCave_1F_EventScript_GetReadyForGolemMultiBattle
VolcanionCave_1F_EventScript_DoGolemSingleBattle::
	setwildbattle SPECIES_GOLEM_ALOLA, 35, TRUE
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_1F_EventScript_DefeatedGolem
	release
	end

VolcanionCave_1F_EventScript_DoGolemMultiBattle::
	clearflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	setwildbattle SPECIES_GOLEM_ALOLA, 35, TRUE
	multi_fixed_players_vs_wild PARTNER_PLAYER_2
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_1F_EventScript_DefeatedGolem
	release
	end

VolcanionCave_1F_EventScript_GetReadyForGolemMultiBattle::
	msgbox VolcanionCave_1F_Text_GotReadyToBattle, MSGBOX_DEFAULT
	setflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	callnative SwitchCharacters
	waitstate
	release
	end

VolcanionCave_1F_EventScript_DefeatedGolem::
	playmoncry SPECIES_GOLEM_ALOLA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	removeobject LOCALID_GOLEM
	addobject LOCALID_GOLEM_BOULDER
	clearflag FLAG_HIDE_VOLCANION_CAVE_1F_GOLEM_BOULDER
	msgbox VolcanionCave_1F_Text_DidWeKillIt, MSGBOX_DEFAULT
	release
	end

VolcanionCave_1F_Text_BattleTogether::
	.string "Battle together with {RIVAL}?$"

VolcanionCave_1F_Text_GotReadyToBattle::
	.string "{PLAYER} got ready to battle!$"

VolcanionCave_1F_Text_DidWeKillIt::
	.string "{PLAYER}: …\p"
	.string "We killed it…\p"
	.string "Yay!$"
