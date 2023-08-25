# truthimiser

A typo maker!         

## • How to run

### Run on Linux (and hopefully with the same file and method, on MacOS)

```./truthimiser_linux.out```          
Or build your own with `gcc` from source.

### Run on Windows
Start it from from the icon.    
Alternatively, start it via cmd/powershell by     
```.\truthimiser_win.exe```     
Or build your own with `gcc` and `mingw` from source.

## • How to use

Whichever method you used, you'll be presented with the program's textual interface. Simply input a line of the text you want truthimised, or provide the text as standard input:          
- **Linux:** ```./truthimiser_linux.out "hello yes this is the input text"```     
- **Windows:** ```.\truthimiser_win.exe "yes hello this is standard input"```

Multiline standard input is not currently supported. Input `!license` or `!source` to view the license or the link to this repo, in-program.

The program will spit out a (hopefully) typo'd version of the input sentence - but could also randomly not make a typo at all.

## • How it works

Truthimiser works by going through the input text character by character, and at a random chance, randomly selecting a neighbour of the character's key on a keyboard - using a dictionary of keys, where nearly each key used for typing on a US layout keyboard has a list of its neighbours, that you can hit by misrake, I mean mistake ;)

## • Why "truthimiser"?

It's a subtle nod to someone who inspired me to make this.
