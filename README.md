# Casio-VideoPlayer-fx9860g
Compress Video files into a 128x64 black and white video format that can be played back on Casio calculators that support .g1w files 

To test this project connect your FX9860g series calculator to your computer and transfer Build.G1A to your calculator<br>
Then transfer the vid.cal file into your Main Files(Not the SD card)

<br>To test this project download the FXVideoPlayer File and load the g1w file into the CASIO FX9860gII software development kit

<br>Or Download the CalculatorBuild Folder and move all the files inside into the root of your calc


<b>IMPORTANT<b>
if you want to test this project on your calc you need to change the path at the top of FXVideoPlayer.h
by default it looks for the vid.cal file in the SDCard Dir or in the SDCard of the calc
If you uncomment the like it looks for the vid.cal file in the root of the calc which only works on calc builds
