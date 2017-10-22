----------------------------------------------------------- About the delivery ----------------------------------------------------------------------------------

1 - There is an executable for Windows32 in project/bin/MiniMiner.exe
2 - Source files (project/src) and project ready to be used with Visual Studio Community 2017
3 - Note that source code uses some C++17 features and hence a modern C++ compiler is required.

------------------------------------------------------------ About the game -------------------------------------------------------------------------------------

It's just a copy of Midas Miner without sound.

As specified:
+ Support drag and click events.
+ Swap and collapse gem animations
+ Last 60 seconds, 5 gem colors and score.

------------------------------------------------------ Architecture description ---------------------------------------------------------------------------------

To facilitate testing and to decouple different resposanbilities between classes in the system several design patterns has been applied. 

The overall game architecture uses classic MVC. Some event is created in the input handler module and then this is passed to the game controller that creates a 
list of commands that apply different algorithms to the model. At the same time the view on every game loop iteration renders the model. 

See Diagram below (Try to zoom out your editor in case it looked broken)

 +------------------------------------------------------------------------------+  The core controller logic is implemented using a set of commands that implement         
 |                                                                              |  **Strategy Pattern** to apply different algorithms on the model during runtime.         
 |        InputHandler                                                          |  For example, to apply the rules to break gems in RemoveCommand or to collapse           
 |             |                                             MiniMiner          |  gems once the ones below them are removed.                                              
 |             |                                                                |                                                                                          
 |             |                                                                |  **Composite Pattern** to create other commands from the basic ones. For                 
 |             |                                                                |  example SwapCommand (exchange two gems) is based on two MoveCommand (Move a gem to x,y).
 |             |Generates                                                       |                                                                                          
 |             |Events                           Model                          |  Advantages:                                                                             
 |             |                        +----------------------+                |  + Easy to unit test algorithms (commands) in controller by mocking some models.         
 |             |           Controller   | GameState            |                |  + Clear separation of responsabilities between the game logic and the rendering.        
 |     +-----------------+ updates the  | Board                |                |  + No complex logic in View and Model.                                                   
 |     | GameController  |    model     | Tile                 |                |                                                                                          
 |     | SwapCommand     |--------------| Score                |                |  Disadvantages and improvements:                                                                 
 |     | RemoveCommand   |              | Timer                |                |  + By trying to use STL in order to achieve more readability some "performance penalty"  
 |     | CollapseCommand |              +----------------------+                |    such as extra copies were introduced in the algorithms.                               
 |     | MoveCommand     |                        |                             |  + Lack of use of interfaces in some modules such as InputHandler.                       
 |     | ...             |                        |                             |  + Lack of unit/integration tests due to the nature of the task. This software is not    
 |     +-----------------+                        |                             |    expected to have a long lifetime.                                                     
 |          Controller                            |                             |                                                                                          
 |                                      +----------------------+   Renders the  |      +----------------------------------------+                                          
 |                                      |      GameView        |      model     |      |                                        |                                          
 |                                      |                      |----------------|------|            King SDL engine             |                                          
 |                                      +----------------------+                |      |                                        |                                          
 |                                               View                           |      |                                        |                                          
 |                                                                              |      +----------------------------------------+                                          
 |                                                                              |                                                                                          
 |                                                                              |                                                                                          
 +------------------------------------------------------------------------------+                                                                                                                                               

Main classes description
GameController: Executes sequencually every command in a list created by CommandFactory. This comand that depends on the kind of input event (ClickEvent, DragEvent, GameOverEvent...)

SwapCommand: Given two coordinates from an input event swaps two items on the board.

MoveCommand: Given the coordinates from an input event and an item, moves the item to.