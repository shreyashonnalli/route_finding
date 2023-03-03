//
//  interface.h
//  Route Finding
//
//  Created by Shreyas Honnalli on 04/03/2021.
//

#ifndef interface_h
#define interface_h
#include <stdio.h>
#include <stdlib.h>

//messages which are displayed in user interface
#define MenuMessage "Welcome to the route finding program, enter 1 to display all nodes, enter 2 to find the distance between two nodes, enter 3 to display the map and enter 4 to exit\n"
#define InvalidMenuMessage "Invalid choice entered, please enter 1, 2, 3 or 4\n"
#define ShortestDistanceMessage "We recommend looking at the list of nodes and the map before this\n"
#define ShortestDistanceStartMessage "Enter the source node ID of your joruney: "
#define ShortestDistanceDestinationMessage "Enter the destination node ID of your journey: "
#define InvalidNodeMessage "No such Node found\n"

//runs user interface
void RunInterface(void);

#endif /* interface_h */
