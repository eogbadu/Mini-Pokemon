#include "PokemonList.h"

// Default constructor
PokemonList::PokemonList()
{
  m_head = nullptr;
  m_size = 0;
}

// Destructor
PokemonList::~PokemonList()
{
  Pokemon* current = m_head;

  // Iterate through the list to delete Pokemon
  while (current != nullptr)
  {
    m_head  = current;
    current = current->GetNext();
    delete m_head;
    m_size --;
  }
  
  // resets
  m_head = nullptr;
  m_size = 0;
}

// Inserts an already dynamically allocated Pokemon to end of linked list
void PokemonList::InsertEnd(Pokemon* end)
{

  // If the list is empty, add to the front
  if(m_head == nullptr)
  {
    m_head = end;
    m_size = 1;
  }
  // If not, iterate to the end of the list and add Pokemon before
  // the nullptr
  else
  {
    Pokemon *temp = m_head;
    while(temp->GetNext() != nullptr)
    {
      temp = temp->GetNext();
    }
    temp->SetNext(end);
    m_size++;
  }

}

// Iterates over PokemonList and displays each Pokemon formatted as in output
void PokemonList::Display()
{
  // Checks to see if the linked list is empty 
  if (m_size == 0)
  { 
    cout << "The linked list is empty" << endl; 
  }
  // If not empty, iterate through the list and print
  else
  {
    Pokemon *temp = m_head;
    for (int i = 0; i < m_size; i++)
    {
      cout << *temp;
      temp = temp->GetNext(); //Moves to next node  
    }
  }
}

// Searches for a Pokemon with a specific index. If found,             
// creates a new Pokemon and copies it into the PokemonList passed in
void PokemonList::Transfer(int index, PokemonList* dest)
{
  // Declare variables
  string name;
  int health;
  string strong;
  string type;
  int index2;

  // Create temporary Pokemon pointers
  Pokemon *current  = m_head;
  Pokemon *previous = m_head;

  // If the index is in the list
  if (Exist(index) == true)
  {
    // If the index is the first in the list, transfer it
    if (current->GetIndex() == index)
    {
      index2   = current->GetIndex();
      name     = current->GetName();
      health   = current->GetHealth();
      strong   = current->GetStrong();
      type     = current->GetType();
      m_head   = current->GetNext();
    }

    // If not the first in the list, locate it
    else
    {
      while (current->GetIndex() != index)
      {
        previous = current;
        current = current->GetNext();
      }

      // Once located, get its details
      previous->SetNext(current->GetNext());
      index2 = current->GetIndex();
      name   = current->GetName();
      health = current->GetHealth();
      strong = current->GetStrong();
      type   = current->GetType();
    }

    // Use details to create new pokemon
    Pokemon *d = new Pokemon(index2, name, type, strong);
    d->SetHealth(health);

    // Add created Pokemon to given list
    dest->InsertEnd(d);

    // Delete old pointer and reduce size of the list
    delete current;
    current = nullptr;
    m_size--;
  }
}


// Searches for a Pokemon with a specific index. If found,             
// removes it from the linked list
void PokemonList::Remove(int index)
{
  // Check that pokemon is in list
  if (Exist(index) == true)
  {
    Pokemon *temp  = m_head;

    // If pokemon is at start of the list remove it
    if (temp->GetIndex() == index)
    {
      m_head = temp->GetNext();
      delete temp;
      m_size--;
    }

    // If not, locate it and then remove it
    else
    {
      Pokemon *current  = m_head;
      Pokemon *previous = m_head;

      while (current->GetIndex() != index)
      {
	previous = current;
	current = current->GetNext();
      }
      previous->SetNext(current->GetNext());
      delete current;
      m_size--;
    }
  }
}

// Returns the size of the linked list
int PokemonList::GetSize()
{
  return m_size;
}

// Returns the Pokemon at the head of the linked list
Pokemon* PokemonList::GetHead()
{
  return m_head;
}

