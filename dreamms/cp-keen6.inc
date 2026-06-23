CP_FINGERPRINTS = [[[,
    LysYWe6XxpX11ZKv09v7ZhL1GPSrv5HRbGKNT7PNB#ffZ2H5vYucpS // CGA
    kz1HSWVWo2T9Dg#Bg@gguX39JUldTxbgBVKPcg4792QEuA7xzp0PpQ // EGA
]]]

CREATURE_FINGERPRINTS = [[[,
    iNyeydqqYRH2cPnLI@AS3oD2YtOQr6j7jYWP8ShEJ9Zy#cb6UE6GtQ=Babobba // CGA
    oJVzSRwyBrX69uVcAzir7er6AebEP1M21ZWDH6LQ9xHIwoX2yvphlc=Babobba // EGA
    AMjP6dRkvvD2cPnLI@poe231X#GMr6FqM9#PUWHLJ9NMiZb6fXqXBQ=Bip // CGA
    jn8UeR6dOw769uVcAzHTmoT1aPgYfxs6sOGDxrHsxxnL0F32k@AD1c=Bip // EGA
    4ksIids7Oo@2cPnLI@yDiYD1mpWKn53efNiP42ZVZ91vIU36fXqXBQ=Blooglet // CGA
    LgpFiRyJd4769uVcAzuUxK@1SNfbP2M21ZWDu2Is9xIt3X@2k@AD1c=Blooglet // EGA
    pAjr6egzPdL2Y3Cc4@@SKlb2n9iyD4pHVW6PQiBSN#ruUCv6bhIEZQ=Blooguard // CGA
    BSDLScdBOMf6gliHUzcmRRX66Foy@7DYzLWDGprUF#xvnWb2zTrdNc=Blooguard // EGA
    rkRlCdVTphb2cPnLI@yiYDX1#zlb77MA@KePDHZDl#1dD8L7bhIEZQ=Blorb // CGA
    V5RfKRU#UVn69uVcAz5qNkfx#sLuz1bM2oODmvz0x6BhkDH1HLNMVc=Blorb // EGA
    Gq8UGcnopCn2cPnLI@V#duH1NDiyf5vCWpqPKl19h94tzgH7iMQwxQ=Bobba // CGA
    MQyFWSlqwSD69uVcAz5EG3HxF8aLD5dJL52D27fI1xPoN1b1JlY3lc=Bobba // EGA
    iNyeydrJqw@21c8CU@AS3oD2pm8in63efNiP8ShEJ9w23@P6fXqXBQ=Ceilick // CGA
    DsAJ6RE0Jsn6Kq4D0z76d836SOW2T2M21ZWDH6LQ9xLedr72k@AD1c=Ceilick // EGA
    Yg4xCdY68RH2cPnLI@Pr19z2pDAj76#3xLCP0YahN9fF6lX6fXqXBQ=Flect // CGA
    Hbqv6RAv4F769uVcAzO9lDj7vO03n5M21ZWDBFRBRxxBph32k@AD1c=Flect // EGA
    SOCjed9fhxX2cPnLI@vDpDv1vZOZr5MVL3KPLnksN#al4zT6mCLNtT=Fleex // CGA
    WO7OGR4KPgb69uVcAzOWyjT2BidTb51V75yDyJLbp9NrND33Myir1b=Fleex // EGA
    GdSXKdTY1Hn1NSWEQ@IAfkf2PpgF@6kPbamP8ShEJ9w23@P6fXqXBQ=Gik // CGA
    wdFVKR5m7RT69uVcAzNwlCD6XbGN72M21ZWDH6LQ9xLedr72k@AD1c=Gik // EGA
    @rxWGdRSraf2cPnLI@M#eUb1psmCX53efNiPTNdkV#EZeyf40wmuJQ=Nospike // CGA
    bTa@KR26nE769uVcAzLbtCj1oTrqz5M21ZWDtzmXx#lZ5lb6emhkpc=Nospike // EGA
    iNyeydTovvz2cPnLI@ghWv70QjNXb43TjW6PIPAFx9htE0r6GBy3RQ=Orbatrix // CGA
    DsAJ6RyJd4769uVcAzTcGAL8a45ur5kB6buMa0tp1xjNdXL2ZurvZc=Orbatrix // EGA
]]]

script[cp]:
    condition = is_game();
    code = [[[$(CRLF)
        cpactive = "";

        func update()
        {
          if (!script_running(cpscript))
          {
            match = scraper_match("BAAeuIagU", "$$(CP_FINGERPRINTS)");

            if (match)
            {
              answer = scraper_match("BcAYAlAjN", "$$(CREATURE_FINGERPRINTS)");

              if (answer != "" && cpactive == "")
              {
                cpactive = answer;

                if (!prop("noautocp"))
                  cpscript = script_run_async("cpauto", answer+"\r");

                if (!prop("notextcp"))
                  overlay_show("cpoverlay", -1, "This creature is called: " + answer);
              }
            }
            else
            {
              cpactive = "";
              overlay_hide("cpoverlay");
            }
          }
        }

        func cpauto(value)
        {
          input_lockout(true);
          sleep(1000);
          keyboard_type(value);
          sleep(500);
          input_lockout(false);
        }
    ]]]
end