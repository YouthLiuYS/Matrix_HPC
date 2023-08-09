import pygame
import sys
from AirCraft_Object import aircraft
from GameInterface_Object import gameinterface
from Bullet import bullet
from EnemyAirCraft_Object import EnemyAircraft
pygame.init()
game_interface = gameinterface()
player_aircraft = aircraft("PersonalProject/aircraft.png",game_interface.screen,game_interface.screen.get_size())
player_bullet = bullet("PersonalProject/player_bullet.png",player_aircraft,player_aircraft.screen,player_aircraft.screenSize)
Enemy_aircraft = EnemyAircraft("PersonalProject/EnemyAircraft.png",game_interface.screen,game_interface.screen.get_size())
while(True):
    for event in pygame.event.get():
      if event.type == pygame.QUIT: 
        sys.exit()
      if event.type == pygame.KEYDOWN:
        player_aircraft.moveByKeyboard(event)

    # fill the color of the background
    game_interface.screen.fill(game_interface.backgroundColor)
    player_aircraft.blitAircraft() 
    player_aircraft.blitAllBullets()
    Enemy_aircraft.move() 
    Enemy_aircraft.Fire_a_Bullet()
  
    Enemy_aircraft.blitAircraft()
    Enemy_aircraft.blitAllBullets()
    
    # update the content of the game interface 
    pygame.display.update()
    