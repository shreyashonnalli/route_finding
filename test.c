
#include "unity.h"
#include "logic.h"

//if node ID of the return is same as the int that was inputted, then there is a node with that ID
//if node ID of return is 0 then there is no node in system with that ID
void test_SearchNode() {
    LoadFile();
    int ID1 = -8847,ID2 = -1,ID3 = 247293216;//Testing a known valid ID and an ID not in system
    struct node node1 = SearchNode(ID1);
    struct node node2 = SearchNode(ID2);
    struct node node3 = SearchNode(ID3);
    TEST_ASSERT_EQUAL_INT(ID1,node1.ID);//ID is in system
    TEST_ASSERT_EQUAL_INT(0, node2.ID);//ID is not in system
    TEST_ASSERT_EQUAL_INT(ID3,node3.ID);//ID is in system
}

//valid line returns 0 indicating success of storage
//invalid line returns 1 indicating cannot store this line in system
void test_StoreData(){
  char buffer1[300] = "<link id=-2143392681 node=247293216 node=-2382 way=-7634 length=4.403466 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>\n";//valid link input
  char buffer2[300] = "<node id=247293173 lat=53.804359 lon=-1.551583 /node>\n";//valid node input
  char buffer3[300] = "<way id=232352761 node=-1888556204 node=-1888556131 /way>\n";//invalid line of buffer
  char buffer4[300] = "<geom id=-7564 node=-2242 node=-2238 node=-2236 node=-2240 node=-2242 /geom>\n";//invalid line of buffer
  int result1 = StoreData(buffer1);
  int result2 = StoreData(buffer2);
  int result3 = StoreData(buffer3);
  int result4 = StoreData(buffer4);
  TEST_ASSERT_EQUAL_INT(result1,0);//valid line
  TEST_ASSERT_EQUAL_INT(result2,0);//valid line
  TEST_ASSERT_EQUAL_INT(result3,1);//invalid line
  TEST_ASSERT_EQUAL_INT(result4,1);//invalid line
}


//if 2 valid nodes are inputed into ShortestDistance then a path struct consisting of the distance and the nodes in the path is returned
//if either of the nodes are invalid then infinity is returned
void test_ShortestDistance(){
  struct node node1=SearchNode(-8847);//first node in data structure
  struct node node2=SearchNode(-8849);//second node in data structure
  struct node node3=SearchNode(52732247);//random node in data structure
  struct node node4 = SearchNode(-2143394791);//should return a struct which has ID 0 i.e. null
  struct node node5 = SearchNode(-1);//should return a node which has ID 0 i.e. null
  struct way path1 = ShortestDistance(node1,node2);//we know this is a link so the distance should be = to the link distance which is 11
  struct way path2 = ShortestDistance(node3,node1);//we dont know distance but as long as its less than infinity then we know path has been created
  struct way path3 = ShortestDistance(node2, node4);//comparison between null and real node returns infinity
  struct way path4 = ShortestDistance(node4, node5);//comparison between 2 invalid nodes returns 0 (as both ID are 0 they are considered the same node)
  TEST_ASSERT_LESS_THAN_INT32(12.00,path1.distance);//we know distance between these 2 is ~11
  TEST_ASSERT_LESS_THAN_INT32(infinity,path2.distance);//we dont know distance of this but as long as its less than infinity then a path has been created
  TEST_ASSERT_LESS_THAN_INT32(1,infinity-path3.distance);//difference infinity and distance of path distance is 0 then infinity distance is returned sucessfully
  TEST_ASSERT_LESS_THAN_INT32(1,path4.distance);//path distance is 0
}
void setUp() {
	 //this function is called before each test, it can be empty
}

void tearDown() {
	 //this function is called after each test, it can be empty
}


//tests all functions which can be automatically tested as written in test plan
int main() {
	UNITY_BEGIN();
  RUN_TEST(test_StoreData);
	RUN_TEST(test_SearchNode);
  RUN_TEST(test_ShortestDistance);
	return UNITY_END();
}
