launch = LAUNCH.BAT
audiohw = $(SOUNDHW)+$(MUSICHW)
CONFIG_FILE = DREAMM.CFG
END = $(NULL)
NOENDDOOM = false
NOKEYS = false
NOSOUND = false
NOVERT = $(NULL)
MUSIC = 0
MUSICHW = sb16
SOUND = 0
SOUNDHW = sb16
SETUP = false
EXPERIENCE = true
MODERN_PRESET = false

//
// keyboard configuration
//
config[keyboard]:
    title = Keyboard Setup
    condition = !$(NOKEYS)
    option[original]:
        name = Original Preset (Arrow Keys Layout + Mouse)
    end
    option[modern]:
        name = Modern Preset (WASD Layout + No Y-Axis Mouse Hack)
        NOVERT = NOVERT
        MODERN_PRESET = true
    end
    option[custom]:
        name = Customized Keybinds
        condition = file_exists("$$(rootpath)\\SETUP.EXE")
        KEYBINDS = $(NULL)
        EXEC = $(rootpath)\SETUP.EXE
        SETUP = true
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

//
// experience configuration
//
config[experience]:
    title = Experience Configuration
    condition = !is_installer() && !$(NOENDDOOM)
    option[original]:
        name = Original (How It Was); priority = 1
        EXPERIENCE = PAUSE
    end
    option[custom]:
        name = Modern (Step Right Into the Game)
        condition = !$(SETUP)
        EXPERIENCE = true
    end
end

MACRO_CONFIGS = [[[$(CRLF)
    chatmacro0		"No"
    chatmacro1		"I'm ready to kick butt!"
    chatmacro2		"I'm OK."
    chatmacro3		"I'm not looking too good!"
    chatmacro4		"Help!"
    chatmacro5		"You suck!"
    chatmacro6		"Next time, scumbag..."
    chatmacro7		"Come here!"
    chatmacro8		"I'll take care of it."
    chatmacro9		"Yes"
]]]

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
    @ECHO OFF
    $(NOVERT)
    $(EXEC)
    $(EXPERIENCE)
]]]

