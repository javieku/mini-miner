----------------------------------------------------------- About the delivery ----------------------------------------------------------------------------------

1 - There is an executable ready to be used for Windows 32 bits in project/bin/MiniMiner.exe
2 - Source files (project/src) and a project ready to be compiled with Visual Studio Community 2017

Note that source code uses some C++17 features and hence a modern C++ compiler is required.

------------------------------------------------------------ About the game -------------------------------------------------------------------------------------

It's a copy of Midas Miner without sounds.

+ Support drag and click events.
+ Swap and collapse tile animations.
+ Last 60 seconds, 5 gem colors and score.
+ Some extra game over action was implemented as a side task.

------------------------------------------------------ Architecture description ---------------------------------------------------------------------------------

To facilitate testing and to decouple different responsibilities between classes in the system several design patterns have been applied. 

The overall game architecture uses classic MVC. Some event is created in the input handler module and then this is passed to the game controller that creates a 
list of commands to apply different algorithms to the model. At the same time the view on every game loop iteration renders the model. 

See Diagram below (Try to zoom out your editor in case it looked broken)
                                                                                                         
 +------------------------------------------------------------------------------+  The core controller logic is implemented using a set of commands that implement         
 |                                                                              |  **Strategy Pattern** to apply different algorithms on the model during runtime.         
 |        InputHandler                                                          |  For example, to apply the rules to remove tiles in RemoveCommand or to collapse         
 |             |                                             MiniMiner          |  the tiles in a column once the ones below them are removed.                             
 |             |                                                                |                                                                                          
 |             |                                                                |  **Composite Pattern** to create other commands from the basic ones. For                 
 |             |                                                                |  example SwapCommand (exchange two gems) is based on two MoveCommand (Move a gem to x,y).
 |             |Generates                                                       |                                                                                          
 |             |Events                           Model                          |  Highlights:                                                                             
 |             |                        +----------------------+                |  + Easy to unit test algorithms in controller by mocking different GameStates.           
 |             |           Controller   | GameState            |                |  + Clear separation of responsabilities between the game logic and the rendering.        
 |     +-----------------+ updates the  | Board                |                |  + No complex logic in the View and Model.                                                   
 |     | GameController  |    model     | Tile                 |                |  + Usage of several stl algorithm such as std::stable_partition and std::adjacent_first  
 |     | SwapCommand     |--------------| Score                |                |    to implement the game logic.                                                          
 |     | RemoveCommand   |              | Timer                |                |                                                                                          
 |     | CollapseCommand |              +----------------------+                |  Disadvantages/Mistakes:                                                                 
 |     | MoveCommand     |                        |                             |  + By trying to use STL in order to achieve more readability some "performance penalty"  
 |     | ...             |                        |                             |    such as extra copies were introduced in the algorithms (See RemoveCommand).           
 |     +-----------------+                        |                             |  + Lack of interfaces in some modules such as InputHandler.                              
 |          Controller                            |                             |  + Lack of unit/integration tests due to the nature of the task. This program is not    
 |                                                |                             |    expected to have a long lifetime.                                                     
 |                                                |                             |  + Use Observer pattern in inputHandler to notify events.                                
 |                                                |                Renders the  |  + Some game logic could have been part of the engine.                                   
 |                                       +----------------------+     model     |      +----------------------------------------+                                          
 |                                       |     GameView         |               |      |                                        |                                          
 |                                       |                      ----------------|------|             King SDL engine            |                                          
 |                                       +----------------------+               |      |                                        |                                          
 |                                               View                           |      |                                        |                                          
 +------------------------------------------------------------------------------+      +----------------------------------------+              

Note the game has just one "state" i.e. it is just the gameplay itself. There is no introduction screen, menus or game over. This could have been implemented by extending
the GameController logic with a FSM (Finite state machine) using **state pattern**. The state would be changed based on the events generated by the input. The current GameController
implementation could have been moved to a "GameplayState" class.

The view also would have been extended with several "Views" to render these new states. 
                                                                                                                                                                                                                                            
------------------------------------------------------ Main classes description ---------------------------------------------------------------------------

>>>>>> Controller classes <<<<<<

- GameController: Executes sequentially a list of commands created by CommandFactory. This command list depends on how the event(ClickEvent, DragEvent,
 * GameOverEvent...) is expected to interact with the model.

- RemoveCommand: Marks as broken three or more consecutive tiles with the same color. It is implemented using a generalization of std::adjacent_first.

- CreateAndMoveCommandCommand: Given a board where some tiles has been already removed, it collapses the tiles above the ones removed and create new ones. It uses std::stable_partition
  to perform the collapse operation.

- SwapCommand: Given two coordinates from an input event swaps two items on the board.

- MoveCommand: Given the coordinates from an input event and a tile, it moves the tile coordinates and updates the board to the given position.

- CollapseCommand: Combines RemoveCommand and CreateAndMoveCommandCommand to implement the logic of creating and removing tiles after an user action that collapsed some of the tiles in the board.

>>>>>> View classes <<<<<<

- GameView: Renders every component in the model with almost zero logic.  

>>>>>> Model classes <<<<<<

- GameModel: A set of model/structs that contains data to be changed by the different commands. 

------------------------------------------------------ Final note ---------------------------------------------------------------------------

For more information, please check documentation in header files, the source code or feel free to send an email to fcojavierob@gmail.com