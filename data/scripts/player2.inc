EventScript_Player2_Singleplayer::
	lock
	goto_if_set FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER, EventScript_Player2_ReadyToBattle
	faceplayer
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, Player2_Message_HiPlayerMagma
	call_if_eq VAR_RESULT, FALSE, Player2_Message_HiPlayerAqua
	waitmessage
	multichoicedefault 21, 6, MULTI_PLAYER_2, 0, FALSE
	switch VAR_RESULT
	case 0, Player2_Singleplayer_Trade
	case 1, Player2_Singleplayer_Talk
	case 2, Player2_Singleplayer_Cancel
	case MULTI_B_PRESSED, Player2_Singleplayer_Cancel
	release
	end

Player2_Singleplayer_Trade::
	@ choose player mon
	msgbox Player2_Text_GiveWhatPokemon, MSGBOX_NPC
	special ChoosePartyMon
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_ge VAR_0x800A, PARTY_SIZE, Player2_Singleplayer_Cancel
	specialvar VAR_0x8008, GetTradeSpecies

	@ choose partner mon
	callnative SwitchParties
	msgbox Player2_Text_ReceiveWhatPokemon, MSGBOX_NPC
	special ChoosePartyMon
	copyvar VAR_0x800B, VAR_0x8004
	specialvar VAR_0x8009, GetTradeSpecies
	callnative SwitchParties
	goto_if_ge VAR_0x800B, PARTY_SIZE, Player2_Singleplayer_Cancel

	@ confirm trade
	callnative BufferSinglePlayerTradeNicknames
	msgbox Player2_Text_GivePokemonForPokemon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, Player2_Singleplayer_Cancel
	case YES, Player2_Singleplayer_DoTrade
	case MULTI_B_PRESSED, Player2_Singleplayer_Cancel
	release
	end

Player2_Singleplayer_DoTrade::
	special DoSinglePlayerTradeScene
	callnative BufferSinglePlayerTradeNicknames
	msgbox Player2_Text_TakeGoodCareOfPokemon, MSGBOX_NPC
	release
	end

Player2_Singleplayer_Talk::
	goto_if_unset FLAG_HIDE_VOLCANION_CAVE_1F_BREAKABLE_ROCK, Player2_Message_Talk
	goto_if_unset FLAG_DEFEATED_VOLCANION_CAVE_1F_GOLEM, Player2_Message_PreGolem
	goto_if_eq VAR_VOLCANION_CAVE_2F_STATE, 0, Player2_Message_PreRoom2
	release
	end
	
Player2_Message_Talk::
	msgbox Player2_Text_Talk, MSGBOX_NPC
	release
	end

Player2_Text_Talk::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}This sucks!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Yes, I'm aware that TEAM AQUA is the\n"
	.string "objectively worse organization here.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Oh come on, you know that's\n"
	.string "not what I meant!\p"
	.string "There's this stupid rock in my way!!\p"
	.string "If only SHELLY had enough DYNAMO\n"
	.string "BADGES to give to all of us…\p"
	.string "Even then, I don't have a POKéMON\n"
	.string "that knows ROCK SMASH.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Sounds to me like there's\n"
	.string "nothing you can do about that.\p"
	.string "Good luck, sucker!!$"

Player2_Message_PreGolem::
	msgbox Player2_Text_PreGolem, MSGBOX_NPC
	release
	end

Player2_Text_PreGolem::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT 5}hmmmm… mmgrmh… mrgrgr…\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}{FONT_NORMAL}Hey, quit mumbling!\p"
	.string "If you have another insult for me\n"
	.string "then just spit it out already!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Shockingly, that isn't what I was\n"
	.string "planning this time.\p"
	.string "I'm simply thinking about my strategy\n"
	.string "to beat the GOLEM blocking the exit.\p"
	.string "{FONT 5}I have no problems when it uses\n"
	.string "THUNDERPUNCH, but I can't easily\l"
	.string "take an EARTHQUAKE.\p"
	.string "I wonder if there's a way to\n"
	.string "avoid both of its moves…\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}{FONT_NORMAL}Sweet! Thanks for the tips, loose lips!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Wait… I said that all out LOUD???$"

