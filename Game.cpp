#include "Game.h"

// Default constructor
Game::Game(string fileName)
{
  m_filename = fileName;
  m_list = new PokemonList();
  m_userPocket = new PokemonList();
  m_enemyPocket = new PokemonList();
}

// Game Destructor
Game::~Game()
{
  delete m_userPocket;
  delete m_enemyPocket;
  delete m_list;
}

// Opens file and reads in each Pokemon. Each Pokemon dynamically allocated 
// and put into m_list 
void Game::LoadFile()
{
  // Declare variables used in LoadFile
  int index;
  string name;
  string type;
  string strong;
  ifstream inStream;

  // Open file to read
  inStream.open(m_filename);
  if(inStream.fail())
  {
    cout << "File failed to load.\n";
  }
  else
  {
     while (inStream >> index)
     {
       // Use getline delimited by a comma ','
       inStream.ignore(256, ',');
       getline(inStream, name, ',');
       getline(inStream, type, ',');
       getline(inStream, strong);
       
       // Create new pokemon with information collected above
       Pokemon *temp = new Pokemon(index, name, type, strong);

       // Insert pokemon into m_list
       m_list->InsertEnd(temp);
     }
  }
  // Close file
  inStream.close();
}

// Allows user to choose team and populates m_userPocket
void Game::ChooseTeam()
{
  // Declare variables
  int count = NUM_TEAM;
  int index;

  // While 5 pokemon have not been selected for the team
  while (count > 0)
  {
    cout << "Pick a Pokemon by entering the index (" << count
	 << " left):" << endl;
    cin >> index;

    // Check if the index entered is available in m_list
    while (!m_list->Exist(index))
    {
      cout << "Please enter a valid index" << endl;
      cin >> index;
    }

    // Transfer Pokemon to m_userPocket
    m_list->Transfer(index, m_userPocket);
    count--;
    
    // Print list of pokemon user can choose from 
    if (count > 0)
    { 
      cout << "Here is a list of Pokemon you can choose from:" << endl;
      cout << "----------------------------------------------" << endl << endl;
      m_list->Display();
      cout << "----------------------------------------------" << endl << endl;
    }    
  }

}

// Displays menu and returns choice
int Game::Menu()
{
  // Declare variables
  int choice;

  // Declare constants
  const int MIN = 1;
  const int MAX = 3;

  // Print out menu
  cout << "----------------------------------------------" << endl;
  cout << "Menu:"      << endl;
  cout << "1. Attack"  << endl;
  cout << "2. Swap"    << endl;
  cout << "3. Forfeit" << endl;
  cout << "----------------------------------------------" << endl;
  // Get input from user and validate
  cin >> choice;
  while ((choice < MIN) || (choice > MAX))
  {
    cout << "Please enter a valid choice: ";
    cin >> choice;
  }
  
  return choice;
}

