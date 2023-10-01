# Pokemon Masters: Victory Road

Pokemon Masters is the cumulative, solo final project in Professor Densmore's EC327 software engineering course. It uses fundamental OOP principles (Abstraction, Encapsulation, Inheritance, Polymorphism) to its fullest extent, 
while incorporating makefiles, state machine logic, and version control through Github.

Project assignment instructions are included as PDFs. 

How to Play:
You are a Pokemon Trainer. You are trying to defeat the gyms but you need your Pokemon to
stay healthy. You must go to gyms and earn experience by battling. However, you also need to
periodically get potions if you want to make sure your Pokemon don’t faint. You “win” the game
by defeating all the gyms without having your Pokemon faint. You can compare games with
others by seeing who completes all the gyms the fastest.

Instructions:
  Download and run PA4.exe, or run 'make' and ./PA4 to play!

## Commands

  m ID x y - "move": command Trainer ID to move to location (x, y)
  
  c ID1 ID2 - "move towards a PokemonCenter”: command Trainer ID1 to start heading to
  PokemonCenter ID2.
  
  g ID1 ID2 - “move towards a PokemonGym”: command Trainer ID1 to start heading towards
  PokemonGym ID2.
  
  s ID - "stop": command Trainer ID to stop doing whatever it is doing
  
  p ID potion_amount - “buy potions”: command Trainer ID to buy potion_amount of potion at a
  PokemonCenter.
  
  b ID battle_amount - “complete battle_amount battles at a PokemonGym”: command Trainer ID to
  complete battle_amount of battles at a PokemonGym.
  
  a - "advance": advance one-time step by updating each object once.
  
  r - "run": advance one-time step and update each object, and repeat until either the
  update function returns true for at least one of the objects, or 5 time steps have
  been done.
  
  q - "quit": terminate the program

Implement a new command:
  n TYPE ID X Y- create a new object with the specified TYPE, ID number, (X, Y) location
  
  TYPE is a one letter abbreviation for the type of object:
  c – PokemonCenter
  g – PokemonGym
  t – Trainer
  w – WildPokemon

  S filename - Save the game in the file specified.
  R filename - Restore the game using the file specified.
