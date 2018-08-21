#ShortSolver is a poker analyzing software for a new poker game called 
Six-Plus Hold'em aka Short-Deck Hold'em

#unlike normal Texas Hold'em, we get rid of all the 2-5 from a deck, make a deck 36 cards instead of 52.

In this project,we use C++ as backend application and Java-script for front-end web-app.

Design:

Hand class to contain all the information for a poker hand


Unprocessed cards vector means a vector of card indices from 0-35
0-8 clubs,9-17 diamonds,18-26 hearts,27-35 spades.
For each suit, we have 0-8 to index all the cards from 6-A.

Processed cards vector is a vector of integers contain 9 elements to correspond to 6-A.
And we use last 4 bits of integer to represent each suit of card.
For example, if processed_cards[0] has bit 2 set(starts from 0), then we have 6 of hearts in 
the current hand.

For string representation of each card, we use the below mapping
card abbreviation
6-6
7-7
8-8
9-9
Ten-T
Jack-J
Queen-Q
King-K
Ace-A

We also use lower case letter to represent suits.
clubs-c
diamonds-d
hearts-h
spades-s

For example, Js is Jack of spades, Th is ten of hearts.



