copy .\GameCode\Final\game.pdb .\GameCode\base\gamex86.pdb
copy .\GameCode\Final\"Client Effects.pdb" .\GameCode\base\
copy .\GameCode\Final\Player.pdb .\GameCode\base\
7z a -tzip h2_game_binaries.zip .\GameCode\base\gamex86.dll .\GameCode\base\gamex86.pdb