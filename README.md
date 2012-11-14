# Accelerometer Light Show

This arduino sketch is designed to allow the user to control a BlinkM device set to address 9 with an accelerometer HOW FUN!

This does things in what would appear as a backwards way... it will send the accelerometer data via serial, and listens for light change events via serial... thus decoupling how the accelerometer controls the lights.  This is a prototype for a larger installation being developed at CCRMA.

The code relies on a library of BlinkM Functions 2007-8, Tod E. Kurt, ThingM
<br>[*Find More information at the ThingM website*](http://thingm.com/)
