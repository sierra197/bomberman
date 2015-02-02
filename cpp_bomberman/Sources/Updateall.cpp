//
// Updateall.cpp for  in /home/peyrot_m/Restart_bomber/Sources
//
// Made by peyrot_m
// Login   <peyrot_m@epitech.net>
//
// Started on  Thu Jun 12 00:31:43 2014 peyrot_m
// Last update Sun Jun 15 23:33:56 2014 Noel DOVAN
//

#include "GameEngine.hh"


void                    GameEngine::UpdateIntro(__attribute__((unused))
						gdl::Clock const &clock,
						__attribute__((unused))
						gdl::Input &input)
{
  std::vector<int>	objs;

  objs =  _objects[1]->getObjs();
  this->_part = objs[1];
  _objects[1]->update(_clock, _input);
}

void			GameEngine::UpdateMenu(__attribute__((unused))
					     gdl::Clock const &clock,
					     __attribute__((unused))
					     gdl::Input &input)
{
  std::vector<int>	objs;

  objs =  _objects[2]->getObjs();
  this->_joueur = objs[0];
  this->_ia = objs[1];
  this->_madness = objs[2];
  this->_width = objs[3];
  this->_height = objs[4];
  this->_map = objs[5];
  if (objs[7] == 1 || _input.getInput(SDL_QUIT))
    end = true;
  this->_part = objs[6];
  if (objs[7] == 2)
    {
      this->IsDoLoad();
      if (this->scene_for_game() == false)
	end = true;
      this->_part = 4;
    }
  _objects[2]->update(_clock, _input);
  objs.clear();
}


void                    GameEngine::UpdateWinGame()
{
  if (this->WinGame)
    {
      this->_part = 8;
    }
}

void                    GameEngine::UpdateLoseGame()
{
  if (this->LoseGame)
    {
      this->_part = 9;
    }
}


void                    GameEngine::UpdateCubeBombe()
{
  size_t		i;
  size_t		end_cube;
  std::vector<int>	objs;
  char			val_a;
  char			val_b;

  i = 4;
  end_cube =  ((this->_width * this->_height) * 2) + 4;
  while (++i < end_cube) // utpate les cube et bombe
    {
      objs =  _objects[i]->getObjs();
      val_a = this->map->mapGetValueAt(_objects[i]->getX(),_objects[i]->getZ());
      val_b = this->map->objectGetValueAt(_objects[i]->getX(),_objects[i]->getZ());
      if (objs[0] == 1)
	{
	  if (val_a == '1' && objs[1] != 1)
	    _objects[i]->setObjs(1);
	  else if (val_a == '2' && objs[1] != 2)
	    _objects[i]->setObjs(2);
	  else if (val_b == '5' &&
		   objs[1] != 7)
	    _objects[i]->setObjs(7);
	  else if (val_b == '8' &&
		   objs[1] != 10)
	    _objects[i]->setObjs(10);
	  else if (val_a == '0' &&
		   (val_b == '2' || val_b == '6'
		    || val_b == '0' || val_b == '4'
		    || val_b == '1' || val_b == '3'))
	    _objects[i]->setObjs(0);
	}
      if (objs[0] == 2)
	{
	  if (val_b == '4')
	    _objects[i]->setObjs(1);
	  if (val_b == '1')
	    _objects[i]->setObjs(3);
	  if (val_b == '3')
	    _objects[i]->setObjs(5);
	  if (val_b == '6')
	    _objects[i]->setObjs(7);
	  if (val_b == '2')
	    _objects[i]->setObjs(9);
	  if (val_b == '7')
	    _objects[i]->setObjs(10);
	  if (val_b == '0')
	    _objects[i]->setObjs(0);
	}
      objs.clear();
      _objects[i]->update(_clock, _input);
    }
}

