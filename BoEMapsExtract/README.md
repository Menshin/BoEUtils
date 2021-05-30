# *Blades of Exile* scenario maps extraction tool

SDL-backend commandline tool that extracts maps from *.exs* Blades of Exile scenarios and dumps them in a BMP or PNG format.

## Features
* Compiles and runs on Win32 or Linux (should work on post-Intel Mac, but hasn't been tested)
* Extracts scenario towns or outdoors (separate chunks or in a (large) merged file)
* Can choose between using Windows (bright) or Mac (darker) as base graphics
* Handles loading and using a scenario custom graphic file (provided it follows BoE naming convention) in BMP or PNG format
* Handles both little-endian (Intel/Win) or big-endian (Motorola 68000/Mac) scenario format

## Usage

`BoEMapsExtract -a|o|t|d|b|m filename.exs`

#### Mandatory argument
One of :
* `a` : extract `a`ll (superseeds -o and -t)
* `o` : extract `o`utdoors only
* `t` : extract `t`owns only

#### Options
* `d` : use Mac (`d`arker) graphics
* `b` : use `B`MP output format instead of PNG
* `m` : `m`erge all outdoors in a single map

## Gallery
<details>
  <summary>Win32/Linux usage</summary>
  
![win_mac_usage](https://user-images.githubusercontent.com/7117411/120117623-5de90080-c18e-11eb-9ca7-1e3925c63fcc.png)
</details>

<details>
  <summary>Fort Talrus, Valley of the Dying Things (Win base graphics, downscale 50%)</summary>
  
![VALLEYDY_town0](https://user-images.githubusercontent.com/7117411/120117658-88d35480-c18e-11eb-8b6f-536a5879923c.png)
</details>
<details>
  <summary>Northeastern Vale, Valley of the Dying Things (Mac base graphics, downscale 50%)</summary>
  
![valleydy_outdoors(2x0)](https://user-images.githubusercontent.com/7117411/120117663-8cff7200-c18e-11eb-8aa8-12f53f5419c4.png)
</details>

<details>
   <summary>Valley of the Dying Things, merged outdoors map (Win base graphics, downscale 25%)</summary>
  
![VALLEYDY_outdoors(merged)](https://user-images.githubusercontent.com/7117411/120117665-8e309f00-c18e-11eb-8e93-4df6790f8eaa.png)
</details>

## Dependencies 
* SDL2 : https://www.libsdl.org/
* SDL2_image : https://www.libsdl.org/projects/SDL_image/

## To build
* *Win32* : compiles out-of-the-box in a Visual Studio project (configured to link against SDL2 and SDL2image)
* *Linux* : provided `makefile` (`make && make install`, output the binary and ressources in `~/BoEMapsExtract`)
