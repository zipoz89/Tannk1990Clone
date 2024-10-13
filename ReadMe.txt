Controlls:
    Player 1
        movement: WSAD
        shooting Space
    Player 2
        movement: Arrow Keys
        shooting Enter



First of all, I need to address that all my professional experience was in c# in Unity but I used to program in c++ before and throughout my collage so I might have used some bad practices,
though I consider myself a quick learner, so adjusting to standards used in the company should be easy.

I didn't add enemy AI, but I implemented the tank controller so that the player input class could be generalized to be a strategy pattern,
and then made AiTankInputStrategy and PlayerInputStrategy, so tanks could be controlled by either AI or player, but then still the ai behavior would have to be implemented.
The easiest way (beside random movement) would be to create some sort of graph on the map for ai to roam around (like in retro games)
or just use a* algorithm for pathing or combination of both but both of them would result in a moderately easy enemy. For harder enemy I would implement behavior tree and prediction to avoid and shoot projectiles.
For game this easy neural network based on reinforcement learning could probably give good results with minimal optimizing effort.

things i would implement if I had more time:
AI enemies
Menu.
Options with key rebind ability.
Some particles and overall fell to the game to give player more feedback (I have experience in graphic programing, shaders and visual effects, but I wasn't able to show it off in this task)
More players and gamemodes ex. teams, free for all, deathmatch, capture the flag...
Some power ups ex. more bullets at once, more speed, invincibility...
Better graphics (here I'm not the expert so I would have to rely on artists)

things i would implement if I had MUCH MORE time:
Multplayer
Multithreading (I'm a fan of ecs frameworks)
