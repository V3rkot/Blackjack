#include <iostream>
#include <array>
#include <ctime>
#include <cstdlib>

enum PlayingCardSuit
{
    Hearts,
    Tiles,
    Clovers,
    Pikes,
    Suits_Number
};

enum PlayingCardRanks
{
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eigth,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    Ranks_Number
};

struct PlayingCard
{
    PlayingCardSuit suit;
    PlayingCardRanks rank;
};

void printCard(const PlayingCard& card)
{
    switch (card.rank)
    {
    case Ace:       std::cout << "A"; break;
    case Two:       
    case Three:     
    case Four:      
    case Five:      
    case Six:       
    case Seven:    
    case Eigth:     
    case Nine:      std::cout << static_cast<int>(card.rank); break;
    case Ten:       std::cout << "T"; break;
    case Jack:      std::cout << "J"; break;
    case Queen:     std::cout << "Q"; break;
    case King:      std::cout << "K"; break;
    }

    switch (card.suit)
    {
    case Hearts:    std::cout << "H"; break;
    case Tiles:     std::cout << "T"; break;
    case Clovers:   std::cout << "C"; break;
    case Pikes:     std::cout << "P"; break;
    }
}

void printDeck(const std::array<PlayingCard, 52> &deck)
{
    for (const auto& card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }

    std::cout << '\n';
}

void swapCard(PlayingCard& a, PlayingCard& b)
{
    PlayingCard temp = a;
    a = b;
    b = temp;
}

void createDeck(std::array<PlayingCard, 52>& deck)
{
    int card{ 0 };
    for (int suit = 0; suit < Suits_Number; suit++)
    {
        for (int rank = 0; rank < Ranks_Number; rank++)
        {
            deck[card].suit = static_cast<PlayingCardSuit>(suit);
            deck[card].rank = static_cast<PlayingCardRanks>(rank);
            card++;
        }
    }
}


int getRandomNuber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck(std::array<PlayingCard, 52>& deck)
{
    for (PlayingCard &card:deck)
    {
        int swapIndex = getRandomNuber(0,deck.size()-1);
        swapCard(card, deck.at(swapIndex));
    }
}

int getCardValue(const PlayingCard& card)
{
    switch (static_cast<int>(card.rank))
    {
    case Ace:       return 11; break;
    case Two:
    case Three:
    case Four:
    case Five:
    case Six:
    case Seven:
    case Eigth:
    case Nine:      
    case Ten:       return static_cast<int>(card.rank); break;
    case Jack:      
    case Queen:    
    case King:      return 10; break;
    default: break;
    }
    return 0;
}

char getPlayerChoice()
{
    std::cout << "(h) to hit, or (s) to stand: ";
    char choice;
    do {
        std::cin >> choice;
    } while (choice != 'h' && choice != 's');
    return choice;
}

bool playBlackjack(std::array<PlayingCard, 52>& deck)
{
    const PlayingCard* cardPtr = &deck[0];
    int playerScore{ 0 };
    int dealerScore{ 0 };

    dealerScore += getCardValue(*cardPtr++);
    playerScore += getCardValue(*cardPtr++);

    while (1)
    {
        std::cout << "You have: " << playerScore << std::endl;
        if (playerScore > 21)
            return false;
        char choice = getPlayerChoice();
        if (choice == 's')
            break;
        playerScore += getCardValue(*cardPtr++);
    }

    while (dealerScore < 17)
    {
        dealerScore += getCardValue(*cardPtr++);
        std::cout << "The dealer now has: " << dealerScore << std::endl;
    }

    if (dealerScore > 21)
        return true;
    return(playerScore > dealerScore);
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    std::array<PlayingCard, 52> Deck;
    createDeck(Deck);
    shuffleDeck(Deck);

    if (playBlackjack(Deck))
        std::cout << "You WIN!" << std::endl;
    else
        std::cout << "You LOSE!" << std::endl;
   
    system("pause");
    return 0;
}