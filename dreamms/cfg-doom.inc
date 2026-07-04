audiohw = $(SOUNDHW)+$(MUSICHW)
CONFIG_FILE = DREAMM.CFG

//
// keyboard configuration
//
config[keyboard]:
    title = Keyboard Setup
    option[default]:
        name = Original (Arrow Keys)
        KEYBINDS = [[[$(CRLF)
            key_right       77
            key_left        75
            key_up          72
            key_down        80
            key_strafeleft  51
            key_straferight 52
            use_mouse       0

            key_flydown     82
            key_flycenter   71
            key_flyup	    73
            key_lookdown    83
            key_lookcenter  79
            key_lookup      81
            key_invleft     16
            key_invright    18
            key_jump        57
        ]]]
    end
    option[wasd]:
        name = Modern (WASD Keys)
        KEYBINDS = [[[$(CRLF)
            key_left        16
            key_right       18
            key_up          17
            key_down        31
            key_strafeleft  30 
            key_straferight 32 
            use_mouse       1

            key_flydown     82
            key_flycenter   71
            key_flyup.      73
            key_lookdown    83
            key_lookcenter  79
            key_lookup      81
            key_invleft     16
            key_invright    18
            key_jump        57
        ]]]
    end
end

//
// music configuration
//
config[music]:
    title = Music Configuration
    option[adlib]:
        name = $(ADLIB_NAME)
        MUSIC = 2; MUSICHW = adlib
    end
    option[sb16]:
        name = $(SB16_NAME); priority = 1
        MUSIC = 3; MUSICHW = sb16
    end
    option[gmidi]:
        name = $(GMIDI_NAME)
        MUSIC = 8; MUSICHW = gmidi
    end
    option[cdda]:
        name = CD Audio; priority = 2
        MUSIC = 10
        condition = file_exists("$$(rootpath)\\CD\\CDDA.SOU")
    end
end

//
// sound configuration
//
config[sound]:
    title = Sound Configuration
    option[speaker]:
        name = $(SPEAKER_NAME)
        SOUND = 1; SOUNDHW = speaker
        condition = file_exists("$$(rootpath)\\DOOM.EXE")
    end
    option[sb16]:
        name = $(SB16_NAME); priority = 1
        SOUND = 3; SOUNDHW = sb16
    end
end

CONFIG = [[[$(CRLF)
    mouse_sensitivity  10
    sfx_volume         8
    music_volume       8
    show_messages      1
    key_fire           29
    key_use            57
    key_strafe         56
    key_speed          54
    mouseb_fire        0
    mouseb_strafe      1
    mouseb_forward     2
    use_joystick       1
    joyb_fire          0
    joyb_strafe        1
    joyb_use           3
    joyb_speed         2
    screenblocks       10
    detaillevel        0
    showmessages       1
    $(AUDIO_CONFIGS)
    $(MACRO_CONFIGS)
    $(KEYBINDS)
]]]

AUDIO_CONFIGS = [[[$(CRLF)
    snd_musicdevice $(MUSIC)
    snd_sfxdevice   $(SOUND)
    snd_channels    8
    snd_sbport      544
    snd_sbirq       7
    snd_sbdma       1
    snd_mport       816
]]]

MACRO_CONFIGS = [[[$(CRLF)
    usegamma        0
    chatmacro0      "no macro"
    chatmacro1      "no macro"
    chatmacro2      "no macro"
    chatmacro3      "no macro"
    chatmacro4      "no macro"
    chatmacro5      "no macro"
    chatmacro6      "no macro"
    chatmacro7      "no macro"
    chatmacro8      "no macro"
    chatmacro9      "no macro"
]]]

script[autoconfig]:
    code = [[[$(CRLF)
        file = "$$(rootpath)\\DREAMM.CFG";

        if (file_exists(file))
        {
          content = file_load_string(file);
          content = substr(content, 0, strstr(content, "snd_musicdevice"));
          content = content + "$$(AUDIO_CONFIGS)$$(CRLF)";
          content = content + "$$(MACRO_CONFIGS)$$(CRLF)";
          content = content + "$$(KEYBINDS)$$(CRLF)";
        }
        else
        {
          content = "$$(CONFIG)";
        }

        file_save(file, content);
    ]]]
end