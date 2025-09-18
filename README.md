# random noise generation
a simple C prject to generate basic noise

## plans and features

 - [x] fix the giant empty space when not many islands spawn
 - [ ] fix colors to make it look better and more like islands
 - [ ] change the way its formed or at least make it so that the islands arent just circles, more like bean shapes

## example output

grey scale noise\
![(image) example of what the code looks like](/previews/noiseMap.png)

color map for terrain with beaches\
![(image) example of what the code looks like](/previews/NoiseMapColorSwapped.png)

height map noise with sandy cliffs\
![(image) example of what the code looks like](/previews/noiseMapWithColor4.png)

both noise and terrain gif\
![(image) example of what the code looks like](/previews/noise.gif)

## installation and guide
`git clone https://github.com/skyels1/noiseGenerator.git`\
`cd noiseGenerator`

to run use `gcc src/main.c -o noiseGen -lrt`

on windows `gcc src/main.c -o noiseGen.exe`

then `./noiseGen`

to save an image change the name before running again