mkdir .\GameCode\base\crashes
copy .\GameCode\Final\gamex86.pdb .\GameCode\base\gamex86.pdb
copy .\GameCode\Final\"Client Effects.pdb" .\GameCode\base\
copy .\GameCode\Final\Player.pdb .\GameCode\base\
copy .\GameCode\resources\crashes\* .\GameCode\base\crashes\
7z a -tzip h2_game_binaries.zip .\GameCode\base\gamex86.dll .\GameCode\base\gamex86.pdb .\GameCode\base\crashes