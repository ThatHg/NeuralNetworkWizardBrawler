RANGER_TEXTURE	= "enemy.png"
MELEE_TEXTURE	= "enemy.png"

function initialize(level)
	maxenemies = get_maxenemies(level);

	for i=0, maxenemies/2, 1 do
		spawn(level, "melee_trainee.lua",	MELEE_TEXTURE,	0)
	end

	for i=0, maxenemies/2, 1 do
		spawn(level, "ranger_trainee.lua",	RANGER_TEXTURE,	1)
	end
end

function spawn_enemy(level)
	type = get_typetospawn(level);
	if type == 0 then 
		spawn(level, "melee_trainee.lua",	MELEE_TEXTURE,	0)
	elseif type == 1 then 
		spawn(level, "ranger_trainee.lua",	RANGER_TEXTURE,	1)
	elseif type == 2 then 
		spawn(level, "melee_boss.lua",		MELEE_TEXTURE,	0)
	elseif type == 3 then 
		spawn(level, "ranger_boss.lua",		RANGER_TEXTURE,	1)
	else
		error("Invalid enemy type.")
	end
end		
