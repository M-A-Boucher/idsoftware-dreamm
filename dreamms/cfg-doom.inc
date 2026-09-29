launch = LAUNCH.BAT
audiohw = $(SOUNDHW)+$(MUSICHW)
CONFIG_FILE = DREAMM.CFG
NOENDDOOM = false
NOKEYS = false
NOSOUND = false
MUSIC = 0
MUSICHW = sb16
SOUND = 0
SOUNDHW = sb16

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
	condition = !$(NOKEYS)
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
	condition = !$(NOSOUND)
    title = Music Configuration
        option[none]:
        name = None
        MUSIC = 0; MUSICHW = sb16
    end
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
	condition = !$(NOSOUND)
    title = Sound Configuration
        option[none]:
        name = None
        SOUND = 0; SOUNDHW = sb16
    end
    option[speaker]:
        name = $(SPEAKER_NAME)
        SOUND = 1; SOUNDHW = speaker
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
    snd_musicdevice    $(MUSIC)
    snd_sfxdevice      $(SOUND)
    snd_channels       8
    snd_sbport         544
    snd_sbirq          7
    snd_sbdma          1
    snd_mport          816
]]]

MACRO_CONFIGS = [[[$(CRLF)
    usegamma           0
    chatmacro0         "No"
    chatmacro1         "I'm ready to kick butt!"
    chatmacro2         "I'm OK."
    chatmacro3         "I'm not looking too good!"
    chatmacro4         "Help!"
    chatmacro5         "You suck!"
    chatmacro6         "Next time, scumbag..."
    chatmacro7         "Come here!"
    chatmacro8         "I'll take care of it."
    chatmacro9         "Yes"
]]]

//
// ENDDOOM configuration
//
config[enddoom]:
    condition = !is_installer()
    title = Exit Screen
    option[show]:
        name = Show
        END = true
    end
    option[hide]:
        name = Skip; priority = 1
        END = false
    end
end

// Installer script
DEICE = [[[$(CRLF)
    @ECHO OFF
    COPY *.1 1.1
    COPY *.2 1.2
    COPY *.3 1.3
    COPY *.4 1.4
    COPY *.5 1.5
    COPY 1.1+1.2+1.3+1.4+1.5 INSTALL.EXE
    INSTALL.EXE -n
]]]

// Launch script
LAUNCH = [[[$(CRLF)
    NOVERT
    $(EXEC)
]]]

// Generate batch to display ENDDOOM
LAUNCHEND = [[[$(CRLF)
    NOVERT
    $(EXEC)
    PAUSE
]]]

script[init]:
    code = [[[$(CRLF)
        video_suppress(true);

        if (is_installer())
          file_save("$$(rootpath)\\DEICE.BAT", "$$(DEICE)");

        if (is_game() || is_demo())
        {          
          file_save("$$(rootpath)\\LAUNCH.BAT", "$$(END)" ? "$$(LAUNCHEND)" : "$$(LAUNCH)");

          file = "$$(rootpath)\\$$(CONFIG_FILE)";

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


          // NOVERT by Istvan Pataki, 'minified' by eientei
          file_save("$$(rootpath)\\NOVERT.COM", "`h:EB 1C 00 00 00 00 3D 03 00 74 05 3D 0B 00 75 09 9C 2E FF 1E 02 01 33 D2 CF 2E FF 2E 02 01 B8 33 35 CD 21 89 1E 02 01 8C 06 04 01 B8 33 25 BA 06 01 CD 21 BA 1E 01 C1 EA 04 42 B8 00 31 CD 21");
        }

        while (video_text()) wait("videomode"); 
        video_suppress(false);
    ]]]
end