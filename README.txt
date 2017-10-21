---------------- Tools -------------------------

+ Small Engine on SDL provided with the assigment. No need to re-invent the wheel.
+ Visual Studio Community 2017 Version 15.2 to develop and compile the game.

---------------- Instructions -------------------------
1 - 

bin/MiniMiner.exe
2 - 
3 - 

---------------- How to use the game ------------------

For now, just drag is support although more events can be easily incorporated. Unfortunately there is no visual feeback when selecting one of the cells. 


---------------- Architectural decisions --------------------

To facilitate testing and to decouple different resposanbilities between class in the system several design patterns has been applied. 

The game itself is built using classic MVC. In short, some event is created in the input handler this is passed to the controller that creates a list of commands that apply different algorithms to the model. 

Apart from this hen the view on every game loop iteration renders the model.

The controller logic is implemented using a set of commands that implement strategy pattern. composite pattern.

