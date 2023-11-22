# Casio-VideoPlayer-fx9860g
Compress Video files into a 128x64 black and white video format that can be played back on Casio calculators that support .g1w files 

To test this project connect your FX9860g series calculator to your computer and transfer Build.G1A to your calculator<br>
Then transfer the vid.cal file into your Main Files(Not the SD card)

To test this project download the FXVideoPlayer File and load the g1w file into the CASIO FX9860gII software development kit
Or Download the CalculatorBuild Folder and move all the files inside into the root of your calc

<img src="https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExOHN6enZtaGg5bHNoa254aGE3cm5vMjE1bHZrNDd4ZWlzc2J3dHF6aiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/e4bo0U05FkSUFnB02s/giphy.gif">

<b>IMPORTANT</b>
if you want to test this project on your calc you need to change the path at the top of FXVideoPlayer.h<br>
by default it looks for the vid.cal file in the SDCard Dir or in the SDCard of the calc<br>
If you uncomment the like it looks for the vid.cal file in the root of the calc which only works on calc builds

The SDK often says "build failed"
I suspect this is an issue with the project itself so please ignore an "build failed"s as it is lying