// Passes an enemy pocket to the user's pocket to attack 
int PokemonList::Attack(PokemonList* enemy)
{
  // Create constants
  const int WIN  = 2;
  const int LOSE = 1;
  // Create temporary pointers
  Pokemon *tempUser  = m_head;
  Pokemon *tempEnemy = enemy->GetHead();

  // Get damage for enemy pokemon
  if (tempUser->GetStrong() == tempEnemy->GetType())
  {
    cout << "CPU's pokemon took " << STRONG_DAMAGE << " damage" << endl;
    tempEnemy->SetHealth(tempEnemy->GetHealth() - STRONG_DAMAGE);
  }
  else if (tempUser->GetStrong() != tempEnemy->GetType())
  {
    cout << "CPU's pokemon took " << DAMAGE2ENEMY << " damage" << endl;
    tempEnemy->SetHealth(tempEnemy->GetHealth() - DAMAGE2ENEMY);
  }

  // Return 2 if enemy Pokemon has been defeated
  if (tempEnemy->GetHealth() <= 0)
  {
    return WIN;
  }
  else
  {
    // Get damage for user pokemon
    if (tempEnemy->GetStrong() == tempUser->GetType())
    {
      cout << "Your pokemon took " << STRONG_DAMAGE << " damage" << endl;
      tempUser->SetHealth(tempUser->GetHealth() - STRONG_DAMAGE);
    }
    else if (tempEnemy->GetStrong() != tempUser->GetType())
    {
      cout << "Your pokemon took " << DAMAGE2USER << " damage" << endl;
      tempUser->SetHealth(tempUser->GetHealth() - DAMAGE2USER);
    }
  }

  // Return 1 if user Pokemon has been defeated 
  if (tempUser->GetHealth() <= 0)
  {
    return LOSE;
  }
  // Return 0 if no Pokemon has been defeated 
  else
  {
    return 0;
  }
}

// Allows user to move a Pokemon from any position into the first position
void PokemonList::SwapPokemon()
{
  int index;

  // Check that size is greater than zero to continue
  if (GetSize() <= 0)
  {
    cout << "Nothing to see here!" << endl;
  }

  // Ask user for pokemon to swap
  else
  {
    cout << "Which Pokemon would you like to choose? (Enter the index#)"
	 << endl;
    Display();
      
    cin >> index;
    
    while (!Exist(index))
    {
      cout << "This is not a valid index, please try again." << endl;
      cin >> index;
    }

    // Create temporary Pokemon pointers
    Pokemon *current  = m_head;
    Pokemon *next     = m_head;
    Pokemon *previous = m_head;
    Pokemon *temp     = m_head;

    // Check if pokemon is the first in the list, then swap
    if (current->GetIndex() == index)
    {
      cout << "choice is head" << endl;
    }
    else
    {
      // Get Pokemon after the first Pokemon in the list
      next = next->GetNext();

      // Check if it is the second pokemon on the list, then swap
      if (next->GetIndex() == index)
      {
	temp->SetNext(next->GetNext());
	next->SetNext(temp);
	m_head = next;
      }
      // If not 1st or 2nd, locate it and swap
      else
      {

	// Find Pokemon you would like to swap 
	while (current->GetIndex() != index)
	{
	  previous = current;
	  current = current->GetNext();
	}
	
	// Make the swap
	temp->SetNext(current->GetNext());
	previous->SetNext(temp);
	current->SetNext(next);
	m_head = current;
      }
    }
    
  }  
}


// Iterates through linked list looking for a specific index of a Pokemon
bool PokemonList::Exist(int index)
{
  // Declare variables
  bool temp = false; // Set default to false
  Pokemon *tempPtr = m_head;

  // Iterate while not nullptr
  while (tempPtr != nullptr)
  {
    // If pokemon is found, change default temp value to true
    if (index == tempPtr->GetIndex())
    {
      temp = true;
    }
    tempPtr = tempPtr->GetNext(); // Go to next Pokemon in the list
  }
  return temp;
}
