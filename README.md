# Heretic2Toolkit
Heretic 2 game code

# What is this repo about ?
Load Game (and sometimes New Game) was crashing, and the usual recommendation (start Tutorial then Load/New) was not working for me.

The debugger pointed to a function not checking for null (ResMngr_DeallocateResource, called from SLList_Des, which may also deallocate twice). Meanwhile I was checking out Anachronox and the comunity patch there, where the author mentioned having to track down a bunch of function pointers.

A lightbulb now flickered into existence, since my above attempts to fix the issue led me to some 'think' actions that were crashing and confused me: that variable was storing pointers to functions in the gamex86.dll, and they were behaving differently when the game was reloading and tryying to call that function. So I decided to transform those pointers to offsets from the dll's base address, and restore them to absolute pointer upon loading a game.

This is the story of the fix, now to see if it actually works..