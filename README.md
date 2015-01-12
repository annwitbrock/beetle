

## Beetle Game    

### - author Ann Witbrock 1995 (copyright)


   ```This game, which I first programmed in C in 1995 in order to learn "Windows" programming, is aimed at children who just want to see who wins. It is based on a popular chance game.```

Two players take turns to see what their dice roll is:


Play begins with attempting, in turn, to successfully roll a 6 to get a body. Next, a 1 gets a head.
Subsequently, any dice roll may get its corresponding remaining parts. 
Any turn continues until a dice roll cannot get a valid available part.


The first player lucky enough to get all the parts out of the box and onto the bug wins.


To play, you would just click on the beetle.exe icon.
You'd need to close and start again when the game is over, or let the loser see how long it "would have taken" to catch up (as live games often go!)

(The game ran on Windows 3.1 and 95 and NT and XP, but wasn't tested on Windows 98, 2000, 7 or 8). The original image assets have been lost.


### C Code notes:

This is very old code for me, but it shows many aspects of a small windows game. It won't be possible to compile it, as the resource files are long gone, but the main code is in `/C/beetle.c`
It was written in plain Windows 95 code, in C, without the luxury of a visual coding environment.
I learnt most of this from Charles Petzold's book on Programming Windows 95.
I apologise for not documenting how to compile it (with its assets). 

This might not have been the most recent version.
There are a few bugs, but I don't have the resource files to fix. 
i.e. 
1) The text in the boxes doesn't reposition properly on resize,
2) The legs dont get properly masked by the body,
3) The parts don't fit perfectly into place in the composite image (they are close).
The main reason I didn't fix the bugs at the time was that my monitor failed and I couldn't replace it.

Given reason to rewrite it, I would highlight the dice for the current player's turn, rather than relying on the beep for turn finish. I would make the game replayable.


### New Beetle for web (20 years later - 2015)

I decided to rewrite it for web. The new WIP version is in `/web/`
(also copyright Ann Witbrock 2015)

You are free to look at it but please do not pretend it is your work.
It uses twitter bootstrap (from getbootstrap.com) for styling.
I expect it to use JQuery too.






