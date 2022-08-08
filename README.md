# README

Given a memory card image (the raw data of a memory card), recover.c scans it for deleted .jpg images and restores each of them to their own accessible JPG file.

JPGs are written in blocks of 512 bytes and their first four bytes always contain a trackable pattern. When recover.c finds this signature it copies blocks of image data into a new JPG file that is created in the same directory. It continues reading data until it finds the signature again at which point it closes the first file and begins writing the next recovered photo into the next JPG file. This continues until there are no more blocks of data to read on the card.

**NOTE:** recover.c assumes that all deleted JPGs are stored back-to-back on the memory card.

recover.c takes one argument: the memory card image in .raw format. If more or less arguments are given the module throws and error and exits. If there is no data on the card image, then recover.c throws an error and exits.

#### EXAMPLE INPUT

./recover.c card.raw

#### EXAMPLE OUTPUT

000.jpg  
001.jpg  
002.jpg  
...

**NOTE:** All images located in the same directory as recover.c
