# Heretic2Toolkit
Heretic 2 game code

# What is this repo about ?
Load Game was crashing constantly for me even when using Tutorial as a springboard, so I tried to do some fixes inside the gamecode. I still see some Newgame crashes, but those are not systematic.

The debugger pointed to a function not checking for null (ResMngr_DeallocateResource, called from SLList_Des, which may also deallocate twice) inside H2Common.dll. Meanwhile I was checking out Anachronox and the comunity patch there, where the author mentioned having to track down a bunch of function pointers.

This gave me an ideea, since my above attempts to fix the issue led me to some 'think' actions that were crashing and I was confused: that variable was storing pointers to functions in the gamex86.dll, and they were behaving differently when the game was reloading and trying to call that function. So I decided to transform those pointers to offsets from the dll's base address, and restore them to absolute pointer upon loading a game.

# Notes:
Changes from 1.07 patch of gamex86.dll (base addr 10f50000) have been added:
- 10f80cb6 (30cb6) singing_ogles 1
- 10f80ed2 (30ed2) flash_screen 0
- 10f81c1d (31c1d) ReadLevel: skip over gi.error "function pointers have moved": message shown, but loadgame aborts now
- 11040ed8 (f0ed8) FAR_CLIP_DIST "8192.0"

# Additions:
- Added cheat for Light: "suckitdown light" this will toggle the Light Shrine effect ON and OFF
- Crash report helpers: run the .\crashes\CopyCrashDumpHere.bat to copy any previous crash dumps to local folder; these should be used for bug reports
- Crash helper to activate FullDump, and another to go back to MiniDump

# In case of crashes
- Disclaimer: NewGame crashes are happening inside quake2.dll and Heretic2.exe and I do not have source-code to investigate them. Maybe when other RE projects on github reach a playable state..
- Save often, when you get a crash I need to replicate it on my PC to investigate, so zip the savegame file, and copy the Windows minidump file locally using crashes\CopyCrashDumpHere.bat
- Attach the savegame file and the Windows minidump to a github Issue[https://github.com/whisperglen/Heretic2Toolkit/issues] and I will take a look at it
- Don't post empty Issues without helpul info: tell me what actions you took, where did you go before the crash etc. If I cannot replicate the rash there's not much I can do!
