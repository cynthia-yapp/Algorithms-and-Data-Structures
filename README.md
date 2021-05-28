a simple dictionary based on a linked list is created to store information from
the City of Melbourne Census of Land Use and Employment (CLUE). A user will be able to search this
dictionary to retrieve information about businesses in Melbourne using the business name (key).
the dictionary is implemented by reading census data from a file and inserting each
property record as a node in a linked list and also search for a key in the
list, outputting any records that match the key. (Note that keys are not guaranteed to be unique!)

The dataset used in this project is a subset of the Business establishment trading name and industry
classification 2018 dataset, accessed from:
https://data.melbourne.vic.gov.au/Business/Business-establishment-trading-name-and-industry-c/vesmc7r2

example of the code: 

In a Rush Espresso −− > Census year: 2018 || Block ID: 44 || Property ID: 105956 || Base property
ID: 105956 || CLUE small area: Melbourne (CBD) || Industry (ANZSIC4) code: 4511 || Industry (ANZSIC4)
description: Cafes and Restaurants || x coordinate: 144.96174 || y coordinate: -37.81561 || Location:
(-37.81560561, 144.9617411) ||
In a Rush Espresso −− > Census year: 2018 || Block ID: 1101 || Property ID: 108973 || Base
property ID: 108973 || CLUE small area: Docklands || Industry (ANZSIC4) code: 4511 || Industry (ANZSIC4)
description: Cafes and Restaurants || x coordinate: 144.95223 || y coordinate: -37.81761 || Location:
(-37.81761044, 144.9522269) ||
Tim Hortons −− > NOTFOUND