Player2_Message_PreRoom2::
	msgbox Player2_Text_PreRoom2, MSGBOX_NPC
	release
	end

Player2_Text_PreRoom2::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}You know, I could get used to\n"
	.string "this teamwork thing!\p"
	.string "But only if you were a TEAM AQUA GRUNT,\n"
	.string "of course.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Go bother a TEAM AQUA GRUNT and\n"
	.string "leave me alone, then.$"

Player2_Singleplayer_Cancel::
	msgbox Player2_Text_WeGotThis, MSGBOX_NPC
	release
	end

Player2_Message_HiPlayerMagma::
	msgbox Player2_Text_HiPlayerMagma, MSGBOX_NPC
	return

Player2_Message_HiPlayerAqua::
	msgbox Player2_Text_HiPlayerAqua, MSGBOX_NPC
	return

Player2_Text_HiPlayerMagma::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}You again?\n"
	.string "What did I do to deserve this?$"

Player2_Text_HiPlayerAqua::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}What, you need something?$"

Player2_Text_GiveWhatPokemon::
	.string "{RIVAL}: What POKéMON do you\nwant to give?$"

Player2_Text_ReceiveWhatPokemon::
	.string "{RIVAL}: What POKéMON do you\nwant to receive?$"

Player2_Text_GivePokemonForPokemon::
	.string "{RIVAL}: Trade {STR_VAR_1}\nfor {STR_VAR_2}?$"

Player2_Text_TakeGoodCareOfPokemon::
	.string "{RIVAL}: I'll take good care\nof {STR_VAR_2}!$"



Player2_Text_WeGotThis::
	.string "{RIVAL}: We got this!$"

Player2_Connect::
	message gText_PleaseWaitForLink
	waitmessage
	special TryTradeLinkup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Player2_LinkSuccess
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_PLAYER_NOT_READY, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_PARTNER_NOT_READY, Player2_AbortLinkTryAgain
	end

Player2_AbortLinkTryAgain::
	special CloseLink
	msgbox CableClub_Text_PleaseVisitAgain, MSGBOX_DEFAULT
	release
	end

Player2_LinkSuccess::
	callnative StoreLinkPlayerName
	setvar VAR_0x8004, USING_TRADE_CENTER
	copyvar VAR_CABLE_CLUB_STATE, VAR_0x8004
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	setwarp MAP_OLDALE_TOWN, VAR_TEMP_0, VAR_TEMP_1
	special DoCableClubWarp
	end

EventScript_Player2_Multiplayer::
	lock
	faceplayer
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, Player2_Text_HiPlayerMagma
	message Player2_Text_HiPlayerAqua
	waitmessage
	multichoicedefault 21, 6, MULTI_PLAYER_2, 0, FALSE
	switch VAR_RESULT
	case 0, Player2_Multiplayer_Trade
	case 1, Player2_Multiplayer_Talk
	case 2, Player2_Multiplayer_Cancel
	case MULTI_B_PRESSED, Player2_Multiplayer_Cancel
	release
	end

Player2_Multiplayer_Trade::
	setvar VAR_0x8005, 0
	special PlayerEnteredTradeSeat
	end

Player2_Multiplayer_Talk::
	msgbox Player2_Text_Talk, MSGBOX_NPC
	release
	end

Player2_Multiplayer_Cancel::
	msgbox Player2_Text_WeGotThis, MSGBOX_NPC
	release
	end

EventScript_Player2_ReadyToBattle::
	lock
	msgbox Player2_Text_ReadyToBattle, MSGBOX_DEFAULT
	release
	end

Player2_Text_ReadyToBattle::
	.string "{RIVAL} is ready to battle!$"
