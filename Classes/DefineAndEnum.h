#ifndef __DEFINE_AND_ENUM_H__
#define __DEFINE_AND_ENUM_H__

#define MAP_LENGTH 18
#define MAP_HEIGHT 12
#define GRID_SIZE 50
#define MAX_EMITTER_NUMBER 10
#define MAX_RECEIVER_NUMBER 10

#include<string>

enum BlockDirec {
	down,
	left,
	up,
	right,
};

enum BlockType
{
	Nothing,//0
	Emitter,//1
	Receiver,//2
	OneFaceMirror,//3
	TwoFaceMirror,//4
	Triangle,//5
	FixedMirror,//6
	DoorTriger,//7
	Door,//8
	Register,//9
	Null10,//10

	YellowGlass,//11
	RedGlass,//12
	BlueGlass,//13

	Null14,//14
	Null15,//15
	Null16,//16
	Null17,//17
	Null18,//18
	Null19,//19
	Null20,//20

	YellowReceiver,//21
	RedReceiver,//22
	BlueReceiver,//23
	OrangeReceiver,//24
	PurpleReceiver,//25
	GreenReceiver,//26
};

enum BlockState {
	Nostate,

	Receiving,
	Received,

	White,
	Red,
	Yellow,
	Blue,
	Orange,
	Purple,
	Green,
};

struct BlockInfo
{
	BlockDirec direc;
	BlockType type;
	BlockState state;
};

bool isGlass(BlockType type);
bool isReceiver(BlockType type);
const std::string getFileNameByType(BlockType type, BlockState state);

#endif