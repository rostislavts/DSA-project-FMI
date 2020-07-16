# DSA-project
This is a DSA project for FMI, Sofia University, Sofia.
It uses [SFML](https://www.sfml-dev.org/) for visualization.

## Tom and Jerry

We all know that funny animation and how creative both of them are.
Now Tom has a drone and wants to make messes with it.

### Commands that the drone can execute
* **N** - Fly North
* **S** - Fly South
* **E** - Fly East
* **W** - Fly West
* **P** - Paint the current position

### Restrictions
* There are furniture in the room and the drone can't fly over them.
* The drone has very small battery, so it must not repeat its movements.

### Tom wants your help
He can give you a text file with all of the needed information.

#### File structure

* Row #1: **M** **N**
  * Size of the room
  * **M** - width
  * **N** - height

* Row #2: **X** **Y**
  * Jerry's position
  
* Row #3: **X** **Y**
  * Tom's position
 
* Row #4: **K** **L**
  * **K** - Number of furniture in the room
  * **L** - Number of the positions that the drone can paint.
  
* The next **K** rows describe the furniture
  * Row #1: **X** **Y**
    * Position of the north-west corner
  * The next rows describe the shape
    * '1' means there is a furniture on that point
    * ' ' means there is no funrniture on that point
    * Example: 
      ```
      111111
      ␣␣␣11
      ```
   * The description of each furniture ends with '==='
   
* The next **L** rows give us the positions that the drone can paint over them.

***Sample input file:***
```
4 4
0 2
3 0
2 1
2 1
11
 1
===
1 3
1
===
1 1
```

#### Tom wants to know the answers of the following questions:
  * What's the length of the shortest path to Jerry?
  * What are all the shortest paths from me to Jerry?
  * How many paint I can use on each path?
  * How many turns are on each path?
  * What are the commands that I must give to the drone?
  
#### Tom wants you to give him a tree of commands for the shortest paths
  * Tom will choose a leaf number. You program must have functions that give information about:
    * The needed commands
    * Length of the path
    * Number of the paints
    * Number of the turns

#### More functionality
  * Tom wants to know what is the max possible number of paints.
  Help him to program the drone that it paints max positions, but with min turns.
  * If Tom has another drone, help him to program both drones that they finish at Jerry's position at the same time with max paints.
  
#### Bonus
  * Implement an animated visualization
