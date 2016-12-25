#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "cocos2d.h"
#include "DefineAndEnum.h"
#include "Block.h"

class Light : public cocos2d::Node
{
public:
	CREATE_FUNC(Light);
	virtual bool init();
	virtual void update(float dt);
	bool _changeHappen;
	void setMap(BlockInfo **_map);
	bool *p_win;
private:
	int emitter_num;
	int trigger_num;
	int opened_door_num, opened_door_index;
	int receiver_num, recv_ok_num;
	cocos2d::Vec2 emitter_pos[MAX_EMITTER_NUMBER];
	cocos2d::Vec2 receiver_pos[MAX_RECEIVER_NUMBER];
	cocos2d::Vec2 trigger_pos[5];
	cocos2d::Vec2 opened_door_pos[5];

	void calcuLightPath(cocos2d::Vec2 startPoint, BlockDirec direc, cocos2d::Color3B color, float opacity);
	void drawLight(cocos2d::Vec2 point1, cocos2d::Vec2 point2, cocos2d::Color3B color, float opacity);
	BlockInfo **map;	

	void handleBlock(BlockDirec direc, BlockInfo &info, cocos2d::Vec2 startpoint, cocos2d::Color3B color, float opacity, int i, int j);
	void mirrorReflection(cocos2d::Vec2 point, BlockType glassType, BlockDirec lightDirec, BlockDirec blockDirec, cocos2d::Color3B color, float opacity);
	bool coloredGlass(BlockType glassType, cocos2d::Color3B &color);
	bool lightRegister(BlockDirec lightDirec, BlockDirec blockDirec, cocos2d::Color3B color, BlockState & state);
	bool lightReceiver(BlockType type, BlockDirec lightDirec, BlockDirec blockDirec, cocos2d::Color3B color, BlockState & state);
	bool doorTriggger(BlockDirec lightDirec, BlockDirec blockDirec, BlockState & state, int position_i, int position_j);
};
#endif