// Manages the battle between m_userPocket and m_enemyPocket.          
// Displays both the m_userPocket and m_enemyPocket                           
// For each round, makes sure each team has Pokemon.
// Makes Pokemon in head fight. 
// Indicates if the round yields user win, enemy win, and if a
// Pokemon was switched. Fights continue until there are no remaining
// Pokemon in one of the lists 
int Game::Battle()
{
  // Declare variables
  int menuResult;
  int attackResult;
  int battleResult;
  int roundCount = 1;

  // Declare Constants
  const int WIN  = 1;
  const int LOSE = 2;
  
  // Print player Pokemon
  cout << "----------------------------------------------" << endl;
  cout << "Print player pocket" << endl;
  m_userPocket->Display();

  // Print CPU Pokemon
  cout << "----------------------------------------------" << endl;
  cout << "Print cpu pocket" << endl;
  m_enemyPocket->Display();

  while ((m_userPocket->GetSize() > 0) && (m_enemyPocket->GetSize() > 0))
  {
    // Print round details
    cout << "----------------------------------------------" << endl;
    cout << "Round " << roundCount << ":" << endl;

    // CPU Pokemon and stats
    Pokemon *enemy = m_enemyPocket->GetHead();
    cout << "CPU's Pokemon: " << enemy->GetName() << " ("
	 << enemy->GetType()  << ":" << enemy->GetHealth()
	 << " health)" << endl;

    // User Pokemon and stats
    Pokemon *user = m_userPocket->GetHead();
    cout << "Your Pokemon: " << user->GetName() << " ("
         << user->GetType()  << ":" << user->GetHealth()
         << " health)" << endl;

    // Print out the menu and get choice
    menuResult = Menu();

    // Perform choice selected by user
    switch (menuResult)
    {
    case 1:
      attackResult = m_userPocket->Attack(m_enemyPocket);
      break;
    case 2:
      m_userPocket->SwapPokemon();
      break;
    case 3:
      cout << "\nCPU won!!!" << endl;
      exit(0);
      break;
    default:
      exit(1);
    }

    // Update round number
    roundCount++;
    
    // Use attack result to update Pokemon/Pokemon health
    // If your pokemon is defeated, remove it from user pocket 
    if (attackResult == 1)
    {
      cout << "Your pokemon has been defeated" << endl << endl;
      m_userPocket->Remove(user->GetIndex());

      // If there is still a pokemon after loss, swap your pokemon
      if (m_userPocket->GetSize() > 0)
      {
	// Print out last Pokemon message
	if (m_userPocket->GetSize() == 1)
	{
          cout << "THIS IS YOUR LAST POKEMON!!!" << endl;
        }
	else
	{
	  // Perform swap
	  m_userPocket->SwapPokemon();
	  user = m_userPocket->GetHead();
	  cout << "You changed your Pokemon to: " << user->GetName() << " ("
	       << user->GetType()  << ":" << user->GetHealth()
	       << " health)" << endl << endl;
	}
      }
      // If no more pokemon, return your loss 
      else
      {
	battleResult = LOSE;
      }
    }
    // If the CPU pokemon is defeated, remove it from enemy pocket
    else if (attackResult == 2)
    {
      cout << "CPU's pokemon has been defeated" << endl << endl;
      m_enemyPocket->Remove(enemy->GetIndex());

      // If enemy still has pokemon, print out new pokemon
      // at m_head to the screen
      if (m_enemyPocket->GetSize() > 0)
      {
	enemy = m_enemyPocket->GetHead();
	cout << "CPU changed its pokemon to: " << enemy->GetName() << " ("
	     << enemy->GetType()  << ":" << enemy->GetHealth()
	     << " health)" << endl << endl;
      }
      // If CPU has no more pokemon, you win
      else
      {
	battleResult = WIN;
      }
    }
  }

  return battleResult;
}

// Loads input file, allows user to choose their team, randomly populates the 
// m_enemyPocket with remaining Pokemon and returns the result of the battle
int Game::Start()
{
  // Declare variables
  int randomIndex;
  int count;
  int enemyCount = 0;
  int battleResult;

  // Initialize m_enemyPocket
  //  m_enemyPocket = new PokemonList();
  
  // Load the file into m_list
  LoadFile();
  count = m_list->GetSize();
  // Print list of pokemon user can choose from
  cout << "Here is a list of Pokemon you can choose from:" << endl;
  cout << "----------------------------------------------" << endl << endl;
  m_list->Display();
  cout << "----------------------------------------------" << endl << endl;

  // Request team selection from user
  ChooseTeam();

  // Randomly populate m_enemyPocket with Pokemon
  // remaining in m_list
  randomIndex = (rand() % count + 1 - 0) + 0;
  while (enemyCount < NUM_TEAM)
  {
    if (m_list->Exist(randomIndex))
    {
      m_list->Transfer(randomIndex, m_enemyPocket);
      enemyCount++;
      randomIndex = (rand() % count + 1 - 0) + 0;
    }
    else
    {
      randomIndex = (rand() % count + 1 - 0) + 0;
    }
  }
  // Get the result of the battle
  battleResult = Battle();
  return battleResult;
}