script[init]:
    code = [[[$(CRLF)

        func ini_update(ini, ikey, ival)
        {
          delim = ikey + "$(TAB)$(TAB)";
          pos = strstr(ini, delim);
          if (pos >= 0)
          {
            vstart = pos + strlen(delim);
            eol = strstr(ini, "$(CRLF)", vstart);
            if (eol < 0) eol = strlen(ini);
              return substr(ini, 0, vstart) + ival + substr(ini, eol);
          }
          else
          {
            if (strlen(ini) > 0)
              return ini + "$(CRLF)" + delim + ival;
            else
              return delim + ival;
          }
        }

        if (is_installer())
            file_save("$$(rootpath)\\DEICE.BAT", "$$(DEICE)");

        if (is_game() || is_demo())
        {
          if ("$$(EXPERIENCE)" != "PAUSE")
            video_suppress(!"$$(SETUP)");

          cfg = file_load_string("$$(rootpath)\\$$(CONFIG_FILE)");

          cfg = ini_update(cfg, "snd_musicdevice", "$$(MUSIC)");
          cfg = ini_update(cfg, "snd_sfxdevice", "$$(SOUND)");
          cfg = ini_update(cfg, "snd_channels", "8");
          cfg = ini_update(cfg, "snd_sbport", "544");
          cfg = ini_update(cfg, "snd_sbirq", "7");
          cfg = ini_update(cfg, "snd_sbdma", "1");
          cfg = ini_update(cfg, "snd_mport", "1");

          cfg = ini_update(cfg, "use_joystick", "1");

          if ("$$(MODERN_PRESET)")
          {
            cfg = ini_update(cfg, "key_right", "18");
            cfg = ini_update(cfg, "key_left", "16");
            cfg = ini_update(cfg, "key_up", "17");
            cfg = ini_update(cfg, "key_down", "31");
            cfg = ini_update(cfg, "key_strafeleft", "30");
            cfg = ini_update(cfg, "key_straferight", "32");
            cfg = ini_update(cfg, "mouseb_forward", "-1");
            cfg = ini_update(cfg, "mouse_sensitivity", "10");

            // Heretic/Hexen
            cfg = ini_update(cfg, "key_flyup", "73");
            cfg = ini_update(cfg, "key_flydown", "82");
            cfg = ini_update(cfg, "key_flycenter", "71");
            cfg = ini_update(cfg, "key_useartifact", "28");

            // Heretic/Hexen/Strife
            cfg = ini_update(cfg, "key_lookup", "81");
            cfg = ini_update(cfg, "key_lookdown", "83");
            cfg = ini_update(cfg, "key_lookcenter", "79");
            cfg = ini_update(cfg, "key_invleft", "16");
            cfg = ini_update(cfg, "key_invright", "18");
            cfg = ini_update(cfg, "key_jump", "-1");

            // Strife
            cfg = ini_update(cfg, "key_useHealth", "35");
            cfg = ini_update(cfg, "key_invquery", "4");
            cfg = ini_update(cfg, "key_mission", "2");
            cfg = ini_update(cfg, "key_invPop", "3");
            cfg = ini_update(cfg, "key_invKey", "5");
            cfg = ini_update(cfg, "key_invHome", "71");
            cfg = ini_update(cfg, "key_invEnd", "79");
            cfg = ini_update(cfg, "key_invUse", "19");
            cfg = ini_update(cfg, "key_invDrop", "14");
            cfg = ini_update(cfg, "mouseb_jump", "1");
          }
          else
          {
            cfg = ini_update(cfg, "key_right", "77");
            cfg = ini_update(cfg, "key_left", "75");
            cfg = ini_update(cfg, "key_up", "72");
            cfg = ini_update(cfg, "key_down", "80");
            cfg = ini_update(cfg, "key_strafeleft", "51");
            cfg = ini_update(cfg, "key_straferight", "52");
            cfg = ini_update(cfg, "mouseb_forward", "2");

            // Heretic/Hexen
            cfg = ini_update(cfg, "key_flyup", "73");
            cfg = ini_update(cfg, "key_flydown", "82");
            cfg = ini_update(cfg, "key_flycenter", "71");
            cfg = ini_update(cfg, "key_useartifact", "28");

            // Heretic/Hexen/Strife
            cfg = ini_update(cfg, "key_lookup", "73");
            cfg = ini_update(cfg, "key_lookdown", "81");
            cfg = ini_update(cfg, "key_lookcenter", "79");
            cfg = ini_update(cfg, "key_invleft", "82");
            cfg = ini_update(cfg, "key_invright", "83");
            cfg = ini_update(cfg, "key_jump", "30");

            // Strife
            cfg = ini_update(cfg, "key_useHealth", "35");
            cfg = ini_update(cfg, "key_invquery", "16");
            cfg = ini_update(cfg, "key_mission", "17");
            cfg = ini_update(cfg, "key_invPop", "44");
            cfg = ini_update(cfg, "key_invKey", "37");
            cfg = ini_update(cfg, "key_invHome", "71");
            cfg = ini_update(cfg, "key_invEnd", "79");
            cfg = ini_update(cfg, "key_invUse", "28");
            cfg = ini_update(cfg, "key_invDrop", "14");
            cfg = ini_update(cfg, "mouseb_jump", "-1");
          }


          file_save("$$(rootpath)\\$$(CONFIG_FILE)", cfg);

          file_save("$$(rootpath)\\LAUNCH.BAT", "$$(LAUNCH)");

          // NOVERT by Istvan Pataki, 'minified' by eientei
          file_save("$$(rootpath)\\NOVERT.COM", "`h:EB 1C 00 00 00 00 3D 03 00 74 05 3D 0B 00 75 09 9C 2E FF 1E 02 01 33 D2 CF 2E FF 2E 02 01 B8 33 35 CD 21 89 1E 02 01 8C 06 04 01 B8 33 25 BA 06 01 CD 21 BA 1E 01 C1 EA 04 42 B8 00 31 CD 21");

          while (video_text()) wait("videomode");
          video_suppress(false);
        }
    ]]]
end
