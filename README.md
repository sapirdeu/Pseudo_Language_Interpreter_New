# Pseudo_Language_Interpreter_New

FlightGear Simulator visualize a real plane with it's system, controlled by a multi-threaded code that represents both the server and the client, that send data to the simulator and receive data from it.  

This is the first milestone, which focuses on building an interpreter for a new programming language- our input is a txt file written in a new programming language, for example fly.txt in the appendix.  
The interpreter will go over the lines in the txt file, those are written in a new programming language, and will interpret them (lexer, parser and execute), similar to the JVM process.  
Each command belongs to it's own class, where it has to implement the "execute" method of the "Command.h" interface, in order to activate the command.  

For example, the line "var a = (1 + b) * 2" will be interpreted to "DefineVarCommand", and it's "execute" implementation is to create this variable, calculating the assignment on the right side of the operator ‘=’ (*Further explanation in the next paragraph), then save the value in a VarType object, which will be inserted to a symbol table with map structure. Later on we can get the value of variable ‘a’ from the map using only O(1) time.  

There is also the "AllExpressions.cpp" file that contains the “Interpreter” class, which takes a mathematical expression with variables and values, assigns the values to the variables, then calculates the expression (after converting the it to postfix form) recursively using the Shunting Yard algorithm. All types of expressions (unary and binary) inherit from “Expression.h” interface.  

## Interpreting and executing the commands that are given in a txt file:
- Firstly, we need to lexer each line in the file to tokens- split each line in the code into a vector of strings, and then we add it to a vector of vectors of strings, where each vector represents a line in the txt file.  
- Secondly, we need to parse each vector to its suitable command, so for example when we see in the txt file “Print(“hi”)” we create a new object called “PrintCommand” and then we activate the command by calling it’s execute method. The parser will repeat it for each vector and execute the suitable command.  
- In addition, the project communicates with the FlightGear simulator both as a client (sending data to the FlightGear) and as a server (receiving data from the FlightGear).  
  - The server and the client run parallely on different threads, which means our project supports multi-threading.
  - The client and server communicate with the FlightGear simulator with sockets using TCP protocol.  
  - In order to connect as a server we create an OpenServerCommand object which receives port number, and in order to connect as a client we create a ConnectCommand object which receives ip and port number (Those are created by the parser as explained above).  
- After the connection as a server and as a client is set, the plane in the simulator warms it’s engine and takes off.  

## Installation:
in order to install the FlightGear simulator type the following commands in the terminal on your computer:  
```
sudo apt-get update
sudo apt-get install flightgear
```

## Excecuting the program:
you should put the “generic_small.xml” in the same folder of where the simulator was installed using the command:  
`sudo cp src_path simulator_path`  
you should put the txt file, for example fly.txt in the same folder with the project files, now we are ready to compile and run the program using the commands:
```
g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
./a.out fly.txt
```

## Appendix:
fly.txt example: 

openDataServer(5400)  
connectControlClient("127.0.0.1",5402)  
var warp -> sim("/sim/time/warp")  
var magnetos -> sim("/controls/switches/magnetos")  
var throttle -> sim("/controls/engines/current-engine/throttle")  
var mixture -> sim("/controls/engines/current-engine/mixture")  
var masterbat -> sim("/controls/switches/master-bat")  
var masterlat -> sim("/controls/switches/master-alt")  
var masteravionics -> sim("/controls/switches/master-avionics")  
var brakeparking -> sim("/sim/model/c172p/brake-parking")  
var primer -> sim("/controls/engines/engine/primer")  
var starter -> sim("/controls/switches/starter")  
var autostart -> sim("/engines/active-engine/auto-start")  
var breaks -> sim("/controls/flight/speedbrake")  
var heading <- sim("/instrumentation/heading-indicator/offset-deg")  
var airspeed <- sim("/instrumentation/airspeed-indicator/indicated-speed-kt")  
var roll <- sim("/instrumentation/attitude-indicator/indicated-roll-deg")  
var pitch <- sim("/instrumentation/attitude-indicator/internal-pitch-deg")  
var rudder -> sim("/controls/flight/rudder")  
var aileron -> sim("/controls/flight/aileron")  
var elevator -> sim("/controls/flight/elevator")  
var alt <- sim("/instrumentation/altimeter/indicated-altitude-ft")  
var rpm <- sim("/engines/engine/rpm")  
Print("waiting 2 minutes for gui")  
Sleep(120000)  
Print("let's start")  
warp = 32000  
Sleep(1000)  
magnetos = 3  
throttle = 0.2  
mixture = 0.949  
masterbat = 1  
masterlat = 1  
masteravionics = 1  
brakeparking = 0  
primer = 3  
starter = 1  
autostart = 1  
Print("engine is warming...")  
Print(rpm)  
while rpm <= 750 {  
&nbsp;&nbsp;&nbsp;&nbsp;   Print(rpm)  
}  
Sleep(5000)  
Print("let's fly")  
var h0 = heading  
breaks = 0  
throttle = 1  
while alt < 1000 {  
&nbsp;&nbsp;&nbsp;&nbsp;   rudder = (h0 - heading)/80  
&nbsp;&nbsp;&nbsp;&nbsp;   aileron = -roll / 70  
&nbsp;&nbsp;&nbsp;&nbsp;   elevator = pitch / 50  
&nbsp;&nbsp;&nbsp;&nbsp;   Sleep(250)  
}  
Print("done")  