void                    GameEngine::UpdatePlayers(int const i)
{
  std::vector<int>	objs;
  objs =  _objects[i]->getObjs();
  Character*    player1 = this->GetPlayerByID(objs[1]);

  if (player1)
    {
      float     x = player1->getX(), y = player1->getY(), s = player1->getSpeed() * this->_clock.getElapsed() * 33;
      if (objs[5] == 1)
	// ((this->map->mapGetValueAt(static_cast<int>(x), static_cast<int>(y) - 1) == '1' ||
	//   this->map->mapGetValueAt(static_cast<int>(x), static_cast<int>(y) - 1) == '2' ||
	//   this->map->objectGetValueAt(static_cast<int>(x), static_cast<int>(y) - 1) == '4' ||
	//   this->map->objectGetValueAt(static_cast<int>(x), static_cast<int>(y) - 1) == '7') &&
	//  (this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) - 1) != '1' &&
	//   this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) - 1) != '2' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) - 1) != '4' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) - 1) != '7') &&
	//  (this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) - 1) != '1' &&
	//   this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) - 1) != '2' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) - 1) != '4' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) - 1) != '7') ?
	//  ((fmod(x, 1.0f) < .5) && (fmod(y, 1.0f) < .5) ? (player1->setPos(x - s, y, x - s - 0.4, y, *this->map)) :
	//   ((fmod(x, 1.0f) > .5) && (fmod(y, 1.0f) < .5) ? (player1->setPos(x + s, y, x + s + 0.4, y, *this->map)) :
	//    player1->setPos(x, y - s, x, y - s - 0.4, *this->map))) :
	//    ((this->map->mapGetValueAt(static_cast<int>(x), static_cast<int>(y) - 1) != '1' &&
	//      this->map->mapGetValueAt(static_cast<int>(x), static_cast<int>(y) - 1) != '2' &&
	//      this->map->objectGetValueAt(static_cast<int>(x), static_cast<int>(y) - 1) != '4' &&
	//      this->map->objectGetValueAt(static_cast<int>(x), static_cast<int>(y) - 1) != '7') ?
	//     ((fmod(x, 1.0f) < 0.4) ?
	//      (player1->setPos(x + s, y, x + s + 0.4, y, *this->map)) :
	//      ((fmod(x, 1.0f) > 0.6) ?
	//       (player1->setPos(x - s, y, x - s - 0.4, y, *this->map)) :
	//       player1->setPos(x, y - s, x, y - s - 0.4, *this->map))) :
	//     player1->setPos(x, y - s, x, y - s - 0.4, *this->map)));
	player1->setPos(x, y - s, x, y - s - 0.4, *this->map);
      if (objs[6] == 1)
	// ((this->map->mapGetValueAt(static_cast<int>(x), static_cast<int>(y) + 1) == '1' ||
	//   this->map->mapGetValueAt(static_cast<int>(x), static_cast<int>(y) + 1) == '2' ||
	//   this->map->objectGetValueAt(static_cast<int>(x), static_cast<int>(y) + 1) == '4' ||
	//   this->map->objectGetValueAt(static_cast<int>(x), static_cast<int>(y) + 1) == '7')  &&
	//  (this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1) != '1' &&
	//   this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1) != '2' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1) != '4' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1) != '7') &&
	//  (this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) + 1) != '1' &&
	//   this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) + 1) != '2' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) + 1) != '4' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) + 1) != '7') ?
	//  ((fmod(x, 1.0f) < .5) && (fmod(y, 1.0f) > .5) ? (player1->setPos(x - s, y, x - s - 0.4, y, *this->map)) :
	//   ((fmod(x, 1.0f) > .5) && (fmod(y, 1.0f) > .5) ? (player1->setPos(x + s, y, x + s + 0.4, y, *this->map)) :
	//     player1->setPos(x, y + s, x, y + s + 0.4, *this->map))) :
	//    ((this->map->mapGetValueAt(static_cast<int>(x), static_cast<int>(y) + 1) != '1' &&
	//      this->map->mapGetValueAt(static_cast<int>(x), static_cast<int>(y) + 1) != '2' &&
	//      this->map->objectGetValueAt(static_cast<int>(x), static_cast<int>(y) + 1) != '4' &&
	//      this->map->objectGetValueAt(static_cast<int>(x), static_cast<int>(y) + 1) != '7') ?
	//     ((fmod(x, 1.0f) < 0.4) ?
	//      (player1->setPos(x + s, y, x + s + 0.4, y, *this->map)) :
	//      ((fmod(x, 1.0f) > 0.6) ?
	//       (player1->setPos(x - s, y, x - s - 0.4, y, *this->map)) :
	//       player1->setPos(x, y + s, x, y + s + 0.4, *this->map))) :
	player1->setPos(x, y + s, x, y + s + 0.4, *this->map);
      if (objs[4] == 1)
	// ((this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y)) == '1' ||
	//   this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y)) == '2' ||
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y)) == '4' ||
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y)) == '7')  &&
	//  (this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) - 1) != '1' &&
	//   this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) - 1) != '2' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) - 1) != '4' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) - 1) != '7') &&
	//  (this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1) != '1' &&
	//   this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1) != '2' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1) != '4' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1) != '7') ?
	//  ((fmod(y, 1.0f) < .5) && (fmod(x, 1.0f) > .5)  ? (player1->setPos(x, y - s, x, y - s - 0.4, *this->map)) :
	//   ((fmod(y, 1.0f) > .5) && (fmod(x, 1.0f) > .5)  ? (player1->setPos(x, y + s, x, y + s + 0.4, *this->map)) :
	//    player1->setPos(x + s, y, x + s + 0.4, y, *this->map))) :
	//    ((this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y)) != '1' &&
	//      this->map->mapGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y)) != '2' &&
	//      this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y)) != '4' &&
	//      this->map->objectGetValueAt(static_cast<int>(x) + 1, static_cast<int>(y)) != '7') ?
	//     ((fmod(y, 1.0f) < 0.4) ?
	//      (player1->setPos(x, y + s, x, y + s + 0.4, *this->map)) :
	//      ((fmod(y, 1.0f) > 0.6) ?
	//       (player1->setPos(x, y - s, x, y - s - 0.4, *this->map)) :
	//       player1->setPos(x + s, y, x + s + 0.4, y, *this->map))) :
	//     player1->setPos(x + s, y, x + s + 0.4, y, *this->map)));
	player1->setPos(x + s, y, x + s + 0.4, y, *this->map);
      if (objs[3] == 1)
	// ((this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y)) == '1' ||
	//   this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y)) == '2' ||
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y)) == '4' ||
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y)) == '7')  &&
	//  (this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) - 1) != '1' &&
	//   this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) - 1) != '2' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) - 1) != '4' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) - 1) != '7') &&
	//  (this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) + 1) != '1' &&
	//   this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) + 1) != '2' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) + 1) != '4' &&
	//   this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y) + 1) != '7') ?
	//  ((fmod(y, 1.0f) < .5) && (fmod(x, 1.0f) < .5)  ? (player1->setPos(x, y - s, x, y - s - 0.4, *this->map)) :
	//   ((fmod(y, 1.0f) > .5) && (fmod(x, 1.0f) < .5)  ? (player1->setPos(x, y + s, x, y + s + 0.4, *this->map)) :
	//    player1->setPos(x - s, y, x - s - 0.4, y, *this->map))) :
	//    ((this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y)) != '1' &&
	//      this->map->mapGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y)) != '2' &&
	//      this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y)) != '4' &&
	//      this->map->objectGetValueAt(static_cast<int>(x) - 1, static_cast<int>(y)) != '7') ?
	//     ((fmod(y, 1.0f) < 0.4) ?
	//      (player1->setPos(x, y + s, x, y + s + 0.4, *this->map)) :
	//      ((fmod(y, 1.0f) > 0.6) ?
	//       (player1->setPos(x, y - s, x, y - s - 0.4, *this->map)) :
	//       player1->setPos(x - s, y, x - s - 0.4, y, *this->map))) :
	//     player1->setPos(x - s, y, x - s - 0.4, y, *this->map)));
	player1->setPos(x - s, y, x - s - 0.4, y, *this->map);
      if (objs[7] == 1)
	player1->DoBombe(*this->map);
    }
  _objects[i]->setX(player1->getX() - 0.5);
  _objects[i]->setZ(player1->getY() - 0.5);
}


Character*              GameEngine::GetPlayerByID(int const id) const
{
  std::list<Character*>::const_iterator it(this->Players.begin());

  while (it != this->Players.end())
    {
      if ((*it)->getType() == id)
        return *it;
      ++it;
    }
  return NULL;
}

Character*              GameEngine::GetPlayerByName(std::string const& name) const
{
  std::list<Character*>::const_iterator it(this->Players.begin());

  while (it != this->Players.end())
    {
      if ((*it)->getName() == name)
        return *it;
      ++it;
    }
  return NULL;
}

void			GameEngine::UpdateAI(int const i)
{
  std::vector<int>	objs;

  objs =  _objects[i]->getObjs();

  Character*    player1 = this->GetPlayerByID(objs[1]);
  if (player1)
    {
      player1->moveIA(*this->map, this->_clock);
      if (player1->getX() > _objects[i]->getX()
	  && player1->getY() == _objects[i]->getZ())
	_objects[i]->setObjs(5);
      if (player1->getX() == _objects[i]->getX()
	  && player1->getY() < _objects[i]->getZ())
	_objects[i]->setObjs(3);
      if (player1->getX() < _objects[i]->getX()
	  && player1->getY() == _objects[i]->getZ())
	_objects[i]->setObjs(6);
      if (player1->getX() == _objects[i]->getX()
	  && player1->getY() > _objects[i]->getZ())
	_objects[i]->setObjs(4);
    }
  _objects[i]->setX(player1->getX());
  _objects[i]->setZ(player1->getY());

}


void                    GameEngine::UpdateCharacters(int const i)
{
  std::vector<int>	objs;
  std::vector<int>	objs2;
  std::vector<AObject*>::iterator       it2(this->_objects.begin());
  std::list<Character*>::iterator       it(this->Players.begin());
  objs =  _objects[i]->getObjs();
  Character*    player1 = this->GetPlayerByID(objs[1]);
  int		z = player1->getType();
  int		x = 0;
  while (it2 != this->_objects.end())
    {
      if (((player1->getLife() <= 0) && x == i) ||
	  (this->map->mapGetValueAt((int)player1->getX(), (int)player1->getY()) == '2'
	   && x == i))
	{
	  if (objs[0] == 5)
	    this->_joueur -= 1;
	  if (player1->getID() == 3)
	    this->_ia -= 1;
	  it2 = this->_objects.erase(it2);
	}
      else
	++it2;
      ++x;
    }
  while (it != this->Players.end())
    {
      if (((*it)->getLife() <= 0 && (*it)->getType() == z) ||
	  (this->map->mapGetValueAt((int)(*it)->getX(), (int)(*it)->getY()) == '2'
	   && (*it)->getType() == z))
        {
          this->map->playerSetValueAt('0', (*it)->getX(), (*it)->getY());
          it = this->Players.erase(it);
        }
      else
	++it;
    }
}


void			 GameEngine::IsFinish()
{
  std::list<Character*>::const_iterator	it(this->Players.begin());
  int					players = 0, ias = 0;

  while (it != this->Players.end())
    {
      if ((*it)->getID() == 1)
	++players;
      else if ((*it)->getID() == 3 || (*it)->getID() == 4)
	++ias;
      ++it;
    }
  if (this->_ia == 0)
    {
      if (this->_boss == false)
	{
	  FMOD_System_PlaySound(this->SoundSystem, FMOD_CHANNEL_FREE,
				this->SoundGame, 1, NULL);
	  FMOD_System_PlaySound(this->SoundSystem, FMOD_CHANNEL_FREE,
				this->SoundBoss, 0, NULL);
	  this->_time = 0;
	  this->Players.push_back(new Character(4, *this->map,
						this->rand, "iaboss",
						(this->_joueur + this->_ia + 1)));

	  Character* boss = this->GetPlayerByName("iaboss");
	  AObject *player = new Player(boss->getType(),4, _model);
	  if (player->initialize(boss->getX() ,
				 0.5,boss->getY() ) == false)
	    throw MyException("player");
	  _objects.push_back(player);

	  this->_boss = true;
	  this->_ia += 1;
	}
      else
	{
	  if (this->_joueur == 1 && players == 0)
	    this->LoseGame = true;
	  else if (this->_joueur > 1 && players == 1)
	    this->WinGame = true;
	}
    }
  else
    {
      if (players == 1 && ias == 0)
	{
	  if (this->_boss == false)
	    {
	      FMOD_System_PlaySound(this->SoundSystem, FMOD_CHANNEL_FREE,
				    this->SoundGame, 1, NULL);
	      FMOD_System_PlaySound(this->SoundSystem, FMOD_CHANNEL_FREE,
				    this->SoundBoss, 0, NULL);
	      this->_time = 0;
	      this->Players.push_back(new Character(4, *this->map,
						    this->rand, "iaboss",
						    (this->_joueur + this->_ia + 1)));
	      Character* boss = this->GetPlayerByName("iaboss");
	      AObject *player = new Player(boss->getType(),4, _model);
	      if (player->initialize(boss->getX() ,
				     0.5,boss->getY() ) == false)
		throw MyException("player");
	      _objects.push_back(player);

	      this->_boss = true;
	      this->_ia += 1;
	    }
	  else
	    this->WinGame = true;
	}
      else if (players == 0 || this->_joueur == 0)
	this->LoseGame = true;
    }
  if (this->WinGame || this->LoseGame)
    {
      FMOD_System_PlaySound(this->SoundSystem, FMOD_CHANNEL_FREE, this->SoundGame,
			    1, NULL);
      FMOD_System_PlaySound(this->SoundSystem, FMOD_CHANNEL_FREE, this->SoundBoss,
			    1, NULL);
      if (this->WinGame)
	FMOD_System_PlaySound(this->SoundSystem, FMOD_CHANNEL_FREE, this->SoundWin,
			      0, NULL);
      else
	FMOD_System_PlaySound(this->SoundSystem, FMOD_CHANNEL_FREE,
			      this->SoundLose, 0, NULL);
    }
}


void                    GameEngine::StopMusic() const
{
  FMOD_System_PlaySound(this->SoundSystem, FMOD_CHANNEL_FREE, this->SoundMenu,
                        1, NULL);
}
